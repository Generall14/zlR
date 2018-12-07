#include "DataRegion.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateHex.hpp>
#include <src/validator/ValidateRWX.hpp>
#include <src/validator/ValidateSize.hpp>
#include <src/validator/ValidateName.hpp>
#include <QFont>
#include <QColor>
#include <iostream>

DataRegion::DataRegion(Data *data):
    DataI("REGION", {"NAME", "RIGHTS", "ADR", "SIZE"}, data)
{
    _validators[0]=(QSharedPointer<QValidator>(new NameValidator("NAME", this)));
    _validators[1]=(QSharedPointer<QValidator>(new RWXValidator()));
    _validators[2]=(QSharedPointer<QValidator>(new HexValidator(8)));
    _validators[3]=(QSharedPointer<QValidator>(new SizeValidator()));

    _delegats[0]=(QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(0).data())));
    _delegats[1]=(QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(1).data())));
    _delegats[2]=(QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(2).data())));
    _delegats[3]=(QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(3).data())));

    _maxTxts = QStringList{"MMMMMMMMMMMMMMMM", "RWX", "0x00000000", "666M"};

    _desc = "/**********************************************************************************************************\r\n"
            " *\r\n"
            " * Max number of regions 20 <0..19>\r\n"
            " *\r\n"
            " **********************************************************************************************************/";

    _minData.append(ReadLine("#define REGION_0 ROM , RX , 0x08000000 , 1k"));
    _minData.append(ReadLine("#define REGION_1 RAM , RWX , 0x20000000 , 1k"));

    _otemplate = true;
    _minCnt = 1;
}

QVariant DataRegion::data(const QModelIndex &index, int role) const
{
    if(index.column() == 3 && role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else
        return DataI::data(index, role);
}
