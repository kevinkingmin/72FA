#pragma once
#include <QString> 
class Global
{
public:
	static int g_OpenCoverStatus;
	static int g_SystemLiquidPerfusion;
	static QString g_machine_no;
	static QString g_userid;
    static int g_pause_flage; // 暂停标记
	static int g_company_id;
	static int g_run_or_maintenance_flage; 
};

