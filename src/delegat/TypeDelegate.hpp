#ifndef TYPEDELEGATE_HPP
#define TYPEDELEGATE_HPP

/**
  * @class TypeDelegate
  * @author Wojciech Kogut
  *
  * Delegat dla stałego zbioru wartości, tworzy QComboBox z listą stringów podaną w konstruktorze.
  */

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class TypeDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TypeDelegate(QObject *parent, QStringList opts);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    QStringList _opts;
};

#endif
