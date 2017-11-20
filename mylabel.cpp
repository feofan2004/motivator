#include "mylabel.h"

void MyLabel::mouseReleaseEvent(QMouseEvent *mre)
{
    if (mre->button() == Qt::LeftButton)
    {
        emit clicked((QObject*)this);
    }
}

