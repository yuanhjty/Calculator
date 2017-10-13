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

    // Let label text auto linefeed.
    ui->labelScreenExpr->setWordWrap(true);

    // Show normal window (not history record window) at begin.
    ui->stackedWidget->setCurrentIndex(0);

    // Digit buttons event, universal slots.
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

    // Other buttons event, universal slots.
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
}


CalcWidget::~CalcWidget()
{
    delete ui;
    delete interpreter;
}


// special slots
// Menu
void CalcWidget::on_pushButtonMenu_released()
{

}

// History
void CalcWidget::on_pushButtonHistory_released()
{
    int currIndex = ui->stackedWidget->currentIndex();
    if (0 == currIndex) {
        // Set history text.
        std::string text;
        for (size_t i = 0, size = history->size(); i < size; ++i)
            text.append("<p>" + (*history)[size - 1 - i].first + " =</p><h><font size=\"4\">"
                    + (*history)[size - 1 - i].second + "</font></h>");
        ui->labelHistory->setText(text.c_str());

        // Switch to history window
        ui->stackedWidget->setCurrentIndex(1);

        ui->pushButtonMenu->setEnabled(false);
        ui->labelScreenAns->setEnabled(false);
        ui->labelScreenExpr->setEnabled(false);
    } else {
        // Switch back to normal window
        ui->stackedWidget->setCurrentIndex(0);

        ui->pushButtonMenu->setEnabled(true);
        ui->labelScreenAns->setEnabled(true);
        ui->labelScreenExpr->setEnabled(true);
    }
}

// ClearHistory
void CalcWidget::on_pushButtonClearHistory_released()
{
    history->clear();
    ui->labelHistory->setText("");
}

// CmdRst
void CalcWidget::on_pushButtonCmdRst_released()
{
    input.clear();
    ui->labelScreenExpr->setText("");
    ui->labelScreenAns->setText("0");
}

// CmdDel
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

// AlphaE
void CalcWidget::on_pushButtonAlphaE_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('e');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("e");
}

// Dot
void CalcWidget::on_pushButtonDot_released()
{
    if (!input.isEmpty() && isNumberToken(input.back())) {
        input.back().append('.');
        ui->labelScreenExpr->setText(input.join(' '));
    } else
        processOthers("0.");
}

// OpUminus
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

// OpAssign
void CalcWidget::on_pushButtonOpAssign_released()
{
    if (!input.isEmpty()) {
        interpreter->interpret(input.join(' ').toStdString());
        interpreter->interpret("complete");
        input.clear();
    }

    highlightAns();

    ui->labelScreenExpr->setText(interpreter->getResult().first.c_str());
    ui->labelScreenAns->setText(interpreter->getResult().second.c_str());
}

// FSqrt
void CalcWidget::on_pushButtonFSqrt_released()
{
    processOthers("sqrt");
}

// FSquare
void CalcWidget::on_pushButtonFSquare_released()
{
    processOthers("^ 2");
}


// universal slots
// digitButton
void CalcWidget::digitButtonReleased()
{
    CalcButton *button = (CalcButton*)sender();
    processDigits(button->text().at(0));
}

// otherButton
void CalcWidget::otherButtonReleased()
{
    CalcButton *button = (CalcButton*)sender();
    processOthers(button->text());
}


// tool methods
// processDigits
void CalcWidget::processDigits(QChar digit)
{
    highlightExpr();

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

// processOthers
void CalcWidget::processOthers(QString &&symbol) {
    highlightExpr();

    input.append(symbol);
    ui->labelScreenExpr->setText(input.join(' '));
    ui->labelScreenAns->setText("0");
}

// isNumberToken
bool CalcWidget::isNumberToken(const QString &token)
{
    if (token[0].isNumber())
        return true;
    return false;
}

// highlightExpr
void CalcWidget::highlightExpr()
{
    QFont exprFont = ui->labelScreenExpr->font();
    exprFont.setPointSize(18);
    ui->labelScreenExpr->setFont(exprFont);

    QFont ansFont = ui->labelScreenAns->font();
    ansFont.setPointSize(14);
    ui->labelScreenAns->setFont(ansFont);
}

// highlightAns
void CalcWidget::highlightAns()
{
    QFont exprFont = ui->labelScreenExpr->font();
    exprFont.setPointSize(14);
    ui->labelScreenExpr->setFont(exprFont);

    QFont ansFont = ui->labelScreenAns->font();
    ansFont.setPointSize(20);
    ui->labelScreenAns->setFont(ansFont);
}
