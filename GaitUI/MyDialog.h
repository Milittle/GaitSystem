#pragma once

#include <fstream>

#include <QDialog.h>
#include <QLabel.h>
#include <QLineEdit.h>
#include <QCheckBox.h>
#include <QPushButton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow.h>
#include <QApplication.h>
#include <QMessageBox.h>

#include "MyEvent.h"

class MyDialog: public QDialog
{
	Q_OBJECT
public:
	MyDialog(QWidget *parent = 0);
	~MyDialog();
signals:
	void mySignal();
	void withParam(int, QString); //信号只需要定义就好
private slots:
	void confirm();
	void enableFindButton(const QString &text);

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QPushButton *findButton;
	QPushButton *closeButton;
	std::fstream f;
	std::vector<std::string> DatabaseID;
private:
	static bool getID(std::vector<std::string> ID, std::string valueID)
	{
		bool t = false;
		for (int i = 0; i < ID.size(); ++i)
		{
			if (ID[i] == valueID)
			{
				t = true;
				return t;
			}
		}
		return t;
	}
};
