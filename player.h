
#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>

class Player : public QObject
{
    Q_OBJECT
friend class MainWindow;
private:
    QMediaPlayer            *control;
    QMediaPlaylist          *playlist;
    QList<QMediaPlaylist>   *allPlaylists;
protected:
    void playerStart();
    void playerPause();
    void playerPrev();
    void playerNext();

public:
    Player(QWidget *parent);
    ~Player();



};

#endif // PLAYER_H

