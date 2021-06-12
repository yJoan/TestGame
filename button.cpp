#include "button.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

Button::Button( QPixmap pix, QGraphicsScene* scene)
    :m_pix(pix)
{
    scene->addItem(this);
    setCursor(QCursor(Qt::PointingHandCursor));//设置鼠标为手指形状
}

Button::~Button()
{

}

QRectF Button::boundingRect() const
{
    return QRectF(QPointF(0,0),m_pix.size());
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,m_pix);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"点击";
        emit clicked();
    }
}
