#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QTabWidget>
#include <QListWidget>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDir>

class MainWindow;

class Player : public QObject
{
    Q_OBJECT
friend class MainWindow;

public:
    int maximumPlaylist;
    int idPlaylist;
    QMediaPlayer            *control;
    QMediaPlaylist          *playlist;
    QList<QMediaPlaylist*>  *allPlaylists;
    MainWindow              *parentPtr;

    QTabWidget              *playlistsWidget;
    QListWidget             **songs;
    QWidget                 *playlistUiWindow;
    QPushButton             *addSongButton;
    QPushButton             *delSongButton;
    QPushButton             *addPlaylistButton;
    QPushButton             *delPlaylistButton;
    QPushButton             *savePlaylistButton;
    QPushButton             *loadPlaylistButton;
    QPushButton             *renamePlaylistButton;
    QVBoxLayout             *playlistsButtons;
    QHBoxLayout             *buttons1;
    QHBoxLayout             *buttons2;
    QVBoxLayout             *playlistLayot;

    Player(MainWindow * parent);
    ~Player();
public slots:
    void setCurrentSongDurationLabel(qint64 a);
    void setCurrentSongCurrentTimeLabel(qint64 a);
    void nextSongInPlaylistManager();
    void prevSongInPlaylistManager();
    void openPlaylistsWidget();
    void addSong();
    void addFuckingPlaylist();
    void delPlaylist();
    void playThisSong(QModelIndex a);
    void deleteThisSong();
    void savePlaylist();
    void loadPlaylist();
};

#endif // PLAYER_H
