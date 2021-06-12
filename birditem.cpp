#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>

#define FLY_BRID_SIZE 45

BirdItem::BirdItem(QGraphicsScene* scene)
    :m_curflyStatus(0)
    ,m_IsLandFall(true)
    ,m_IsRaise(true)
{
    scene->addItem(this);//将当前的小鸟对象添加到场景中去
    m_scene = scene;

    //定时刷新小鸟
    m_bridRefreshTimer = new QTimer(this);
    connect(m_bridRefreshTimer,SIGNAL(timeout()),
            this,SLOT(onRefreshBrid()));
    m_bridRefreshTimer->start(10);
}

//重写绘图区域
QRectF BirdItem::boundingRect() const
{
    return QRectF(60,FLY_BRID_SIZE*5,FLY_BRID_SIZE,FLY_BRID_SIZE);
}

//小鸟上升动画
void BirdItem::flyRaiseAnimation()
{
    if(m_IsRaise)
    {
        m_IsRaise = false;
        m_flyAnimation->stop();//停止上一个动画

        int nMove = pos().y();//鸟儿移动的y值
        if(nMove > -180)//-180最顶端的值,场景里面是以中心为圆点的
        {
            m_flyAnimation->setDuration(300);//动画时长
            //设置动画结束时的位置
            m_flyAnimation->setEndValue(QPoint(pos().x(),pos().y()-FLY_BRID_SIZE));
        }
        else//小鸟飞到了顶上
        {
            m_flyAnimation->setDuration(300);//动画时长
            //设置动画结束时的位置
            m_flyAnimation->setEndValue(pos());
        }
        m_flyAnimation->setEasingCurve(QEasingCurve::Linear);//设置动画曲线效果
        m_flyAnimation->start();//启动动画
        connect(m_flyAnimation,SIGNAL(finished()),
                this,SLOT(onflyRaiseAnimationFinished()));
    }
}

//下降动画
void BirdItem::flyLandfallAnimation()
{
    if(m_IsLandFall)
    {
        m_flyAnimation->stop();
        m_flyAnimation->setDuration(300);

        //下降一个小鸟高度
        m_flyAnimation->setEndValue(QPoint(pos().x(),pos().y()+FLY_BRID_SIZE));
        m_flyAnimation->start();
        m_IsLandFall = false;
    }
}

bool BirdItem::checkIsCollided()
{
    //collidingItems返回与当前游戏项冲突(碰撞)的所有项
    if(!collidingItems().isEmpty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//刷新小鸟
void BirdItem::onRefreshBrid()
{
    update();
}

void BirdItem::onflyRaiseAnimationFinished()
{
    m_IsLandFall = true;
    flyLandfallAnimation();//执行下降动画
}

void BirdItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(m_curflyStatus<10)//翅膀向上
    {
        m_curflyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird1.png"));
    }else if(m_curflyStatus<20)//翅膀居中
    {
        m_curflyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird2.png"));
    }else if(m_curflyStatus<30)//翅膀向下
    {
        m_curflyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird3.png"));
    }else
    {
        m_curflyStatus = 0;
    }
}

void BirdItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)//按下的是空格
    {
        flyRaiseAnimation();//上升动画
    }
}
