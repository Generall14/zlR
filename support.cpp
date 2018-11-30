#include "support.hpp"
#include <QString>
#include <iostream>
#include <src/Data.hpp>
#include <stdexcept>
#include <maingui.hpp>
#include <QFile>
#include <QDebug>

/**
 * Czyta argumenty programu i zwraca wypełnioną strukturę args.
 */
args readArgs(QApplication &a)
{
    args temp;
    if(a.arguments().size()>1)
    {
        if(!a.arguments().at(1).startsWith("-"))
        {
            temp.iadr = a.arguments().at(1);
            return temp;
        }
    }

    for(QString v: a.arguments().mid(1))
    {
        if(!v.compare("-h", Qt::CaseInsensitive))
            temp.help = true;
        else if(!v.compare("-m", Qt::CaseInsensitive))
            temp.manulal = true;
        else if(!v.compare("-q", Qt::CaseInsensitive))
            temp.quiet = true;
        else if(!v.compare("-c", Qt::CaseInsensitive))
            temp.check = true;
        else if(!v.compare("-v", Qt::CaseInsensitive))
            temp.verifyT = true;
        else if(v.startsWith("-i", Qt::CaseInsensitive))
            temp.iadr = v.mid(2);
        else if(v.startsWith("-t", Qt::CaseInsensitive))
            temp.tadr = v.mid(2);
        else if(v.startsWith("-o", Qt::CaseInsensitive))
            temp.oadr = v.mid(2);
        else
            std::cerr << "Nieznany argument \"" << v.toStdString() << "\"" << std::endl;
    }

    return temp;
}

/**
 * Na podstawie wskazanych parametrów uruchamia program w odpowiednim trybie.
 */
int run(QApplication &a, args r)
{
    if(r.help)
        displayAndQuit(":/help.txt");
    if(r.manulal)
        displayAndQuit(":/template.txt");

    if((r.check)||(r.quiet)||(r.verifyT))
    {
        if(r.iadr.isEmpty())
            throw std::runtime_error("run: brak zdefiniowanego pliku wejściowego -i");
    }
    QSharedPointer<Data> dat = QSharedPointer<Data>(new Data(r.iadr), &QObject::deleteLater);
    if(r.check)
        return 0;

    if((r.quiet)||(r.verifyT))
    {
        if(dat->isOk())
            throw std::runtime_error("run: nie można przetworzyć szablonu z powodu błędu danych wejściowych");
        if(r.tadr.isEmpty())
            throw std::runtime_error("run: brak zdefiniowanego pliku szablonu -t");
        if(r.quiet)
        {
            if(r.oadr.isEmpty())
                throw std::runtime_error("run: brak zdefiniowanego pliku wyjściowego -o");
        }
        dat->Make(r.tadr, r.oadr);
        return 0;
    }

    MainGUI w(dat, r.iadr, r.tadr, r.oadr);
    w.show();

    return a.exec();
}

/**
 * Wyświetla tekst wskazanego pliku i zamyka aplikacje.
 */
void displayAndQuit(QString file)
{
    QFile hfile(file);
    hfile.open(QIODevice::ReadOnly | QIODevice::Text);
    std::cout << hfile.readAll().toStdString() << std::endl << "...";
    hfile.close();
    getchar();
    exit(0);
}
