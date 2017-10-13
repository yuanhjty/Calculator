#include "CalcWidget.h"
#include "ui_CalcWidget.h"
#include "ui_HistoryShower.h"

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget),
    historyShower(new HistoryShower),
    interpreter(new CommandInterpreter)
{
    ui->setupUi(this);

    setWindowTitle("Calculator");

    historyShower->setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // label text auto linefeed
    ui->labelScreenExpr->setWordWrap(true);

    // digit buttons event
    connect(ui->pushButtonD0, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD1, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD2, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD3, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD4, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD5, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD6, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD7, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD8, &CalcButton::released, this, &CalcWidget::digitButtonReleased);
    connect(ui->pushButtonD9, &CalcButton::released, this, &CalcWidget::digitButtonReleased);

    // other buttons event
    connect(ui->pushButtonOpPlus, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonOpBMinus, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonOpMulti, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonOpDivide, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonOpMod, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonOpPow, &CalcButton::released, this, &CalcWidget::otherButtonReleased);

    connect(ui->pushButtonFSin, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFCos, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFTan, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFAsin, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFAcos, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFAtan, &CalcButton::released, this, &CalcWidget::otherButtonReleased);

    connect(ui->pushButtonFLg, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonFLn, &CalcButton::released, this, &CalcWidget::otherButtonReleased);

    connect(ui->pushButtonBracketL, &CalcButton::released, this, &CalcWidget::otherButtonReleased);
    connect(ui->pushButtonBracketR, &CalcButton::released, this, &CalcWidget::otherButtonReleased);

    connect(ui->pushButtonConstPi, &CalcButton::released, this, &CalcWidget::otherButtonReleased);

    // signals from hisoryShower
    connect(historyShower, &HistoryShower::activateMainWidget, this, &CalcWidget::activateMainWidget);
    connect(historyShower, &HistoryShower::deleteHistory, this, &CalcWidget::deleteHistory);
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


// universal slots
void CalcWidget::digitButtonReleased()
{
    CalcButton *button = (CalcButton*)sender();
    processDigits(button->text().at(0));
}

void CalcWidget::otherButtonReleased()
{
    CalcButton *button = (CalcButton*)sender();
    processOthers(button->text());
}

void CalcWidget::activateMainWidget()
{
    ui->groupBoxMain->setEnabled(true);
}

void CalcWidget::deleteHistory()
{
    history->clear();
}

// special slots
void CalcWidget::on_pushButtonCmdRst_released()
{
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

void CalcWidget::on_pushButtonAlphaE_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('e');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("e");
}

void CalcWidget::on_pushButtonDot_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('.');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("0.");
}

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

void CalcWidget::on_pushButtonOpUMinus_released()
{
    if (!input.isEmpty()) {
        QString& token = input.back();
        if (isNumberToken(token)) {
            input.back().append('-');
            ui->labelScreenExpr->setText(input.join(' '));
        } else
            processOthers("-");
    } else
        processOthers("-");
}

void CalcWidget::on_pushButtonFSqrt_released()
{
    processOthers("sqrt");
}

void CalcWidget::on_pushButtonFSquare_released()
{
    processOthers("^ 2");
}

void CalcWidget::on_pushButtonHistory_released()
{
    // Get current geometry of main window and reference widget.
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    QRect mainRect = this->geometry();
    QRect refeRect = ui->groupBoxKeys->geometry();

    // Disable main widget
    ui->groupBoxMain->setEnabled(false);

    // Set geometry for historyShower and show the widget
    historyShower->setGeometry(mainRect.x() + refeRect.x(), mainRect.y() + refeRect.y(),
                               mainRect.width() - refeRect.x(), mainRect.height() - refeRect.y());
    historyShower->show();

    //  Print history record in historyShower.
    history = interpreter->getHistory();
    historyShower->printHistory(history);
}

void CalcWidget::on_pushButtonMenu_released()
{

}
