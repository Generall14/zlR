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
    _delegats[4]=(QSharedPointer<QItemDelegate>(new BTypeDelegate(this, "KEEP")));
    _delegats[5]=(QSharedPointer<QItemDelegate>(new BTypeDelegate(this, "NOLOAD")));

    _maxTxts = QStringList{"MMMMMMMMMMMM", "MMMMM", "MMMMM", "MMMMM", "M", "M"};

    _iEditable[1] = true;
    _iEditable[2] = true;
    _iEditable[3] = true;

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
