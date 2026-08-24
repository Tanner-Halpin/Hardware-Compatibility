#pragma once

#include <QDialog>
#include "ui_newlist.h"
#include "hardwareanalysis.h"
#include <qcompleter.h>
#include <qvector.h>
#include <qsqlquerymodel.h>

inline std::vector<std::string> names;

class NewList : public QDialog, public Ui::NewListClass
{
	Q_OBJECT

public:
	NewList(QWidget *parent = nullptr);
	~NewList();
	void set_name();
	QVector<QString> sql_parse(QString component);
	std::vector<QLineEdit*> name_labels;

private slots:
	void on_okButton_clicked();

private:
	Ui::NewListClass ui;
};