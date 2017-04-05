#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMediaPlayer"
#include "QVideoFrame"
#include "surface.h"
#include "qmediaplaylist.h"
#include "ledbar.h"
#include "QToolTip"
#include "QMovie"
#include "QKeyEvent"
#include <QtConcurrent/QtConcurrent>

#define NUM_LED_MODULES 16
#define DATAGRAM_PREFIX_SIZE 1


LedBar ledModules[NUM_LED_MODULES];
int activeModules = 0;

const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowModality(Qt::WindowModal);

    elapsedTime = new QElapsedTimer();
    elapsedTime->start();

    ui->setupUi(this);

    playlist = new QMediaPlaylist();
    player = new QMediaPlayer();

    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(updatePlaylistComboIndex(int)));

    generatePlaylist();

    surface=new MyVideoSurface(ledModules, NUM_LED_MODULES);

    player->setVideoOutput(surface);
    player->setPlaybackRate(1);
    //player->play();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendDataToModuleSlot()));

    scanTimer = new QTimer(this);
    connect(scanTimer, SIGNAL(timeout()),this,SLOT(scanTimeout()));

    playlistTimer = new QTimer(this);
    connect(playlistTimer, SIGNAL(timeout()),this,SLOT(playlistTimeout()));

    oneSecUpdateTimer=new QTimer(this);
    oneSecUpdateTimer->setInterval(1000);
    connect(oneSecUpdateTimer, SIGNAL(timeout()),this,SLOT(oneSecUpdate()));
    oneSecUpdateTimer->start();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(7777,QAbstractSocket::DefaultForPlatform);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    ui->scanProgressBar->setVisible(false);
    ui->animControlButton->setToolTip(tr("Control animation feeding"));

    ui->menuBar->show();


    QMovie *infeedLblMovie = new QMovie("/Users/TheoMeyer/Downloads/infeed-loading_R.gif");
    QMovie *outfeedLblMovie = new QMovie("/Users/TheoMeyer/Downloads/outfeed-loading_R.gif");

    ui->infeedLoadingLabel->setMovie(infeedLblMovie);
    ui->infeedLoadingLabel->close();
    infeedLblMovie->start();

    ui->outfeedLoadingLabel->setMovie(outfeedLblMovie);
    ui->outfeedLoadingLabel->close();
    outfeedLblMovie->start();

    ui->playlistComboBox->setFocus();

    ui->txFpsLineEdit->setValidator(new QIntValidator(0, 100, this));

    ui->feedbackFpsLCD->display("0.0");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    //ui->gfxLabel->setPixmap(QPixmap::fromImage(buffer).scaled(ui->gfxLabel->width(),ui->gfxLabel->height(), Qt::KeepAspectRatio));
}

void MainWindow::on_animControlButton_clicked()
{
    if(player->state() == QMediaPlayer::PausedState || player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        qDebug()<<"play!";
        ui->animControlButton->setText("||");
        ui->infeedLoadingLabel->show();

    }
    else
    {
        player->stop();
        qDebug()<<"stop!";
        ui->animControlButton->setText(">");
        ui->infeedLoadingLabel->close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    player->stop();
    surface->onQuit();
}

void MainWindow::sendDataToModuleSlot()
{
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::sendDataToModule);
}

void MainWindow::sendDataToModule()
{
    QByteArray datagram;
    datagram.resize(LED_PER_MODULE*3+DATAGRAM_PREFIX_SIZE);

    datagram[0]=0xDA; //DAta command

    for(int modIndex =0; modIndex<NUM_LED_MODULES; modIndex++)
    {
        //memcpy(datagram.data_ptr(),ledModules[modIndex].pixelBuffer,LED_PER_MODULE*3);
        for(int ledIndex = 0; ledIndex<LED_PER_MODULE; ledIndex++)
        {
            datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex]=ledModules[modIndex].pixelBuffer[3*ledIndex];
            datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+1]=ledModules[modIndex].pixelBuffer[3*ledIndex+1];
            datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+2]=ledModules[modIndex].pixelBuffer[3*ledIndex+2];
        }

        if(ui->gammaCheckBox->checkState())
        {
            for(int ledIndex = 0; ledIndex<LED_PER_MODULE; ledIndex++)
            {
                datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex]=gamma8[datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex]];
                datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+1]=gamma8[datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+1]];
                datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+2]=gamma8[datagram[DATAGRAM_PREFIX_SIZE+3*ledIndex+2]];
            }
        }

        //SEND UDP PACKET HERE
        udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress(ledModules[modIndex].IP), 8888);

    }
}

void MainWindow::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress senderIP;
        uint16_t senderPORT;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(),&senderIP,&senderPORT);

        //Module IP identification
        if(datagram.size()==6 && (uint8_t)datagram[0]==0xDE)
        {
            uint32_t ip4address = (datagram[1]<<24&0xFF000000)
                    | (datagram[2]<<16&0x00FF0000)
                    | (datagram[3]<<8&0x0000FF00)
                    | (datagram[4]&0x000000FF);

            ledModules[activeModules].IP=QHostAddress(ip4address);
            ledModules[activeModules].ID=datagram[5];

            qDebug()<<ledModules[activeModules].IP;
            qDebug()<<ledModules[activeModules].ID;

            if(ledModules[activeModules].ID > 0)
            {
                for(int k=0; k<activeModules-1;k++)
                {
                    if(ledModules[k].ID==ledModules[activeModules].ID)
                    {
                        //ID already exists on the network...
                        qDebug()<<"The ID "<<QString::number(datagram[5])<<" already exists on the network...";
                        return;
                    }
                }
                ui->ipList->addItem("ID:" + QString::number(ledModules[activeModules].ID) + " - IP:" + QString(QHostAddress(ip4address).toString()));
                ledModules[activeModules].valid=true;
                activeModules++;
            }
        }
        else if((uint8_t)datagram[0]==0xF)
        {
            for(int k=0; k<activeModules;k++)
            {
                if(ledModules[k].ID==(uint8_t)datagram[2])
                {
                    ledModules[k].fps=datagram[1];
                    qDebug()<<"Module " << ledModules[k].ID << " - FPS : " << ledModules[k].fps;
                }
            }
        }
    }
}

void MainWindow::on_txControlButton_clicked()
{
    if(timer->isActive())
    {
        ui->txControlButton->setText(">");
        timer->stop();
        ui->statusBar->showMessage("Wireless transmission stopped !",3000);
        ui->outfeedLoadingLabel->close();
    }
    else
    {
        ui->txControlButton->setText("||");
        if(ui->txFpsLineEdit->text().toInt()>0 && ui->txFpsLineEdit->text().toInt()<100)
            timer->start(1000.0/ui->txFpsLineEdit->text().toInt());
        else
        {
            timer->start(1000.0/20.0);
            ui->txFpsLineEdit->setText(tr("20"));
        }

        ui->statusBar->showMessage("Wireless transmission started !",3000);
        ui->outfeedLoadingLabel->show();
    }
}



void MainWindow::on_scanButton_clicked()
{
    ui->statusBar->showMessage("Start scanning the network for LED devices...",3000);
    ui->scanButton->setText("Scanning...");
    ui->scanButton->setDisabled(1);
    ui->txControlButton->setDisabled(1);
    ui->animControlButton->setDisabled(1);

    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->stop();
        ui->animControlButton->setText(">");
        ui->infeedLoadingLabel->close();
    }
    if(timer->isActive())
    {
        ui->txControlButton->setText(">");
        timer->stop();
        ui->outfeedLoadingLabel->close();
    }

    ui->outputGroupBox->setEnabled(0);
    ui->inputGroupBox->setEnabled(0);


    ui->ipList->clear();
    activeModules=0;
    for(int i =0; i<NUM_LED_MODULES;i++)
    {
        ledModules[i].ID=0;
        ledModules[i].valid=false;
    }


    QByteArray datagram;
    datagram.resize(1);
    datagram[0]=0xDE;
    udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, 8888);

    scanTimer->start(100);
    ui->scanProgressBar->setValue(0);
    ui->scanProgressBar->setVisible(true);

}

void MainWindow::scanTimeout()
{
    ui->scanProgressBar->setValue(ui->scanProgressBar->value()+10);

    if(ui->scanProgressBar->value()>=ui->scanProgressBar->maximum())
    {
        scanTimer->stop();

        ui->outputGroupBox->setEnabled(1);
        ui->inputGroupBox->setEnabled(1);

        ui->scanButton->setText("Scan for devices");
        ui->scanButton->setDisabled(0);
        ui->txControlButton->setDisabled(0);
        ui->animControlButton->setDisabled(0);

        ui->scanProgressBar->setVisible(false);
        ui->statusBar->showMessage(QString("Found ") + QString::number(activeModules) + QString(" devices!"),3000);
    }
}

void MainWindow::on_animPrevCheckBox_stateChanged(int arg1)
{
    surface->setShowFullPrev(arg1);
}

void MainWindow::on_modulePrevCheckBox_stateChanged(int arg1)
{
    surface->setShowModulesPrev(arg1);
}

void MainWindow::on_playlistComboBox_currentIndexChanged(int index)
{
    playlist->setCurrentIndex(index);
}

void MainWindow::on_animDurationSlider_sliderMoved(int position)
{
    QToolTip::showText(ui->animDurationSlider->mapToGlobal(QPoint(0,0)),
                       QString::number(ui->animDurationSlider->value()) + " seconds" );
}

void MainWindow::on_autoAnimRadioButton_clicked(bool checked)
{
    if(checked)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    }
}

void MainWindow::on_soloAnimRadioButton_clicked(bool checked)
{
    if(checked)
    {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
}

void MainWindow::updatePlaylistComboIndex(int index)
{
    ui->playlistComboBox->setCurrentIndex(index);
}


void MainWindow::on_nextAnimButton_clicked()
{
    QMediaPlaylist::PlaybackMode mode = playlist->playbackMode();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->next();
    playlist->setPlaybackMode(mode);
}

void MainWindow::on_previousAnimButton_clicked()
{
    QMediaPlaylist::PlaybackMode mode = playlist->playbackMode();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->previous();
    playlist->setPlaybackMode(mode);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        qDebug()<<"Left";
    }
    else if (event->key() == Qt::Key_Right)
    {
        qDebug()<<"Right";
    }
    else if (event->key() == Qt::Key_Up)
    {
        if(!scanTimer->isActive())
            on_previousAnimButton_clicked();
    }
    else if (event->key() == Qt::Key_Down)
    {
        if(!scanTimer->isActive())
            on_nextAnimButton_clicked();
    }
    else if (event->key() == Qt::Key_I)
    {
        if(!scanTimer->isActive())
            on_animControlButton_clicked();
    }
    else if (event->key() == Qt::Key_O)
    {
        if(!scanTimer->isActive())
            on_txControlButton_clicked();
    }
    else if (event->key() == Qt::Key_P)
    {
        if(!scanTimer->isActive())
            on_scanButton_clicked();
    }
    else if (event->key() == Qt::Key_Space)
    {
        if(!event->isAutoRepeat())
        {
            if(surface->getStrobePeriod()==0)
                surface->setStrobePeriod(200);

            qDebug()<<"Enable strobe";
        }
    }
    else if (event->key() == Qt::Key_W)
    {
        surface->setRed(255);
        surface->setGreen(255);
        surface->setBlue(255);
    }
    else if (event->key() == Qt::Key_Q)
    {
        surface->setRed(255);
        surface->setGreen(1);
        surface->setBlue(1);
    }
    else if (event->key() == Qt::Key_S)
    {
        surface->setRed(1);
        surface->setGreen(255);
        surface->setBlue(1);
    }
    else if (event->key() == Qt::Key_D)
    {
        surface->setRed(1);
        surface->setGreen(1);
        surface->setBlue(255);
    }
    else if (event->key() == Qt::Key_X)
    {
        surface->setRed(255);
        surface->setGreen(255);
        surface->setBlue(1);
    }
    else if (event->key() == Qt::Key_C)
    {
        surface->setRed(1);
        surface->setGreen(255);
        surface->setBlue(255);
    }
    else if (event->key() == Qt::Key_V)
    {
        surface->setRed(255);
        surface->setGreen(1);
        surface->setBlue(255);
    }
    else if (event->key() == Qt::Key_B)
    {
        surface->setRed(1);
        surface->setGreen(1);
        surface->setBlue(1);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int k = event->key();
    if (k == Qt::Key_Space)
    {
        if(surface->getStrobePeriod()>0)
            surface->setStrobePeriod(0);
    }
    else if (k == Qt::Key_W || k == Qt::Key_Q || k== Qt::Key_S || Qt::Key_D || Qt::Key_X || Qt::Key_C || Qt::Key_V || Qt::Key_B)
    {
        surface->setRed(0);
        surface->setGreen(0);
        surface->setBlue(0);
    }
}

void MainWindow::playlistTimeout()
{
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    on_nextAnimButton_clicked();
}

void MainWindow::on_fixedDurationRadioButton_toggled(bool checked)
{
    if(checked)
    {
        playlistTimer->setInterval(30000);
        playlistTimer->start();
        ui->animDurationSlider->setEnabled(1);
    }
    else
    {
        playlistTimer->stop();
        ui->animDurationSlider->setEnabled(1);
    }
}

void MainWindow::on_animDurationSlider_valueChanged(int value)
{
    playlistTimer->setInterval(value*1000);
}

void MainWindow::generatePlaylist()
{
    ui->playlistComboBox->clear();
    playlist->clear();

    QString playlistLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/SubtroLedPlaylist/";
    if(QDir(playlistLocation).exists())
    {
        qDebug()<<"Playlist folder exists";
    }
    else
    {
        qDebug()<<"No plalist folder";
        if(QDir().mkdir(playlistLocation))
            qDebug()<<"Playlist folder created";

    }

    QDirIterator it(playlistLocation, QStringList() << "*.mp4", QDir::Files, QDirIterator::Subdirectories);
    if(!it.hasNext())
        qDebug()<<"Playlist directory is empty";

    while (it.hasNext())
        playlist->addMedia(QUrl::fromLocalFile(it.next()));

    QStringList playlistString;
    for(int i = 0; i<playlist->mediaCount(); i++)
        playlistString.append(playlist->media(i).canonicalUrl().fileName());
    //playlistString.sort();
    ui->playlistComboBox->addItems(playlistString);

    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player->setPlaylist(playlist);
}

void MainWindow::oneSecUpdate()
{
    float avgFps=0.0;
    for(int i=0; i<activeModules;i++)
        avgFps+=ledModules[i].fps;
    avgFps/=activeModules;
    if(avgFps<1.0)
        avgFps=0;
    ui->feedbackFpsLCD->display(avgFps);
}