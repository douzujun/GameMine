#include "GameOption.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
GameOption::GameOption(QWidget* parent):QDialog(parent)
{
    levels = 1; //默认为简单
    ok_button = new QPushButton(tr("确定"));
    group = new QGroupBox(tr("难度设定"));
    easy_button = new QRadioButton(tr("简单难度"));
    easy_button->setChecked(true);  //默认选中简单难度
    mid_button = new QRadioButton(tr("中等难度"));
    hard_button = new QRadioButton(tr("困难"));
    //布局安装
    QVBoxLayout* button_layout = new QVBoxLayout;
    button_layout->addWidget(easy_button);
    button_layout->addWidget(mid_button);
    button_layout->addWidget(hard_button);
    group->setLayout(button_layout);
    QHBoxLayout* ok_layout = new QHBoxLayout;
    ok_layout->addStretch();
    ok_layout->addWidget(ok_button);
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(group);
    main_layout->addLayout(ok_layout);
    setLayout(main_layout);
    setWindowTitle(tr(" "));

    connect(ok_button,SIGNAL(clicked()),this,SLOT(chose_level()));
    connect(ok_button,SIGNAL(clicked()),this,SLOT(hide()));  //点击确定，隐藏对话框
}
void GameOption::chose_level()
{
    if(easy_button->isChecked())
        levels = 1;
    else if(mid_button->isChecked())
        levels = 2;
    else if(hard_button->isChecked())
        levels = 3;
    emit new_level(levels);
}
void GameOption::closeEvent(QCloseEvent*)
{
    emit new_level(levels);
    hide();  //关闭对话框只是影藏
}
