#include "sqlparsing.h"
#include "loadbuildlist.h"

void SQLParsing::CPU_Specs(PC* p, Component* component, QString processor)
{
	the_PC = p;
	QSqlQuery query;

	QSqlQuery q;
	q.exec("SELECT " + processor + "_Name FROM Computer_" + processor + " WHERE " + processor + "_Name = '" + QString::fromStdString(component->fullname) + "'");

	QSqlQuery a;

	QSqlQuery the_size;
	the_size.prepare("SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Computer_" + processor + "'");
	the_size.exec();

	if (the_size.next())
	{
		size_table = the_size.value(0).toInt();
	}

	while (q.next())
	{
		if (component->fullname == q.value(0).toString())
		{
			for (int i{ 0 }; i < size_table - 1; ++i)
			{
				a.prepare("SELECT COL_NAME(OBJECT_ID('Computer_" + processor + "'),:index)");
				a.bindValue(":index", i + 2);
				
				a.exec();
				
				while (a.next())
				{
					QString a_value = a.value(0).toString();
					query.exec("SELECT " + a_value + " FROM Computer_" + processor + " WHERE " + processor + "_NAME = '" + QString::fromStdString(component->fullname) + "'");

					if (query.next())
					{
						QString term = query.value(0).toString();
						QString name = a.value(0).toString();

						component->attributes.push_back(the_PC->createAttribute(name.toStdString(), term.toStdString()));
					}
				}
			}
		}
	}
}

// * Line 49: I set this up a little strangely so I want to explain it a little more. 
// * Each Computer Part list has a list; a vector of 'attributes' which are the specifications of each individual component, however each of those are apart of the whole PC object 
// * Hence why it is 'the_PC->createAttribute()'. It is making an attribute for a part, but it is stored as data apart of the entire computer part list