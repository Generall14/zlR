#include "DataSection.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>
#include <src/delegat/TypeDelegate.hpp>
#include <src/delegat/RegDelegate.hpp>
#include <src/Data.hpp>
#include <src/delegat/BTypeDelegate.hpp>
#include <src/validator/ValidateContainsOther.hpp>
#include <iostream>
#include <src/DataI.hpp>
#include <src/validator/ValidateContainsConst.hpp>
#include <QDebug>

DataSection::DataSection(Data *data):
    DataI("SECTION", {"NAME", "LMA_ADDR", "VMA_ADDR", "TYPE", "KEEP", "NOLOAD"}, data)
{
    QStringList vals = {"DATA", "BSS", "NOINIT"};

    _validators[0]=(QSharedPointer<QValidator>(new NameValidator("NAME", this)));
    _validators[1]=(QSharedPointer<QValidator>(new ValidateContainsOther("NAME",
                                                                         _datPtr->GetByName("REGION").data())));
    _validators[2]=(QSharedPointer<QValidator>(new ValidateContainsOther("NAME",
                                                                         _datPtr->GetByName("REGION").data())));
    _validators[3]=(QSharedPointer<QValidator>(new ValidateContainsConst(vals)));

    _delegats[0]=(QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(0).data())));
    _delegats[1]=(QSharedPointer<QItemDelegate>(new RegDelegate(this, _datPtr->GetByName("REGION").data())));
    _delegats[2]=(QSharedPointer<QItemDelegate>(new RegDelegate(this, _datPtr->GetByName("REGION").data())));
    _delegats[3]=(QSharedPointer<QItemDelegate>(new TypeDelegate(this, vals)));

    _maxTxts = QStringList{"MMMMMMMMMMMM", "MMMMM", "MMMMM", "MMMMM", "", ""};

    _iEditable[1] = true;
    _iEditable[2] = true;
    _iEditable[3] = true;

    _editable[4] = false;
    _editable[5] = false;

    _desc =
       "/**********************************************************************************************************\r\n"
       " * USER SECTIONS DEFINITION\r\n"
       " *\r\n"
       " * Possible parameters:\r\n"
       " * NAME         - unique name of section\r\n"
       " * LMA_ADDR     - defined region name\r\n"
       " * VMA_ADDR     - defined region name\r\n"
       " * TYPE         - DATA, BSS, NOINIT\r\n"
       " *                DATA - like data section, BSS - like bss section, NOINIT - not initialized data\r\n"
       " * KEEP         - KEEP or empty\r\n"
       " * NOLOAD       - NOLOAD or empty\r\n"
       " **********************************************************************************************************/";

    _minData.append(ReadLine("#define SECTION_0 FUNC_RAM, ROM, RAM, DATA,,"));
}

QVariant DataSection::data(const QModelIndex &index, int role) const
{
    if((index.column()!=4)&&(index.column()!=5))
        return DataI::data(index, role);
    if(role==Qt::CheckStateRole)
    {
        if(!_pureData.at(index.row()).data.at(index.column()).isEmpty())
            return Qt::Checked;
        return Qt::Unchecked;
    }
    if(role==Qt::DisplayRole)
    {
        if(_pureData[index.row()].data[index.column()].isEmpty())
            return "";
        return "YES";
    }
    return DataI::data(index, role);
}

bool DataSection::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if((index.column()!=4)&&(index.column()!=5))
        return DataI::setData(index, value, role);
    if(role==Qt::CheckStateRole)
    {
        QString V = "";
        if(value.toBool())
            V = "YES";
        _pureData[index.row()].data[index.column()] = V;
    }
    else if(role==Qt::EditRole)
        _pureData[index.row()].data[index.column()] = value.toString();
    _dirty = true;
    Check();
    emit Changed();
    return false;
}

Qt::ItemFlags DataSection::flags(const QModelIndex & index) const
{
    if((index.column()!=4)&&(index.column()!=5))
        return DataI::flags(index);

    return Qt::ItemIsEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable;
}
