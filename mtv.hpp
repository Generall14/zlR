#ifndef MTV_HPP
#define MTV_HPP

/**
  * @class mQTableView
  * @author Wojciech Kogut
  *
  * QTableView przechwytujace przycisk delete i wysyłający sygnał delete_req().
  */

#include <QObject>
#include <QTableView>
#include <QKeyEvent>

class mQTableView : public QTableView
{
    Q_OBJECT
public:
    mQTableView();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

signals:
    void delete_req();
};

#endif
