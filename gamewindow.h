#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "gamescene.h"
#include "birditem.h"
#include <QWidget>
#include <QParallelAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onStartClicked();

private:
    void initControl();
    void loadStyleSheet(const QString& sheetName);//加载样式
    void startWelcome();//启动欢迎

private:
    Ui::GameWindow *ui;
    GameScene *m_scene;     //游戏场景
    BirdItem* m_birdItem;   //鸟儿对象
    bool m_startGame;       //开始标志
    QParallelAnimationGroup* m_letterGroupFading;//渐渐消失动画组
};
#endif // GAMEWINDOW_H
