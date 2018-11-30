#include "LEDelegate.hpp"

LEDelegate::LEDelegate(QObject *parent, QValidator *validator):
    QItemDelegate(parent),
    _val(validator)
{

}

/**
 * Tworzy nowy edytor QLineEdit.
 */
QWidget *LEDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QLineEdit* editor = new QLineEdit(parent);
    if(_val)
        editor->setValidator(_val);
    return editor;
}

/**
 * Ustawia dane w edytorze.
 * @param editor - Wskaźnik na edytor.
 * @param index - Indeks danych.
 */
void LEDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* le = static_cast<QLineEdit*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setText(val);
}
