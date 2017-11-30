#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <fstream>

#include <QStringList.h>
#include <QFileInfo.h>
#include <QDir.h>
#include <QThread.h>
#include <QMessageBox.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "Dealing.h"

class MatchImage: public QObject
{
	Q_OBJECT

signals:
	void setMessage(int, int);
	void setDataBaseID(QString);
public:

	MatchImage();
	~MatchImage();
	void readMatFromFile(QStringList filePath, Dealing& dealing);
	void dealOpticalW(std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& out, std::string databaseID, std::vector<double> &usRowW, std::vector<double> &usColW, std::vector<double> &vsRowW, std::vector<double> &vsColW);
	void dealEigW(std::vector<std::vector<arma::mat>>& inputs, std::vector<double> &usRowW, std::vector<double> &usColW, std::vector<double> &vsRowW, std::vector<double> &vsColW);
	void dealMatch(std::vector<arma::mat>& sequence, std::vector<std::vector<arma::mat> >& out, std::vector<std::string> dataBaseIDVec);
	void dealEig(std::vector<std::vector<arma::mat>>& inputs);
	std::vector<double> MatchImage::dealNor(std::vector<std::vector<double>> &vec);
	void dealEuclideanD();
	std::vector<double> readFromDataBase(std::string path);
	double calcDistance(std::vector<std::vector<double> > feature);
	double calcCellDis(std::vector<double>, std::vector<double>);
	void sendDis();


public:

	static std::string changeS(std::string path)
	{
		int position = 0;
		while ((position = path.find("/", position)) != std::string::npos) {
			path.insert(position, "/");
			position += 2;
		}
		return path;
	}

	static void cv_mat_to_arma_mat(const cv::Mat cv_mat_in, arma::mat& arma_mat_out)
	{
		for (int r = 0; r<cv_mat_in.rows; r++) {
			for (int c = 0; c<cv_mat_in.cols; c++) {
				auto t = cv_mat_in.data[r * cv_mat_in.cols + c];
				arma_mat_out(r, c) = static_cast<double>(t);
			}
		}
	}

	template<typename T>
	static void arma_mat_to_cv_mat(const arma::Mat<T>& arma_mat_in, cv::Mat_<T>& cv_mat_out)
	{
		cv::transpose(cv::Mat_<T>(static_cast<int>(arma_mat_in.n_cols),
			static_cast<int>(arma_mat_in.n_rows),
			const_cast<T*>(arma_mat_in.memptr())),
			cv_mat_out);
	}

	static std::vector<std::set<int> > findNoZero(arma::mat m)
	{
		std::vector<std::set<int> > temp;
		std::set<int> tempX;
		std::set<int> tempY;
		for (int i = 0; i < m.n_rows; ++i)
		{
			for (int j = 0; j < m.n_cols; ++j)
			{
				if (m(i, j) != 0)
				{
					tempX.insert(i);
					tempY.insert(j);
				}
			}
		}
		temp.push_back(tempX);
		temp.push_back(tempY);
		return temp;
	}

	static std::vector<std::vector<int> > findNoZeroM(arma::mat m)
	{
		std::vector<std::vector<int> > temp;
		std::vector<int> tempX;
		std::vector<int> tempY;
		for (int i = 0; i < m.n_rows; ++i)
		{
			for (int j = 0; j < m.n_cols; ++j)
			{
				if (m(i, j) != 0)
				{
					tempX.push_back(i);
					tempY.push_back(j);
				}
			}
		}
		temp.push_back(tempX);
		temp.push_back(tempY);
		return temp;
	}

	static int getMean(std::set<int> tempX)
	{
		long long sum = 0;
		for (auto it = tempX.begin(); it != tempX.end(); ++it)
		{
			sum += *it;
		}
		int mean = sum / tempX.size();
		return mean;
	}

	static int getMaxValue(std::vector<std::vector<double>> vec)
	{
		int max = 0;
		for (auto i = vec.begin(); i != vec.end(); ++i)
		{
			if (i->size() > max)
			{
				max = i->size();
			}
		}
		return max;
	}

	static void  writeVector(std::vector<double> vec, std::string name)
	{
		std::fstream out;
		out.open(name, std::ios::app);
		for (int i = 0; i < vec.size(); ++i)
		{
			out << vec[i] << std::endl;
		}
		out.close();
	}

	static bool isFileExist(QString fullFilePath)
	{
		QFileInfo fileInfo(fullFilePath);
		if (fileInfo.exists())
		{
			return true;
		}
		return false;
	}

private:
	arma::mat fx;
	arma::mat fy;
	arma::mat fz;
	arma::mat u;
	arma::mat v;

	std::string dataBID;

	//ÓÃÓÚ´æ´¢Æ¥ÅäÌØÕ÷
	std::vector<double> usRowW;
	std::vector<double> usColW;
	std::vector<double> vsRowW;
	std::vector<double> vsColW;

	std::vector<std::vector<std::vector<double> > > DataSetUV;

	std::vector<std::string> dataBaseIDVecC;

	std::vector<double> distance;
};
