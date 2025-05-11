//#include "stdafx.h"
#include <utility>
#include <windows.h>
#include "Render.h"

/***********************************************************************
*
*                            ����������
*
************************************************************************/
/// Ĭ�ϳ���
const uint32_t DEFAULT_WIDTH = 16;
const uint32_t DEFAULT_HEIGHT = 16;
const uint32_t DEFAULT_DATA_SIZE = DEFAULT_WIDTH * DEFAULT_HEIGHT * 3 / 2;


/***********************************************************************
*
*                            ������������
*
************************************************************************/
/// \brief ���캯��
CRender::CRender(HANDLE handler)
	: m_wind(handler)
	, m_handler(NULL)
{
}
/// \brief ���캯��
CRender::CRender()
: m_wind(NULL)
, m_handler(NULL)
{
}

/// \brief ���þ��
void CRender::setHandle(HANDLE handler)
{
	m_wind = handler;
}

/// \brief ��������
CRender::~CRender()
{
	close();
}

/// \brief   �򿪴���
bool CRender::open()
{
	if(m_wind == NULL)
	{
		return false;
	}

	memset(&m_params, 0, sizeof(m_params));
	m_params.eVideoRenderMode = VR_MODE_GDI;
	m_params.hWnd = (VR_HWND)m_wind;
	m_params.nWidth = DEFAULT_WIDTH;	//GDI��ʾ��ʱ��ֵ����Ϊ0���������
	m_params.nHeight = DEFAULT_HEIGHT;	//GDI��ʾ��ʱ��ֵ����Ϊ0���������
	
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

/// \brief  �رմ���
bool CRender::close()
{
	if (m_handler != NULL)
	{
		VR_Close(m_handler);
		m_handler = NULL;
	}
	return true;
}

/// \brief �Ƿ��
bool CRender::isOpen() const
{
	return NULL != m_handler;
}

/// \brief  ��ʾͼƬ
/// \param[in] image  ͼƬ
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

