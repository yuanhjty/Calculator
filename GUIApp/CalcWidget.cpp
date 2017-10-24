#include "CalcWidget.h"
#include "ui_CalcWidget.h"

#include <QComboBox>

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget),
    interpreter(new Interpreter),
    countMethodGroup(new QButtonGroup(this)),
    angleUnitGroup(new QButtonGroup(this)),
    numberBaseGroup(new QButtonGroup(this)),
    countMethodCmds({"default", "fixed", "scientific"}),
    angleUnitCmds({"degree", "radian"}),
    numberBaseCmds({"binary", "octal", "decimal", "hex"}),
    screenLargeFont("Courier", 16),
    screenSmallFont("Courier", 12),
    screenInComputeMode(false),
    curCalcType(CALC_SCI),
    calcTypeCmds({"science", "programmer"}),
    initScreens({&CalcWidget::initSciScreen, &CalcWidget::initProgScreen}),
    updateScreens({&CalcWidget::updateSciScreen, &CalcWidget::updateProgScreen}),
    updateAnss({&CalcWidget::updateSciAns, &CalcWidget::updateProgAns}),
    numRgx("\\d+(\\.\\d*)?(e[\\+\\-]?\\d*)?|[0-9A-F]+"),
    sciHst(interpreter->history())
{
    ui->setupUi(this);
    progAnsLabels = {ui->labelProgAnsBin, ui->labelProgAnsOct,
                     ui->labelProgAnsDec, ui->labelProgAnsHex};
    exprLabels = {ui->labelSciExpr, ui->labelProgExpr};
    ansLabels = {ui->labelSciAns, ui->labelProgAns};

    initWidgetStyles();
    initSciNumNotation();
    initSciAglUnits();
    initProgNumBases();
    initConverter();
    installEventFilters();
    connectSignalsAndSlots();

    ui->stackedWidgetCalc->setCurrentIndex(curCalcType);
    ui->stackedWidgetSciKeyBrdAndHst->setCurrentIndex(HST_CLOSE);
    ansLabels[curCalcType]->setFont(screenLargeFont);
}

CalcWidget::~CalcWidget()
{
    delete ui;
    delete interpreter;
    delete angleUnitGroup;
    delete countMethodGroup;
    delete numberBaseGroup;
}


/**Initialize*****************************************************************/
void CalcWidget::initWidgetStyles()
{
    labelCommonStyleSheet = "";

    labelCheckedStyleSheet =
        "color: rgb(18, 150, 219);"
        "font-weight: bold;";

    pushButtonCommonStyleSheet =
        "QPushButton {"
            "border: 0px;"
            "background-color: rgb(240, 240, 240);"
        "}"

        "QPushButton:hover {"
            "border: 0px;"
            "background-color: rgb(220, 220, 220);"
        "}"

        "QPushButton:pressed {"
            "border: 0px;"
            "background-color: rgb(200, 200, 200);"
        "}";

    pushButtonCheckedStyleSheet =
        "border: 0px;"
        "background-color: white; "
        "color: rgb(18, 150, 219);"
        "font-weight: bold;";

    setStyleSheet(
                "CalcWidget {"
                    "border: 0px;"
                "}"

                "QGroupBox {"
                    "border: 0px;"
                    "background-color: rgb(255, 255, 255);"
                "}"
                "#groupBoxSciKeyBrdAndHst, #groupBoxSciHstMenu {"
                    "border: 0px;"
                    "background-color: rgb(240, 240, 240);"
                "}"

                "QComboBox {"
                    "border: 0px;"
                    "padding: 0px 10px 0px 10px;"
                    "color: rgb(18, 150, 219);"
                "}"
                "QComboBox::drop-down {"
                    "subcontrol-origin: padding;"
                    "border: 0px;"
                "}"
                "QComboBox::drop-down:hover {"
                    "border: 0px;"
                    "top: 2px;"
                "}"
                "QComboBox::drop-down:pressed {"
                    "border: 0px;"
                    "top: 4px;"
                "}"
                "QComboBox::down-arrow {"
                    "border: 0px;"
                    "border-image: url(:/images/down-arrow);"
                "}"

                + pushButtonCommonStyleSheet +

                "#pushButtonSciMenu, #pushButtonSciHst, "
                "#pushButtonCnvMenu, #pushButtonProgMenu {"
                    "border: 0px;"
                    "background-color: rgb(255, 255, 255);"
                "}"
                "#pushButtonSciMenu:hover, #pushButtonSciHst:hover, "
                "#pushButtonCnvMenu:hover, #pushButtonProgMenu:hover {"
                    "border: 0px;"
                    "background-color: rgb(220, 220, 220);"
                "}"
                "#pushButtonSciMenu:pressed, #pushButtonSciHst:pressed, "
                "#pushButtonCnvMenu:pressed, #pushButtonProgMenu:pressed {"
                    "border: 0px;"
                    "background-color: rgb(200, 200, 200);"
                "}"
                );
}

void CalcWidget::initSciNumNotation()
{
    ui->pushButtonSciNoteDFLT->setCheckable(true);
    ui->pushButtonSciNoteDFLT->setChecked(false);
    ui->pushButtonSciNoteFIX->setCheckable(true);
    ui->pushButtonSciNoteFIX->setChecked(false);
    ui->pushButtonSciNoteSCI->setCheckable(true);
    ui->pushButtonSciNoteSCI->setChecked(false);

    countMethodGroup->addButton(ui->pushButtonSciNoteDFLT, DLFLT);
    countMethodGroup->addButton(ui->pushButtonSciNoteFIX, FIX);
    countMethodGroup->addButton(ui->pushButtonSciNoteSCI, SCI);

    countMethodGroup->button(DLFLT)->setChecked(true);
    countMethodGroup->button(DLFLT)->setStyleSheet(pushButtonCheckedStyleSheet);
}

void CalcWidget::initSciAglUnits()
{
    ui->pushButtonSciAglDeg->setCheckable(true);
    ui->pushButtonSciAglDeg->setChecked(false);
    ui->pushButtonSciAglRad->setCheckable(true);
    ui->pushButtonSciAglRad->setChecked(false);

    angleUnitGroup->addButton(ui->pushButtonSciAglDeg, DEG);
    angleUnitGroup->addButton(ui->pushButtonSciAglRad, RAD);

    angleUnitGroup->button(RAD)->setChecked(true);
    angleUnitGroup->button(RAD)->setStyleSheet(pushButtonCheckedStyleSheet);
}

void CalcWidget::initProgNumBases()
{
    ui->pushButtonProgBin->setCheckable(true);
    ui->pushButtonProgBin->setChecked(false);
    ui->pushButtonProgOct->setCheckable(true);
    ui->pushButtonProgOct->setChecked(false);
    ui->pushButtonProgDec->setCheckable(true);
    ui->pushButtonProgDec->setChecked(false);
    ui->pushButtonProgHex->setCheckable(true);
    ui->pushButtonProgHex->setChecked(false);

    numberBaseGroup->addButton(ui->pushButtonProgBin, BIN);
    numberBaseGroup->addButton(ui->pushButtonProgOct, OCT);
    numberBaseGroup->addButton(ui->pushButtonProgDec, DEC);
    numberBaseGroup->addButton(ui->pushButtonProgHex, HEX);

    numberBaseGroup->button(DEC)->setChecked(true);
    numberBaseGroup->button(DEC)->setStyleSheet(pushButtonCheckedStyleSheet);
    progAnsLabels[DEC]->setStyleSheet(labelCheckedStyleSheet);
    setProgDecKeyBrd();
}

void CalcWidget::initConverter()
{
    cnvUnderlyingUnits = {
        {"m", "nm", "um", "mm", "cm", "km", "in", "ft", "yd", "mile", "sea-mile"},
        {"sq-m", "sq-mm", "sq-cm", "sq-km", "sq-in", "sq-ft", "sq-yd", "sq-mile", "ha", "acre"},
        {"cu-m", "cu-cm", "cu-in", "cu-ft", "cu-yd", "mL", "L", "uk-pt",  "us-pt",
         "uk-qt",  "us-qt",  "uk-gal",  "us-gal",  "uk-fl-oz",  "us-fl-oz"},
        {"g", "ct", "mg", "cg", "kg", "t", "oz", "lb"},
        {"s", "us", "ms", "min", "h", "d", "w", "y"},
        {"m-s", "cm-s", "in-s", "km-h", "ft-h", "knot", "Mach"},
        {"J", "KJ", "cal"},
        {"W", "KW", "hp"},
        {"Pa", "atmos", "bar", "kPa", "mmHg"},
        {"rad", "deg"},
        {"bit", "B", "Kb", "Kib", "KB", "KiB", "Mb", "Mib", "MB", "MiB", "Gb", "Gib", "GB", "GiB",
         "Tb", "Tib", "TB", "TiB", "Pb", "Pib", "PB", "PiB", "Eb", "Eib", "EB", "EiB",
         "Zb", "Zib", "ZB", "ZiB", "Yb", "Yib", "YB", "YiB"}
    };

    cnvSkinUnits = {
        {"m", "nm", "µm", "mm", "cm", "km", "in", "ft", "yd", "mile", "sea mile"},
        {"m²", "mm²", "cm²", "km²", "in²", "ft²", "yd²", "mile²", "ha", "acre"},
        {"m³", "cm³", "in³", "ft³", "yd³", "mL", "L", "pt(UK)", "pt(US)",
         "qt(UK)", "qt(US)", "gal(UK)", "gal(US)", "fl.oz(UK)", "fl.oz(US)"},
        {"g", "ct", "mg", "cg", "kg", "t", "oz", "lb"},
        {"s", "µs", "ms", "min", "h", "day", "week", "year"},
        {"m/s", "cm/s", "in/s", "km/h", "ft/h", "knot", "Mach"},
        {"J", "KJ", "cal"},
        {"W", "KW", "hp"},
        {"Pa", "atmos", "bar", "kPa", "mmHg"},
        {"RAD", "DEG"},
        {"bit", "B", "Kb", "Kib", "KB", "KiB", "Mb", "Mib", "MB", "MiB", "Gb", "Gib", "GB", "GiB",
         "Tb", "Tib", "TB", "TiB", "Pb", "Pib", "PB", "PiB", "Eb", "Eib", "EB", "EiB",
         "Zb", "Zib", "ZB", "ZiB", "Yb", "Yib", "YB", "YiB"}
    };

    cnvTypes = QStringList({"LENGTH", "AREA", "VOLUME", "WEIGHT", "TIME", "VELOCITY",
                    "ENERGY", "POWER", "PRESSURE", "ANGLE", "DATA"});

    cnvCmds = {"length", "area", "volume", "weight", "time", "velocity",
                   "energy", "power", "pressure", "angle", "data"};

    cnvExpr = QStringList({"0", "", "to", ""});
}

bool CalcWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (ui->stackedWidgetSciKeyBrdAndHst->currentIndex() == HST_OPEN
            && event->type() == QEvent::MouseButtonRelease) {
        ui->pushButtonSciMenu->setEnabled(true);
        ui->pushButtonSciHst->setEnabled(true);
        ui->stackedWidgetSciKeyBrdAndHst->setCurrentIndex(HST_CLOSE);
        return true;
    } else {
        return QObject::eventFilter(watched, event);
    }
}

void CalcWidget::installEventFilters()
{
    ui->pushButtonSciMenu->installEventFilter(this);
    ui->labelSciType->installEventFilter(this);
    ui->pushButtonSciHst->installEventFilter(this);
    ui->labelSciExpr->installEventFilter(this);
    ui->labelSciAns->installEventFilter(this);
}

void CalcWidget::connectSignalsAndSlots()
{
    connect(ui->pushButtonSciMenu, &QPushButton::clicked, this, &CalcWidget::openCalcMenu);
    connect(ui->pushButtonCnvMenu, &QPushButton::clicked, this, &CalcWidget::openCalcMenu);
    connect(ui->pushButtonProgMenu, &QPushButton::clicked, this, &CalcWidget::openCalcMenu);

    void (QButtonGroup::*btnGrpToggledSignal)(int, bool) = &QButtonGroup::buttonToggled;
    connect(angleUnitGroup, btnGrpToggledSignal, this, &CalcWidget::toggleAngleUnit);
    connect(countMethodGroup, btnGrpToggledSignal, this, &CalcWidget::toggleCountMethod);
    connect(numberBaseGroup, btnGrpToggledSignal, this, &CalcWidget::toggleNumberBase);

    connect(ui->pushButtonSciCmdDel, &QPushButton::clicked, this, &CalcWidget::procExprCmdDel);
    connect(ui->pushButtonSciCmdClr, &QPushButton::clicked, this, &CalcWidget::procExprCmdClr);

    connect(ui->pushButtonProgCmdDel, &QPushButton::clicked, this, &CalcWidget::procExprCmdDel);
    connect(ui->pushButtonProgCmdClr, &QPushButton::clicked, this, &CalcWidget::procExprCmdClr);

    connect(ui->pushButtonSciOprAsgn, &QPushButton::clicked, this, &CalcWidget::procExprOprAsgn);
    connect(ui->pushButtonSciOprPlus, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciOprBMinus, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciOprMulti, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciOprDivide, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciOprMod, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciOprPow, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnSin, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnCos, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnTan, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnAsin, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnAcos, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnAtan, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnLg, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciFcnLn, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciBrktL, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonSciBrktR, &QPushButton::clicked, this, &CalcWidget::procExprOprs);

    connect(ui->pushButtonProgOprAsgn, &QPushButton::clicked, this, &CalcWidget::procExprOprAsgn);
    connect(ui->pushButtonProgOprPlus, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprBMinus, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprUMinus, &QPushButton::clicked, this, &CalcWidget::procExprOprUMinus);
    connect(ui->pushButtonProgOprMulti, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprDivide, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprMod, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprAnd, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprOr, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprXor, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprNot, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprLsh, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgOprRsh, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgBrktL, &QPushButton::clicked, this, &CalcWidget::procExprOprs);
    connect(ui->pushButtonProgBrktR, &QPushButton::clicked, this, &CalcWidget::procExprOprs);

    connect(ui->pushButtonSciDgt0, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt1, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt2, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt3, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt4, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt5, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt6, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt7, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt8, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonSciDgt9, &QPushButton::clicked, this, &CalcWidget::procExprDgts);

    connect(ui->pushButtonProgDgt0, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt1, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt2, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt3, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt4, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt5, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt6, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt7, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt8, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgt9, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtA, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtB, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtC, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtD, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtE, &QPushButton::clicked, this, &CalcWidget::procExprDgts);
    connect(ui->pushButtonProgDgtF, &QPushButton::clicked, this, &CalcWidget::procExprDgts);

    connect(ui->pushButtonCnvDgt0, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt1, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt2, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt3, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt4, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt5, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt6, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt7, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt8, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
    connect(ui->pushButtonCnvDgt9, &QPushButton::clicked, this, &CalcWidget::procCnvDgts);
}
/*****************************************************************************/

/**Process unrepairable error*************************************************/
void CalcWidget::procError()
{
    screenToDisplayMode();
    exprLabels[curCalcType]->setText(expr.join(' '));
    ansLabels[curCalcType]->setText(interpreter->result().second.c_str());
    expr.clear();
    if (CALC_PROG == curCalcType) {
        ui->labelProgAnsBin->setText("0");
        ui->labelProgAnsOct->setText("0");
        ui->labelProgAnsDec->setText("0");
        ui->labelProgAnsHex->setText("0");
    }
}
/*****************************************************************************/

/**Update screen**************************************************************/
void CalcWidget::initSciScreen() {
    ui->labelSciExpr->setText("");
    ui->labelSciAns->setText("0");
}

void CalcWidget::initProgScreen() {
    ui->labelProgExpr->setText("");
    ui->labelProgAns->setText("0");
    ui->labelProgAnsBin->setText("0");
    ui->labelProgAnsOct->setText("0");
    ui->labelProgAnsDec->setText("0");
    ui->labelProgAnsHex->setText("0");
}

void CalcWidget::updateSciScreen()
{
    ui->labelSciExpr->setText(interpreter->result().first.c_str());
    ui->labelSciAns->setText(interpreter->result().second.c_str());
}

void CalcWidget::updateProgScreen()
{
    ui->labelProgExpr->setText(interpreter->result().first.c_str());
    ui->labelProgAns->setText(interpreter->result().second.c_str());
    updateProgMultAns();
}

void CalcWidget::updateSciAns()
{
    ui->labelSciAns->setText(interpreter->result().second.c_str());
}

void CalcWidget::updateProgAns()
{
    ui->labelProgAns->setText(interpreter->result().second.c_str());
    updateProgMultAns();
}

void CalcWidget::updateProgMultAns()
{
    Calculator::ValueType value = interpreter->value();
    ui->labelProgAnsBin->setText(NumeralConverter::valueTobinaryString(value).c_str());
    ui->labelProgAnsOct->setText(NumeralConverter::valueToOctalString(value).c_str());
    ui->labelProgAnsDec->setText(NumeralConverter::valueToDecimalString(value).c_str());
    ui->labelProgAnsHex->setText(NumeralConverter::valueToHexString(value).c_str());
}

void CalcWidget::updateCnvScreen()
{
    ui->labelCnvExpr->setText(cnvExpr.at(0));
    ui->labelCnvAns->setText(interpreter->result().second.c_str());
}

void CalcWidget::screenToComputeMode()
{
    screenInComputeMode = true;
    exprLabels[curCalcType]->setFont(screenLargeFont);
    ansLabels[curCalcType]->setFont(screenSmallFont);
}

void CalcWidget::screenToDisplayMode()
{
    screenInComputeMode = false;
    exprLabels[curCalcType]->setFont(screenSmallFont);
    ansLabels[curCalcType]->setFont(screenLargeFont);
}
/*****************************************************************************/


/**Set programmer calculator's keyboard***************************************/
void CalcWidget::setProgBinKeyBrd()
{
    ui->pushButtonProgDgt2->setEnabled(false);
    ui->pushButtonProgDgt3->setEnabled(false);
    ui->pushButtonProgDgt4->setEnabled(false);
    ui->pushButtonProgDgt5->setEnabled(false);
    ui->pushButtonProgDgt6->setEnabled(false);
    ui->pushButtonProgDgt7->setEnabled(false);
    ui->pushButtonProgDgt8->setEnabled(false);
    ui->pushButtonProgDgt9->setEnabled(false);
    ui->pushButtonProgDgtA->setEnabled(false);
    ui->pushButtonProgDgtB->setEnabled(false);
    ui->pushButtonProgDgtC->setEnabled(false);
    ui->pushButtonProgDgtD->setEnabled(false);
    ui->pushButtonProgDgtE->setEnabled(false);
    ui->pushButtonProgDgtF->setEnabled(false);
}

void CalcWidget::setProgOctKeyBrd()
{
    ui->pushButtonProgDgt2->setEnabled(true);
    ui->pushButtonProgDgt3->setEnabled(true);
    ui->pushButtonProgDgt4->setEnabled(true);
    ui->pushButtonProgDgt5->setEnabled(true);
    ui->pushButtonProgDgt6->setEnabled(true);
    ui->pushButtonProgDgt7->setEnabled(true);
    ui->pushButtonProgDgt8->setEnabled(false);
    ui->pushButtonProgDgt9->setEnabled(false);
    ui->pushButtonProgDgtA->setEnabled(false);
    ui->pushButtonProgDgtB->setEnabled(false);
    ui->pushButtonProgDgtC->setEnabled(false);
    ui->pushButtonProgDgtD->setEnabled(false);
    ui->pushButtonProgDgtE->setEnabled(false);
    ui->pushButtonProgDgtF->setEnabled(false);
}

void CalcWidget::setProgDecKeyBrd()
{
    ui->pushButtonProgDgt2->setEnabled(true);
    ui->pushButtonProgDgt3->setEnabled(true);
    ui->pushButtonProgDgt4->setEnabled(true);
    ui->pushButtonProgDgt5->setEnabled(true);
    ui->pushButtonProgDgt6->setEnabled(true);
    ui->pushButtonProgDgt7->setEnabled(true);
    ui->pushButtonProgDgt8->setEnabled(true);
    ui->pushButtonProgDgt9->setEnabled(true);
    ui->pushButtonProgDgtA->setEnabled(false);
    ui->pushButtonProgDgtB->setEnabled(false);
    ui->pushButtonProgDgtC->setEnabled(false);
    ui->pushButtonProgDgtD->setEnabled(false);
    ui->pushButtonProgDgtE->setEnabled(false);
    ui->pushButtonProgDgtF->setEnabled(false);
}

void CalcWidget::setProgHexKeyBrd()
{
    ui->pushButtonProgDgt2->setEnabled(true);
    ui->pushButtonProgDgt3->setEnabled(true);
    ui->pushButtonProgDgt4->setEnabled(true);
    ui->pushButtonProgDgt5->setEnabled(true);
    ui->pushButtonProgDgt6->setEnabled(true);
    ui->pushButtonProgDgt7->setEnabled(true);
    ui->pushButtonProgDgt8->setEnabled(true);
    ui->pushButtonProgDgt9->setEnabled(true);
    ui->pushButtonProgDgtA->setEnabled(true);
    ui->pushButtonProgDgtB->setEnabled(true);
    ui->pushButtonProgDgtC->setEnabled(true);
    ui->pushButtonProgDgtD->setEnabled(true);
    ui->pushButtonProgDgtE->setEnabled(true);
    ui->pushButtonProgDgtF->setEnabled(true);
}
/*****************************************************************************/

/**Toggle numeral format******************************************************/
void CalcWidget::toggleAngleUnit(int id, bool checked)
{
    if (checked) {
        angleUnitGroup->button(id)->setStyleSheet(pushButtonCheckedStyleSheet);
        interpreter->interpret(angleUnitCmds.at(id).toStdString());
    } else {
        angleUnitGroup->button(id)->setStyleSheet(pushButtonCommonStyleSheet);
    }

    ui->labelSciAns->setText(interpreter->valueStr().c_str());
}

void CalcWidget::toggleCountMethod(int id, bool checked)
{
    if (checked) {
        countMethodGroup->button(id)->setStyleSheet(pushButtonCheckedStyleSheet);
        interpreter->interpret(countMethodCmds.at(id).toStdString());
    } else {
        countMethodGroup->button(id)->setStyleSheet(pushButtonCommonStyleSheet);
    }

    ui->labelSciAns->setText(interpreter->valueStr().c_str());
}

void CalcWidget::toggleNumberBase(int id, bool checked)
{
    QString exprText;
    if (checked) {
        numberBaseGroup->button(id)->setStyleSheet(pushButtonCheckedStyleSheet);
        progAnsLabels[id]->setStyleSheet(labelCheckedStyleSheet);
        interpreter->interpret(numberBaseCmds.at(id).toStdString());
        switch (id) {
        case BIN:
            setProgBinKeyBrd();
            exprText = QString(NumeralConverter::valueTobinaryString(interpreter->value(), "").c_str());
            break;
        case OCT:
            setProgOctKeyBrd();
            exprText = QString(interpreter->valueStr().c_str());
            break;
        case DEC:
            setProgDecKeyBrd();
            exprText = QString(interpreter->valueStr().c_str());
            break;
        case HEX:
            setProgHexKeyBrd();
            exprText = QString(interpreter->valueStr().c_str());
            break;
        default:
            break;
        }
    } else {
        numberBaseGroup->button(id)->setStyleSheet(pushButtonCommonStyleSheet);
        progAnsLabels[id]->setStyleSheet(labelCommonStyleSheet);
    }

    expr.clear();

    if (exprText != QString("0")) {
        ui->labelProgExpr->setText(exprText);
        expr << exprText;
    }

    ui->labelProgAns->setText(interpreter->valueStr().c_str());
    updateProgMultAns();
}
/*****************************************************************************/

/**Switch calculator type*****************************************************/
void CalcWidget::openCalcMenu()
{
    curCalcType = CALC_MENU;
    ui->stackedWidgetCalc->setCurrentIndex(curCalcType);
}

void CalcWidget::openConveter(CnvType cnvType)
{
    curCalcType = CALC_CNV;
    curCnvType = cnvType;

    ui->labelCnvType->setText(cnvTypes.at(curCnvType));
    ui->labelCnvExpr->setText("0");
    ui->labelCnvAns->setText("0");

    ui->comboBoxFromUnit->blockSignals(true);
    ui->comboBoxFromUnit->clear();
    ui->comboBoxFromUnit->insertItems(0, cnvSkinUnits.at(curCnvType));
    ui->comboBoxFromUnit->setCurrentIndex(0);
    ui->comboBoxFromUnit->blockSignals(false);

    ui->comboBoxToUnit->blockSignals(true);
    ui->comboBoxToUnit->clear();
    ui->comboBoxToUnit->insertItems(0, cnvSkinUnits.at(curCnvType));
    ui->comboBoxToUnit->setCurrentIndex(0);
    ui->comboBoxToUnit->blockSignals(false);

    ui->stackedWidgetCalc->setCurrentIndex(curCalcType);

    cnvExpr[0] = "0";
    cnvExpr[1] = cnvUnderlyingUnits.at(curCnvType)[ui->comboBoxFromUnit->currentIndex()];
    cnvExpr[3] = cnvUnderlyingUnits.at(curCnvType)[ui->comboBoxToUnit->currentIndex()];

    interpreter->interpret(cnvCmds[curCnvType]);
}

void CalcWidget::openCalculator(CalcType calcType)
{
    curCalcType = calcType;
    ui->stackedWidgetCalc->setCurrentIndex(curCalcType);
    screenToDisplayMode();
    (this->*initScreens[curCalcType])();
    expr.clear();

    interpreter->interpret(calcTypeCmds.at(curCalcType).toStdString());
    interpreter->clear();
}

/*****************************************************************************/

/**Switch calculators*********************************************************/
void CalcWidget::on_pushButtonCalcScience_clicked() { openCalculator(CALC_SCI); }
void CalcWidget::on_pushButtonCalcProgrammer_clicked() { openCalculator(CALC_PROG); }
void CalcWidget::on_pushButtonCnvLength_clicked() { openConveter(CNV_LENGTH); }
void CalcWidget::on_pushButtonCnvArea_clicked() { openConveter(CNV_AREA); }
void CalcWidget::on_pushButtonCnvVolume_clicked() { openConveter(CNV_VOLUME); }
void CalcWidget::on_pushButtonCnvWeight_clicked() { openConveter(CNV_WEIGHT); }
void CalcWidget::on_pushButtonCnvTime_clicked() { openConveter(CNV_TIME); }
void CalcWidget::on_pushButtonCnvVelocity_clicked() { openConveter(CNV_VELOCITY); }
void CalcWidget::on_pushButtonCnvEnergy_clicked() { openConveter(CNV_ENERGY); }
void CalcWidget::on_pushButtonCnvPower_clicked() { openConveter(CNV_POWER); }
void CalcWidget::on_pushButtonCnvPressure_clicked() { openConveter(CNV_PRESSURE); }
void CalcWidget::on_pushButtonCnvAngle_clicked() { openConveter(CNV_ANGLE); }
void CalcWidget::on_pushButtonCnvData_clicked() { openConveter(CNV_DATA); }
/*****************************************************************************/

/**Science and programmer calculator's operations*****************************/
void CalcWidget::evaluate()
{
    if (!screenInComputeMode) {
        screenToComputeMode();
        (this->*initScreens[curCalcType])();
    }

    interpreter->interpret(expr.join(' ').toStdString());
    auto errorState = interpreter->errorState();

    if ((errorState & ERROR_FIELD) != ERROR_NOERROR) {
        switch (ErrorState(errorState & REPAIR_FIELD)) {
        case REPAIR_NOREPAIR:
            procError();
            break;
        case REPAIR_APPEND:
            exprLabels[curCalcType]->setText(expr.join(' '));
            break;
        case REPAIR_IGNORE:
            if (std::regex_match(expr.back().toStdString(), numRgx)
                    && (expr.back().endsWith(QChar('e'))
                        || expr.back().endsWith(QChar('-'))))
                exprLabels[curCalcType]->setText(expr.join(' '));
            else
                expr.pop_back();
            break;
        case REPAIR_REPLACE:
            expr.removeAt(expr.size() - 2);
            exprLabels[curCalcType]->setText(expr.join(' '));
            break;
        default:
            break;
        }
    } else {
        (this->*updateScreens[curCalcType])();
    }
}

void CalcWidget::procExprDgt(QChar dgt) {
    if (!expr.empty() && std::regex_match(expr.back().toStdString(), numRgx)) {
        QString &lstExprNode = expr.back();
        if (lstExprNode.size() == 1 && lstExprNode.at(0) == QChar('0'))
            lstExprNode[0] = dgt;
        else
            lstExprNode.append(dgt);
    } else {
        expr.append(QString(dgt));
    }
    evaluate();
}

void CalcWidget::procExprOpr(const QString &opr) {
    expr.append(opr);
    evaluate();
}

void CalcWidget::procExprDgts() { procExprDgt(((QPushButton *)sender())->text().at(0)); }
void CalcWidget::procExprOprs() { procExprOpr(((QPushButton *)sender())->text()); }
void CalcWidget::procExprOprUMinus() { procExprOpr("-"); }
void CalcWidget::on_pushButtonSciFcnSqre_clicked() { procExprOpr("^2"); }
void CalcWidget::on_pushButtonSciFcnSqrt_clicked() { procExprOpr("sqrt"); }
void CalcWidget::on_pushButtonSciSymPi_clicked() { procExprOpr("pi"); }

void CalcWidget::procExprOprAsgn()
{
    srchVldExprAndUpdtScrn();
    interpreter->interpret("complete");
    if (screenInComputeMode)
        screenToDisplayMode();
    expr.clear();
}

void CalcWidget::srchVldExprAndUpdtScrn()
{
    QStringList vldExpr = expr;
    interpreter->interpret(vldExpr.join(' ').toStdString());
    auto errorState = interpreter->errorState();
    while ((errorState & ERROR_FIELD) != ERROR_NOERROR) {
        vldExpr.pop_back();
        interpreter->interpret(vldExpr.join(' ').toStdString());
        errorState = interpreter->errorState();
    }
    (this->*updateAnss[curCalcType])();
    exprLabels[curCalcType]->setText(expr.join(' '));
}

void CalcWidget::procExprCmdDel()
{
    if (expr.isEmpty())
        return;

    QString &lstExprNode = expr.back();
    if (std::regex_match(lstExprNode.toStdString(), numRgx)) {
        lstExprNode.remove(lstExprNode.size() - 1, 1);
        if (lstExprNode.isEmpty())
            expr.pop_back();
    } else {
        expr.pop_back();
    }

    if (!expr.isEmpty())
        srchVldExprAndUpdtScrn();
    else
        procExprCmdClr();
}

void CalcWidget::procExprCmdClr()
{
    expr.clear();
    interpreter->clear();

    screenToDisplayMode();
    (this->*updateScreens[curCalcType])();
}
/*****************************************************************************/

/**Science calculator's operations********************************************/
void CalcWidget::on_pushButtonSciSymDot_clicked()
{
    if (!expr.empty() && std::regex_match(expr.back().toStdString(), numRgx)
            && !expr.back().contains(QChar('e')))
        expr.back().append(QChar('.'));
    else
        expr.append(QString("0."));

    evaluate();
}

void CalcWidget::on_pushButtonSciSymE_clicked()
{
    if (!expr.empty() && std::regex_match(expr.back().toStdString(), numRgx)
            && !expr.back().contains(QChar('e'))) {
        QString &lstExprNode = expr.back();
        if (lstExprNode.size() == 1 && lstExprNode.at(0) == QChar('0'))
            lstExprNode[0] = 'e';
        else
            lstExprNode.append(QChar('e'));
    } else {
        expr.append(QString("e"));
    }

    evaluate();
}

void CalcWidget::on_pushButtonSciOprUMinus_clicked()
{
    if (!expr.empty() && std::regex_match(expr.back().toStdString(), numRgx)
            && expr.back().endsWith(QChar('e')) && !expr.back().contains(QChar('-')))
            expr.back().append(QChar('-'));
    else
        expr.append(QString("-"));

    evaluate();
}

void CalcWidget::on_pushButtonSciHst_clicked()
{
    ui->stackedWidgetSciKeyBrdAndHst->setCurrentIndex(HST_OPEN);
    ui->pushButtonSciMenu->setEnabled(false);
    ui->pushButtonSciHst->setEnabled(false);

    // Set history text.
    std::string hstText;

    for (size_t i = 0, size = sciHst->size(); i < size; ++i)
        hstText.append(
                    "<p><br><font size=\"4\">" + (*sciHst)[size - 1 - i].first + "</font></p>"
                + " =<h><font size=\"5\">" + (*sciHst)[size - 1 - i].second + "</font></h>");
    ui->labelSciHst->setText(hstText.c_str());
}

void CalcWidget::on_pushButtonSciClrHst_clicked()
{
    ui->labelSciHst->clear();
    interpreter->clearHistory();
}
/*****************************************************************************/

/**Converter's operations*****************************************************/
void CalcWidget::convert()
{
    interpreter->interpret(cnvExpr.join(' ').toStdString());
    updateCnvScreen();
}

void CalcWidget::procCnvDgts()
{
    QChar dgt = ((QPushButton *)sender())->text().at(0);
    QString &number = cnvExpr[0];
    if (number.size() == 1 && number.at(0) == QChar('0'))
        number[0] = dgt;
    else
        number.append(dgt);
    convert();
}

void CalcWidget::on_comboBoxFromUnit_currentIndexChanged(int index)
{
    cnvExpr[1] = cnvUnderlyingUnits.at(curCnvType).at(index);
    convert();
}

void CalcWidget::on_comboBoxToUnit_currentIndexChanged(int index)
{
    cnvExpr[3] = cnvUnderlyingUnits.at(curCnvType).at(index);
    convert();
}

void CalcWidget::on_pushButtonCnvSymDot_clicked()
{
    QString &number = cnvExpr[0];
    QChar dot = '.';
    if (!number.contains(dot)) {
        number.append(dot);
        convert();
    }
}

void CalcWidget::on_pushButtonCnvCmdClr_clicked()
{
    cnvExpr[0] = "0";
    convert();
}

void CalcWidget::on_pushButtonCnvCmdDel_clicked()
{
    QString &number = cnvExpr[0];
    if (number.size() > 1)
        number.remove(number.size() - 1, 1);
    else
        number = "0";
    convert();
}
/*****************************************************************************/
