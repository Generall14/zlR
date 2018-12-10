#include "DataDReg.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>
#include <src/validator/ValidateContainsOther.hpp>
#include <src/delegat/RegDelegate.hpp>
#include <src/Data.hpp>

DataDReg::DataDReg(Data *data):
    DataDefs(data, "DREG", {"NAME", "VAL"})
{
    _validators[0]=(QSharedPointer<QValidator>(new NameValidator("NAME", this)));
    _validators[1]=(QSharedPointer<QValidator>(new ValidateContainsOther("NAME",
                                                                         _datPtr->GetByName("REGION").data())));

    _delegats[0]=QSharedPointer<QItemDelegate>(new LEDelegate(this, _validators.at(0).data()));
    _delegats[1]=(QSharedPointer<QItemDelegate>(new RegDelegate(this, _datPtr->GetByName("REGION").data())));

    _maxTxts = QStringList{"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM", "MMMMMMMMMMMM"};

    _editable[0] = false;

    _iEditable[1] = true;

    _minData.append(ReadLine("#define STACK_REGION                        RAM"));
    _minData.append(ReadLine("#define HEAP_REGION                         RAM"));
    _minData.append(ReadLine("#define VECTORS_VMA_REGION                  ROM"));
    _minData.append(ReadLine("#define VECTORS_LMA_REGION                  ROM"));
    _minData.append(ReadLine("#define AFTERVECTORS_VMA_REGION             ROM"));
    _minData.append(ReadLine("#define AFTERVECTORS_LMA_REGION             ROM"));
    _minData.append(ReadLine("#define RODATA_VMA_REGION                   ROM"));
    _minData.append(ReadLine("#define RODATA_LMA_REGION                   ROM"));
    _minData.append(ReadLine("#define TEXT_VMA_REGION                     ROM"));
    _minData.append(ReadLine("#define TEXT_LMA_REGION                     ROM"));
    _minData.append(ReadLine("#define DATA_VMA_REGION                     RAM"));
    _minData.append(ReadLine("#define DATA_LMA_REGION                     ROM"));
    _minData.append(ReadLine("#define BSS_VMA_REGION                      RAM"));
    _minData.append(ReadLine("#define BSS_LMA_REGION                      RAM"));
}
