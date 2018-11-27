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
            macs.append(Macro(text.mid(sidx, eidx-sidx+1), data));
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
    if(_expanded.isEmpty())
        _expanded = ExpandAll();
    if(_expanded.isEmpty())
        return false;

    int fi, li;
    for(int i=0;i<text.size();i++)
    {
        fi = text.at(i).indexOf("$MAC[");
        if(fi<0)
            continue;
        li = text.at(i).indexOf("]", fi);
        if(li<0)
            throw std::runtime_error("Macro::Apply: brak domknięcia nawiasu w \""+
                                     text.at(i).toStdString()+"\"");
        QString pre, su, name;
        name = text.at(i).mid(fi+5, li-fi-5);
        if(name.compare(_name))
            continue;
        pre = text.at(i).mid(0, fi);
        su = text.at(i).mid(li+1);
        text[i].remove(fi, li-fi+1);

        if(_expanded.size()==1)
            text[i] = pre+_expanded.at(0)+su;
        else
        {
            text[i] = pre+_expanded.at(0);
            for(int k=_expanded.size()-1;k>0;k--)
            {
                text.insert(i+1, _expanded.at(k)+su);
                su.clear();
            }
        }
        return true;
    }

    return false;
}

/**
 * Zwraca rozwinięty tekst dla struktury o wskazanym nmerze.
 */
QStringList Macro::ExpandSingle(int i)
{
    QStringList temp = _text;

    bool found = true;
    int fi, li;
    QString loc;
    while(found)
    {
        found = false;
        for(int l=0;l<temp.size();l++)
        {
            fi = temp.at(l).indexOf("$LOC[");
            if(fi<0)
                continue;
            li = temp.at(l).indexOf("]", fi);
            if(li<0)
                throw std::runtime_error("Macro::ExpandSingle: brak domknięcia nawiasu w \""+
                                         temp.at(l).toStdString()+"\"");

            loc = temp.at(l).mid(fi+5, li-fi-5);
            temp[l].remove(fi, li-fi+1);
            temp[l].insert(fi, _data->GetLocalByName(i, loc));

            found = true;
            break;
        }
    }

    return temp;
}

/**
 * Zwraca rozwinięty tekst dla wszystkich struktur.
 */
QStringList Macro::ExpandAll()
{
    QStringList temp;
    for(int i=0;i<_data->rowCount();i++)
        temp.append(ExpandSingle(i));
    return temp;
}
