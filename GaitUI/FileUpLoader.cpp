#include "FileUpLoader.h"

FileUpLoader::FileUpLoader()
{
}


FileUpLoader::~FileUpLoader()
{
}


QStringList FileUpLoader::readAllFileName(std::string filePath)
{
	QDir dir(filePath.c_str());
	QStringList string_list;
	if (!dir.exists())
	{
		return  string_list;
	}
	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	int file_count = list.count();
	if (file_count <= 0)
	{
		return  string_list;
	}
	
	for (int i = 0; i < file_count; ++i)
	{
		QFileInfo file_info = list.at(i);
		QString suffix = file_info.suffix();
		if (QString::compare(suffix, QString("png"), Qt::CaseInsensitive) == 0)
		{
			QString absolute_file_path = file_info.absoluteFilePath();
				string_list.append(absolute_file_path);
		}
	}
	return string_list;
}

