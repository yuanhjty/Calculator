#ifndef CALCWIDGET_H
#define CALCWIDGET_H


#include "../Calculator/CommandInterpreter.h"

#include <string>
#include <utility>
#include <QWidget>

namespace Ui {
class CalcWidget;
}

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWidget(QWidget *parent = 0);
    ~CalcWidget();

private slots:
    // special slots
    void on_pushButtonMenu_released();
    void on_pushButtonHistory_released();
    void on_pushButtonClearHistory_released();

    void on_pushButtonCmdRst_released();
    void on_pushButtonCmdDel_released();

    void on_pushButtonAlphaE_released();
    void on_pushButtonDot_released();

    void on_pushButtonOpUMinus_released();
    void on_pushButtonOpAssign_released();

    void on_pushButtonFSqrt_released();
    void on_pushButtonFSquare_released();

    // universal slots
    void digitButtonReleased();
    void otherButtonReleased();

private:
    // tool methods
    void processDigits(QChar digit);
    void processOthers(QString&& symbol);

    bool isNumberToken(const QString& token);
    void highlightExpr();
    void highlightAns();

private:
    Ui::CalcWidget *ui;
    CommandInterpreter *interpreter;
    std::deque<Calculator::Result_Type> *history;
    QStringList input;
};

#endif // CALCWIDGET_H
