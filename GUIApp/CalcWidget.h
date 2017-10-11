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
    // brackets
    void on_pushButtonBracketL_released();
    void on_pushButtonBracketR_released();

    // commands
    void on_pushButtonCmdRst_released();
    void on_pushButtonCmdDel_released();


    // constant symbols
    void on_pushButtonAlphaE_released();


    // constant symbols
    void on_pushButtonConstPi_released();

    // digits
    void on_pushButtonD1_released();
    void on_pushButtonD2_released();
    void on_pushButtonD3_released();
    void on_pushButtonD4_released();
    void on_pushButtonD5_released();
    void on_pushButtonD6_released();
    void on_pushButtonD7_released();
    void on_pushButtonD8_released();
    void on_pushButtonD9_released();
    void on_pushButtonD0_released();
    void on_pushButtonDot_released();

    // operators
    void on_pushButtonOpAssign_released();
    void on_pushButtonOpPlus_released();
    void on_pushButtonOpBMinus_released();
    void on_pushButtonOpUMinus_released();
    void on_pushButtonOpMulti_released();
    void on_pushButtonOpDivide_released();
    void on_pushButtonOpMod_released();
    void on_pushButtonOpPow_released();

    // functions
    void on_pushButtonFSin_released();
    void on_pushButtonFCos_released();
    void on_pushButtonFTan_released();
    void on_pushButtonFAsin_released();
    void on_pushButtonFAcos_released();
    void on_pushButtonFAtan_released();
    void on_pushButtonFLg_released();
    void on_pushButtonFLn_released();
    void on_pushButtonFSqrt_released();
    void on_pushButtonFSquare_released();

private:
    Ui::CalcWidget *ui;

    CommandInterpreter* interpreter;
    const std::deque<Calculator::Result_Type>* history;
    QStringList input;

private:
    bool isNumberToken(const QString& token);

    void processDigits(QChar digit);
    void processOthers(QString&& symbol);

    void setStrongExpr();
    void setStrongAns();
};

#endif // CALCWIDGET_H
