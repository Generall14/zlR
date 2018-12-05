#ifndef DATADREG_HPP
#define DATADREG_HPP

/**
  * @class DataDReg
  * @author Wojciech Kogut
  *
  * Specyfikacja DataI dla <TODO>.
  */

#include <QObject>
#include <src/DataDefs.hpp>

class DataDReg : public DataDefs
{
    Q_OBJECT
public:
    DataDReg(Data* data);
};

#endif
