#include"mineLand.h"
#include <QDebug>
#include <QGridLayout>
#include <ctime>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include "windows.h"

mineLand::mineLand(QWidget* parent):QDialog(parent)
{
    QFont font("宋体", 12, QFont::Bold);

    //名字
//    QPixmap tm(":/images/time.jpg");
    timerName = new QLabel(tr("时间:"));
    timerName->setFont(font);
//    timerName->setPixmap(tm);
    boomCnt = new QLabel(tr("剩余:"));
    boomCnt->setFont(font);

    //计时器标签
    timerLabel = new QLabel();

    //选定地雷个数
    scoreLabel = new QLabel();

    //表情
    emoctionLabel = new QLabel();
    emoctionLabel->showFullScreen();

    //设置时钟背景
    lcdNum = new QLCDNumber(timerLabel);
    QPalette p = lcdNum->palette();
    p.setColor(QPalette::Normal, QPalette::WindowText,Qt::red);
    lcdNum->setPalette(p);
    lcdNum->setStyleSheet("background-color: black");
    lcdNum->setWindowFlags(Qt::FramelessWindowHint);
    lcdNum->setWindowOpacity(0.5);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();

    //选定地雷个数
    lcdNum2 = new QLCDNumber(scoreLabel);
    lcdNum2->setPalette(p);
    lcdNum2->setStyleSheet("background-color: black");
    lcdNum2->setWindowFlags(Qt::FramelessWindowHint);
    lcdNum2->setWindowOpacity(0.5);

    //表情
    QPixmap map(":/images/good.png");
    emoctionLabel->setPixmap(map);

    levels = 10;  //默认难度等级为最简单
    for(int i = 0 ; i < 225 ; ++i)
        mines.push_back(new mineButton(i));  //容器内安防255个地雷

    //top
    QGridLayout *top = new QGridLayout;
    QGridLayout *left = new QGridLayout;
    QGridLayout *right = new QGridLayout;
    QGridLayout *rightItem = new QGridLayout;

    //下部
    QGridLayout *layout = new QGridLayout;

    //up-down
    QVBoxLayout *up_down = new QVBoxLayout;

    left->addWidget(boomCnt, 0, 0, 1, 1);
    left->addWidget(scoreLabel, 0, 1, 1, 5);

    rightItem->addWidget(timerName, 0, 0, 1, 1);
    rightItem->addWidget(timerLabel, 0, 1, 1, 4);

    right->addWidget(emoctionLabel, 0, 0, 1, 8);
    right->addLayout(rightItem, 0, 9, 1, 5);

    top->addLayout(left, 0, 0, 1, 5);
    top->addLayout(right, 0, 6, 1, 6);

    auto MINE = mines.begin();
    for(int i = 0 ; i < 15 ; ++i)
    {
        for(int j = 0 ; j < 15 ; ++j)
        {
            layout->addWidget(*MINE,i, j, 1, 1);  //安装225个地雷

            connect(*MINE,SIGNAL(NO_button(int)), this, SLOT(show_empty(int)));  //建立连接,点击空白区域，自动展开雷区
            connect(*MINE,SIGNAL(find_mine()), this, SLOT(winner()));            //标记出所有地雷
            connect(*MINE,SIGNAL(get_mine()), this, SLOT(loster()));             //点到地雷
            ++MINE;
        }
    }

    layout->setSpacing(0);

    up_down->addLayout(top);
    up_down->addLayout(layout);

    setLayout(up_down);

    type_button.push_back(100);  //初始化容器
    create_mine();
    setWindowIcon(QIcon(":/images/bomber.jpg"));

}

//计时
int mineLand::staticTime = 0;

void mineLand::showTime()
{
    QTime time = QTime::currentTime();
    if (staticTime >= 60) staticTime = 0;
    time.setHMS(0, 0, staticTime++, 0);
    QString text = time.toString("mm:ss");
    if (showColon)
    {
        text[2] = ':';
        showColon = false;
    } else {
        text[2] = ' ';
        showColon = true;
    }
    lcdNum->display(text);
}

//生成雷算法
void mineLand::create_mine()
{
    srand(unsigned(time(0)));  //制作随机数种子a
    if(!type_button.isEmpty())
        type_button.clear();   //清空数组
    for(int i = 0 ; i < 225 ; ++i)
        type_button.push_back(9);
    nus();    //生成对应等级的概率

    //第一步：在225个中生成level*15个地雷
    auto pt = type_button.begin();
    int buttons = 0;  //地雷计数
    do{
        for(int i = 0 ; i < 224 ; ++i)      //这里设定最后一个格子肯定不会是类
        {
            int nu = rand() % probability;
//            qDebug() << nu;
            if(nu == 1 && (*(pt+i)) != 0)  //随即到莫个数。且这个数不为0（地雷）
            {
                ++buttons;        //雷数目+1
                *(pt+i) = 0;      //生成了一个雷
            }
            if(buttons == levels) //如果一个循环内生成的地雷>levels*20,则立刻退出循环
                break;
        }
    } while(buttons < levels);

    surplus = levels;
    QString str = QString::number(surplus);
    lcdNum2->display(str);

    //第二部，在每个按钮周边如果有N个雷，就生成数字N
    for(int i = 0 ; i < 225 ; ++i)
    {
        int j = i+1;
        int numbers = 0;            //代表周围地雷数目
        if(j%15 != 1 and j-16 > 0)  //先判断左上角位于坐标内
        {
            if(*(pt+i-16) == 0)     //在判断左上角是否为地雷
                ++numbers;
        }
        if(j-15 > 0)               //上方
        {
            if(*(pt+i-15) == 0)
                ++numbers;
        }
        if(j%15 != 0 and j-14 > 0) //右上
        {
            if(*(pt+i-14) == 0)
                ++numbers;
        }
        if(j%15 != 1 and j-1 > 0)  //左边
        {
            if(*(pt+i-1) == 0)
                ++numbers;
        }
        if(j%15 != 0 and j+1 <225)    //右边
        {
            if(*(pt+i+1) == 0)
                ++numbers;
        }
        if(j%15 != 1 and j+14 < 225)  //左下
        {
            if(*(pt+i+14) == 0)
                ++numbers;
        }
        if(j+15 < 225)  //下方
        {
            if(*(pt+i+15) == 0)
                ++numbers;
        }
        if(j%15 != 0 and j+16 < 225)         //右下
        {
            if(*(pt+i+16) == 0)
                ++numbers;
        }
        if((*(pt+i)) != 0 and numbers != 0)  //如果自身不是雷且周围有雷，则设为数字
            *(pt+i) = numbers;
    }
    //第三步，把类型和地雷关联
    auto BUTTON = mines.begin();
    for(int i = 0 ; i < 225 ; ++i)
    {
        int m = *(pt+i);
        (*(BUTTON+i))->resetType(m);
    }
}

//递归搜索空白
void mineLand::show_empty(int nu)
{
    if(nu < 0 or nu >224 or (*(mines.begin()+nu))->is_click())
        return;   //越界就停止递归
    if((*(type_button.begin() + nu)) > 0 and (*(type_button.begin() + nu)) < 9)
    {
        (*(mines.begin() + nu))->like_click();   //如果是数字则停止搜索
        return;
    }
    if((*(type_button.begin() + nu)) == 9)
    {
        (*(mines.begin() + nu))->like_click();
        show_empty(nu - 1);
        show_empty(nu + 1);
    }
} 

void mineLand::winner()
{
    int real_mine = 0;
    int fake_mine = 0;
    for(auto A : mines)
    {
        if(A->type_button() == true)
            ++real_mine;
        if(A->is_click() == true)
            ++fake_mine;
    }
    if(real_mine == levels and real_mine+fake_mine == 225)//胜利条件为所有地雷正确标出，且其他都点击过
    {
        QPixmap map(":/images/perfect.png");
        emoctionLabel->setPixmap(map);
        emit win();
        for(auto A : mines)
            A->unclick();   //游戏胜利后放置左键点击地雷造成重复判断
    }
}
void mineLand::loster()
{

    QPixmap map(":/images/bad.png");
    emoctionLabel->setPixmap(map);
    for(auto A : mines)
        A->like_click();   //失败后所有按钮全部点开
    emit lost();

}

void mineLand::new_game()
{
    mineLand::staticTime = 0;

    QPixmap map(":/images/good.png");
    emoctionLabel->setPixmap(map);
    for(auto A : mines)
        A->resetType(10);  //所有按钮都重置为初始状体
    create_mine();         //重置地雷
}


void mineLand::set_level(int i)
{
    levels = i * 10;
}

