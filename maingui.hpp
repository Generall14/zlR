#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QMainWindow>
#include <QTableView>

class MainGUI : public QMainWindow
{
    Q_OBJECT
public:
    MainGUI(QWidget *parent = 0);
    ~MainGUI();

private:
    void InitGUI();
    void InitMenu();

    QTableView* regTBV = nullptr;
    QTableView* secTBV = nullptr;
};

#endif // MAINGUI_HPP
