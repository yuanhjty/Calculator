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
    void on_pushButtonD1_released();

    void on_pushButtonD2_released();

private:
    Ui::CalcWidget *ui;

private:
    CommandInterpreter interpreter;
    std::string input;
    std::pair<std::string, std::string> result;
    QString expr;
    QString ans;

    void updateResult();
    void processDigit(const std::string& digit);
    void processNonPostfixOperator(const std::string& operatr);
    void processPostfixOperator(const std::string& operatr);
    void processFunction(const std::string& function);
    void processVariable(const std::string& symbol);
};

#endif // CALCWIDGET_H
