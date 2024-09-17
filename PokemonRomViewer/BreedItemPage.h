#pragma once
#include "afxwin.h"


// CBreedItemPage �Ի���

class CBreedItemPage : public CBreedTabPage
{
	DECLARE_DYNAMIC(CBreedItemPage)

public:
	CBreedItemPage();   // ��׼���캯��
	virtual ~CBreedItemPage();

	void OnConfigChanged(BOOL bRomChanged, BOOL bUILangChanged);
	void TransData(BOOL bToControls);

// �Ի�������
	enum { IDD = IDD_BREED_ITEM };

protected:
	CListBox	m_ctrlItemList[2];

	afx_msg void SetItemDesc(UINT uID);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
};
