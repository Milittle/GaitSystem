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
	//给线程传输对象的函数时候，线程内使用的对象，要保证生命周期大于线程生命周期
 	MatchImage MI1;
	MatchImage MI2;
};

