#include <iostream>
#include <string>
#include "attributes.h"

void Attribute::setAttribute(std::string& attribute) { m_attribute = attribute; }
void Attribute::setvalue(std::string& value) { m_value = value; }

Attribute Attribute::createAttribute(std::string attribute, std::string value) // Create an attribute specification for a component
{
	Attribute a;
	a.setAttribute(attribute), a.setvalue(value);

	return a;
}

std::string Attribute::get_attribute()
{
	return m_attribute;
}

std::string Attribute::get_value()
{
	return m_value;
}

std::ostream& operator<<(std::ostream& out, Attribute& a) // Output a an individual component attribute
{
	out << a.m_attribute << ":   " << a.m_value;
	return out;
}

std::istream& operator>>(std::istream& in, std::vector<Attribute>& a) // Inputting in a list of attributes
{
	in >> a;
	return in;
}

std::ostream& operator<<(std::ostream& out, std::vector<Attribute>& a) // Output format for an an list of component attributes
{
	for (size_t i = 0; i < a.size(); i++)
	{
		out << a[i].m_attribute << ": " << a[i].m_value << std::endl;
	}
	return out;
}
