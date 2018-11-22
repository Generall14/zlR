#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QMainWindow>
#include <QTableView>
#include <src/Data.hpp>

class MainGUI : public QMainWindow
{
    Q_OBJECT
public:
    MainGUI(QSharedPointer<Data> dat, QWidget *parent = 0);
    ~MainGUI();

private:
    void InitGUI();
    void InitMenu();

    QSharedPointer<Data> _dat;

    QTableView* regTBV = nullptr;
    QTableView* secTBV = nullptr;
};

#endif // MAINGUI_HPP
