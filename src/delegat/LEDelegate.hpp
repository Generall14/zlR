#ifndef LEDELEGATE_HPP
#define LEDELEGATE_HPP

#include <QItemDelegate>
#include <QLineEdit>
#include <QValidator>

class LEDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    LEDelegate(QObject *parent, QValidator* validator = nullptr);
    ~LEDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private:
    QValidator* _val = nullptr;
};

#endif
