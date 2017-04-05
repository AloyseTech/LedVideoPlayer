#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMediaPlayer"
#include "QMediaPlaylist"
#include "surface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void update();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void generatePlaylist();
    void sendDataToModule();


private slots:
    void on_animControlButton_clicked();
    void sendDataToModuleSlot();
    void processPendingDatagrams();
    void on_txControlButton_clicked();
    void on_scanButton_clicked();
    void scanTimeout();
    void on_animPrevCheckBox_stateChanged(int arg1);
    void on_modulePrevCheckBox_stateChanged(int arg1);
    void on_playlistComboBox_currentIndexChanged(int index);
    void on_animDurationSlider_sliderMoved(int position);
    void on_autoAnimRadioButton_clicked(bool checked);
    void on_soloAnimRadioButton_clicked(bool checked);
    void updatePlaylistComboIndex(int index);
    void on_nextAnimButton_clicked();
    void on_previousAnimButton_clicked();
    void playlistTimeout();
    void on_fixedDurationRadioButton_toggled(bool checked);
    void on_animDurationSlider_valueChanged(int value);
    void oneSecUpdate();

private:
    Ui::MainWindow *ui;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    MyVideoSurface *surface;

    QTimer *timer, *scanTimer, *playlistTimer, *oneSecUpdateTimer;

    QElapsedTimer *ledTimer;

    QElapsedTimer *elapsedTime;

    QUdpSocket *udpSocket;

};

#endif // MAINWINDOW_H
