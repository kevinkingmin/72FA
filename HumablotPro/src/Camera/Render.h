
#pragma once

#include <stdint.h>
#include <vector>
#include "RGBConvert.h"
#include "VideoRender.h"
#include "..//Include/GenICam/CAPI/SDK.h"//GenICam/CAPI/SDK.h"

//绘制窗口类
class CRender
{
public:

	/// \brief 构造函数
	CRender(HANDLE handler);

	/// \brief 构造函数
	CRender();

	/// \brief 设置句柄
	void setHandle(HANDLE handler);

	/// \brief 析构函数
	~CRender();

	/// \brief   打开窗口
	bool open();

	/// \brief  关闭窗口
	bool close();

	/// \brief 是否打开
	bool isOpen() const;

	/// \brief 设置宽度
	void setWidth(uint32_t iWidth){	m_width = iWidth; }

	/// \brief 这只高度
	void setHeight(uint32_t iHeight){ m_height = iHeight; }

	/// \brief 获取宽度
	uint32_t getWidth()  { return m_width; }

	/// \brief 获取高度
	uint32_t getHeight() { return m_height; }

	/// \brief  显示图片
	/// \param[in] displayBuffer	数据缓冲
	/// \param[in] iWidth			图片宽
	/// \param[in] iHeight			图片高
	/// \param[in] iPixelFormat		图片像素格式
	bool display(uint8_t* displayBuffer, int iWidth, int iHeight, int64_t iPixelFormat);
	
private:
	int					m_width;			///< 图像宽
	int					m_height;			///< 图像高			
	HANDLE				m_wind;				///< 窗口句柄
	VR_HANDLE			m_handler;			///< 绘图句柄
	VR_OPEN_PARAM_S		m_params;			///< 显示参数
};



