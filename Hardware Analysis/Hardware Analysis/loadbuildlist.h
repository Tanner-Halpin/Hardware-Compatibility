#pragma once

#include <QDialog>
#include "ui_loadbuildlist.h"
#include "parts.h"
#include "build.h"
#include "newlymadelist.h"
#include "hardwareanalysis.h"
#include "sqlparsing.h"
#include "attributes.h"
#include <sstream>

class loadbuildlist : public QDialog, public Ui::loadbuildlistClass
{
	Q_OBJECT

public:
	loadbuildlist(QWidget *parent = nullptr);
	~loadbuildlist();
	void set_names(PC p);
	std::vector<QLineEdit*> name_labels;
	std::vector<QLabel*> attribute_labels;
	std::vector<Component*> data_labels;

private slots:
	void on_saveChanges_clicked();

private:
	Ui::loadbuildlistClass ui;
	PC the_PC;
};

