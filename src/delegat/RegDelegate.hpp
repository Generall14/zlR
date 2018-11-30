#ifndef REGDELEGATE_HPP
#define REGDELEGATE_HPP

/**
  * @class RegDelegate
  * @author Wojciech Kogut
  *
  * Delegat dla wartości REGION, tworzy QComboBox z listą regionów zawartych we wskazanym obiekcie.
  */

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class DataI;

class RegDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    RegDelegate(QObject *parent, DataI* region);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    DataI* _reg = nullptr;
};

#endif
