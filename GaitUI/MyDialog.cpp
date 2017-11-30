#include "MyDialog.h"


MyDialog::MyDialog(QWidget *parent)
	: QDialog(parent)
{
	label = new QLabel(tr("LabelID"));
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);
	findButton = new QPushButton(tr("ConfirmID"));
	findButton->setDefault(true);
	findButton->setEnabled(false);
	closeButton = new QPushButton(tr("Close"));

	connect(lineEdit, &QLineEdit::textChanged,
		this, &MyDialog::enableFindButton);
	connect(findButton, &QPushButton::clicked,
		this, &MyDialog::confirm);
	connect(closeButton, &QPushButton::clicked,
		this, &MyDialog::close);

	// 使用布局管理器布局控件
	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	// 设置窗口的布局管理器
	setLayout(mainLayout);
	setWindowTitle(tr("AddToDatabase"));
	setFixedHeight(sizeHint().height());
};


MyDialog::~MyDialog()
{
}


void MyDialog::enableFindButton(const QString &text)
{
	findButton->setEnabled(text != "");
}

void MyDialog::confirm()
{
	std::string value = lineEdit->text().toStdString();
	f.open("./ID.txt", std::ios::in);
	if (!f)
	{
		return;
	}
	else
	{
		DatabaseID.clear();
		std::string temp;
		while (!f.eof())
		{
			f >> temp;
			DatabaseID.push_back(temp);
		}
		if (getID(DatabaseID, value))
		{
			QMessageBox::information(NULL, 
				"Warning", "ID is Exist, Please Change It", 
				QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}
		else
		{
			emit mySignal();
			emit withParam(1, QString::fromStdString(value));
			this->close();
		}
	}
	f.close();
}