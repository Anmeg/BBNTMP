/**
 * @file producer.cpp
 * @brief Implementation of producer class
 */

#include <QDir>
#include <bb/Application>
#include <QThread>
#include <bps/bps.h>
#include <iostream.h>


#include "utility.hpp"
#include "videothumbnailer.hpp"
#include "producer.hpp"

Producer::Producer(const QVariantList& videoFiles, int start)
    : m_index(start)
 {
	QDir dir;
	dir.mkpath("thumbnails/");
	m_filepath = dir.homePath() + "/thumbnails/";
	qDebug() << "m_filepath " << m_filepath;
	m_thumbPng = "-thumb.png";

	m_result.clear();
	for (int i = 0; i < videoFiles.size(); ++ i)
	{
		QVariantMap v = videoFiles[i].toMap();
		m_result.append(v["path"].toString());
	}
	qDebug() << "m_result size() " << m_result.size();
}

void Producer::produce()
{
	if (m_index >= m_result.size()) {
			emit finished();
		} else {
		//do whatever to retrieve the data
		//and then emit a produced signal with the data
		QStringList pathElements = m_result[m_index].split('/',
				QString::SkipEmptyParts, Qt::CaseSensitive);
		// Each thumbnail should have <videoFileNameWithExtention>-thumb.png format
		QString finalFileName = m_filepath
				+ pathElements[pathElements.size() - 1] + m_thumbPng;

		//create thumbnail
		try {
			VideoThumbnailer videoThumbnailer;
			videoThumbnailer.generateThumbnail(
					m_result[m_index].toUtf8().constData(),
					finalFileName.toUtf8().constData());
		} catch (exception& e) {
			std::cerr << "Error: " << e.what() << endl;
			//finalFileName = "asset:///images/play.png";
		} catch (...) {
			std::cerr << "General error" << endl;
			//finalFileName = "asset:///images/play.png";
		}
		qDebug() << " process data === " << m_index;
		++m_index;

		//if no more data, emit a finished signal

		emit produced(finalFileName, m_index - 1);
	}
}
