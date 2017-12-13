
// turntableDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"


// CturntableDlg �Ի���
class CturntableDlg : public CDialogEx
{
// ����
public:
	CturntableDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TURNTABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_mscom;
	void SetManual();
	void ReadCurrentAngle();
	void SetSpeed(int speed);
	void RotateRight();
	void StopRotateRight();
	void RotateLeft();
	void StopRotateLeft();
	void StopRotate();
	void CancelCurrentZero();
	void SetCurrentPosZero();
	void StopRotateBacktoZero();
	void RotateBacktoZero();
	void SetAuto();
	void SetTargetAngle(int targetangle);
	void PositionStart();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CString m_currentAngle;
	int m_speed;
	int m_targetangle;
	afx_msg void OnBnClickedButton6();
};
