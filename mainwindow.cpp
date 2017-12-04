#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    flag  = true;
    flag2 = false;
    flag3 = true;
    animationTimer = new QTimer;
    slideShowTimer = new QTimer;
    background = new QImage(":/images/default.jpg");

    allPics = new QQueue<QString>;
    currentPicIndex = 0;
    mainLayout = new QVBoxLayout;
    uiWindow = new MyWidget;
    uiWindow->setMinimumSize(350,450);
    backgroundLabel = new QLabel(uiWindow);
    backgroundLabel->setPixmap(QPixmap::fromImage(QImage(":/images/default.jpg")).scaled(350,450,Qt::IgnoreAspectRatio, Qt::FastTransformation));
    backgroundLabel->show();
    prevButton    = new QPushButton(uiWindow);
    stopButton    = new QPushButton(uiWindow);
    pauseButton   = new QPushButton(uiWindow);
    playButton    = new QPushButton(uiWindow);
    nextButton    = new QPushButton(uiWindow);
    openPicButton = new QPushButton(uiWindow);
    openPlaylistsButton = new QPushButton(uiWindow);
    length = new QSlider(Qt::Horizontal, uiWindow);
    currentSongDuration = new QLabel(uiWindow);
    currentSongTimeLeft = new MyLabel(uiWindow);
    currentSongTimeHadPassed = new MyLabel(uiWindow);
    volume = new QSlider(Qt::Horizontal, uiWindow);
    picChangeSpeedSlider = new QSlider(Qt::Horizontal, uiWindow);

    setMyStyle(); //icons, styleSheets etc.
/*Layouts--------------------------------------------------------------------*/
    controls = new QVBoxLayout;

    lengthLayout = new QHBoxLayout;
    currentSongTimeHadPassed->show();
    currentSongDuration->show();
    currentSongTimeLeft->hide();
    lengthLayout->addWidget(currentSongTimeLeft);
    lengthLayout->addWidget(currentSongTimeHadPassed);
    lengthLayout->addWidget(length);
    lengthLayout->addWidget(currentSongDuration);

    volumeLayout = new QHBoxLayout;
    volumeLayout->addWidget(volume);
    volumeLayout->setAlignment(Qt::AlignRight);

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(prevButton);
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addWidget(pauseButton);
    buttonsLayout->addWidget(playButton);
    buttonsLayout->addWidget(nextButton);

    buttonsAndVolumeLayout = new QHBoxLayout;
    buttonsAndVolumeLayout->addLayout(buttonsLayout);
    buttonsAndVolumeLayout->addLayout(volumeLayout);
    buttonsAndVolumeLayout->setAlignment(Qt::AlignCenter);

    controls->addLayout(buttonsAndVolumeLayout);
    controls->addLayout(lengthLayout);
    controls->setAlignment(Qt::AlignBottom);

    filesLayout = new QVBoxLayout;
    fileButtonsLayout = new QHBoxLayout;
    fileButtonsLayout->addWidget(openPicButton);
    fileButtonsLayout->addWidget(openPlaylistsButton);
    filesLayout->addLayout(fileButtonsLayout);
    filesLayout->addWidget(picChangeSpeedSlider);
    fileButtonsLayout->setAlignment(Qt::AlignRight);

    imageLayout = new QHBoxLayout;
    labelForPic = new QLabel(uiWindow);
    pic = new QImage;
    labelForPic->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(labelForPic);
    mainLayout->addLayout(filesLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(imageLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(controls);
    uiWindow->setLayout(mainLayout);
/*---------------------------------------------------------------------------*/
    uiWindow->setMouseTracking(true);
    this->setCentralWidget(uiWindow);
    this->show();
    player = new Player(this);
    animation(1);//hide controls
    animationTimerStart();
    connect(uiWindow, &MyWidget::isMouseOnWindow, this, &MainWindow::controlsAnimation);
    connect(prevButton, &QPushButton::clicked, player->playlist, &QMediaPlaylist::previous);
    connect(stopButton, &QPushButton::clicked, player->control,  &QMediaPlayer::stop);
    connect(pauseButton,&QPushButton::clicked, player->control,  &QMediaPlayer::pause);
    connect(playButton, &QPushButton::clicked, player->control,  &QMediaPlayer::play);
    connect(nextButton, &QPushButton::clicked, player->playlist, &QMediaPlaylist::next);
    connect(openPlaylistsButton, &QPushButton::clicked, player, &Player::openPlaylistsWidget);
    connect(currentSongTimeHadPassed, &MyLabel::clicked, this, &MainWindow::switchCurrentSongTimeMode);
    connect(currentSongTimeLeft, &MyLabel::clicked, this, &MainWindow::switchCurrentSongTimeMode);
    connect(nextButton, &QPushButton::clicked, player, &Player::nextSongInPlaylistManager);
    connect(prevButton, &QPushButton::clicked, player, &Player::prevSongInPlaylistManager);

    connect(openPicButton, &QPushButton::clicked, this, &MainWindow::openPic);

    connect(picChangeSpeedSlider, &QSlider::valueChanged, slideShowTimer, &QTimer::setInterval);
    connect(pauseButton,&QPushButton::clicked, this, &MainWindow::pauseSlideShow);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::startSlideShow);
    connect(slideShowTimer, &QTimer::timeout, this, &MainWindow::nextPic);
    QDir ff(":/images/images");
        QStringList nameFilter;

        nameFilter << "*.jpg";
        QFileInfoList lt = ff.entryInfoList( nameFilter, QDir::Files );

        QFileInfo fo;
        foreach (fo, lt)
        {
            qDebug()<<"!";
            allPics->push_back(fo.absoluteFilePath());
        }
}

void MainWindow::openPic()
{
    QStringList filename = QFileDialog::getOpenFileNames(this,"Browse","C://","Image Files (*.png *.jpg *.bmp)");
    if(filename.size()>0)
    {
    foreach(QString i, filename)
    {
        allPics->push_back(i);
    }
    if(allPics->first() == NULL)
    {
        qDebug()<<"huy";
        return ;
    }
    nextPic();
    }
}

void MainWindow::nextPic()
{   if(allPics->size()>0)
    {
    pic->load(allPics->at(currentPicIndex));
    *background = blur(*pic,pic->rect(),90);
    changeBackground();
    labelForPic->setPixmap(QPixmap::fromImage(pic->scaled(this->height()*0.85,this->width()*0.90, Qt::KeepAspectRatio)));
    currentPicIndex++;
    qDebug()<<allPics->size();
    if(currentPicIndex >= allPics->size())
    {
        currentPicIndex = 0;
    }
    }
}

void MainWindow::startSlideShow()
{
    slideShowTimer->start();
}

void MainWindow::pauseSlideShow()
{
    slideShowTimer->stop();
}

void MainWindow::setMyStyle()
{
    this->setWindowTitle("QtPlayer");
    this->setWindowIcon(QIcon(":/icons/MainWindow.png"));
    prevButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    prevButton->setIcon(QIcon(":/icons/prev.png"));
    stopButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    stopButton->setIcon(QIcon(":/icons/stop.png"));
    pauseButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    pauseButton->setIcon(QIcon(":/icons/pause.png"));
    playButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    playButton->setIcon(QIcon(":/icons/play.png"));
    nextButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    nextButton->setIcon(QIcon(":/icons/next.png"));
    openPicButton->setIcon(QIcon(":/icons/openPic.png"));
    openPicButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    openPicButton->setText("Open Images");
    openPlaylistsButton->setIcon(QIcon(":/icons/openPlaylists.png"));
    openPlaylistsButton->setText("Open Playlist's Manager");
    openPlaylistsButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    currentSongTimeHadPassed->setText("00:00:00");
    currentSongDuration->setText(" 00:00:00");
    currentSongTimeLeft->setText("-00:00:00");
    length->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    length->setStyleSheet("QSlider::handle:horizontal {\
                          background: white;\
                          width: 15px;\
                          height: 1px;\
                          border-radius: 5px;\
                          }\
                          ");
    volume->setValue(100);
    volume->setMaximumWidth(150);
    volume->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    volume->setStyleSheet("QSlider::handle:horizontal {\
                          background: white;\
                          width: 15px;\
                          height: 1px;\
                          border-radius: 5px;\
                          }");
    picChangeSpeedSlider->setMinimum(2000);
    picChangeSpeedSlider->setMaximum(7000);
    picChangeSpeedSlider->setValue(2000);
    picChangeSpeedSlider->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    picChangeSpeedSlider->setStyleSheet("QSlider::handle:horizontal {\
                          background: white;\
                          width: 15px;\
                          height: 1px;\
                          border-radius: 5px;\
                          }");
    currentSongDuration->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    currentSongTimeHadPassed->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    currentSongTimeLeft->setStyleSheet("background-color: rgba(255, 255, 255, 0);");


}

void MainWindow::switchCurrentSongTimeMode()
{
    if(currentSongTimeHadPassed->isHidden())
    {
        currentSongTimeHadPassed->show();
        currentSongTimeLeft->hide();
        flag3 = true;
    }
    else if(currentSongTimeLeft->isHidden())
    {
        currentSongTimeHadPassed->hide();
        currentSongTimeLeft->show();
        flag3 = false;
    }
}

void MainWindow::controlsAnimation(bool mouseOnWindow)
{
    if(mouseOnWindow == true && flag==true && flag2==true)
    {
        flag=false;
        flag2=false;
        animation(-1);
        qDebug() << "in";
    }
    else if(mouseOnWindow == false && flag==false && flag2==true)
    {
        flag=true;
        flag2=false;
        animation(1);
        qDebug() << "out";

    }
    animationTimerStart();

}

void MainWindow::animationTimerStart()
{
    if (flag == false)
    {
       length->show();
       volume->show();
       prevButton->show();
       stopButton->show();
       pauseButton->show();
       playButton->show();
       nextButton->show();
       currentSongDuration->show();
       openPicButton->show();
       openPlaylistsButton->show();
       picChangeSpeedSlider->show();
       if(flag3 == true)
       {
           currentSongTimeHadPassed->show();
       }
       else
       {
           currentSongTimeLeft->show();
       }
    }
    connect(animationTimer,&QTimer::timeout,this,&MainWindow::animationTimerStop);
    animationTimer->start(1000);
}

void  MainWindow::animationTimerStop()
{
    if(flag == true)
    {
       length->hide();
       volume->hide();
       prevButton->hide();
       stopButton->hide();
       pauseButton->hide();
       playButton->hide();
       nextButton->hide();
       currentSongDuration->hide();
       openPicButton->hide();
       openPlaylistsButton->hide();
       picChangeSpeedSlider->hide();
       currentSongTimeHadPassed->hide();
       currentSongTimeLeft->hide();
    }

    flag2=true;
    animationTimer->stop();
}

void MainWindow::animation(int a)
{
    int animationDuration = 1000;
    QEasingCurve animationType(QEasingCurve::InOutQuint);
    QPropertyAnimation *lengthAnimation                 = new QPropertyAnimation(length,"pos");
    QPropertyAnimation *volumeAnimation                 = new QPropertyAnimation(volume,"pos");
    QPropertyAnimation *prevButtonAnimation             = new QPropertyAnimation(prevButton, "pos");
    QPropertyAnimation *stopButtonAnimation             = new QPropertyAnimation(stopButton, "pos");
    QPropertyAnimation *pauseButtonAnimation            = new QPropertyAnimation(pauseButton, "pos");
    QPropertyAnimation *playButtonAnimation             = new QPropertyAnimation(playButton, "pos");
    QPropertyAnimation *nextButtonAnimation             = new QPropertyAnimation(nextButton, "pos");
    QPropertyAnimation *time1Animation                  = new QPropertyAnimation(currentSongDuration, "pos");
    QPropertyAnimation *time2Animation                  = new QPropertyAnimation(currentSongTimeLeft, "pos");
    QPropertyAnimation *time3Animation                  = new QPropertyAnimation(currentSongTimeHadPassed, "pos");
    QPropertyAnimation *openPicButtonAnimation          = new QPropertyAnimation(openPicButton, "pos");
    QPropertyAnimation *openPlaylistsButtonAnimation    = new QPropertyAnimation(openPlaylistsButton, "pos");
    QPropertyAnimation *picChangeSpeedSliderAnimation   = new QPropertyAnimation(picChangeSpeedSlider, "pos");

    lengthAnimation->setStartValue(length->pos());
    lengthAnimation->setEndValue(QPoint(length->x(),length->y()+200*a));
    lengthAnimation->setEasingCurve(animationType);
    lengthAnimation->setDuration(animationDuration);

    volumeAnimation->setStartValue(volume->pos());
    volumeAnimation->setEndValue(QPoint(volume->x(),volume->y()+200*a));
    volumeAnimation->setEasingCurve(animationType);
    volumeAnimation->setDuration(animationDuration);

    prevButtonAnimation->setStartValue(prevButton->pos());
    prevButtonAnimation->setEndValue(QPoint(prevButton->x(),prevButton->y()+200*a));
    prevButtonAnimation->setEasingCurve(animationType);
    prevButtonAnimation->setDuration(animationDuration);

    stopButtonAnimation->setStartValue(stopButton->pos());
    stopButtonAnimation->setEndValue(QPoint(stopButton->x(),stopButton->y()+200*a));
    stopButtonAnimation->setEasingCurve(animationType);
    stopButtonAnimation->setDuration(animationDuration);

    pauseButtonAnimation->setStartValue(pauseButton->pos());
    pauseButtonAnimation->setEndValue(QPoint(pauseButton->x(),pauseButton->y()+200*a));
    pauseButtonAnimation->setEasingCurve(animationType);
    pauseButtonAnimation->setDuration(animationDuration);

    playButtonAnimation->setStartValue(playButton->pos());
    playButtonAnimation->setEndValue(QPoint(playButton->x(),playButton->y()+200*a));
    playButtonAnimation->setEasingCurve(animationType);
    playButtonAnimation->setDuration(animationDuration);

    nextButtonAnimation->setStartValue(nextButton->pos());
    nextButtonAnimation->setEndValue(QPoint(nextButton->x(),nextButton->y()+200*a));
    nextButtonAnimation->setEasingCurve(animationType);
    nextButtonAnimation->setDuration(animationDuration);

    time1Animation->setStartValue(currentSongDuration->pos());
    time1Animation->setEndValue(QPoint(currentSongDuration->x(),currentSongDuration->y()+200*a));
    time1Animation->setEasingCurve(animationType);
    time1Animation->setDuration(animationDuration);

    time2Animation->setStartValue(currentSongTimeLeft->pos());
    time2Animation->setEndValue(QPoint(currentSongTimeLeft->x(),currentSongTimeLeft->y()+200*a));
    time2Animation->setEasingCurve(animationType);
    time2Animation->setDuration(animationDuration);

    time3Animation->setStartValue(currentSongTimeHadPassed->pos());
    time3Animation->setEndValue(QPoint(currentSongTimeHadPassed->x(),currentSongTimeHadPassed->y()+200*a));
    time3Animation->setEasingCurve(animationType);
    time3Animation->setDuration(animationDuration);

    openPicButtonAnimation->setStartValue(openPicButton->pos());
    openPicButtonAnimation->setEndValue(QPoint(openPicButton->x(),openPicButton->y()-200*a));
    openPicButtonAnimation->setEasingCurve(animationType);
    openPicButtonAnimation->setDuration(animationDuration);

    openPlaylistsButtonAnimation->setStartValue(openPlaylistsButton->pos());
    openPlaylistsButtonAnimation->setEndValue(QPoint(openPlaylistsButton->x(),openPlaylistsButton->y()-200*a));
    openPlaylistsButtonAnimation->setEasingCurve(animationType);
    openPlaylistsButtonAnimation->setDuration(animationDuration);

    picChangeSpeedSliderAnimation->setStartValue(picChangeSpeedSlider->pos());
    picChangeSpeedSliderAnimation->setEndValue(QPoint(picChangeSpeedSlider->x(),picChangeSpeedSlider->y()-200*a));
    picChangeSpeedSliderAnimation->setEasingCurve(animationType);
    picChangeSpeedSliderAnimation->setDuration(animationDuration);

    lengthAnimation->start();
    volumeAnimation->start();
    prevButtonAnimation->start();
    stopButtonAnimation->start();
    pauseButtonAnimation->start();
    playButtonAnimation->start();
    nextButtonAnimation->start();
    time1Animation->start();
    time2Animation->start();
    time3Animation->start();
    openPicButtonAnimation->start();
    openPlaylistsButtonAnimation->start();
    picChangeSpeedSliderAnimation->start();

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    changeBackground();
}

void MainWindow::changeBackground()
{
    backgroundLabel->setPixmap(QPixmap::fromImage(*background).scaled(this->size(),Qt::IgnoreAspectRatio, Qt::FastTransformation));
    backgroundLabel->resize(this->size());
}

QImage MainWindow::blur(const QImage &image, const QRect &rect, int radius)
{
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

    QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    int r1 = rect.top();
    int r2 = rect.bottom();
    int c1 = rect.left();
    int c2 = rect.right();

    int bpl = result.bytesPerLine();
    int rgba[4];
    unsigned char* p;

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r1) + col * 4;
        for (int i = 0; i < 4; i++)
            rgba[i] = p[i] << 4;

        p += bpl;
        for (int j = r1; j < r2; j++, p += bpl)
            for (int i = 0; i < 4; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c1 * 4;
        for (int i = 0; i < 4; i++)
            rgba[i] = p[i] << 4;

        p += 4;
        for (int j = c1; j < c2; j++, p += 4)
            for (int i = 0; i < 4; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r2) + col * 4;
        for (int i = 0; i < 4; i++)
            rgba[i] = p[i] << 4;

        p -= bpl;
        for (int j = r1; j < r2; j++, p -= bpl)
            for (int i = 0; i < 4; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c2 * 4;
        for (int i = 0; i < 4; i++)
            rgba[i] = p[i] << 4;

        p -= 4;
        for (int j = c1; j < c2; j++, p -= 4)
            for (int i = 0; i < 4; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    return result;
}

MainWindow::~MainWindow(){}
