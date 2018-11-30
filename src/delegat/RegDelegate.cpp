#include "RegDelegate.hpp"
#include <QComboBox>
#include <src/DataI.hpp>

/**
 * @param region - wskaźnik na obiekt z którego zostaną odczytane nazwy struktur.
 */
RegDelegate::RegDelegate(QObject *parent, DataI *region):
    QItemDelegate(parent),
    _reg(region)
{
}

/**
 * tworzy QComboBox z listą regionów dostępnych we wskazanym obiekcie.
 */
QWidget *RegDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(_reg->GetNames());
    return editor;
}

void RegDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* le = static_cast<QComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
