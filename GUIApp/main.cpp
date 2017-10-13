#include "CalcWidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcWidget w;
    w.setWindowIcon(QIcon("calculator.o"));
    w.setWindowTitle("Calculator");
    w.show();

    return a.exec();
}
