#ifndef MAINGUI_HPP
#define MAINGUI_HPP

#include <QMainWindow>

class MainGUI : public QMainWindow
{
    Q_OBJECT

public:
    MainGUI(QWidget *parent = 0);
    ~MainGUI();
};

#endif // MAINGUI_HPP
