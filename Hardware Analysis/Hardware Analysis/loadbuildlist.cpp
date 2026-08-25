#include "loadbuildlist.h"

loadbuildlist::loadbuildlist(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

loadbuildlist::~loadbuildlist()
{
}

void loadbuildlist::set_names(PC p) // Changed to a Q line edit to allow customizing the already made list
{
	the_PC = p;
	name_labels = 
	{
		ui.cpuLabel,
		ui.gpuLabel,
		ui.storageLabel,
		ui.ramLabel,
		ui.moboLabel,
		ui.psuLabel,
	};

	data_labels =
	{
		the_PC.CPU,
		the_PC.GPU,
		the_PC.SSD,
		the_PC.RAM,
		the_PC.Motherboard,
		the_PC.PSU,
	};

	attribute_labels =
	{
		ui.label,
		ui.label_2,
		ui.label_3,
		ui.label_4,
		ui.label_5,
		ui.label_6
	};

	for (size_t i = 0; i < 6; ++i)
	{
		std::stringstream ss;

		ss << *data_labels[i];
		QString s = QString::fromStdString(ss.str());

		name_labels[i]->setText(s);
		attribute_labels[i]->setText(data_labels[i]->print_components());
	}
}

// Function to save changes for swapped out parts, and updates the Computer Build Roster and Component List

void loadbuildlist::on_saveChanges_clicked() 
{
	std::vector<QString> terms = { "Processor", "Graphics", "Storage", "RAM", "Motherboard", "PSU" };
	PC* p = new PC(the_PC);

	Component* compList[6] = { p->CPU, p->GPU, p->SSD, p->RAM, p->Motherboard, p->PSU };

	SQLParsing q;

	for (size_t i = 0; i < 6; ++i)
	{
		data_labels[i]->fullname = name_labels[i]->text().toStdString();
		name_labels[i]->setText(QString::fromStdString(data_labels[i]->fullname));

		compList[i]->attributes.clear();
		q.CPU_Specs(p, compList[i], terms[i]);

		this->close();
	}

	delete p;
}