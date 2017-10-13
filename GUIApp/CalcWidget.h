#ifndef CALCWIDGET_H
#define CALCWIDGET_H


#include "../Calculator/CommandInterpreter.h"
#include "HistoryShower.h"

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

private:
    // eventFilter
//    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    // special slots
    void on_pushButtonHistory_released();
    void on_pushButtonMenu_released();

    void on_pushButtonCmdRst_released();
    void on_pushButtonCmdDel_released();

    void on_pushButtonAlphaE_released();
    void on_pushButtonDot_released();
    void on_pushButtonOpUMinus_released();

    void on_pushButtonFSqrt_released();
    void on_pushButtonFSquare_released();

    void on_pushButtonOpAssign_released();

    // universal slots
    void digitButtonReleased();
    void otherButtonReleased();

    // to process signals from historyShower
    void activateMainWidget();
    void deleteHistory();

private:
    // tool methods
    bool isNumberToken(const QString& token);

    void processDigits(QChar digit);
    void processOthers(QString&& symbol);

    void setStrongExpr();
    void setStrongAns();

private:
    Ui::CalcWidget *ui;
    HistoryShower *historyShower;

    CommandInterpreter *interpreter;
    std::deque<Calculator::Result_Type> *history;
    QStringList input;
};

#endif // CALCWIDGET_H
