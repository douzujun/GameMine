#include <QDialog>
#include <QTextEdit>
#include <QCloseEvent>
class GameInstruction:public QDialog
{

private:
    QTextEdit* instruction;
public:
    GameInstruction(QWidget* parent = 0);
protected:
    void closeEvent(QCloseEvent*);

};
