#include "Macro.hpp"
#include <src/Data.hpp>
#include <src/DataI.hpp>
#include <src/DataSection.hpp>
#include <src/DataRegion.hpp>
#include <QDebug>

/**
 * Konstruktor.
 * @param text - tekst makra, w pierwszej lini symbol $MACRO_..., w ostatniej $ENDM
 * @param data - wskaźnik do danych.
 */
Macro::Macro(QStringList text, Data *data)
{
    if(text.at(0).startsWith("$MACRO_SEC "))
        _data = data->GetSections().data();
    else if(text.at(0).startsWith("$MACRO_REG "))
        _data = data->GetRegions().data();
    else
        throw std::runtime_error("Macro::Macro: WTF? \""+text.at(0).toStdString()+"\".");

    QStringList ll = text.at(0).split(" ", QString::SkipEmptyParts);
    if(ll.size()<2)
        throw std::runtime_error("Macro::Macro: tu brakuje nazwy \""+text.at(0).toStdString()+"\".");
    _name = ll.at(1);

    text.removeLast();
    text.removeFirst();
    _text = text;
}

/**
 * Ładuje i rozwija wszystkie makra w tekście podanym jako QStringList. Dane do rozwinięcia
 * makr pobierze z przekazanego wskaźnika do obiektu Data.
 * @param text - odczytany plik szablonu.
 * @param data - wskaźnik na obiekt z danymi do rozwinięcia makr.
 */
void Macro::ProcessAll(QStringList& text, Data* data)
{
    QList<Macro> macs = Macro::LoadMacros(text, data);

    int founds = 666;
    while(founds)
    {
        founds = 0;
        for(auto mac: macs)
            founds += mac.Apply(text);
    }
}

/**
 * Ładuje makra z wskazanego pliku (usuwa z niego tekst definicji makr).
 * @param text - odczytany plik szablonu z którego załadowane zostaną makra.
 * @param data - wskaźnik na obiekt z danymi do rozwinięcia makr.
 * @return - lista odczytanych makr.
 */
QList<Macro> Macro::LoadMacros(QStringList& text, Data* data)
{
    QList<Macro> macs;

    bool found = true;
    bool end = false;
    int sidx, eidx;
    while(found)
    {
        found = false;
        end = false;
        for(int i=0;i<text.size();i++)
        {
            if(!found)
            {
                if(text.at(i).startsWith("$MACRO_"))
                {
                    found = true;
                    sidx = i;
                    continue;
                }
            }
            else
            {
                if(text.at(i).startsWith("$ENDM"))
                {
                    end = true;
                    eidx = i;
                    break;
                }
            }
        }
        if((found)&&(!end))
            throw std::runtime_error("Macro::LoadMacros: nie odnaleziono końcowego znacznika makra \""+
                                     text.at(sidx).toStdString()+"\".");
        if(found)
        {
            macs.append(Macro(text.mid(sidx, eidx-sidx), data));
            for(int j=eidx;j>=sidx;j--)
                text.removeAt(j);
        }
    }
    return macs;
}

/**
 * Rozwija makro we wskaanym tekście.
 * @param text - odczytany plik szablonu w którym rozwinąć makra.
 * @return - true - znaleziono i rozwinięto makro, false - nie odnaleniono wywołania makra.
 */
bool Macro::Apply(QStringList& text)
{
    return false;
    //<TODO>
}
