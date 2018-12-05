#ifndef DATADSTCK_HPP
#define DATADSTCK_HPP

/**
  * @class DataDStck
  * @author Wojciech Kogut
  *
  * Specyfikacja DataI dla <TODO>.
  */

#include <QObject>
#include <src/DataDefs.hpp>

class DataDStck : public DataDefs
{
    Q_OBJECT
public:
    DataDStck(Data* data);
};

#endif
