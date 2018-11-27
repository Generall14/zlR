#include "maingui.hpp"
#include <QApplication>
#include <stdexcept>
#include <iostream>
#include <QMessageBox>
#include <src/Data.hpp>
#include <QSharedPointer>
#include <src/OtherShitSolver.hpp>
#include <QDebug>

int RunGUI(QApplication &a)
{
    QString adr = "tst.h";
    QSharedPointer<Data> dat = QSharedPointer<Data>(new Data(adr), &QObject::deleteLater);

    MainGUI w(dat, adr);
    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
    bool gui = true;
    QString err;

    QApplication a(argc, argv);

    qDebug() << OtherShitSolver::GetBoleanValue("");
    qDebug() << OtherShitSolver::GetBoleanValue("fds");
    return;

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
