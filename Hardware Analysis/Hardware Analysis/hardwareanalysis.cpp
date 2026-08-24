#include "hardwareanalysis.h"
#include "newlist.h"
#include "newlymadelist.h"
#include "ui_NewList.h"
#include "loadbuildlist.h"
#include "attributes.h"
#include "parts.h"
#include <sstream>

HardwareAnalysis::HardwareAnalysis(QWidget *parent) 
    : QWidget(parent)
{
    ui.setupUi(this);
	Parts p;

	// Below are CLI Commands that will retrieve computer information from your computer. 

	p.getProcessor("(Get-WmiObject Win32_Processor).Name");
	p.getProcessor("(Get-CimInstance Win32_VideoController).Name");
	p.getProcessor("(Get-CimInstance -ClassName Win32_DiskDrive).Model");
	p.getProcessor("(Get-WmiObject win32_baseboard).Product + ' ' + (Get-WmiObject win32_baseboard).Manufacturer");

	QString parts[6] = { "CPU:  ", "GPU:  ", "Storage:  ", "Motherboard:  ", "Memory:  ", "Power Supply:  " };

	for (size_t i = 0; i < p.gathered_parts.size(); ++i) 
	{
		ui.addressName->addItem(parts[i] + p.gathered_parts[i]);
	}
}

HardwareAnalysis::~HardwareAnalysis()
{}

void HardwareAnalysis::on_deleteButton_clicked()
{
	QListWidgetItem* currentItem = ui.hardwareList->currentItem();
	if (currentItem)
	{
		int row = ui.hardwareList->row(currentItem); // Index in the QListWidgetItem
		ui.hardwareList->takeItem(row);

		b.get_buildRoster().erase(b.get_buildRoster().begin() + row); // Erase that same index in the Build Roster vector

		delete currentItem;
	}
}

void HardwareAnalysis::on_hardwareList_doubleClicked() // GUI element that allows you to select the Computer Build list
{
	loadbuildlist c(this);
	QListWidgetItem* current = ui.hardwareList->currentItem();
	int row = ui.hardwareList->row(current);

	PC p = b.get_buildRoster()[row];

	c.set_names(p);

	if (current)
	{
		c.exec();
	}
}


void HardwareAnalysis::on_addButton_clicked() // After enetering in each component name, click add to create the list
{
	NewList dialog(this);
	dialog.exec();

	std::stringstream word;

	if (b.get_buildRoster().size() > 0 && status == true)
	{
		dialog.set_name();

		word << b.get_buildRoster()[b.get_buildRoster().size() - 1];
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(word.str()), ui.hardwareList);
	}
	status = false; 
	// The 'status' bool (created in newlymadelist.h, will prevent a list from being made when selecting 'x' on the keyboard.
}