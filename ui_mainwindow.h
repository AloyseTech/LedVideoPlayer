/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_animation;
    QAction *actionAbout;
    QAction *actionAbout_2;
    QWidget *centralWidget;
    QGroupBox *playerGroupBox;
    QPushButton *animControlButton;
    QPushButton *previousAnimButton;
    QPushButton *nextAnimButton;
    QComboBox *playlistComboBox;
    QRadioButton *soloAnimRadioButton;
    QRadioButton *autoAnimRadioButton;
    QRadioButton *fixedDurationRadioButton;
    QSlider *animDurationSlider;
    QLabel *infeedLoadingLabel;
    QPushButton *addAnimationToPlaylist;
    QLabel *bpmUnitLabel;
    QLineEdit *bpmLineEdit;
    QGroupBox *outputGroupBox;
    QCheckBox *gammaCheckBox;
    QPushButton *txControlButton;
    QLabel *outfeedLoadingLabel;
    QLineEdit *txFpsLineEdit;
    QLabel *txRateLabel;
    QLabel *txRateUnitLabel;
    QLCDNumber *feedbackFpsLCD;
    QLabel *txRateLabel_2;
    QSlider *brightnessSlider;
    QProgressBar *scanProgressBar;
    QListWidget *ipList;
    QPushButton *scanButton;
    QGroupBox *inputGroupBox;
    QComboBox *switchComboBox;
    QGroupBox *groupBox;
    QCheckBox *modulePrevCheckBox;
    QCheckBox *animPrevCheckBox;
    QLabel *label;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMaximumSize(QSize(600, 400));
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        actionAdd_animation = new QAction(MainWindow);
        actionAdd_animation->setObjectName(QStringLiteral("actionAdd_animation"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_2 = new QAction(MainWindow);
        actionAbout_2->setObjectName(QStringLiteral("actionAbout_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        playerGroupBox = new QGroupBox(centralWidget);
        playerGroupBox->setObjectName(QStringLiteral("playerGroupBox"));
        playerGroupBox->setGeometry(QRect(10, 60, 341, 151));
        playerGroupBox->setFocusPolicy(Qt::NoFocus);
        animControlButton = new QPushButton(playerGroupBox);
        animControlButton->setObjectName(QStringLiteral("animControlButton"));
        animControlButton->setGeometry(QRect(100, 60, 41, 32));
        animControlButton->setFocusPolicy(Qt::NoFocus);
        previousAnimButton = new QPushButton(playerGroupBox);
        previousAnimButton->setObjectName(QStringLiteral("previousAnimButton"));
        previousAnimButton->setGeometry(QRect(60, 60, 41, 32));
        previousAnimButton->setFocusPolicy(Qt::NoFocus);
        nextAnimButton = new QPushButton(playerGroupBox);
        nextAnimButton->setObjectName(QStringLiteral("nextAnimButton"));
        nextAnimButton->setGeometry(QRect(140, 60, 41, 32));
        nextAnimButton->setFocusPolicy(Qt::NoFocus);
        playlistComboBox = new QComboBox(playerGroupBox);
        playlistComboBox->setObjectName(QStringLiteral("playlistComboBox"));
        playlistComboBox->setGeometry(QRect(10, 25, 181, 31));
        playlistComboBox->setFocusPolicy(Qt::ClickFocus);
        playlistComboBox->setFrame(true);
        soloAnimRadioButton = new QRadioButton(playerGroupBox);
        soloAnimRadioButton->setObjectName(QStringLiteral("soloAnimRadioButton"));
        soloAnimRadioButton->setGeometry(QRect(200, 20, 102, 20));
        soloAnimRadioButton->setFocusPolicy(Qt::NoFocus);
        soloAnimRadioButton->setChecked(true);
        autoAnimRadioButton = new QRadioButton(playerGroupBox);
        autoAnimRadioButton->setObjectName(QStringLiteral("autoAnimRadioButton"));
        autoAnimRadioButton->setGeometry(QRect(200, 40, 102, 20));
        autoAnimRadioButton->setFocusPolicy(Qt::NoFocus);
        autoAnimRadioButton->setChecked(false);
        fixedDurationRadioButton = new QRadioButton(playerGroupBox);
        fixedDurationRadioButton->setObjectName(QStringLiteral("fixedDurationRadioButton"));
        fixedDurationRadioButton->setEnabled(true);
        fixedDurationRadioButton->setGeometry(QRect(200, 60, 121, 20));
        fixedDurationRadioButton->setFocusPolicy(Qt::NoFocus);
        fixedDurationRadioButton->setChecked(false);
        animDurationSlider = new QSlider(playerGroupBox);
        animDurationSlider->setObjectName(QStringLiteral("animDurationSlider"));
        animDurationSlider->setEnabled(false);
        animDurationSlider->setGeometry(QRect(200, 80, 131, 22));
        animDurationSlider->setFocusPolicy(Qt::NoFocus);
        animDurationSlider->setMinimum(1);
        animDurationSlider->setMaximum(60);
        animDurationSlider->setPageStep(5);
        animDurationSlider->setValue(30);
        animDurationSlider->setOrientation(Qt::Horizontal);
        infeedLoadingLabel = new QLabel(playerGroupBox);
        infeedLoadingLabel->setObjectName(QStringLiteral("infeedLoadingLabel"));
        infeedLoadingLabel->setGeometry(QRect(300, 130, 32, 16));
        infeedLoadingLabel->setFocusPolicy(Qt::NoFocus);
        addAnimationToPlaylist = new QPushButton(playerGroupBox);
        addAnimationToPlaylist->setObjectName(QStringLiteral("addAnimationToPlaylist"));
        addAnimationToPlaylist->setGeometry(QRect(10, 60, 41, 32));
        addAnimationToPlaylist->setFocusPolicy(Qt::NoFocus);
        bpmUnitLabel = new QLabel(playerGroupBox);
        bpmUnitLabel->setObjectName(QStringLiteral("bpmUnitLabel"));
        bpmUnitLabel->setGeometry(QRect(240, 120, 31, 21));
        bpmUnitLabel->setAlignment(Qt::AlignCenter);
        bpmLineEdit = new QLineEdit(playerGroupBox);
        bpmLineEdit->setObjectName(QStringLiteral("bpmLineEdit"));
        bpmLineEdit->setGeometry(QRect(200, 120, 41, 21));
        bpmLineEdit->setInputMethodHints(Qt::ImhDigitsOnly);
        bpmLineEdit->setMaxLength(3);
        bpmLineEdit->setAlignment(Qt::AlignCenter);
        bpmLineEdit->setClearButtonEnabled(false);
        outputGroupBox = new QGroupBox(centralWidget);
        outputGroupBox->setObjectName(QStringLiteral("outputGroupBox"));
        outputGroupBox->setGeometry(QRect(10, 220, 341, 101));
        outputGroupBox->setFocusPolicy(Qt::NoFocus);
        gammaCheckBox = new QCheckBox(outputGroupBox);
        gammaCheckBox->setObjectName(QStringLiteral("gammaCheckBox"));
        gammaCheckBox->setGeometry(QRect(10, 80, 91, 21));
        gammaCheckBox->setFocusPolicy(Qt::NoFocus);
        gammaCheckBox->setChecked(true);
        txControlButton = new QPushButton(outputGroupBox);
        txControlButton->setObjectName(QStringLiteral("txControlButton"));
        txControlButton->setGeometry(QRect(10, 30, 41, 32));
        txControlButton->setFocusPolicy(Qt::NoFocus);
        outfeedLoadingLabel = new QLabel(outputGroupBox);
        outfeedLoadingLabel->setObjectName(QStringLiteral("outfeedLoadingLabel"));
        outfeedLoadingLabel->setGeometry(QRect(300, 70, 32, 16));
        outfeedLoadingLabel->setFocusPolicy(Qt::NoFocus);
        txFpsLineEdit = new QLineEdit(outputGroupBox);
        txFpsLineEdit->setObjectName(QStringLiteral("txFpsLineEdit"));
        txFpsLineEdit->setGeometry(QRect(70, 60, 30, 21));
        txFpsLineEdit->setInputMethodHints(Qt::ImhDigitsOnly);
        txFpsLineEdit->setMaxLength(2);
        txFpsLineEdit->setAlignment(Qt::AlignCenter);
        txFpsLineEdit->setClearButtonEnabled(false);
        txRateLabel = new QLabel(outputGroupBox);
        txRateLabel->setObjectName(QStringLiteral("txRateLabel"));
        txRateLabel->setGeometry(QRect(10, 60, 61, 21));
        txRateUnitLabel = new QLabel(outputGroupBox);
        txRateUnitLabel->setObjectName(QStringLiteral("txRateUnitLabel"));
        txRateUnitLabel->setGeometry(QRect(100, 60, 31, 21));
        txRateUnitLabel->setAlignment(Qt::AlignCenter);
        feedbackFpsLCD = new QLCDNumber(outputGroupBox);
        feedbackFpsLCD->setObjectName(QStringLiteral("feedbackFpsLCD"));
        feedbackFpsLCD->setGeometry(QRect(190, 50, 91, 41));
        feedbackFpsLCD->setSmallDecimalPoint(false);
        feedbackFpsLCD->setDigitCount(4);
        feedbackFpsLCD->setProperty("intValue", QVariant(0));
        txRateLabel_2 = new QLabel(outputGroupBox);
        txRateLabel_2->setObjectName(QStringLiteral("txRateLabel_2"));
        txRateLabel_2->setGeometry(QRect(190, 30, 91, 21));
        txRateLabel_2->setAlignment(Qt::AlignCenter);
        brightnessSlider = new QSlider(outputGroupBox);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(60, 30, 121, 22));
        brightnessSlider->setMinimum(1);
        brightnessSlider->setMaximum(100);
        brightnessSlider->setSingleStep(1);
        brightnessSlider->setValue(100);
        brightnessSlider->setOrientation(Qt::Horizontal);
        brightnessSlider->setInvertedAppearance(false);
        brightnessSlider->setInvertedControls(false);
        scanProgressBar = new QProgressBar(centralWidget);
        scanProgressBar->setObjectName(QStringLiteral("scanProgressBar"));
        scanProgressBar->setGeometry(QRect(370, 250, 211, 23));
        scanProgressBar->setFocusPolicy(Qt::NoFocus);
        scanProgressBar->setMaximum(1000);
        scanProgressBar->setValue(0);
        ipList = new QListWidget(centralWidget);
        ipList->setObjectName(QStringLiteral("ipList"));
        ipList->setGeometry(QRect(360, 10, 231, 211));
        ipList->setFocusPolicy(Qt::NoFocus);
        ipList->setSortingEnabled(false);
        scanButton = new QPushButton(centralWidget);
        scanButton->setObjectName(QStringLiteral("scanButton"));
        scanButton->setGeometry(QRect(360, 220, 231, 32));
        scanButton->setFocusPolicy(Qt::NoFocus);
        scanButton->setAutoDefault(true);
        scanButton->setFlat(false);
        inputGroupBox = new QGroupBox(centralWidget);
        inputGroupBox->setObjectName(QStringLiteral("inputGroupBox"));
        inputGroupBox->setGeometry(QRect(10, 0, 341, 61));
        switchComboBox = new QComboBox(inputGroupBox);
        switchComboBox->setObjectName(QStringLiteral("switchComboBox"));
        switchComboBox->setGeometry(QRect(10, 30, 321, 26));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(370, 280, 221, 41));
        groupBox->setFocusPolicy(Qt::NoFocus);
        modulePrevCheckBox = new QCheckBox(groupBox);
        modulePrevCheckBox->setObjectName(QStringLiteral("modulePrevCheckBox"));
        modulePrevCheckBox->setGeometry(QRect(100, 20, 81, 20));
        modulePrevCheckBox->setFocusPolicy(Qt::NoFocus);
        animPrevCheckBox = new QCheckBox(groupBox);
        animPrevCheckBox->setObjectName(QStringLiteral("animPrevCheckBox"));
        animPrevCheckBox->setGeometry(QRect(10, 20, 87, 20));
        animPrevCheckBox->setFocusPolicy(Qt::NoFocus);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(10, 330, 581, 21));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        scanButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Subtronic Led Video Streaming", Q_NULLPTR));
        actionAdd_animation->setText(QApplication::translate("MainWindow", "Add animation...", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", Q_NULLPTR));
        actionAbout_2->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        playerGroupBox->setTitle(QApplication::translate("MainWindow", "Player", Q_NULLPTR));
        animControlButton->setText(QApplication::translate("MainWindow", ">", Q_NULLPTR));
        previousAnimButton->setText(QApplication::translate("MainWindow", "<<", Q_NULLPTR));
        nextAnimButton->setText(QApplication::translate("MainWindow", ">>", Q_NULLPTR));
        soloAnimRadioButton->setText(QApplication::translate("MainWindow", "Solo", Q_NULLPTR));
        autoAnimRadioButton->setText(QApplication::translate("MainWindow", "Automatic", Q_NULLPTR));
        fixedDurationRadioButton->setText(QApplication::translate("MainWindow", "Fixed duration", Q_NULLPTR));
        infeedLoadingLabel->setText(QApplication::translate("MainWindow", "LOADING", Q_NULLPTR));
        addAnimationToPlaylist->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        bpmUnitLabel->setText(QApplication::translate("MainWindow", "BPM", Q_NULLPTR));
        bpmLineEdit->setText(QApplication::translate("MainWindow", "120", Q_NULLPTR));
        outputGroupBox->setTitle(QApplication::translate("MainWindow", "Output feed", Q_NULLPTR));
        gammaCheckBox->setText(QApplication::translate("MainWindow", "True color", Q_NULLPTR));
        txControlButton->setText(QApplication::translate("MainWindow", ">", Q_NULLPTR));
        outfeedLoadingLabel->setText(QApplication::translate("MainWindow", "LOADING", Q_NULLPTR));
        txFpsLineEdit->setText(QApplication::translate("MainWindow", "40", Q_NULLPTR));
        txRateLabel->setText(QApplication::translate("MainWindow", "TX rate :", Q_NULLPTR));
        txRateUnitLabel->setText(QApplication::translate("MainWindow", "FPS", Q_NULLPTR));
        txRateLabel_2->setText(QApplication::translate("MainWindow", "Feedback FPS", Q_NULLPTR));
        scanButton->setText(QApplication::translate("MainWindow", "Scan for devices", Q_NULLPTR));
        inputGroupBox->setTitle(QApplication::translate("MainWindow", "Input", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Preview", Q_NULLPTR));
        modulePrevCheckBox->setText(QApplication::translate("MainWindow", "Modules", Q_NULLPTR));
        animPrevCheckBox->setText(QApplication::translate("MainWindow", "Animation", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Keys : \342\207\204 Player Switch \342\207\205 Bright [SPACE] Strob [W] White [B] Black [Q] Red [S] Green [D] Blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
