#include <iostream>
#include <vector>
#include <sstream>
#include "loadbuildlist.h"
#include "qstandarditemmodel.h"
#include "parts.h"

std::ostream& operator<<(std::ostream& out, Component& c) // Display a component 
{
	out << c.fullname;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, Component& c) // Inputting a component object
{
	in >> c.company >> c.type >> c.version >> c.model;
	return in;
}

Component* Parts::CreateItem(std::string name) // Creation of a computer component. A "part" 
{
	std::vector<Component*> customPC;
	Component* d = new Component;

	d->fullname = name;

	count++;

	std::stringstream ss(name);
	std::string word;

	std::string* attributesList[4]{ &d->company, &d->type, &d->version, &d->model }; 
	
	// Parts are parsed in this manner to let them be searchable by company, version, etc

	int i = 0;
	while (ss >> word)
	{
		*attributesList[i] = word;
		i++;

		if (i > 3)
			break;
	}
	i = 0;

	componentList.push_back(d);

	return d;
}

void Parts::getProcessor(std::string command) // Powershell command for displaying the command
{
	QProcess process;

	QString program = "powershell.exe";
	QStringList arguments;

	arguments << "-Command" << QString::fromStdString(command);
	process.start(program, arguments);

	process.waitForFinished();
	QString output = process.readAllStandardOutput();

	gathered_parts.push_back(output.trimmed());
}

// //out << c.company << " " << c.type << " " << c.version << " " << c.model << "\n";

// Above only showed the specifications of the name. The overload now shows the fullname of the component. 
// The format above is meant for searching for specific parts by company(AMD, Intel, NVIDIA), the type (Ryzen, Intel Core, Xeon, Radeon), version( i7, Ryzen 8, etc), and model (i5-10600k)


QString Component::get_attribute(int index) 
{
	return QString::fromStdString(this->attributes[index].get_attribute());
}

QString Component::get_value(int index)
{
	return QString::fromStdString(this->attributes[index].get_value());
}

// Print component attributes:

QString Component::print_components()
{
	std::ostringstream ss;
	for (auto& i : this->attributes)
	{
		ss << i.get_attribute() << ":  " << i.get_value() << std::endl;
	}

	QString result = QString::fromStdString(ss.str());
	return result;
}