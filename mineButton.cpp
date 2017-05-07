#include"mineButton.h"
#include <QDebug>

mineButton::mineButton(int i , QWidget* parent):QPushButton(parent)
{
    NO = i;  //设置每个按钮单独的编号
    setFixedSize(36,36);  //固定大小
}
void mineButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)  //如果是地雷，显示地雷图片
    {
        if(button_type == 0 and enable_click == true)
        {
            emit get_mine();  //点到地雷了
            setIcon(QIcon(":/images/bomber.jpg"));
        }
        if(button_type > 0 and button_type < 9 and enable_click == true)  //如果是数字，则显示数字图片
        {
            QString name = ":/images/" + QString::number(button_type);
            if (button_type <= 3)
                name = name + ".jpg";
            else
                name = name + ".png";
            setIcon(QIcon(name));
        }
        if(button_type == 9 and enable_click == true)  //如果是空白，显示空白图片
        {
            setIcon(QIcon(":/images/cd.png"));
            emit NO_button(NO);   //无论点击数字还是空白，都发射信号
        }
        enable_click = false;  //左键点击完后，不在接受点击
    }
    if(event->button() == Qt::RightButton)
    {
        if(right_click == false and enable_click == true)  //如果尚未被右键标记
        {
            setIcon(QIcon(":/images/know.png"));
            right_click = true;  //已经被右键标记
        }
        else if(right_click == true and enable_click == true)
        {
            setIcon(QIcon(":/images/empty.png"));
            right_click = false;  //取消右键标记
        }
    }
    // if(right_click == true and button_type == 0)  //右键标记到正确的地雷，发射信号
    emit find_mine();
    setIconSize(size());
    QPushButton::mousePressEvent(event);
}
bool mineButton::type_button()const
{
    //如果按钮被右键标记且该按钮类型为地雷，返回true
    if(right_click == true and button_type == 0)
        return true;
    return false;
}

void mineButton::resetType(int i)
{
    button_type = i;
    right_click = false;
    enable_click = true;  //初始化按钮的各项状态
    setIcon(QIcon(":/images/empty.png"));
    setIconSize(size());
}

void mineButton::like_click()  //该函数用于模拟鼠标点击
{
    if(enable_click == false)  //如果已左键点击过，直接退出
        return;
    if(button_type == 0)
        setIcon(QIcon(":/images/bomber.jpg"));
    if(button_type > 0 and button_type < 9)  //如果是数字，则显示数字图片
    {
        QString name = ":/images/" + QString::number(button_type);
//        qDebug() << button_type << "\n";
        if (button_type <= 3)
            name = name + ".jpg";
        else
            name = name + ".png";
        setIcon(QIcon(name));
    }
    if(button_type == 9)  //如果是空白，显示空白图片
        setIcon(QIcon(":/images/cd.png"));
    setIconSize(size());
    enable_click = false;
}
bool mineButton::is_click() const
{
    if (enable_click == false)
        return true;
    return false;
}
void mineButton::unclick()
{
    enable_click = false;
}
