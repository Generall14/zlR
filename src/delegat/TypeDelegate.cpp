#include "TypeDelegate.hpp"
#include <QComboBox>
#include <src/wtf/WComboBox.hpp>

TypeDelegate::TypeDelegate(QObject *parent, QStringList opts):
    QItemDelegate(parent),
    _opts(opts)
{
}

/**
 * Tworzy QComboBox z listą stringów podaną w konstruktorze.
 */
QWidget *TypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    WComboBox* editor = new WComboBox(parent);
    editor->addItems(_opts);
    return editor;
}

void TypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    WComboBox* le = static_cast<WComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
