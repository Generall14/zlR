#ifndef REGDELEGATE_HPP
#define REGDELEGATE_HPP

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class DataRegion;

class RegDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    RegDelegate(QObject *parent, DataRegion* region);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    DataRegion* _reg = nullptr;
};

#endif
