#include "mineGame.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc , char** argv)
{
    QApplication app(argc,argv);

    QPixmap pixmap(":images/start2.jpg");        //创建QPixmap对象，设置启动图片
    QSplashScreen splash(pixmap); //利用QPixmap对象创建一个QSplashScreen对象
    splash.show ();               //显示此启动图片

    app.processEvents ();           //使程序在显示启动动画的同时能能响应鼠标等其他事件

    mineGame B;
    B.show();

    //表示在主窗体对象初始化完成后，结束启动画面
    splash.finish (&B);

    return app.exec();
}
