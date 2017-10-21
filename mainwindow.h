
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QSlider>
#include <QtDebug>


class MainWindow : public QMainWindow
{

    Q_OBJECT
private:
    QWidget     *window;

    QVBoxLayout    *mainLayout;
     QVBoxLayout    *control;
      QHBoxLayout    *lengthLayout;
       QSlider        *length;
      QHBoxLayout    *buttonsLineLayout;
       QIcon          *prevIcon;
       QPushButton    *prevButton;
       QIcon          *pauseIcon;
       QPushButton    *pauseButton;
       QIcon          *playIcon;
       QPushButton    *playButton;
       QIcon          *nextIcon;
       QPushButton    *nextButton;

    QHBoxLayout    *imageLayout;
     QLabel        *labelForPic;

     Player *player;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void prevButtonPushed();
    void pauseButtonPushed();
    void playButtonPushed();
    void nextButtonPushed();

    void updateSlider();

};

#endif // MAINWINDOW_H

