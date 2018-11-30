#ifndef LEDELEGATE_HPP
#define LEDELEGATE_HPP

/**
  * @class LEDelegate
  * @author Wojciech Kogut
  *
  * Delegat dla dowolnych wartości, edytorem jest QLineEdit z opcjonalnie podanym validatorem.
  */

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class LEDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    LEDelegate(QObject *parent, QValidator* validator = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    QValidator* _val = nullptr;
};

#endif
