#ifndef PROCESSREAGENTMODEL_H
#define PROCESSREAGENTMODEL_H
#include "../Model.h"

class MODELSHARED_EXPORT ProcessReagentModel
{
public:
    ProcessReagentModel();
    int getId() const;
    void setId(int id);

    int getProcessParaId() const;
    void setProcessParaId(int id);

    int getPaperId() const;
    void setPaperId(int paperId);

    int getReagentId() const;
    void setReagentId(int reagentId);

    int getPumpNo() const;
    void setPumpNo(int pumpNo);

	float getFluidMeasure() const;
	void setFluidMeasure(float fluidMeasure);

private:
    int _id;
    int _processParaId;
    int _paperId;
    int _reagentId;
    int _pumpNo;
	float _fluidMeasure;
};

#endif // PROCESSREAGENTMODEL_H
