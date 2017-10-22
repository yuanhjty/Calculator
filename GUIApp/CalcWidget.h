#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include "../calc/Interpreter.h"
#include <vector>
#include <string>

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class CalcWidget;
}

enum AngleUnit { DEG, RAD };

enum CountMethod { DLFLT, FIX, SCI };

enum StackedWidgetCalc { CALC_SCI = 0, CALC_PROG = 1, CALC_CNV = 2, CALC_MENU = 3 };

enum StackedWidgetHst { HST_CLOSE = 0, HST_OPEN = 1 };

enum CnvType {CNV_LENGTH = 0, CNV_AREA = 1, CNV_VOLUME = 2, CNV_WEIGHT = 3, CNV_TIME = 4, CNV_VELOCITY = 5,
              CNV_ENERGY = 6, CNV_POWER = 7, CNV_PRESSURE = 8, CNV_ANGLE = 9, CNV_DATA = 10};

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWidget(QWidget *parent = 0);
    ~CalcWidget();

private:
    bool eventFilter(QObject *watched, QEvent *event);

    void initWidgetStyles();
    void initSciCntMethods();
    void initSciAglUnits();
    void initProgNumBases();
    void initConverter();
    void installEventFilters();
    void connectSignalsAndSlots();

    void openCalcMenu();
    void openConveter(CnvType type);
    void convert();
    void procCnvDgt();

private slots:
    void toggleAngleUnit(int id, bool checked);
    void toggleCountMethod(int id, bool checked);

    void on_pushButtonSciHst_clicked();
    void on_pushButtonCalcScience_clicked();

    void on_pushButtonCalcProgrammer_clicked();

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

    void on_comboBoxFromUnit_currentIndexChanged(int index);
    void on_comboBoxToUnit_currentIndexChanged(int index);

    void on_pushButtonCnvSymDot_clicked();

    void on_pushButtonCnvCmdClr_clicked();

    void on_pushButtonCnvCmdDel_clicked();

private:
    Ui::CalcWidget *ui;
    Interpreter *interpreter;

    QButtonGroup *angleUnitGroup;
    QButtonGroup *countMethodGroup;

    QString pushButtonCommonStyleSheet;
    QString pushButtonCheckedStyleSheet;

    QList<QStringList> cnvUnderlyingUnits;
    QList<QStringList> cnvSkinUnits;
    QStringList cnvTypeNames;
    std::vector<std::string> cnvCmdNames;
    QStringList cnvExpr;
    CnvType curCnvType;
};

#endif // CALCWIDGET_H
