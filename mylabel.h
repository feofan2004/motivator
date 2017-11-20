#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0) : QLabel(parent){}

protected:
    void mouseReleaseEvent(QMouseEvent *mre);

signals:
    void clicked(QObject *sender);
};

#endif // MYLABEL_H
