//#include "stdafx.h"
#include <utility>
#include <windows.h>
#include "Render.h"

/***********************************************************************
*
*                            常量定义区
*
************************************************************************/
/// 默认长宽
const uint32_t DEFAULT_WIDTH = 16;
const uint32_t DEFAULT_HEIGHT = 16;
const uint32_t DEFAULT_DATA_SIZE = DEFAULT_WIDTH * DEFAULT_HEIGHT * 3 / 2;


/***********************************************************************
*
*                            对象函数定义区
*
************************************************************************/
/// \brief 构造函数
CRender::CRender(HANDLE handler)
	: m_wind(handler)
	, m_handler(NULL)
{
}
/// \brief 构造函数
CRender::CRender()
: m_wind(NULL)
, m_handler(NULL)
{
}

/// \brief 设置句柄
void CRender::setHandle(HANDLE handler)
{
	m_wind = handler;
}

/// \brief 析构函数
CRender::~CRender()
{
	close();
}

/// \brief   打开窗口
bool CRender::open()
{
	if(m_wind == NULL)
	{
		return false;
	}

	memset(&m_params, 0, sizeof(m_params));
	m_params.eVideoRenderMode = VR_MODE_GDI;
	m_params.hWnd = (VR_HWND)m_wind;
	m_params.nWidth = DEFAULT_WIDTH;	//GDI显示的时候，值可以为0以外的任意
	m_params.nHeight = DEFAULT_HEIGHT;	//GDI显示的时候，值可以为0以外的任意
	
	if(VR_SUCCESS != VR_Open(&m_params, &m_handler)) 
	{
		//TRACE("%s cant't display BGR on this computer", __FUNCTION__);
		return false;
	}

	m_width = 0;
	m_height = 0;
	//TRACE("%s open success.\n", __FUNCTION__);
	return true;
}

/// \brief  关闭窗口
bool CRender::close()
{
	if (m_handler != NULL)
	{
		VR_Close(m_handler);
		m_handler = NULL;
	}
	return true;
}

/// \brief 是否打开
bool CRender::isOpen() const
{
	return NULL != m_handler;
}

/// \brief  显示图片
/// \param[in] image  图片
bool CRender::display(uint8_t* displayBuffer, int iWidth, int iHeight, int64_t iPixelFormat)
{
	if (displayBuffer == NULL || iWidth == 0 || iHeight == 0)
	{
		return false;
	}
	
	uint32_t width = iWidth;
	uint32_t height = iHeight;
	
	if (isOpen() && (getWidth() != width || getHeight() != height) && (getWidth() != 0 || getHeight() != 0))
	{
		close();
	}
	
	if (!isOpen())
	{
		open();
	}

	if (isOpen())
	{
		setHeight(iHeight);
		setWidth(iWidth);

		VR_FRAME_S	renderParam = {0};
		renderParam.data[0] = displayBuffer;
		renderParam.stride[0] = iWidth;
		renderParam.nWidth = iWidth;
		renderParam.nHeight = iHeight;

		if (iPixelFormat == EPixelType::gvspPixelMono8)
		{
			renderParam.format = VR_PIXEL_FMT_MONO8;
		}
		else
		{
			renderParam.format = /*VR_PIXEL_FMT_MONO8*/VR_PIXEL_FMT_RGB24;
		}

		if (VR_SUCCESS != VR_RenderFrame(m_handler, &renderParam, NULL))
		{
			//TRACE("%s render failed.", __FUNCTION__);
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}	
}

