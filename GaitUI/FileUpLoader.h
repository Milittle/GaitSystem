#pragma once
#include <vector>
#include <set>

#include <QDir.h>

#include <armadillo>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Dealing.h"

class FileUpLoader
{
public:
	FileUpLoader();
	~FileUpLoader();
public:
	__declspec(dllexport) QStringList readAllFileName(std::string filePath);
};

