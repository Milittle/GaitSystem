#include "Dealing.h"

Dealing::Dealing()
{
}


Dealing::~Dealing()
{
}

std::vector<arma::Mat<double>> Dealing::getSequenceMat()
{
	return sequenceMat;
}

void Dealing::setSequence(std::vector<arma::Mat<double>> sequence)
{
	mt.lock();
	sequenceMat.assign(sequence.begin(), sequence.end());
	mt.unlock();
}

