#ifndef BIRDITEM_H
#define BIRDITEM_H
#include <QGraphicsObject>
#include <QPropertyAnimation>
class BirdItem:public QGraphicsObject
{
    Q_OBJECT
public:
    BirdItem(QGraphicsScene* scene);

public:
    QRectF boundingRect()const;//重写绘图区域
    void flyRaiseAnimation();//上升动画
    void flyLandfallAnimation();//下降动画
    bool checkIsCollided();     //碰撞检测

private slots:
    void onRefreshBrid();//定时刷新小鸟
    void onflyRaiseAnimationFinished();//上升动画结束
private:
    //重写绘图事件
    void paint(QPainter*, const QStyleOptionGraphicsItem*,QWidget*);
    void keyPressEvent(QKeyEvent* event);//重写键盘事件,空格控制小鸟

private:
    QTimer* m_bridRefreshTimer; //刷新小鸟计时器
    QGraphicsScene* m_scene;    //所在场景
    QPropertyAnimation* m_flyAnimation;//飞行动画
    int m_curflyStatus;//当前飞行状态
    bool m_IsLandFall;//下降标志
    bool m_IsRaise;   //上升标志
};

#endif // BIRDITEM_H
