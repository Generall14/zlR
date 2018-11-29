#ifndef TYPEDELEGATE_HPP
#define TYPEDELEGATE_HPP

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
