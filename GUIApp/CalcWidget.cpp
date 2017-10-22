#include "CalcWidget.h"
#include "ui_CalcWidget.h"

#include <QComboBox>

CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget),
    interpreter(new Interpreter),
    angleUnitGroup(new QButtonGroup(this)),
    countMethodGroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    initWidgetStyles();
    initSciCntMethods();
    initSciAglUnits();
    initProgNumBases();
    initConverter();
    installEventFilters();
    connectSignalsAndSlots();

    ui->stackedWidgetCalc->setCurrentIndex(CALC_SCI);
}

CalcWidget::~CalcWidget()
{
    delete ui;
    delete interpreter;
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

void CalcWidget::initWidgetStyles()
{
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

                "QComboBox {"
                    "border: 0px;"
                    "padding: 0px 10px 0px 10px;"
                    "color: rgb(18, 150, 219);"
                "}"

                "QComboBox::drop-down {"
                    "subcontrol-origin: padding;"
                    "border: 0px;"
                "}"

                "QComboBox::down-arrow {"
                    "border: 0px;"
                    "border-image: url(:/images/down-arrow);"
                "}"

                "#groupBoxSciKeyBrdAndHst, #groupBoxSciHstMenu {"
                    "border: 0px;"
                    "background-color: rgb(240, 240, 240);"
                "}"

                + pushButtonCommonStyleSheet +

                "#pushButtonSciMenu, #pushButtonSciHst, "
                "#pushButtonCnvMenu {"
                    "border: 0px;"
                    "background-color: rgb(255, 255, 255);"
                "}"

                "#pushButtonSciMenu:hover, #pushButtonSciHst:hover, "
                "#pushButtonCnvMenu:hover {"
                    "border: 0px;"
                    "background-color: rgb(220, 220, 220);"
                "}"

                "#pushButtonSciMenu:pressed, #pushButtonSciHst:pressed, "
                "#pushButtonCnvMenu:pressed {"
                    "border: 0px;"
                    "background-color: rgb(200, 200, 200);"
                "}"
                );
}

void CalcWidget::initSciCntMethods()
{
    ui->pushButtonSciCntDFLT->setCheckable(true);
    ui->pushButtonSciCntDFLT->setChecked(false);

    ui->pushButtonSciCntFIX->setCheckable(true);
    ui->pushButtonSciCntFIX->setChecked(false);

    ui->pushButtonSciCntSCI->setCheckable(true);
    ui->pushButtonSciCntSCI->setChecked(false);

    countMethodGroup->addButton(ui->pushButtonSciCntDFLT, DLFLT);
    countMethodGroup->addButton(ui->pushButtonSciCntFIX, FIX);
    countMethodGroup->addButton(ui->pushButtonSciCntSCI, SCI);
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

    cnvTypeNames = QStringList({"LENGTH", "AREA", "VOLUME", "WEIGHT", "TIME", "VELOCITY",
                    "ENERGY", "POWER", "PRESSURE", "ANGLE", "DATA"});

    cnvCmdNames = {"length", "area", "volume", "weight", "time", "velocity",
                   "energy", "power", "pressure", "angle", "data"};

    cnvExpr = QStringList({"0", "", "to", ""});
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
//    connect(ui->pushButtonProgMenu, &QPushButton::clicked, this, &CalcWidget::openCalcMenu);

    void (QButtonGroup::*btnGrpToggledSignal)(int, bool) = &QButtonGroup::buttonToggled;
    connect(angleUnitGroup, btnGrpToggledSignal, this, &CalcWidget::toggleAngleUnit);
    connect(countMethodGroup, btnGrpToggledSignal, this, &CalcWidget::toggleCountMethod);

    connect(ui->pushButtonCnvDgt0, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt1, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt2, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt3, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt4, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt5, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt6, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt7, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt8, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
    connect(ui->pushButtonCnvDgt9, &QPushButton::clicked, this, &CalcWidget::procCnvDgt);
}

void CalcWidget::openCalcMenu()
{
    ui->stackedWidgetCalc->setCurrentIndex(CALC_MENU);
}

void CalcWidget::openConveter(CnvType type)
{
    curCnvType = type;

    ui->labelCnvType->setText(cnvTypeNames.at(curCnvType));
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

    ui->stackedWidgetCalc->setCurrentIndex(CALC_CNV);

    cnvExpr[0] = "0";
    cnvExpr[1] = cnvUnderlyingUnits.at(curCnvType)[ui->comboBoxFromUnit->currentIndex()];
    cnvExpr[3] = cnvUnderlyingUnits.at(curCnvType)[ui->comboBoxToUnit->currentIndex()];

    interpreter->interpret(cnvCmdNames[curCnvType]);
}

void CalcWidget::convert()
{
    interpreter->interpret(cnvExpr.join(' ').toStdString());
    ui->labelCnvExpr->setText(cnvExpr.at(0));
    ui->labelCnvAns->setText(interpreter->result().second.c_str());
}

void CalcWidget::procCnvDgt()
{
    QChar dgt = ((QPushButton *)sender())->text().at(0);
    QString &number = cnvExpr[0];
    if (number.size() == 1 && number.at(0) == QChar('0'))
        number[0] = dgt;
    else
        number.append(dgt);
    convert();
}


void CalcWidget::toggleAngleUnit(int id, bool checked)
{
    if (checked) {
        angleUnitGroup->button(id)->setStyleSheet(pushButtonCheckedStyleSheet);
        switch (id) {
        case DEG:
            interpreter->interpret("degree");
            break;
        case RAD:
            interpreter->interpret("radian");
            break;
        default:
            break;
        }
        // update screen
    } else {
        angleUnitGroup->button(id)->setStyleSheet(pushButtonCommonStyleSheet);
    }
}

void CalcWidget::toggleCountMethod(int id, bool checked)
{
    if (checked) {
        countMethodGroup->button(id)->setStyleSheet(pushButtonCheckedStyleSheet);
        switch (id) {
        case DLFLT:
            interpreter->interpret("default");
            break;
        case FIX:
            interpreter->interpret("fixed");
            break;
        case SCI:
            interpreter->interpret("scientific");
            break;
        default:
            break;
        }
        // update screen
    } else {
        countMethodGroup->button(id)->setStyleSheet(pushButtonCommonStyleSheet);
    }
}

void CalcWidget::on_pushButtonSciHst_clicked()
{
    ui->stackedWidgetSciKeyBrdAndHst->setCurrentIndex(HST_OPEN);
    ui->pushButtonSciMenu->setEnabled(false);
    ui->pushButtonSciHst->setEnabled(false);
}


void CalcWidget::on_pushButtonCalcScience_clicked()
{
    ui->stackedWidgetCalc->setCurrentIndex(CALC_SCI);
    interpreter->interpret("science");
}

void CalcWidget::on_pushButtonCalcProgrammer_clicked()
{
    ui->stackedWidgetCalc->setCurrentIndex(CALC_PROG);
    interpreter->interpret("programmer");
}

/**Switch converter***********************************************************/
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

/**Execute convert*/
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
/*****************************************/

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
