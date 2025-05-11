
#pragma once

#include <stdint.h>
#include <vector>
#include "RGBConvert.h"
#include "VideoRender.h"
#include "..//Include/GenICam/CAPI/SDK.h"//GenICam/CAPI/SDK.h"

//���ƴ�����
class CRender
{
public:

	/// \brief ���캯��
	CRender(HANDLE handler);

	/// \brief ���캯��
	CRender();

	/// \brief ���þ��
	void setHandle(HANDLE handler);

	/// \brief ��������
	~CRender();

	/// \brief   �򿪴���
	bool open();

	/// \brief  �رմ���
	bool close();

	/// \brief �Ƿ��
	bool isOpen() const;

	/// \brief ���ÿ��
	void setWidth(uint32_t iWidth){	m_width = iWidth; }

	/// \brief ��ֻ�߶�
	void setHeight(uint32_t iHeight){ m_height = iHeight; }

	/// \brief ��ȡ���
	uint32_t getWidth()  { return m_width; }

	/// \brief ��ȡ�߶�
	uint32_t getHeight() { return m_height; }

	/// \brief  ��ʾͼƬ
	/// \param[in] displayBuffer	���ݻ���
	/// \param[in] iWidth			ͼƬ��
	/// \param[in] iHeight			ͼƬ��
	/// \param[in] iPixelFormat		ͼƬ���ظ�ʽ
	bool display(uint8_t* displayBuffer, int iWidth, int iHeight, int64_t iPixelFormat);
	
private:
	int					m_width;			///< ͼ���
	int					m_height;			///< ͼ���			
	HANDLE				m_wind;				///< ���ھ��
	VR_HANDLE			m_handler;			///< ��ͼ���
	VR_OPEN_PARAM_S		m_params;			///< ��ʾ����
};



