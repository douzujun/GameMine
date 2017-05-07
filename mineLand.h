#ifndef MINELAND_H_
#define MINELAND_H_
#include <QDialog>
#include "mineButton.h"
#include <QLabel>
#include <QLCDNumber>

class mineLand:public QDialog
{
    Q_OBJECT
private:
    int levels;  //等级，分别有10,20,30三个等级
    QList<mineButton*> mines;  //放置255个mineButton
    QList<int> type_button;    //放置255个整数用于表示对应的button类型
    int probability;           //用于不同等级下生成地雷的概率

    QLabel *emoctionLabel;     //表情标签
    QLabel *timerLabel;        //计时器标签
    QLabel *timerName;         //计时器
    QLabel *boomCnt;           //剩余地雷
    QLabel *scoreLabel;        //计分器
    QLCDNumber *lcdNum;        //LCD
    QLCDNumber *lcdNum2;       //计分

    bool showColon;            //用于显示时间是否显示 ":"

    //生成雷的算法
    void nus(){ probability = 225 / levels; }

public:

    static int staticTime;     //计时
    int winTime;
    int lostTime;
    int surplus;

    mineLand(QWidget* parent = 0);
    void create_mine();

signals:
    void win();
    void lost();
public slots:
    void show_empty(int);  //显示被点击按钮周围的空白按钮
    void winner();         //标记出所有地雷
    void loster();         //点到地雷，游戏结束
    void new_game();
    void set_level(int);   //设置不同的雷数

    //计时器
    void showTime();

};
#endif
