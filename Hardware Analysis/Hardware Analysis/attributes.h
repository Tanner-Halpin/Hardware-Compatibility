#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

class Attribute
{
private:
	std::string m_attribute, m_value;

public:
	void setAttribute(std::string& attribute);
	void setvalue(std::string& value);
	Attribute createAttribute(std::string attribute, std::string value);
	std::string get_attribute();
	std::string get_value();

	friend std::ostream& operator<<(std::ostream& out, Attribute& a);
	friend std::istream& operator>>(std::istream& in, std::vector<Attribute>& a);
	friend std::ostream& operator<<(std::ostream& out, std::vector<Attribute>& a);
};

#endif // !ATTRIBUTES_H