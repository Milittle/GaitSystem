#pragma once

#include <fstream>
#include <sstream>

#include <QtWidgets/QMainWindow>
#include "ui_GaitUI.h"
#include <QMessageBox.h>
#include <QFileDialog.h>
#include <QTimer.h>

#include <opencv2\core\core.hpp>

#include "FileUpLoader.h"
#include "MyThread.h"
#include "MyDialog.h"

class GaitUI : public QMainWindow
{
	Q_OBJECT

public:
	GaitUI(QWidget *parent = Q_NULLPTR);
public slots:
	void changePicture();
	void setProgressBar(int, int);
	void setRecognitionID(QString);
private:
	Ui::GaitUIClass ui;
protected:
	bool eventFilter(QObject *target, QEvent *e);
	bool event(QEvent *event);
	void dealSignal();
	void dealSignalWithParam(int, QString);
	bool setDataBaseID(std::string temp);
	void readDataBaseNum(std::string);
	std::vector<double> readDataBaseInfo(std::string);
	void setControlStatus(bool);
	void showWarning(std::string);
private:
	MyThread myThread;
	MyDialog myDialog;
	int dataBaseNum;
	std::vector<arma::mat> sequence;
	std::vector<std::vector<arma::mat> > UV;
	std::string dataBaseID;
	std::vector<std::string> dataBaseIDVec;
	std::vector<double> usRowW;
	std::vector<double> usColW;
	std::vector<double> vsRowW;
	std::vector<double> vsColW;
	std::vector<std::vector<std::vector<double> > > databaseUV;
	MatchImage MM;
	bool signT;
private:
	int count;
	QStringList list;
	QPixmap *pix;
	QTimer *timer;
};