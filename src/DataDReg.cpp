#include "DataDReg.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>

DataDReg::DataDReg(Data *data):
    DataDefs(data, "DREG", {"NAME", "VAL"})
{
    _validators[0]=(QSharedPointer<QValidator>(new NameValidator("NAME", this)));

    _delegats[0]=QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(0).data()));

    _maxTxts = QStringList{"MMMMMMMMMMMMMMMM", "MMMMMMMM"};

    _editable[0] = false;
}
