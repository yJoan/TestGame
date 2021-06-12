#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsObject>
#include <QPixmap>
class Button : public QGraphicsObject
{
    Q_OBJECT
public:
    Button(QPixmap pix, QGraphicsScene* scene);
    ~Button();
signals:
    void clicked();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);



private:
    QGraphicsScene *m_scene;
    QPixmap m_pix;
};

#endif // BUTTON_H
