#pragma once
#include <thread>
#include <iostream>

#include "MatchImage.h"

class MyThread: public QObject
{
	Q_OBJECT
public:
	MyThread();
	~MyThread();
public:
	void dealReadImageMat(QStringList filelist);
	void dealOpticalVec(MatchImage & MI, std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& UV, std::string databaseID, std::vector<double> &, std::vector<double> &, std::vector<double> &, std::vector<double> &);
	void dealMatch(MatchImage & MI, std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> > &UV, std::vector<std::string> dataBaseIDVec);
	Dealing dealing;
	//���̴߳������ĺ���ʱ���߳���ʹ�õĶ���Ҫ��֤�������ڴ����߳���������
 	MatchImage MI1;
	MatchImage MI2;
};

