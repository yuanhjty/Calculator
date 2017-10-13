#include "HistoryShower.h"
#include "ui_HistoryShower.h"

HistoryShower::HistoryShower(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryShower)
{
    ui->setupUi(this);

    installEventFilter(this);
}

HistoryShower::~HistoryShower()
{
    delete ui;
}

void HistoryShower::printHistory(const std::deque<Calculator::Result_Type> *history)
{
    std::string text;

    // The operations of the std begin, end, rbegin and rend iterators
    // behave differently due to different implementation.
    // So traverse via index.
    for (size_t i = 0, size = history->size(); i < size; ++i)
        text.append("<p>" + (*history)[size - 1 - i].first + " =</p><h><font size=\"5\">"
                    + (*history)[size - 1 - i].second + "</font></h>");

    ui->label->setText(text.c_str());
}

bool HistoryShower::eventFilter(QObject *watched, QEvent *event)
{
    if (this == watched && QEvent::WindowDeactivate == event->type()) {
        emit activateMainWidget();
        hide();
        return true;
    } else
        return QWidget::eventFilter(watched, event);
}

void HistoryShower::on_pushButtonDelete_released()
{
    ui->label->setText("");
    emit deleteHistory();
}
