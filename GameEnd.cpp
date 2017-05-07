#include "GameEnd.h"
#include <QVBoxLayout>

GameEnd::GameEnd(QWidget* parent):QDialog(parent)
{  
    con = true;
    show_label = new QLabel;
//    show_label->setFixedSize(250,100);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(show_label);
    setLayout(layout);
    setWindowTitle(tr("Come On !"));
//    setFixedSize(250,100);  //设置窗体和标签一样大
}
void GameEnd::win_show()
{
    con = true;
    how_show();
}
void GameEnd::lost_show()
{
    con = false;
    how_show();
}
void GameEnd::how_show()
{
    QPalette pt = show_label->palette();
//    pt.setColor(QPalette::Background, Qt::black);
//    show_label->setPalette(pt);

    if(con == true)   //显示胜率or失败，同时显示不同颜色
    {
//        show_label->setText(tr("胜利!"));
//        pt.setColor(QPalette::WindowText,Qt::green);
        QPixmap win_map(":/images/win.jpg");
        show_label->setPixmap(win_map);
    }
    else if(con == false)
    {
//        show_label->setText(tr("失败!"));
//        pt.setColor(QPalette::WindowText,Qt::red);
        QPixmap lose_map(":/images/end.jpg");
        show_label->setPixmap(lose_map);
    }
//    QFont ft;
//    ft.setPointSize(35);
//    show_label->setFont(ft);  //设置字体大小
//    show_label->setPalette(pt);  //设置字体颜色
//    show_label->setAlignment(Qt::AlignCenter);//设置字体居中
    exec();
}
void GameEnd::closeEvent(QCloseEvent*)
{
    hide();//确保关闭窗口只是隐藏窗口
}
