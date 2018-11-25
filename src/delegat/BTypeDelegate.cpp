#include "BTypeDelegate.hpp"
#include <QComboBox>

BTypeDelegate::BTypeDelegate(QObject *parent, QString tru):
    QItemDelegate(parent),
    _true(tru)
{
}

QWidget *BTypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QStringList opts = {"", _true};
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(opts);
    return editor;
}

void BTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* le = static_cast<QComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
