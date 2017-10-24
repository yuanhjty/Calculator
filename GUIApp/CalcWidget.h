#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include "../calc/Interpreter.h"
#include <vector>
#include <string>
#include <regex>

#include <QWidget>
#include <QButtonGroup>
#include <QLabel>
#include <QFont>

namespace Ui {
class CalcWidget;
}

enum AngleUnit { DEG, RAD };

enum CountMethod { DLFLT, FIX, SCI };

enum NumberBase { BIN, OCT, DEC, HEX };

enum CalcType { CALC_SCI, CALC_PROG, CALC_CNV, CALC_MENU };

enum HstState { HST_CLOSE, HST_OPEN };

enum CnvType {CNV_LENGTH, CNV_AREA, CNV_VOLUME, CNV_WEIGHT, CNV_TIME, CNV_VELOCITY,
              CNV_ENERGY, CNV_POWER, CNV_PRESSURE, CNV_ANGLE, CNV_DATA};

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWidget(QWidget *parent = 0);
    ~CalcWidget();

private:
    // Initialize
    void initWidgetStyles();
    void initSciNumNotation();
    void initSciAglUnits();
    void initProgNumBases();
    void initConverter();
    bool eventFilter(QObject *watched, QEvent *event);
    void installEventFilters();
    void connectSignalsAndSlots();

    // Process unrepairable error
    void procError();

    // Update screen
    void initSciScreen();
    void initProgScreen();
    void updateSciScreen();
    void updateProgScreen();
    void updateProgMultAns();
    void updateSciAns();
    void updateProgAns();
    void updateCnvScreen();

    void screenToComputeMode();
    void screenToDisplayMode();

    // Set programmer calculator's keyboard
    void setProgBinKeyBrd();
    void setProgOctKeyBrd();
    void setProgDecKeyBrd();
    void setProgHexKeyBrd();

    // Toggle numeral format
    void toggleAngleUnit(int id, bool checked);
    void toggleCountMethod(int id, bool checked);
    void toggleNumberBase(int id, bool checked);

    // Switch calculator's type
    void openCalcMenu();
    void openConveter(CnvType cnvType);
    void openCalculator(CalcType calcType);
private slots:
    void on_pushButtonCalcScience_clicked();
    void on_pushButtonCalcProgrammer_clicked();

    // Switch converters
    void on_pushButtonCnvLength_clicked();
    void on_pushButtonCnvArea_clicked();
    void on_pushButtonCnvVolume_clicked();
    void on_pushButtonCnvWeight_clicked();
    void on_pushButtonCnvTime_clicked();
    void on_pushButtonCnvVelocity_clicked();
    void on_pushButtonCnvEnergy_clicked();
    void on_pushButtonCnvPower_clicked();
    void on_pushButtonCnvPressure_clicked();
    void on_pushButtonCnvAngle_clicked();
    void on_pushButtonCnvData_clicked();

    // Science and programmer calculator's operations
private:
    void evaluate();
    void procExprDgt(QChar dgt);
    void procExprOpr(const QString &opr);
    void procExprDgts();
    void procExprOprs();
    void procExprOprUMinus();
private slots:
    void on_pushButtonSciFcnSqre_clicked();
    void on_pushButtonSciFcnSqrt_clicked();
    void on_pushButtonSciSymPi_clicked();
private:
    void procExprOprAsgn();
    void srchVldExprAndUpdtScrn();
    void procExprCmdDel();
    void procExprCmdClr();
private slots:
    void on_pushButtonSciSymE_clicked();
    void on_pushButtonSciOprUMinus_clicked();
    void on_pushButtonSciHst_clicked();
    void on_pushButtonSciClrHst_clicked();

private:
    // Converter's operations
    void convert();
    void procCnvDgts();
private slots:
    void on_comboBoxFromUnit_currentIndexChanged(int index);
    void on_comboBoxToUnit_currentIndexChanged(int index);
    void on_pushButtonCnvSymDot_clicked();
    void on_pushButtonCnvCmdClr_clicked();
    void on_pushButtonCnvCmdDel_clicked();

    void on_pushButtonSciSymDot_clicked();

private:
    Ui::CalcWidget *ui;
    Interpreter *interpreter;

    /**For numeral format conversion*********/
    QButtonGroup *countMethodGroup;
    QButtonGroup *angleUnitGroup;
    QButtonGroup *numberBaseGroup;
    QStringList countMethodCmds;
    QStringList angleUnitCmds;
    QStringList numberBaseCmds;
    QList<QLabel *> progAnsLabels;
    /****************************************/

    /**For interface style*******************/
    QString pushButtonCommonStyleSheet;
    QString pushButtonCheckedStyleSheet;
    QString labelCommonStyleSheet;
    QString labelCheckedStyleSheet;
    QFont screenLargeFont;
    QFont screenSmallFont;
    /****************************************/

    /**For science and programmer calculator*/
    bool screenInComputeMode; /* The program exits compute mode and starts displaying the
                         * result when the key '=' is clicked.
                         * And switch to compute mode whenever an evaluation begins. */
    CalcType curCalcType;
    QStringList calcTypeCmds;
    QList<QLabel *> exprLabels;
    QList<QLabel *> ansLabels;
    QList<void (CalcWidget::*)()> initScreens;
    QList<void (CalcWidget::*)()> updateScreens;
    QList<void (CalcWidget::*)()> updateAnss;
    QStringList expr;        // Operation expression
    std::regex numRgx;
    const std::deque<Calculator::ResultType> *sciHst;
    /****************************************/

    /**For Converters************************/
    QList<QStringList> cnvUnderlyingUnits;
    QList<QStringList> cnvSkinUnits;
    QStringList cnvTypes;
    std::vector<std::string> cnvCmds;
    QStringList cnvExpr;
    CnvType curCnvType;
    /****************************************/
};

#endif // CALCWIDGET_H
