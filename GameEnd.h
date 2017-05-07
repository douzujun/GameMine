#ifndef GAMEEND_H_
#define GAMEEND_H_
#include <QDialog>
#include <QLabel>
#include <QCloseEvent>
#include <QPixmap>

class GameEnd:public QDialog
{
    Q_OBJECT
private:
    bool con;
    QLabel *show_label;

public:
    GameEnd(QWidget* parent = 0);//构造函数
    void how_show();

protected:
    void closeEvent(QCloseEvent*);

public slots:
    void win_show();   //显示胜利or失败
    void lost_show();
};
#endif
