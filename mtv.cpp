#include "mtv.hpp"

mQTableView::mQTableView():
    QTableView()
{}

void mQTableView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete)
        emit delete_req();
    else
        QTableView::keyPressEvent(event);
}
