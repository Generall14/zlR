#include "Macro.hpp"
#include <src/Data.hpp>
#include <src/DataI.hpp>

Macro::Macro(QString name, QStringList text, DataI* data):
    _name(name),
    _text(text),
    _data(data)
{

}

/**
 * Ładuje i rozwija wszystkie makra w tekście podanym jako QStringList. Dane do rozwinięcia
 * makr pobierze z przekazanego wskaźnika do obiektu Data.
 * @param text - odczytany plik szablonu.
 * @param data - wskaźnik na obiekt z danymi do rozwinięcia makr.
 */
void Macro::ProcessAll(QStringList& text, Data* data)
{
    //<TODO>
}

/**
 * Ładuje makra z wskazanego pliku (usuwa z niego tekst definicji makr).
 * @param text - odczytany plik szablonu z którego załadowane zostaną makra.
 * @param data - wskaźnik na obiekt z danymi do rozwinięcia makr.
 * @return - lista odczytanych makr.
 */
QList<Macro> Macro::LoadMacros(QStringList& text, Data* data)
{
    //<TODO>
}

/**
 * Rozwija makro we wskaanym tekście.
 * @param text - odczytany plik szablonu w którym rozwinąć makra.
 * @return - true - znaleziono i rozwinięto makro, false - nie odnaleniono wywołania makra.
 */
bool Macro::Apply(QStringList& text)
{
    //<TODO>
}
