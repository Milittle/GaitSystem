#pragma once
#include <vector>
#include <mutex>

#include <armadillo>

class Dealing
{
public:
	Dealing();
	~Dealing();
public:
	std::vector<arma::Mat<double> > getSequenceMat();
	void setSequence(std::vector<arma::Mat<double> > sequence);
	std::vector<arma::Mat<double> > sequenceMat;
private:
	std::mutex mt;
};

