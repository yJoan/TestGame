#include "gamewindow.h"
#include "button.h"
#include "ui_gamewindow.h"
#include <QFile>
#include <QDebug>
#include <QGraphicsView>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QStyleOption>
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
    ,m_startGame(false)
{
    ui->setupUi(this);
    setWindowTitle("飞翔的小鸟");
    initControl();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::paintEvent(QPaintEvent* event)
{
    //自定义paint事件
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void GameWindow::initControl()
{
    loadStyleSheet("GameWindow");
    QRectF gameRect = rect();
    m_scene = new GameScene(this,gameRect);//初始化游戏场景

    //初始化游戏视图(将场景添加到视图中)
    QGraphicsView* view = new QGraphicsView(m_scene,this);
    view->setScene(m_scene);//设置游戏场景
    view->setStyleSheet("border:none;background:transparent");//视图无边框透明

    view->setCacheMode(QGraphicsView::CacheBackground);//设置缓存为背景模式
    startWelcome(); //  启动欢迎
}

//加载样式
void GameWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/BirdGame/Resources/qss/"+sheetName+".css");
    if(file.open(QFile::ReadOnly))
    {
        QString strStyleSheet = this->styleSheet();//获取当前样式
        strStyleSheet += file.readAll();
        this->setStyleSheet(strStyleSheet);//设置样式
        file.close();
    }
}

void GameWindow::startWelcome()
{
   //小鸟
   m_birdItem = new BirdItem(m_scene);

   //字母:"我向风一样自由,无法挽留...."
   const int nLetters = 12;
   struct{
       char const *pix;
       qreal initX,initY;//起始位置
       qreal descX,descY;//终止位置

   }letterData[nLetters] = {
     {"我",-1400,-1000,250,100},//第一行
     {"向",-1200,-1000,300,100},
     {"风",-1000,-1000,350,100},
     {"一",-800,-1000,400,100},
     {"样",-400,-1000,450,100},
     {"自",-200,-1000,500,100},
     {"由",0,-1000,550,100},
     {"无",-200,-600,350,160},//第二行
     {"法",0,-600,400,160},
     {"挽",200,-600,450,160},
     {"留",400,-600,500,160},
     {"...",200,-600,550,160}
   };

   //连续动画组
   QSequentialAnimationGroup* letersGroupMoving = new QSequentialAnimationGroup(this);
   m_letterGroupFading = new QParallelAnimationGroup(this);

   for(int i=0;i<nLetters;++i) {
       QString htmlText = QString("<span style=\"font-family:'Berlin Sans FB';font-size:38px;font-weight:600;color:#194819;\">%1</span>").arg(letterData[i].pix);
       QGraphicsTextItem *letter = new QGraphicsTextItem();
       letter->setHtml(htmlText);
       letter->setPos(letterData[i].initX,letterData[i].initY);

       //文本项属性动画
       QPropertyAnimation *moveAnimation = new  QPropertyAnimation(letter,"pos",letersGroupMoving);
       moveAnimation->setEndValue(QPointF(letterData[i].descX,letterData[i].descY));//设置结束位置
       moveAnimation->setDuration(200);//动画时长
       moveAnimation->setEasingCurve(QEasingCurve::OutElastic);//线性曲线
       letersGroupMoving->addPause(50);

       //文本项渐渐消失动画
       QPropertyAnimation *fadeAnimation = new QPropertyAnimation(letter,"opacity",m_letterGroupFading);
       fadeAnimation->setDuration(1000);
       fadeAnimation->setEndValue(0);//从不透明到透明
       fadeAnimation->setEasingCurve(QEasingCurve::OutElastic);

       m_scene->addItem(letter);//往游戏场景中添加字符图形项
   }


   //启动字符动画
   letersGroupMoving->start(QAbstractAnimation::DeleteWhenStopped);//动画停止后删除

   //按钮图形项
   QPixmap pix =QPixmap(":/BirdGame/Resources/image/startButton.png");
   Button *btnItem = new Button(pix,m_scene);
   btnItem->setPos(350,450);
   connect(btnItem,SIGNAL(clicked()),this,SLOT(onStartClicked()));

   //按钮图形项渐渐消失动画
   QPropertyAnimation *btnfadeAnimation = new QPropertyAnimation(btnItem,"opacity",m_letterGroupFading);
   btnfadeAnimation->setDuration(600);
   btnfadeAnimation->setEndValue(0);//从不透明到透明
   btnfadeAnimation->setEasingCurve(QEasingCurve::OutElastic);
}

void GameWindow::onStartClicked()
{
    qDebug()<<"点击启动";
    m_letterGroupFading->start(QAbstractAnimation::DeleteWhenStopped);
}

