#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QObject>

#pragma execution_character_set("utf-8")

#include "analysis_global.h"
class ANALYSISSHARED_EXPORT Analysis
{

public:
    Analysis();

	QString m_test_project_name;
	//int m_nSampleID;
	//int m_nTestPaperID;

	bool AnalysisMothed(QString test_project_name,QString file_path);
	//test_id 也是文件名
	bool AnalysisMothed(QString testId,int paperId, QString sampleId, QString solution_name, QString patiant_name);

	bool AnalysisMothed_new(QString TestId, int paperId, QString sampleId, QString solution_name, QString patiant_name);
    	bool AnalysisMothed_wz(QString inputPath,QString outputPath);
};

#endif // ANALYSIS_H
