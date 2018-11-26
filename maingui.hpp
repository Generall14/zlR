#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QMainWindow>
#include <QTableView>

class Data;

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
    QTableView* defTBV = nullptr;

private slots:
    void Save();
};

#endif // MAINGUI_HPP
