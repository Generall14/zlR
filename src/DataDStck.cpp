#include "DataDStck.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>

DataDStck::DataDStck(Data *data):
    DataDefs(data, "DSTCK", {"NAME", "VAL"})
{
    _validators[0]=(QSharedPointer<QValidator>(new NameValidator("NAME", this)));

    _delegats[0]=QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(0).data()));

    _maxTxts = QStringList{"MMMMMMMMMMMMMMMM", "MMMMMMMM"};

    _editable[0] = false;

    _minData.append(ReadLine("#define MAIN_STACK_SIZE 1024"));
    _minData.append(ReadLine("#define PROCESS_STACK_SIZE 1024"));
}
