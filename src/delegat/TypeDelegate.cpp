#include "TypeDelegate.hpp"
#include <QComboBox>

TypeDelegate::TypeDelegate(QObject *parent, QStringList opts):
    QItemDelegate(parent),
    _opts(opts)
{
}

QWidget *TypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(_opts);
    return editor;
}

void TypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* le = static_cast<QComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
