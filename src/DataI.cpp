#include "DataI.hpp"

DataI::DataI(QString sign):
    _sign(sign)
{

}

/**
 * Odczytuje ze wskazanego pliku część tekstu od wskazanego znacznika ("//##+sign") do pierwszej kolejnej linii
 * zaczynającej się na "//##" lub do końca pliku.
 * @param adr - adres pliku.
 * @param sign - znacznik początku (bez //##).
 * @return Odczytana część pliku jako QStringList.
 */
QStringList DataI::GetPieceOfFile(QString adr, QString sign)
{
    //<TODO>
}

/**
 * Funkcja ładuje dane z pliku o wskazanym adresie (czysci dane i przekierowuje zlecenie do metody wirtualnej
 * FromFileP(...)).
 */
void DataI::FromFile(QString adr)
{
    Clear();
    FromFileP(GetPieceOfFile(adr, _sign));
    emit Changed();
}

/**
 * Funkcja zwraca ciąg tekstów które należy dodać do pliku konfiguracyjnego (wstawia znacznik i wynik funkcji
 * wirtualnej AppendToFileP() ).
 */
QStringList DataI::AppendToFile()
{
    QStringList temp;
    temp.append("//##"+_sign);
    temp.append(AppendToFileP());
    return temp;
}
