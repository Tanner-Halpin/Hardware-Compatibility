#ifndef PARTS_H
#define PARTS_H
#include "attributes.h"
#include "hardwareanalysis.h"

struct Component
{
	std::string fullname = "";
	std::string company="", type="", version="", model="";
	std::vector<Attribute> attributes;
	QString print_components();
	QString get_attribute(int index);
	QString get_value(int index);
};

std::ostream& operator<<(std::ostream& out, Component& c);
std::ifstream& operator>>(std::ifstream& in, Component& c);

class Parts : public Attribute
{
protected:
	inline static std::vector<Component*> componentList;

public:
	int count = 0;
	std::vector<QString> gathered_parts;
	Component* CreateItem(std::string name);
	void getProcessor(std::string command);
};


#endif // !PARTS_H
