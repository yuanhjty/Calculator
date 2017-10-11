#include "CalcWidget.h"
#include "ui_CalcWidget.h"

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget),
    interpreter(new CommandInterpreter),
    history(interpreter->getHistory())
{
    ui->setupUi(this);

    setWindowTitle("Calculator");
    resize(400, 600);

    ui->labelScreenExpr->setWordWrap(true);
}


CalcWidget::~CalcWidget()
{
    delete ui;
    delete interpreter;
}


bool CalcWidget::isNumberToken(const QString &token)
{
    if (token[0].isNumber())
        return true;
    return false;
}

void CalcWidget::processDigits(QChar digit)
{
    setStrongExpr();

    if (input.isEmpty() || !isNumberToken(input.back()))
        input.append(digit);
    else
    {
        QString& token = input.back();
        if (1 == token.size() && '0' == token[0])
            token[0] = digit;
        else
            token.append(digit);
    }

    ui->labelScreenExpr->setText(input.join(' '));
    ui->labelScreenAns->setText("0");
}

void CalcWidget::processOthers(QString &&symbol) {
    setStrongExpr();

    input.append(symbol);
    ui->labelScreenExpr->setText(input.join(' '));
    ui->labelScreenAns->setText("0");
}

void CalcWidget::setStrongExpr()
{
    QFont exprFont = ui->labelScreenExpr->font();
    exprFont.setPointSize(18);
    ui->labelScreenExpr->setFont(exprFont);

    QFont ansFont = ui->labelScreenAns->font();
    ansFont.setPointSize(14);
    ui->labelScreenAns->setFont(ansFont);
}

void CalcWidget::setStrongAns()
{
    QFont exprFont = ui->labelScreenExpr->font();
    exprFont.setPointSize(14);
    ui->labelScreenExpr->setFont(exprFont);

    QFont ansFont = ui->labelScreenAns->font();
    ansFont.setPointSize(20);
    ui->labelScreenAns->setFont(ansFont);
}


// slots
// commands
void CalcWidget::on_pushButtonCmdRst_released()
{
    interpreter->interpret("reset");
    input.clear();
    ui->labelScreenExpr->setText("");
    ui->labelScreenAns->setText("0");
}

void CalcWidget::on_pushButtonCmdDel_released()
{
    if (!input.isEmpty()) {
        QString& token = input.back();
        if (isNumberToken(token)) {
            token.remove(token.size() - 1, 1);
            if (token.isEmpty())
                input.pop_back();
        } else
            input.pop_back();

        ui->labelScreenExpr->setText(input.join(' '));
        ui->labelScreenAns->setText("0");
    }
}

// brackets
void CalcWidget::on_pushButtonBracketL_released()
{
    processOthers("(");
}

void CalcWidget::on_pushButtonBracketR_released()
{
    processOthers(")");
}

// alphabet 'e'
void CalcWidget::on_pushButtonAlphaE_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('e');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("e");
}


// constant symbols
void CalcWidget::on_pushButtonConstPi_released()
{
    processOthers("pi");
}


// digits
void CalcWidget::on_pushButtonD1_released()
{
    processDigits('1');
}

void CalcWidget::on_pushButtonD2_released()
{
    processDigits('2');
}

void CalcWidget::on_pushButtonD3_released()
{
    processDigits('3');
}

void CalcWidget::on_pushButtonD4_released()
{
    processDigits('4');
}

void CalcWidget::on_pushButtonD5_released()
{
    processDigits('5');
}

void CalcWidget::on_pushButtonD6_released()
{
    processDigits('6');
}

void CalcWidget::on_pushButtonD7_released()
{
    processDigits('7');
}

void CalcWidget::on_pushButtonD8_released()
{
    processDigits('8');
}

void CalcWidget::on_pushButtonD9_released()
{
    processDigits('9');
}

void CalcWidget::on_pushButtonD0_released()
{
    processDigits('0');
}

void CalcWidget::on_pushButtonDot_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('.');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("0.");
}


// operators
void CalcWidget::on_pushButtonOpAssign_released()
{
    if (!input.isEmpty()) {
        interpreter->interpret(input.join(' ').toStdString());
        interpreter->interpret("complete");
        input.clear();
    }

    setStrongAns();

    ui->labelScreenExpr->setText(interpreter->getResult().first.c_str());
    ui->labelScreenAns->setText(interpreter->getResult().second.c_str());
}

void CalcWidget::on_pushButtonOpPlus_released()
{
    processOthers("+");
}

void CalcWidget::on_pushButtonOpBMinus_released()
{
    processOthers("-");
}

void CalcWidget::on_pushButtonOpUMinus_released()
{
    if (!input.isEmpty()) {
        QString& token = input.back();
        if (isNumberToken(token)) {
            input.back().append('-');
            ui->labelScreenExpr->setText(input.join(' '));
        }
    } else
        processOthers("-");
}

void CalcWidget::on_pushButtonOpMulti_released()
{
    processOthers("*");
}

void CalcWidget::on_pushButtonOpDivide_released()
{
    processOthers("/");
}

void CalcWidget::on_pushButtonOpMod_released()
{
    processOthers("%");
}

void CalcWidget::on_pushButtonOpPow_released()
{
    processOthers("^");
}


// functions
void CalcWidget::on_pushButtonFSin_released()
{
    processOthers("sin");
}

void CalcWidget::on_pushButtonFCos_released()
{
    processOthers("cos");
}

void CalcWidget::on_pushButtonFTan_released()
{
    processOthers("tan");
}

void CalcWidget::on_pushButtonFAsin_released()
{
    processOthers("asin");
}

void CalcWidget::on_pushButtonFAcos_released()
{
    processOthers("acos");
}

void CalcWidget::on_pushButtonFAtan_released()
{
    processOthers("atan");
}

void CalcWidget::on_pushButtonFLg_released()
{
    processOthers("lg");
}

void CalcWidget::on_pushButtonFLn_released()
{
    processOthers("ln");
}

void CalcWidget::on_pushButtonFSqrt_released()
{
    processOthers("sqrt");
}

void CalcWidget::on_pushButtonFSquare_released()
{
    processOthers("^ 2");
}
