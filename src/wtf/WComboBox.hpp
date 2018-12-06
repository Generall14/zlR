#ifndef WCOMBOBOX_HPP
#define WCOMBOBOX_HPP

/**
  * @class WComboBox
  * @author Wojciech Kogut
  *
  * To jest głupie jak but i narazie jest wyłączone, ale niech tu zostanie.
  */

#include <QObject>
#include <QComboBox>
#include <QTimer>

class WComboBox : public QComboBox
{
    Q_OBJECT
public:
    WComboBox(QWidget* parent = nullptr);
    ~WComboBox();

private slots:
    void tim();

private:
    QTimer* _tmr = nullptr;
};

#endif
