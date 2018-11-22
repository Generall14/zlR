#include "maingui.hpp"
#include <QApplication>
#include <stdexcept>
#include <iostream>
#include <QMessageBox>
#include <src/Data.hpp>
#include <QSharedPointer>

int RunGUI(QApplication &a)
{
    QSharedPointer<Data> dat = QSharedPointer<Data>(new Data("tst.h"), &QObject::deleteLater);

    MainGUI w(dat);
    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
    bool gui = true;
    QString err;

    QApplication a(argc, argv);

    try
    {
        return RunGUI(a);
    }
    catch(std::runtime_error e)
    {
        err = "Coś się zesrało: "+QString(e.what())+".";
    }
    catch(...)
    {
        err = "Coś się zesrało.";
    }
    if(gui)
        QMessageBox::critical(nullptr, "FATAL ERROR!", err, QMessageBox::Abort);
    std::cout << err.toStdString() << std::endl;
    return -1;
}
