#include "GaitUI.h"


GaitUI::GaitUI(QWidget *parent)
	: QMainWindow(parent),
	  dataBaseNum(0),
	  signT(true)
{
	ui.setupUi(this);
	ui.loadModelBtn->installEventFilter(this);
	ui.addToDataBaseBtn->installEventFilter(this);
	ui.recognitionBtn->installEventFilter(this);
	ui.deleteDataBaseBtn->installEventFilter(this);
	ui.progressBar->setVisible(false);
	pix = new QPixmap();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(changePicture()));
	count = 0;
	void (MyDialog::*funSignal)() = &MyDialog::mySignal;
	void (MyDialog::*testSignal)(int, QString) = &MyDialog::withParam;
	connect(&myDialog, funSignal, this, &GaitUI::dealSignal);
	connect(&myDialog, testSignal, this, &GaitUI::dealSignalWithParam);
	void (MatchImage::*message)(int, int) = &MatchImage::setMessage;
	connect(&MM, message, this, &GaitUI::setProgressBar);
	void (MatchImage::*IDMess)(QString) = &MatchImage::setDataBaseID;
	connect(&MM, IDMess, this, &GaitUI::setRecognitionID);


	readDataBaseNum("./ID.txt");
	ui.database_number_edit->clear();
	ui.database_number_edit->append(QString::number(dataBaseNum, 10));
	ui.database_number_edit->setAlignment(Qt::AlignCenter);
}


bool GaitUI::eventFilter(QObject * target, QEvent * e)
{
	if (target == ui.loadModelBtn)
	{
		if (e->type() == QEvent::MouseButtonPress)
		{
			if (!signT)
			{
				return QMainWindow::eventFilter(target, e);
			}
			QString dir = QFileDialog::getExistingDirectory(this, 
				tr("Open Model"), "D://data", 
				QFileDialog::ShowDirsOnly | 
				QFileDialog::DontResolveSymlinks);
			FileUpLoader test;
			list = test.readAllFileName(dir.toStdString());
			timer->start(40);
			count = 0;
			if (list.size() > 0)
			{
				myThread.dealReadImageMat(list);
			}
		}
	}
    else if (target == ui.addToDataBaseBtn)
	{
		if (e->type() == QEvent::MouseButtonPress)
		{
			if (!signT)
			{
				return QMainWindow::eventFilter(target, e);
			}
			sequence = myThread.dealing.getSequenceMat();
			if (sequence.size() > 2)
			{
				myDialog.exec();
			}
			else
			{
				QMessageBox::information(NULL, "Warning", "Don't Have Model", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			}
		}
	}
	else if (target == ui.recognitionBtn)
	{
		if (e->type() == QEvent::MouseButtonPress)
		{
			if (!signT)
			{
				return QMainWindow::eventFilter(target, e);
			}
			if (dataBaseNum == 0)
			{
				showWarning("DataBase Doesn't Have Person!");
				return QMainWindow::eventFilter(target, e);
			}
			sequence = myThread.dealing.getSequenceMat();
			if (sequence.size() < 2)
			{
				showWarning("Don't Have Model");
				return QMainWindow::eventFilter(target, e);
			}
			UV.clear();
			myThread.dealMatch(MM, sequence, UV, dataBaseIDVec);
			setControlStatus(false);
		}
	}
	return QMainWindow::eventFilter(target, e);
}


bool GaitUI::event(QEvent *event)
{
	MyEvent* pEvent = (MyEvent*)event;
	switch (event->type())
	{
		case QEvent::User + 1:
			ui.database_number_edit->append(QString::number(pEvent->GetValue(), 10));
			break;
		default:
			break;
	}
	return QMainWindow::event(event);
}


void GaitUI::changePicture()
{
	QString picName;

	if (count > list.size() - 1)
	{
		timer->stop();
		return;
	}
	picName = list.at(count);
	count += 1;
	pix->load(picName, 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
	ui.image_show_label->setPixmap(*pix);
	update();
}


bool GaitUI::setDataBaseID(std::string temp)
{
	std::fstream f;
	f.open("ID.txt", std::ios::app);
	if (!f)
	{
		return false;
	}
	else
	{
		f << temp << std::endl;
	}
	dataBaseIDVec.push_back(temp);
	return true;
}


void GaitUI::readDataBaseNum(std::string file)
{
	std::fstream f;
	f.open(file, std::ios::in);
	if (!f)
	{
		showWarning("Load DabaseNum Failure");
		return;
	}
	else
	{
		std::string temp;
		char buffer[255];
		while (!f.eof())
		{
			f.getline(buffer, 255);
			temp = buffer;
			if (temp != "")
			{
				dataBaseIDVec.push_back(temp);
				dataBaseNum++;
			}
		}
	}
	f.close();
}


std::vector<double> GaitUI::readDataBaseInfo(std::string path)
{
	std::fstream f;
	std::vector<double> feature;
	std::string d;
	f.open(path, std::ios::in);
	if (!f)
	{
		QMessageBox::information(NULL, "Warning", "Don't have database", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return feature;
	}
	while (!f.eof())
	{
		f >> d;
		feature.push_back(atof(d.c_str()));
	}
	f.close();
	return feature;
}


void GaitUI::setControlStatus(bool sign)
{
	ui.addToDataBaseBtn->setEnabled(sign);
	ui.deleteDataBaseBtn->setEnabled(sign);
	ui.loadModelBtn->setEnabled(sign);
	ui.recognitionBtn->setEnabled(sign);
	signT = sign;
}


void GaitUI::showWarning(std::string info)
{
	QMessageBox::information(NULL, "Warning", QString::fromStdString(info), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/*------信号处理函数定义------*/
void GaitUI::dealSignal()
{
	/*ui.database_number_edit->clear();
	ui.database_number_edit->append("hello");*/
}


void GaitUI::dealSignalWithParam(int n, QString hello)
{
	dataBaseID = hello.toStdString();
	if (setDataBaseID(dataBaseID))
	{
		dataBaseNum++;
		ui.database_number_edit->clear();
		ui.database_number_edit->setAlignment(Qt::AlignCenter);
		ui.database_number_edit->append(QString::number(dataBaseNum, 10));
		sequence = myThread.dealing.getSequenceMat();
		UV.clear();
		usRowW.clear(), usColW.clear(), vsRowW.clear(), vsColW.clear();
		myThread.dealOpticalVec(MM, sequence, UV, dataBaseID, usRowW, usColW, vsRowW, vsColW);
		setControlStatus(false); //设置控件不可用
	}
	else
	{
		QMessageBox::information(NULL, "Warning", "Insert ID Failure", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}


void GaitUI::setProgressBar(int n, int sum)
{
	ui.progressBar->setVisible(true);
	ui.progressBar->setRange(0, sum);
	ui.progressBar->setValue(n);
	if (n == sum - 1)
	{
		ui.progressBar->setValue(0);
		ui.progressBar->setVisible(false);
		QMessageBox::information(NULL, "Tips", "Finished", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		setControlStatus(true); //设置空间不可用
	}
}


void GaitUI::setRecognitionID(QString RecognitionID)
{
	ui.recognition_obj_edit->clear();
	ui.recognition_obj_edit->append(RecognitionID);
	ui.recognition_obj_edit->setAlignment(Qt::AlignCenter);
}