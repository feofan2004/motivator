<<<<<<< HEAD
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    window = new QWidget;

    prevIcon = new QIcon(":/icons/prev.png");
    prevButton  = new QPushButton(window);
    prevButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    prevButton->setIcon(*prevIcon);

    pauseIcon = new QIcon(":/icons/pause.png");
    pauseButton = new QPushButton(window);
    pauseButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    pauseButton->setIcon(*pauseIcon);

    playIcon = new QIcon(":/icons/play.png");
    playButton  = new QPushButton(window);
    playButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    playButton->setIcon(*playIcon);

    nextIcon = new QIcon(":/icons/next.png");
    nextButton  = new QPushButton(window);
    nextButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    nextButton->setIcon(*nextIcon);


    mainLayout = new QVBoxLayout;

    imageLayout = new QHBoxLayout;
    QImage pic;
    pic.load(":/images/1.jpg");
    labelForPic = new QLabel(window);
    labelForPic->setPixmap(QPixmap::fromImage(pic));
    labelForPic->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(labelForPic);
    labelForPic->show();

    control = new QVBoxLayout;

    lengthLayout = new QHBoxLayout;
    length = new QSlider(Qt::Horizontal, window);
    lengthLayout->addWidget(length);

    buttonsLineLayout = new QHBoxLayout;
    buttonsLineLayout->addWidget(prevButton);
    buttonsLineLayout->addWidget(pauseButton);
    buttonsLineLayout->addWidget(playButton);
    buttonsLineLayout->addWidget(nextButton);
    buttonsLineLayout->setAlignment(Qt::AlignCenter);

    control->addLayout(buttonsLineLayout);
    control->addLayout(lengthLayout);
    control->setAlignment(Qt::AlignBottom);

    mainLayout->addLayout(imageLayout);
    mainLayout->addLayout(control);

    window->setStyleSheet("background-color:lightblue;");
    window->setLayout(mainLayout);
    window->show();

    player = new Player(this);

    connect(prevButton,   SIGNAL(clicked()), this, SLOT(prevButtonPushed()));
    connect(pauseButton,  SIGNAL(clicked()), this, SLOT(pauseButtonPushed()));
    connect(playButton,   SIGNAL(clicked()), this, SLOT(playButtonPushed()));
    connect(nextButton,   SIGNAL(clicked()), this, SLOT(nextButtonPushed()));
}

void MainWindow::prevButtonPushed()
{
    player->playerPrev();
}

void MainWindow::pauseButtonPushed()
{
    player->playerPause();
}

void MainWindow::playButtonPushed()
{
    player->playerStart();
}

void MainWindow::nextButtonPushed()
{
    player->playerNext();
}

void MainWindow::updateSlider()
{
    length->setValue(length->value()+1);
}

MainWindow::~MainWindow()
{

}
=======
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    window = new QWidget;

    prevIcon = new QIcon(":/icons/prev.png");
    prevButton  = new QPushButton(window);
    prevButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    prevButton->setIcon(*prevIcon);

    pauseIcon = new QIcon(":/icons/pause.png");
    pauseButton = new QPushButton(window);
    pauseButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    pauseButton->setIcon(*pauseIcon);

    playIcon = new QIcon(":/icons/play.png");
    playButton  = new QPushButton(window);
    playButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    playButton->setIcon(*playIcon);

    nextIcon = new QIcon(":/icons/next.png");
    nextButton  = new QPushButton(window);
    nextButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    nextButton->setIcon(*nextIcon);


    mainLayout = new QVBoxLayout;

    imageLayout = new QHBoxLayout;
    QImage pic;
    pic.load(":/images/1.jpg");
    labelForPic = new QLabel(window);
    labelForPic->setPixmap(QPixmap::fromImage(pic));
    labelForPic->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(labelForPic);
    labelForPic->show();

    control = new QVBoxLayout;

    lengthLayout = new QHBoxLayout;
    length = new QSlider(Qt::Horizontal, window);
    lengthLayout->addWidget(length);

    buttonsLineLayout = new QHBoxLayout;
    buttonsLineLayout->addWidget(prevButton);
    buttonsLineLayout->addWidget(pauseButton);
    buttonsLineLayout->addWidget(playButton);
    buttonsLineLayout->addWidget(nextButton);
    buttonsLineLayout->setAlignment(Qt::AlignCenter);

    control->addLayout(buttonsLineLayout);
    control->addLayout(lengthLayout);
    control->setAlignment(Qt::AlignBottom);

    mainLayout->addLayout(imageLayout);
    mainLayout->addLayout(control);

    window->setStyleSheet("background-color:lightblue;");
    window->setLayout(mainLayout);
    window->show();

    player = new Player(this);

    connect(prevButton,   SIGNAL(clicked()), this, SLOT(prevButtonPushed()));
    connect(pauseButton,  SIGNAL(clicked()), this, SLOT(pauseButtonPushed()));
    connect(playButton,   SIGNAL(clicked()), this, SLOT(playButtonPushed()));
    connect(nextButton,   SIGNAL(clicked()), this, SLOT(nextButtonPushed()));
}

void MainWindow::prevButtonPushed()
{
    player->playerPrev();
}

void MainWindow::pauseButtonPushed()
{
    player->playerPause();
}

void MainWindow::playButtonPushed()
{
    player->playerStart();
}

void MainWindow::nextButtonPushed()
{
    player->playerNext();
}

void MainWindow::updateSlider()
{
    length->setValue(length->value()+1);
}

MainWindow::~MainWindow()
{

}
>>>>>>> 1cc405a32d2e037764fbcd83d36353b2e055d184
