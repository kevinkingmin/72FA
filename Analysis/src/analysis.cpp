#include "analysis.h"
#include "PictureAnalysis.h"

Analysis::Analysis()
{
}

bool Analysis::AnalysisMothed(QString sampleId,QString file_path)
{
    PictureAnalysis pictureAnalysis(nullptr);
    return pictureAnalysis.Analysis(sampleId,file_path);
}

bool Analysis::AnalysisMothed(QString TestId,int paperId,QString sampleId,QString solution_name,QString patiant_name)
{
    PictureAnalysis pictureAnalysis(nullptr);
    return pictureAnalysis.AnalysisOne(TestId,paperId,sampleId, solution_name, patiant_name);
}

