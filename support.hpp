#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <QApplication>

struct args
{
    QString iadr; /**<Adres wejściowego pliku danych.*/
    QString tadr; /**<Adres pliku szalonu.*/
    QString oadr; /**<Adres pliku wyjściowego.*/
    bool quiet = false; /**<Bez GUI.*/
    bool check = false; /**<Tylko sprawdzenie.*/
    bool help = false; /**<Wyświetl pomoc programu.*/
    bool manulal = false; /**<Wyświetl opis składni szablonu.*/
    bool verifyT = false; /**<SprawdŹ szablon.*/
};

args readArgs(QApplication &a);
int run(QApplication &ap, args r);
[[ noreturn ]] void displayAndQuit(QString file);

#endif
