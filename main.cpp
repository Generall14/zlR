#include "maingui.hpp"
#include <QApplication>
#include <stdexcept>
#include <iostream>
#include <QMessageBox>
#include <support.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    args _args = readArgs(a);

    QString err;
    try
    {
        return run(a, _args);
    }
    catch(std::runtime_error e)
    {
        err = "Coś się zesrało: "+QString(e.what())+".";
    }
    catch(...)
    {
        err = "Coś się zesrało i nie wiadomo co!";
    }

    if((!_args.quiet)&&(!_args.check)&&(!_args.verifyT))
        QMessageBox::critical(nullptr, "FATAL ERROR!", err, QMessageBox::Abort);
    std::cerr << err.toStdString() << std::endl;
    return -1;
}
