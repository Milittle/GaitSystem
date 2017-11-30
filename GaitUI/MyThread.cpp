#include "MyThread.h"

MyThread::MyThread()
{
}


MyThread::~MyThread()
{
}


void MyThread::dealReadImageMat(QStringList filelist)
{
	dealing.sequenceMat.clear();
	std::thread t(&MatchImage::readMatFromFile, &MI1, filelist, std::ref(dealing));
	t.detach();
}


void MyThread::dealOpticalVec(MatchImage & MI, std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& UV, std::string databaseID, std::vector<double> &usRowW, std::vector<double> &usColW, std::vector<double> &vsRowW, std::vector<double> &vsColW)
{
	std::thread t(&MatchImage::dealOpticalW, &MI, std::ref(sequence), std::ref(UV), databaseID, std::ref(usRowW), std::ref(usColW), std::ref(vsRowW), std::ref(vsColW));
	t.detach();
}


void MyThread::dealMatch(MatchImage & MI, std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat>> &UV, std::vector<std::string> dataBaseIDVec)
{
	std::thread t(&MatchImage::dealMatch, &MI, std::ref(sequence), std::ref(UV), dataBaseIDVec);
	t.detach();
}
