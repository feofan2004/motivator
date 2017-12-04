#include "player.h"
#include "mainwindow.h"

Player::Player(MainWindow* parent)
{
    maximumPlaylist=2;
    idPlaylist=0;
    parentPtr = parent;
    control          = new QMediaPlayer();

    allPlaylists     = new QList<QMediaPlaylist*>;
    playlistUiWindow = new QWidget;
    addSongButton          = new QPushButton(playlistUiWindow);
    delSongButton          = new QPushButton(playlistUiWindow);
    addPlaylistButton      = new QPushButton(playlistUiWindow);
    delPlaylistButton      = new QPushButton(playlistUiWindow);
    savePlaylistButton     = new QPushButton(playlistUiWindow);
    loadPlaylistButton     = new QPushButton(playlistUiWindow);
    renamePlaylistButton   = new QPushButton(playlistUiWindow);
    playlistsButtons = new QVBoxLayout;
    playlistLayot    = new QVBoxLayout;
    buttons1         = new QHBoxLayout;
    buttons2         = new QHBoxLayout;
    songs            = new QListWidget*[10];
    playlistsWidget  = new QTabWidget(playlistUiWindow);

    addSongButton->setText("Add Song");
    delSongButton->setText("Del Song");
    addPlaylistButton->setText("Add Playlist");
    delPlaylistButton->setText("Del Playlist");
    savePlaylistButton->setText("Save Playlist");
    loadPlaylistButton->setText("Load Playlist");
    renamePlaylistButton->setText("Rename Playlist");
    buttons1->addWidget(addSongButton);
    buttons1->addWidget(delSongButton);
    buttons1->addWidget(addPlaylistButton);
    buttons1->addWidget(delPlaylistButton);
    buttons2->addWidget(savePlaylistButton);
    buttons2->addWidget(loadPlaylistButton);
    buttons2->addWidget(renamePlaylistButton);
    playlistsButtons->addLayout(buttons1);
    playlistsButtons->addLayout(buttons2);
    songs[0] = new QListWidget;
    playlistsWidget->addTab(songs[0],"for all");
    playlist         = new QMediaPlaylist;
    allPlaylists->push_back(playlist);
    playlistsWidget->setCurrentIndex(0);
    QDir ff1(QCoreApplication::applicationDirPath()+"/playlists/all");
    QStringList nameFilter;
    nameFilter << "*.mp3"<< "*.flac";
    QFileInfoList lt = ff1.entryInfoList( nameFilter, QDir::Files );
    QFileInfo fo;
    foreach (fo, lt)
    {
        playlist = allPlaylists->at(playlistsWidget->currentIndex());
        playlist->addMedia(QUrl::fromLocalFile(fo.absoluteFilePath()));
        playlist->load(QUrl::fromLocalFile(fo.absoluteFilePath()));
        QString songName=fo.absoluteFilePath().section('/',-1);
        songs[playlistsWidget->currentIndex()]->addItem(songName);
    }
    connect(songs[0], &QListWidget::doubleClicked, this, &Player::playThisSong);
    connect(parentPtr->prevButton,&QPushButton::clicked,allPlaylists->at(0),&QMediaPlaylist::previous);
    connect(parentPtr->nextButton,&QPushButton::clicked,allPlaylists->at(0),&QMediaPlaylist::next);
    songs[1] = new QListWidget;
    playlistsWidget->addTab(songs[1],"learning");
    playlist         = new QMediaPlaylist;
    allPlaylists->push_back(playlist);
    playlistsWidget->setCurrentIndex(1);
    QDir ff2(QCoreApplication::applicationDirPath()+"/playlists/ln");
    lt = ff2.entryInfoList( nameFilter, QDir::Files );
    foreach (fo, lt)
    {
        playlist = allPlaylists->at(playlistsWidget->currentIndex());
        playlist->addMedia(QUrl::fromLocalFile(fo.absoluteFilePath()));
        playlist->load(QUrl::fromLocalFile(fo.absoluteFilePath()));
        QString songName=fo.absoluteFilePath().section('/',-1);
        songs[playlistsWidget->currentIndex()]->addItem(songName);
    }
    connect(songs[1], &QListWidget::doubleClicked, this, &Player::playThisSong);
    connect(parentPtr->prevButton,&QPushButton::clicked,allPlaylists->at(1),&QMediaPlaylist::previous);
    connect(parentPtr->nextButton,&QPushButton::clicked,allPlaylists->at(1),&QMediaPlaylist::next);
    songs[2] = new QListWidget;
    playlistsWidget->addTab(songs[2],"test");
    playlist         = new QMediaPlaylist;
    allPlaylists->push_back(playlist);
    playlistsWidget->setCurrentIndex(2);
    QDir ff3(QCoreApplication::applicationDirPath()+"/playlists/test");
    lt = ff3.entryInfoList( nameFilter, QDir::Files );
    foreach (fo, lt)
    {
        playlist = allPlaylists->at(playlistsWidget->currentIndex());
        playlist->addMedia(QUrl::fromLocalFile(fo.absoluteFilePath()));
        playlist->load(QUrl::fromLocalFile(fo.absoluteFilePath()));
        QString songName=fo.absoluteFilePath().section('/',-1);
        songs[playlistsWidget->currentIndex()]->addItem(songName);
    }
    connect(songs[2], &QListWidget::doubleClicked, this, &Player::playThisSong);
    connect(parentPtr->prevButton,&QPushButton::clicked,allPlaylists->at(2),&QMediaPlaylist::previous);
    connect(parentPtr->nextButton,&QPushButton::clicked,allPlaylists->at(2),&QMediaPlaylist::next);
    playlistLayot->addWidget(playlistsWidget);
    playlistLayot->addLayout(playlistsButtons);
    playlistUiWindow->setLayout(playlistLayot);
    playlistUiWindow->setWindowIcon(QIcon(":/icons/MainWindow.png"));
    playlistUiWindow->setWindowTitle("Playlist Manager");


    connect(addPlaylistButton,  &QPushButton::clicked,          this,               &Player::addFuckingPlaylist);
    connect(addSongButton,      &QPushButton::clicked,          this,               &Player::addSong);
    connect(parentPtr->volume,  &QSlider::valueChanged,         control,            &QMediaPlayer::setVolume);
    connect(control,            &QMediaPlayer::positionChanged, this,               &Player::setCurrentSongCurrentTimeLabel);
    connect(control,            &QMediaPlayer::durationChanged, this,               &Player::setCurrentSongDurationLabel);
    connect(parentPtr->length,  &QSlider::sliderMoved,          control,            &QMediaPlayer::setPosition);

    connect(delSongButton,      &QPushButton::clicked,          this,               &Player::deleteThisSong);
    connect(delPlaylistButton,  &QPushButton::clicked,          this,               &Player::delPlaylist);
    connect(savePlaylistButton, &QPushButton::clicked,          this,               &Player::savePlaylist);
    connect(loadPlaylistButton, &QPushButton::clicked,          this,               &Player::loadPlaylist);
}

void Player::prevSongInPlaylistManager()
{
    songs[playlistsWidget->currentIndex()]->setCurrentRow(songs[playlistsWidget->currentIndex()]->currentRow()-1);
}

void Player::nextSongInPlaylistManager()
{
    songs[playlistsWidget->currentIndex()]->setCurrentRow(songs[playlistsWidget->currentIndex()]->currentRow()+1);

}

void Player::savePlaylist()
{
    if(playlist->mediaCount()>0)
    {
    QString fileName;
    fileName += QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    fileName += "/playlists/";
    if(!QDir(fileName).exists())
    {
        QDir().mkdir(fileName);

    }
    fileName += playlistsWidget->tabText(playlistsWidget->currentIndex());
    fileName += ".qtppl";

    QFile playlistOut(fileName);

    if(!playlistOut.open(QFile::WriteOnly | QFile::Text))
    {

    }
    else
    {
        QTextStream outStream(&playlistOut);

        for(int i=0;i<playlist->mediaCount();i++)
        {
        QMediaContent a=playlist->media(i);
        outStream <<(a.canonicalUrl()).toLocalFile()<<endl;

        }

    }
    playlistOut.close();
}


}
void Player::loadPlaylist()
{
    QString fileName = QFileDialog::getOpenFileName(parentPtr,"Browse","C://","List File (*.qtppl)");
    QFile playlistOut(fileName);

    if(!playlistOut.open(QFile::ReadOnly | QFile::Text))
    {

    }
    else
    {
        QTextStream outStream(&playlistOut);

        if(!outStream.atEnd())
        {
        maximumPlaylist+=1;
        idPlaylist+=1;
        if(maximumPlaylist<10)
        {
            QString tmp="playlist ";
            tmp+= QString::number(idPlaylist);
            QMediaPlaylist*tmp1= new QMediaPlaylist;

            allPlaylists->push_back(tmp1);
            songs[maximumPlaylist] = new QListWidget;
            playlistsWidget->addTab(songs[maximumPlaylist],tmp);
            playlistsWidget->setCurrentIndex(maximumPlaylist);
            connect(songs[maximumPlaylist], &QListWidget::doubleClicked, this, &Player::playThisSong);
            connect(parentPtr->prevButton,&QPushButton::clicked,allPlaylists->at(maximumPlaylist),&QMediaPlaylist::previous);
            connect(parentPtr->nextButton,&QPushButton::clicked,allPlaylists->at(maximumPlaylist),&QMediaPlaylist::next);
            while (true)
               {
                    if(outStream.atEnd())
                    {
                        break;
                    }
                    QString fileName1;

                    fileName1=outStream.readLine();

                    tmp1->addMedia(QUrl::fromLocalFile( fileName1));
                    tmp1->load(QUrl::fromLocalFile( fileName1));
                    QString songName= fileName1.section('/',-1);
                    songs[maximumPlaylist]->addItem(songName);
                    qDebug()<<songName;
               }

            control->setPlaylist(tmp1);
        }
        else
        {
            maximumPlaylist-=1;
        }
        }
    }
    playlistOut.close();


}

void Player::delPlaylist()
{
    qDebug() << maximumPlaylist << "!" << idPlaylist;
    if(playlistsWidget->currentIndex() != 0)
    {
        allPlaylists->removeAt(playlistsWidget->currentIndex());
        playlistsWidget->removeTab(playlistsWidget->currentIndex());
        maximumPlaylist-=1;

    }
}

void Player::deleteThisSong()
{
    playlist->removeMedia(songs[playlistsWidget->currentIndex()]->currentRow());
    songs[playlistsWidget->currentIndex()]->takeItem(songs[playlistsWidget->currentIndex()]->currentRow());

}

void Player::playThisSong(QModelIndex a)
{
   qDebug() << "a.row " << a.row() << " current index " << playlistsWidget->currentIndex();
   QMediaPlaylist *tmp =  allPlaylists->at(playlistsWidget->currentIndex());
   control->setPlaylist(tmp);
   for (int i = 0; i < a.row(); i++)
   {
       tmp->next();
   }
   control->play();

}

void Player::setCurrentSongDurationLabel(qint64 a)
{
    parentPtr->length->setMaximum(a);
    qint64 seconds = (control->duration() / 1000)    % 60;
    qint64 minutes = (control->duration() / 60000)   % 60;
    qint64 hours   = (control->duration() / 3600000) % 24;
    QTime time(hours, minutes, seconds);
    parentPtr->currentSongDuration->setText(time.toString());

}

void Player::setCurrentSongCurrentTimeLabel(qint64 a)
{
    parentPtr->length->setValue(a);
//    if(a==control->duration())
//    {
//        nextSongInPlaylistManager();
//    }
    qint64 seconds = (control->position() / 1000)    % 60;
    qint64 minutes = (control->position() / 60000)   % 60;
    qint64 hours   = (control->position() / 3600000) % 24;
    QTime time(hours, minutes, seconds);
    parentPtr->currentSongTimeHadPassed->setText(time.toString());

    seconds = ((control->duration() / 1000) % 60) - seconds;
    if(seconds<0)
    {
        seconds=60+seconds;
        minutes+=1;
    }
    minutes = ((control->duration() / 60000)   % 60) - minutes;
    hours = ((control->duration() / 3600000) % 24) - hours;
    QTime time2(hours, minutes, seconds);
    QString timeStr;
    timeStr += "-";
    timeStr += time2.toString();
    parentPtr->currentSongTimeLeft->setText(timeStr);
}

void Player::addSong()
{
    QStringList filename = QFileDialog::getOpenFileNames(parentPtr,"Browse","C://","Music File (*.mp3)");
    foreach(QString i, filename)
    {
        playlist = allPlaylists->at(playlistsWidget->currentIndex());
        playlist->addMedia(QUrl::fromLocalFile(i));
        playlist->load(QUrl::fromLocalFile(i));
        QString songName=i.section('/',-1);
        songs[playlistsWidget->currentIndex()]->addItem(songName);
    }
    control->setPlaylist(playlist);
}

void Player::addFuckingPlaylist()
{
    maximumPlaylist+=1;
    idPlaylist+=1;
    if(maximumPlaylist<10)
    {
        QString tmp="playlist ";
        tmp+= QString::number(idPlaylist);
        allPlaylists->push_back(new QMediaPlaylist);
        songs[maximumPlaylist] = new QListWidget;
        playlistsWidget->addTab(songs[maximumPlaylist],tmp);
        playlistsWidget->setCurrentIndex(maximumPlaylist);
        connect(songs[maximumPlaylist], &QListWidget::doubleClicked, this, &Player::playThisSong);
        connect(parentPtr->prevButton,&QPushButton::clicked,allPlaylists->at(maximumPlaylist),&QMediaPlaylist::previous);
        connect(parentPtr->nextButton,&QPushButton::clicked,allPlaylists->at(maximumPlaylist),&QMediaPlaylist::next);

    }
    else
    {
        maximumPlaylist-=1;
    }
}

void Player::openPlaylistsWidget()
{
    playlistUiWindow->show();
}

Player::~Player(){}
