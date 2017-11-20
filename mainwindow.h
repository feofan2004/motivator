#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QSlider>
#include <QLabel>
#include <QWidget>
#include <QtDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QEvent>
#include <QQueue>
#include <QStandardPaths>
#include "mywidget.h"
#include "player.h"
#include "mylabel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MyWidget            *uiWindow;
    QImage              *pic;
    QQueue<QString>     *allPics;
    int                 currentPicIndex;
    QImage              *background;
    QLabel              *backgroundLabel;

    QTimer *animationTimer;
    QTimer *slideShowTimer;

QVBoxLayout    *mainLayout;
  QVBoxLayout    *controls;
    QHBoxLayout    *buttonsAndVolumeLayout;
      QHBoxLayout    *volumeLayout;
         QSlider        *volume;
      QHBoxLayout    *buttonsLayout;
        QPushButton    *prevButton;
        QPushButton    *stopButton;
        QPushButton    *pauseButton;
        QPushButton    *playButton;
        QPushButton    *nextButton;
    QHBoxLayout    *lengthLayout;
      QSlider        *length;
      QLabel         *currentSongDuration;
      MyLabel        *currentSongTimeLeft;
      MyLabel        *currentSongTimeHadPassed;

    QHBoxLayout    *imageLayout;
     QLabel        *labelForPic;
     Player        *player;

     QVBoxLayout    *filesLayout;
     QHBoxLayout    *fileButtonsLayout;
     QPushButton    *openMusicButton;
     QPushButton    *openPicButton;
     QPushButton    *openPlaylistsButton;
     QPushButton    *addPlaylistButton;
     QSlider        *picChangeSpeedSlider;

     bool flag;
     bool flag2;
     bool flag3;

    void controlsAnimation(bool mouseOnWindow);
    void animation(int a);
    void animationTimerStart();
    void animationTimerStop();
    void setMyStyle();
    QImage blur(const QImage &image, const QRect &rect, int radius);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
     void switchCurrentSongTimeMode();
     void changeBackground();
     void openPic();
     void nextPic();
     void pauseSlideShow();
     void startSlideShow();

};

#endif // MAINWINDOW_H
