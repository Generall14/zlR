#ifndef BTYPEDELEGATE_HPP
#define BTYPEDELEGATE_HPP

/**
  * @class BTypeDelegate
  * @author Wojciech Kogut
  *
  * Delegat dla wartości logicznych, gdzie false jest pustym stringiem a true wskazaną wartością.
  */

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class BTypeDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    BTypeDelegate(QObject *parent, QString tru);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    QString _true;
};

#endif
