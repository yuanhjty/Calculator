#include "CalcWidget.h"
#include "ui_CalcWidget.h"

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget)
{
    ui->setupUi(this);

    setWindowTitle("Calculator");
    resize(400, 600);

//    ui->pushButtonMenu->setStyleSheet(
//                "background-image: url(:/images/calcApp-icon);"
//                );
}


CalcWidget::~CalcWidget()
{
    delete ui;
}

void CalcWidget::updateResult()
{
    result = interpreter.getResult();
    expr = QString(result.first.c_str());

    ui->labelScreenExpr->setText(expr);
    ui->labelScreenAns->setText(QString(result.second.c_str()));
}

void CalcWidget::processDigit(const std::string& digit)
{
    input.append(digit);
    if (interpreter.interpret(input) != E_OPERAND_MISSING)
        updateResult();
    else
        input.pop_back();
}

void CalcWidget::processNonPostfixOperator(const std::string& operatr)
{
    if (' ' != input.back())
        input.append(" ");
    input.append(operatr + " ");

    if (expr.endsWith(QChar(' ')))
        expr.append(" ");
    expr.append(operatr.c_str());
    expr.append(" ");
}

void CalcWidget::processPostfixOperator(const std::string& operatr) {
    if (' ' != input.back())
        input.append(1, ' ');
    input.append(operatr + ' ');
}

void CalcWidget::processFunction(const std::string &function)
{

}


void CalcWidget::processVariable(const std::string &symbol)
{

}


// slots
void CalcWidget::on_pushButtonD1_released()
{
    processDigit("1");
}

void CalcWidget::on_pushButtonD2_released()
{
    processDigit("2");
}
