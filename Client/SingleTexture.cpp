#include "stdafx.h"
#include "SingleTexture.h"
#include "Device.h"

CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}

CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::Insert_Texture(const TCHAR* pFilePath,
										const TCHAR* pStateKey, 
										const int & iCnt)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// D3DXGetImageInfoFromFile : �̹��� ���Ͽ� ����Ͽ� �̹��� ����ü ������ ä���ִ� �Լ�
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		Safe_Release(m_pTexInfo->pTexture);
		Safe_Delete(m_pTexInfo);
		ERR_MSG(L"single D3DXGetImageInfoFromFile Failed");
		return E_FAIL;
	}


	//D3DPOOL_DEFAULT = 0,	// ���� ������ �޸�, ���� �׷��� ī�� �޸𸮸� ����
	//D3DPOOL_MANAGED = 1,	// DX 3D�� ���� �ڿ��� ����, �׷��� �޸𸮸� ��������� RAM�� ���
	//D3DPOOL_SYSTEMMEM = 2,	// �ý��� �޸�(RAM)�� ���
	//D3DPOOL_SCRATCH = 3,	// �ý��� �޸𸮸� ��������� DX ��ġ�� ���� �Ұ�
	
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
											pFilePath,
											m_pTexInfo->tImgInfo.Width,
											m_pTexInfo->tImgInfo.Height,
											m_pTexInfo->tImgInfo.MipLevels,
											0,			// ������ ��� ���(D3DUSAGE_RENDERTARGET : ȭ�� ��¿� �ؽ�ó)
											m_pTexInfo->tImgInfo.Format,
											D3DPOOL_MANAGED,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											0,
											nullptr,
											nullptr,
											&(m_pTexInfo->pTexture))))
	{
		Safe_Release(m_pTexInfo->pTexture);
		Safe_Delete(m_pTexInfo);
		ERR_MSG(L"single D3DXCreateTextureFromFileEx Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}