#include "GameInstruction.h"
#include <QHBoxLayout>
#include <QFont>

GameInstruction::GameInstruction(QWidget* parent):QDialog(parent)
{
    instruction = new QTextEdit;
    instruction->setFixedSize(400,400);
    QString A(tr("第一条：基本定式不要忘，现场推理真够呛。\n"
                 "第二条：鼠标点击不要快，稳定节奏把空开。\n"
                 "第三条：顺手标雷不要惯，积累下来记录悬。\n"
                 "第四条：无从下手不要愣，就近猜雷把心横。\n"
                 "第五条：遇到猜雷不要怕，爆了脸上不留疤。\n"
                 "第六条：猜雷猜错不要悔，哭天抢地也白费。\n"
                 "第七条：碰上好局不要慌，紧盯局部慢扩张。\n"
                 "第八条：痛失好局不要恨，既然有缘定有份。\n"));

    instruction->append(A);

    QFont font("黑体", 12, QFont::Bold);
    instruction->setFont(font);
    instruction->setReadOnly(true);  //只读

    QHBoxLayout* main_layout = new QHBoxLayout;
    main_layout->addWidget(instruction);
    setLayout(main_layout);
    setFixedSize(400,400);
    setWindowTitle(tr("帮助"));
}
void GameInstruction::closeEvent(QCloseEvent*)
{
    hide();  //不关闭窗口
}
