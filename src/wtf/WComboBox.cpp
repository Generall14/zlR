#include "WComboBox.hpp"

WComboBox::WComboBox(QWidget *parent):
    QComboBox(parent)
{
    _tmr = new QTimer();
    connect(_tmr, SIGNAL(timeout()), this, SLOT(tim()));
    _tmr->setSingleShot(true);
//    _tmr->start(25);
}

WComboBox::~WComboBox()
{
    delete _tmr;
}

void WComboBox::tim()
{
    this->showPopup();
}
