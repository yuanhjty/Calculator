#include "CalcWidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcWidget w;
    w.setWindowTitle("Calculator");
    w.show();

    return a.exec();
}
