#ifndef HISTORYSHOWER_H
#define HISTORYSHOWER_H

#include "../Calculator/Calculator.h"
#include "ui_HistoryShower.h"

#include <QWidget>

namespace Ui {
class HistoryShower;
}

class HistoryShower : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryShower(QWidget *parent = 0);
    ~HistoryShower();

    void printHistory(const std::deque<Calculator::Result_Type>* history);

private slots:
    void on_pushButtonDelete_released();

signals:
    void deleteHistory();
    void activateMainWidget();

private:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::HistoryShower *ui;
};

#endif // HISTORYSHOWER_H
