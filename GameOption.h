#ifndef GAMEOPTION_H_
#define GAMEOPTION_H_
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QCloseEvent>

class GameOption:public QDialog
{
    Q_OBJECT
private:
    int levels;  //难度等级，1为10歌雷，2为20个，3为30个
    QPushButton  *ok_button;
    QRadioButton *easy_button;
    QRadioButton *mid_button;
    QRadioButton *hard_button;
    QGroupBox *group;
public:
    GameOption(QWidget* parent = 0);
protected:
    void closeEvent(QCloseEvent*);
private slots:
    void chose_level();  //确定是那个难度被选中了
signals:
    void new_level(int);

};
#endif
