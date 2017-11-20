#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QEvent>

class MainWindow;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:
    void isMouseOnWindow(bool);
};

#endif // MYWIDGET_H
