#ifndef MINEGAME_H_
#define MINEGAME_H_
#include"mineLand.h"
#include"GameEnd.h"
#include"GameOption.h"
#include"GameInstruction.h"
#include<QMainWindow>
#include<QAction>
#include <QMenu>
#include <QMenuBar>

class mineGame:public QMainWindow
{
    Q_OBJECT
private:
    QAction* begin_action;
    QAction* option_action;  //难度选项
    QAction* close_action;
    QAction* info_action;    //游戏说明
    QAction* calcuate_action;//调用计算器

    QMenu* game_menu;
    QMenu* help_menu;
    QMenuBar* menus;            //菜单栏
    mineLand* mine_land;        //游戏窗体
    GameOption* options;        //难度选择框
    GameEnd* game_end;          //游戏结束对话框
    GameInstruction* helps;     //游戏帮助说明
public:
    mineGame(QWidget* parent = 0); //构造函数
private slots:
    void new_level();       //显示难度选择对话框
    void show_help();       //显示帮助对话框
    void show_calcuate();   //显示计算器
};  
#endif
