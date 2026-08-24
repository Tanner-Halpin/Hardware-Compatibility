#ifndef SQL_PARSING
#define SQL_PARSING

#include <qsqlquery.h>
#include "loadbuildlist.h"
#include "build.h"

class SQLParsing 
{
public:
	void CPU_Specs(PC* p, Component* component, QString processor);

private: 
	PC* the_PC;
	int size_table;
};

#endif