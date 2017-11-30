#include "MatchImage.h"


MatchImage::MatchImage()
{

}


MatchImage::~MatchImage()
{
}


void MatchImage::readMatFromFile(QStringList filePath, Dealing& dealing)
{
	std::vector<arma::Mat<double>> temp;
	for (int i = 0; i < filePath.size(); ++i)
	{
		std::string change = filePath.at(i).toStdString();
		change = changeS(change);
		cv::Mat opencv_mat = cv::imread(change, cv::IMREAD_GRAYSCALE);
		/*cv::Mat opencv_mat_out(opencv_mat.rows, opencv_mat.cols, cv::IMREAD_GRAYSCALE);
		cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 15));
		cv::dilate(opencv_mat, opencv_mat_out, element);*/
		arma::mat arma_mat(opencv_mat.rows, opencv_mat.cols);
		cv_mat_to_arma_mat(opencv_mat, arma_mat);
		int mean = getMean(findNoZero(arma_mat).at(1)); //求非零列元素的均值
		arma_mat = arma::shift(arma_mat, 160 - mean, 1);//平移 从行上面进行平移 需要注意引用传参没有改变类型，只是通过返回值来修改原值
		temp.push_back(arma_mat);
	}
	dealing.setSequence(temp);
}


void MatchImage::dealOpticalW(std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& out, std::string databaseID, std::vector<double> &usRowW, std::vector<double> &usColW, std::vector<double> &vsRowW, std::vector<double> &vsColW)
{
	dataBID = databaseID;
	std::vector<arma::mat> returnTemp;
	for (int n = 0; n < sequence.size() - 1; ++n)
	{
		arma::mat f1 = sequence.at(n);
		arma::mat f2 = sequence.at(n + 1);
		arma::mat v1(f1.n_rows, f1.n_cols);
		arma::mat v2;
		v1.zeros();
		v2 = v1;
		fx = v1;
		fy = v1;
		fz = v1;
		int alpha2 = 625;
		int imax = 20; //循环次数

					   //这里计算出来的梯度是有误差的
		arma::mat filter1;
		filter1 << -1 << 1 << arma::endr
			<< -1 << 1 << arma::endr;
		filter1 = filter1 * 0.25;
		arma::mat temp1 = arma::conv2<arma::mat, arma::mat>(f1, filter1, "same");
		arma::mat temp2 = arma::conv2<arma::mat, arma::mat>(f2, filter1, "same");
		fx = temp1 + temp2;


		arma::mat filter11;
		filter11 << -1 << -1 << arma::endr
			<< 1 << 1 << arma::endr;
		filter11 = filter11 * 0.25;
		arma::mat temp11 = arma::conv2<arma::mat, arma::mat>(f1, filter11, "same");
		arma::mat temp22 = arma::conv2<arma::mat, arma::mat>(f2, filter11, "same");
		fy = temp11 + temp22;


		arma::mat filter111;
		filter111 << 1 << 1 << arma::endr
			<< 1 << 1 << arma::endr;
		filter111 = filter111 * 0.25;
		arma::mat temp111 = arma::conv2<arma::mat, arma::mat>(f1, filter111, "same");
		arma::mat temp222 = arma::conv2<arma::mat, arma::mat>(f2, filter111, "same");
		fz = temp111 + temp222;


		for (int i = 0; i < imax; ++i)
		{
			arma::mat mat1 = fx % v1;
			arma::mat mat2 = fy % v2;
			arma::mat mat3 = mat1 + mat2;
			mat3 = mat3 + fz;

			arma::mat mat4 = fx % fx;
			arma::mat mat5 = fy % fy;
			arma::mat mat6 = mat4 + mat5;
			mat6 = mat6 + alpha2;

			arma::mat delta = mat3 / mat6;

			v1 = v1 - fx % delta;
			v2 = v2 - fy % delta;
		}

		u = v1;
		v = v2;
		int d = round(f1.n_rows / 50.0);
		int hs_size = f1.n_rows / d;
		int ws_size = f1.n_cols / d;
		arma::mat us, vs;
		us.zeros(hs_size, ws_size);
		vs = us;

		double N = pow(d, 2.0);
		for (int i = 0; i < hs_size - 1; ++i)
		{
			for (int j = 0; j < ws_size - 1; ++j)
			{
				int hk = i * d;
				int hl = (i + 1) * d - 1;
				int wk = j * d;
				int wl = (j + 1) * d - 1;
				double sum1 = arma::sum(arma::sum(u(arma::span(hk, hl), arma::span(wk, wl))));
				double sum2 = arma::sum(arma::sum(v(arma::span(hk, hl), arma::span(wk, wl))));
				if (sum1 > 0)
				{
					std::cout << sum1 << std::endl;
				}
				if (sum2 > 0)
				{
					std::cout << sum2 << std::endl;
				}
				us(i, j) = sum1 / N;
				vs(i, j) = sum2 / N;
			}
		}
		returnTemp.push_back(us);
		returnTemp.push_back(vs);
		out.push_back(returnTemp);
		returnTemp.clear();
		emit setMessage(n, sequence.size() - 1);
	}
	dealEigW(out, usRowW, usColW, vsRowW, vsColW);
}


void MatchImage::dealEigW(std::vector<std::vector<arma::mat> > &inputs, std::vector<double> &usRowW, std::vector<double> &usColW, std::vector<double> &vsRowW, std::vector<double> &vsColW)
{
	std::vector<std::vector<double>> usRow;
	std::vector<std::vector<double>> usCol;
	std::vector<std::vector<double>> vsRow;
	std::vector<std::vector<double>> vsCol;
	for (int i = 0; i < inputs.size(); ++i)
	{
		arma::mat mus = inputs.at(i).at(0);
		arma::mat mvs = inputs.at(i).at(1);
		std::vector<std::set<int> > MUSrowAndcol = findNoZero(mus);
		std::vector<std::set<int> > MVSrowAndcol = findNoZero(mvs);
		std::vector<std::vector<int> > MUSTOTALrowAndcol = findNoZeroM(mus);
		std::vector<std::vector<int> > MVSTOTALrowAndcol = findNoZeroM(mvs);

		double usRvalue = 0;
		std::vector<double> usRtemp;
		for (auto usi = MUSrowAndcol.at(0).begin(); usi != MUSrowAndcol.at(0).end(); ++usi)
		{
			for (auto usii = MUSTOTALrowAndcol.at(0).begin(); usii != MUSTOTALrowAndcol.at(0).end(); ++usii)
			{
				if (*usi == *usii && mus(*usi, *usii) < 0)
				{
					usRvalue += mus(*usi, *usii);
				}
			}
			usRtemp.push_back(-usRvalue);
		}
		usRow.push_back(usRtemp);

		double usCvalue = 0;
		std::vector<double> usCtemp;
		for (auto usi = MUSrowAndcol.at(1).begin(); usi != MUSrowAndcol.at(1).end(); ++usi)
		{
			for (auto usii = MUSTOTALrowAndcol.at(1).begin(); usii != MUSTOTALrowAndcol.at(1).end(); ++usii)
			{
				if (*usi == *usii && mus(*usi, *usii) < 0)
				{
					usCvalue += mus(*usi, *usii);
				}
			}
			usCtemp.push_back(-usCvalue);
		}
		usCol.push_back(usCtemp);


		double vsRvalue = 0;
		std::vector<double> vsRtemp;
		for (auto vsi = MVSrowAndcol.at(0).begin(); vsi != MVSrowAndcol.at(0).end(); ++vsi)
		{
			for (auto vsii = MVSTOTALrowAndcol.at(0).begin(); vsii != MVSTOTALrowAndcol.at(0).end(); ++vsii)
			{
				if (*vsi == *vsii && mus(*vsi, *vsii) < 0)
				{
					vsRvalue += mus(*vsi, *vsii);
				}
			}
			vsRtemp.push_back(-vsRvalue);
		}
		vsRow.push_back(vsRtemp);

		double vsCvalue = 0;
		std::vector<double> vsCtemp;
		for (auto vsi = MVSrowAndcol.at(1).begin(); vsi != MVSrowAndcol.at(1).end(); ++vsi)
		{
			for (auto vsii = MVSTOTALrowAndcol.at(1).begin(); vsii != MVSTOTALrowAndcol.at(1).end(); ++vsii)
			{
				if (*vsi == *vsii && mvs(*vsi, *vsii) < 0)
				{
					vsCvalue += mvs(*vsi, *vsii);
				}
			}
			vsCtemp.push_back(-vsCvalue);
		}
		vsCol.push_back(vsCtemp);
	}

	usRowW = dealNor(usRow);
	usColW = dealNor(usCol);
	vsRowW = dealNor(vsRow);
	vsColW = dealNor(vsCol);

	QDir *qdir = new QDir;
	bool exist = qdir->exists("DataBase//" + QString::fromStdString(dataBID));
	if (!exist)
	{
		qdir->mkpath("DataBase//" + QString::fromStdString(dataBID));
	}

	writeVector(usRowW, "DataBase//" + dataBID + "//usRowW.txt");
	writeVector(usColW, "DataBase//" + dataBID + "//usColW.txt");
	writeVector(vsRowW, "DataBase//" + dataBID + "//vsRowW.txt");
	writeVector(vsColW, "DataBase//" + dataBID + "//vsColW.txt");
}


void MatchImage::dealMatch(std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& out, std::vector<std::string> dataBaseIDVec)
{
	dataBaseIDVecC.clear();
	dataBaseIDVecC.assign(dataBaseIDVec.begin(), dataBaseIDVec.end());
	std::vector<arma::mat> returnTemp;
	for (int n = 0; n < sequence.size() - 1; ++n)
	{
		arma::mat f1 = sequence.at(n);
		arma::mat f2 = sequence.at(n + 1);
		arma::mat v1(f1.n_rows, f1.n_cols);
		arma::mat v2;
		v1.zeros();
		v2 = v1;
		fx = v1;
		fy = v1;
		fz = v1;
		int alpha2 = 625;
		int imax = 20; //循环次数

					   //这里计算出来的梯度是有误差的
		arma::mat filter1;
		filter1 << -1 << 1 << arma::endr
			<< -1 << 1 << arma::endr;
		filter1 = filter1 * 0.25;
		arma::mat temp1 = arma::conv2<arma::mat, arma::mat>(f1, filter1, "same");
		arma::mat temp2 = arma::conv2<arma::mat, arma::mat>(f2, filter1, "same");
		fx = temp1 + temp2;


		arma::mat filter11;
		filter11 << -1 << -1 << arma::endr
			<< 1 << 1 << arma::endr;
		filter11 = filter11 * 0.25;
		arma::mat temp11 = arma::conv2<arma::mat, arma::mat>(f1, filter11, "same");
		arma::mat temp22 = arma::conv2<arma::mat, arma::mat>(f2, filter11, "same");
		fy = temp11 + temp22;


		arma::mat filter111;
		filter111 << 1 << 1 << arma::endr
			<< 1 << 1 << arma::endr;
		filter111 = filter111 * 0.25;
		arma::mat temp111 = arma::conv2<arma::mat, arma::mat>(f1, filter111, "same");
		arma::mat temp222 = arma::conv2<arma::mat, arma::mat>(f2, filter111, "same");
		fz = temp111 + temp222;


		for (int i = 0; i < imax; ++i)
		{
			arma::mat mat1 = fx % v1;
			arma::mat mat2 = fy % v2;
			arma::mat mat3 = mat1 + mat2;
			mat3 = mat3 + fz;

			arma::mat mat4 = fx % fx;
			arma::mat mat5 = fy % fy;
			arma::mat mat6 = mat4 + mat5;
			mat6 = mat6 + alpha2;

			arma::mat delta = mat3 / mat6;

			v1 = v1 - fx % delta;
			v2 = v2 - fy % delta;
		}

		u = v1;
		v = v2;
		int d = round(f1.n_rows / 50.0);
		int hs_size = f1.n_rows / d;
		int ws_size = f1.n_cols / d;
		arma::mat us, vs;
		us.zeros(hs_size, ws_size);
		vs = us;

		double N = pow(d, 2.0);
		for (int i = 0; i < hs_size - 1; ++i)
		{
			for (int j = 0; j < ws_size - 1; ++j)
			{
				int hk = i * d;
				int hl = (i + 1) * d - 1;
				int wk = j * d;
				int wl = (j + 1) * d - 1;
				double sum1 = arma::sum(arma::sum(u(arma::span(hk, hl), arma::span(wk, wl))));
				double sum2 = arma::sum(arma::sum(v(arma::span(hk, hl), arma::span(wk, wl))));
				if (sum1 > 0)
				{
					std::cout << sum1 << std::endl;
				}
				if (sum2 > 0)
				{
					std::cout << sum2 << std::endl;
				}
				us(i, j) = sum1 / N;
				vs(i, j) = sum2 / N;
			}
		}

		returnTemp.push_back(us);
		returnTemp.push_back(vs);
		out.push_back(returnTemp);
		returnTemp.clear();

		emit setMessage(n, sequence.size() - 1);
	}
	dealEig(out);
	dealEuclideanD();
}


void MatchImage::dealEig(std::vector<std::vector<arma::mat> > &inputs)
{
	std::vector<std::vector<double>> usRow;
	std::vector<std::vector<double>> usCol;
	std::vector<std::vector<double>> vsRow;
	std::vector<std::vector<double>> vsCol;
	for (int i = 0; i < inputs.size(); ++i)
	{
		arma::mat mus = inputs.at(i).at(0);
		arma::mat mvs = inputs.at(i).at(1);
		std::vector<std::set<int> > MUSrowAndcol = findNoZero(mus);
		std::vector<std::set<int> > MVSrowAndcol = findNoZero(mvs);
		std::vector<std::vector<int> > MUSTOTALrowAndcol = findNoZeroM(mus);
		std::vector<std::vector<int> > MVSTOTALrowAndcol = findNoZeroM(mvs);

		double usRvalue = 0;
		std::vector<double> usRtemp;
		for (auto usi = MUSrowAndcol.at(0).begin(); usi != MUSrowAndcol.at(0).end(); ++usi)
		{
			for (auto usii = MUSTOTALrowAndcol.at(0).begin(); usii != MUSTOTALrowAndcol.at(0).end(); ++usii)
			{
				if (*usi == *usii && mus(*usi, *usii) < 0)
				{
					usRvalue += mus(*usi, *usii);
				}
			}
			usRtemp.push_back(-usRvalue);
		}
		usRow.push_back(usRtemp);

		double usCvalue = 0;
		std::vector<double> usCtemp;
		for (auto usi = MUSrowAndcol.at(1).begin(); usi != MUSrowAndcol.at(1).end(); ++usi)
		{
			for (auto usii = MUSTOTALrowAndcol.at(1).begin(); usii != MUSTOTALrowAndcol.at(1).end(); ++usii)
			{
				if (*usi == *usii && mus(*usi, *usii) < 0)
				{
					usCvalue += mus(*usi, *usii);
				}
			}
			usCtemp.push_back(-usCvalue);
		}
		usCol.push_back(usCtemp);


		double vsRvalue = 0;
		std::vector<double> vsRtemp;
		for (auto vsi = MVSrowAndcol.at(0).begin(); vsi != MVSrowAndcol.at(0).end(); ++vsi)
		{
			for (auto vsii = MVSTOTALrowAndcol.at(0).begin(); vsii != MVSTOTALrowAndcol.at(0).end(); ++vsii)
			{
				if (*vsi == *vsii && mus(*vsi, *vsii) < 0)
				{
					vsRvalue += mus(*vsi, *vsii);
				}
			}
			vsRtemp.push_back(-vsRvalue);
		}
		vsRow.push_back(vsRtemp);

		double vsCvalue = 0;
		std::vector<double> vsCtemp;
		for (auto vsi = MVSrowAndcol.at(1).begin(); vsi != MVSrowAndcol.at(1).end(); ++vsi)
		{
			for (auto vsii = MVSTOTALrowAndcol.at(1).begin(); vsii != MVSTOTALrowAndcol.at(1).end(); ++vsii)
			{
				if (*vsi == *vsii && mvs(*vsi, *vsii) < 0)
				{
					vsCvalue += mvs(*vsi, *vsii);
				}
			}
			vsCtemp.push_back(-vsCvalue);
		}
		vsCol.push_back(vsCtemp);
	}

	usRowW = dealNor(usRow);
	usColW = dealNor(usCol);
	vsRowW = dealNor(vsRow);
	vsColW = dealNor(vsCol);
}


std::vector<double> MatchImage::dealNor(std::vector<std::vector<double>> &vec)
{
	int max = getMaxValue(vec);
	std::vector<double> temp;
	int size = 0;
	for (int i = 0; i < max; ++i)
	{
		double value = 0;
		for (int j = 0; j < vec.size(); ++j)
		{
			size = vec.at(j).size();
			if ((i + 1) > size)
			{
				vec.at(j).push_back(0.0);
			}
			else {
				value += vec.at(j).at(i);
			}
		}
		temp.push_back(value);
	}
	return temp;
}


void MatchImage::dealEuclideanD()
{
	int size_sum = dataBaseIDVecC.size();
	std::vector<std::vector<double> > info;
	distance.clear();
	for (int i = 0; i < size_sum; ++i)
	{
		std::string temp = dataBaseIDVecC[i];
		info.push_back(readFromDataBase(".\\DataBase\\" + temp + "\\usRowW.txt"));
		info.push_back(readFromDataBase(".\\DataBase\\" + temp + "\\usColW.txt"));
		info.push_back(readFromDataBase(".\\DataBase\\" + temp + "\\vsRowW.txt"));
		info.push_back(readFromDataBase(".\\DataBase\\" + temp + "\\vsColW.txt"));
		DataSetUV.push_back(info);
		distance.push_back(calcDistance(info));
		info.clear();
	}
	sendDis();
}


std::vector<double> MatchImage::readFromDataBase(std::string path)
{
	std::fstream f;
	std::vector<double> feature;
	std::string d;
	f.open(path, std::ios::in);
	if (!f)
	{
		//QMessageBox::information(NULL, "Warning", "Don't have database", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return feature;
	}
	f >> d;
	while (!f.eof())
	{
		feature.push_back(atof(d.c_str()));
		f >> d;
	}
	f.close();
	return feature;
}


double MatchImage::calcDistance(std::vector<std::vector<double> > feature)
{
	double dis = 0.0;
	std::vector<double> temp = feature.at(0);
	dis += calcCellDis(usRowW, temp);

	temp.clear();
	temp = feature.at(1);
	dis += calcCellDis(usColW, temp);

	temp.clear();
	temp = feature.at(2);
	dis += calcCellDis(vsRowW, temp);

	temp.clear();
	temp = feature.at(3);
	dis += calcCellDis(vsColW, temp);

	return dis;
}


double MatchImage::calcCellDis(std::vector<double> fCell, std::vector<double> temp)
{
	double usCurrentR = 0.0;
	double usSourceR = 0.0;
	double dis = 0.0;
	for (int i = 0; i < fCell.size(); ++i)
	{
		usCurrentR = fCell.at(i);
		if (i > temp.size() - 1)
		{
			usSourceR = 0;
		}
		else
		{
			usSourceR = temp.at(i);
		}
		dis += abs(usCurrentR - usSourceR);
	}
	return dis;
}


void MatchImage::sendDis()
{
	int ID = 0;
	double currrent = distance.at(0);
	for (int i = 1; i < distance.size(); ++i)
	{
		if (distance.at(i) < currrent)
		{
			currrent = distance.at(i);
			ID = i;
		}
	}
	emit setDataBaseID(QString::fromStdString(dataBaseIDVecC.at(ID)));
}