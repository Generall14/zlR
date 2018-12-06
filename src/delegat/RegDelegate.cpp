#include "RegDelegate.hpp"
#include <QComboBox>
#include <src/DataI.hpp>
#include <src/wtf/WComboBox.hpp>

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
    WComboBox* editor = new WComboBox(parent);
    editor->addItems(_reg->GetNames());
    return editor;
}

void RegDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    WComboBox* le = static_cast<WComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
