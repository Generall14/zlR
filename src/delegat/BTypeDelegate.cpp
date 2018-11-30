#include "BTypeDelegate.hpp"
#include <QComboBox>

/**
 * @param tru - wartość jaka ma być sugerowana jako true.
 */
BTypeDelegate::BTypeDelegate(QObject *parent, QString tru):
    QItemDelegate(parent),
    _true(tru)
{
}

/**
 * Tworzy nowy edytor QComboBox z wartością pustą oraz wskazaną w konstruktorze.
 */
QWidget *BTypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
    QStringList opts = {"", _true};
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(opts);
    return editor;
}

/**
 * Ustawia dane w edytorze.
 * @param editor - Wskaźnik na edytor.
 * @param index - Indeks danych.
 */
void BTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* le = static_cast<QComboBox*>(editor);
    QString val = index.model()->data(index, Qt::DisplayRole).toString();
    le->setCurrentText(val);
}
