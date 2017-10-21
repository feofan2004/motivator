
#include "player.h"

Player::Player(QWidget *parent)
{
    control = new QMediaPlayer();
    playlist = new QMediaPlaylist;
    //allPlaylists = new QList<QMediaPlaylist>;
   // playlist->addMedia(QUrl("qrc:/music/Skins.mp3"));
    //playlist->load(QUrl("qrc:/music/Skins.mp3"));
    control->setPlaylist(playlist);
    //connect(,SIGNAL(control->durationChanged(1000)),, SLOT(parent->));
}

void Player::playerStart()
{
    qDebug() << "Amma here";
    control->play();
}

void Player::playerPause()
{
    control->pause();
}

void Player::playerPrev()
{

}

void Player::playerNext()
{

}

Player::~Player()
{

}

