
// turntableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "turntable.h"
#include "turntableDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CturntableDlg �Ի���




CturntableDlg::CturntableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CturntableDlg::IDD, pParent)
	, m_currentAngle(_T(""))
	, m_speed(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_targetangle = 0;
	m_targetangle = 0;
}

void CturntableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	//  DDX_Text(pDX, IDC_EDIT1, m_angle);
	DDX_Text(pDX, IDC_EDIT1, m_currentAngle);
	DDX_Text(pDX, IDC_EDIT3, m_speed);
	//  DDX_Text(pDX, IDC_EDIT2, m_targetangle);
	DDX_Text(pDX, IDC_EDIT2, m_targetangle);
	DDV_MinMaxInt(pDX, m_targetangle, -180, 180);
}

BEGIN_MESSAGE_MAP(CturntableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CturntableDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CturntableDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CturntableDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CturntableDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CturntableDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CturntableDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CturntableDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CturntableDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CturntableDlg ��Ϣ�������

BOOL CturntableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(m_mscom.get_PortOpen())
		m_mscom.put_PortOpen(false); 
	//ֱ���ڴ��ڿؼ���������������������Щ����
	//m_mscom.put_CommPort(2);    //ѡ�񴮿�
	//m_mscom.put_InBufferSize(1024);
	//m_mscom.put_OutBufferSize(512);
	//m_mscom.put_InputLen(0);         //���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
 //   m_mscom.put_InputMode(0);           //�������뷽ʽΪ�ı���ʽ
 //   m_mscom.put_RTSEnable(1);           //����RT����
	//m_mscom.put_Settings("9600,e,7,2");         //comb2ѡ��Ĳ����ʣ�żУ�飬7����λ��2��ֹͣλ
    if(!m_mscom.get_PortOpen())
	{
		m_mscom.put_PortOpen(true);         //�򿪴���
		MessageBox("����2�򿪳ɹ�");
	}
	else
	{
		m_mscom.put_OutBufferCount(0);
		MessageBox("����2��ʧ��");
	}
	SetManual();
	SetTimer(1,200,NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CturntableDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CturntableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CturntableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CturntableDlg::SetManual()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);	
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,49);
	databuf.SetAt(14,48);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;//��Ϊ���ڷ��ص����ַ������͵ģ�retVal��vt��VT_BSTR
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("�����ֶ�ģʽ��������!");
	}
}
void CturntableDlg::SetSpeed(int speed)
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	char strspeed[9];
	databuf.SetSize(21);//���ٶ�Ϊspeed
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,87);
	databuf.SetAt(4,68);
	databuf.SetAt(5,48);
	databuf.SetAt(6,50);
	databuf.SetAt(7,49);
	databuf.SetAt(8,48);
	sprintf_s(strspeed,"%08X",speed);//��߲��㣬���а�λ
	databuf.SetAt(9,strspeed[4]);//��ת�����������ȵͺ��
	databuf.SetAt(10,strspeed[5]);
	databuf.SetAt(11,strspeed[6]);
	databuf.SetAt(12,strspeed[7]);
	databuf.SetAt(13,strspeed[0]);
	databuf.SetAt(14,strspeed[1]);
	databuf.SetAt(15,strspeed[2]);
	databuf.SetAt(16,strspeed[3]);	
	commanddata=databuf[0];
	for(int i=1;i<=16;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(17,crc[0]);
	databuf.SetAt(18,crc[1]);
	databuf.SetAt(19,42);
	databuf.SetAt(20,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("�����ٶȲ�������!");
	}
}

void CturntableDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(17);	
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,82);
	databuf.SetAt(4,68);
	databuf.SetAt(5,48);
	databuf.SetAt(6,50);
	databuf.SetAt(7,55);
	databuf.SetAt(8,54);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,48);
	databuf.SetAt(12,50);
	commanddata=databuf[0];
	for(int i=1;i<=12;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(13,crc[0]);
	databuf.SetAt(14,crc[1]);
	databuf.SetAt(15,42);
	databuf.SetAt(16,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	//angleΪ���ջ����ĵ�8λ��ʼ��4λ
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;//��Ϊ���ڷ��ص����ַ������͵ģ�retVal��vt��VT_BSTR
	int temp;
	CString anglestring;
	anglestring.Append(str.Mid(7,1),4);
	anglestring+=str.Mid(7,4);
	sscanf_s(anglestring,"%X",&temp);
	//���ַ�����Ҫ��Ϊ��ֵ��Ȼ�����10���ǽǶ�
	float angle=temp/10.0f;
	m_currentAngle.Format("%.1f��",angle);
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}

void CturntableDlg::RotateRight()
{
	SetSpeed(m_speed);
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//˳ʱ��ת
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,55);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("˳ʱ��ת����������!");
	}
}
void CturntableDlg::StopRotateRight()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//˳ʱ��ͣ
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,55);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("˳ʱ��ͣ��������!");
	}
}
void CturntableDlg::RotateLeft()
{
	SetSpeed(m_speed);
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//��ʱ��ת
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,56);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("��ʱ��ת����������!");
	}
}
void CturntableDlg::StopRotateLeft()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//��ʱ��ͣ
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,56);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("��ʱ��ͣ��������!");
	}
}
void CturntableDlg::StopRotate()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//ֹͣת��
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,57);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("ֹͣת����������!");
	}
}
void CturntableDlg::CancelCurrentZero()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//ȡ����ǰ���
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,51);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("ȡ����ǰ����������!");
	}
}
void CturntableDlg::SetCurrentPosZero()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//�赱ǰλ��Ϊ���
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,51);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("���õ�ǰλ��Ϊ����������!");
	}
}
void CturntableDlg::StopRotateBacktoZero()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//ֹͣ�����
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,82);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,54);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("ֹͣ������������!");
	}
}
void CturntableDlg::RotateBacktoZero()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//�ص��ο����
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,54);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("�ص��ο�����������!");
	}
}
void CturntableDlg::SetAuto()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//��Ϊ�Զ�
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,49);
	databuf.SetAt(14,48);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("��Ϊ�Զ���������!");
	}
}
void CturntableDlg::SetTargetAngle(int targetangle)
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	char strangle[9];
	databuf.SetSize(21);//��Ϊ�Զ�
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,87);
	databuf.SetAt(4,68);
	databuf.SetAt(5,48);
	databuf.SetAt(6,50);
	databuf.SetAt(7,55);
	databuf.SetAt(8,52);
	sprintf_s(strangle,"%08X",targetangle);
	databuf.SetAt(9,strangle[4]);
	databuf.SetAt(10,strangle[5]);
	databuf.SetAt(11,strangle[6]);
	databuf.SetAt(12,strangle[7]);
	databuf.SetAt(13,strangle[0]);
	databuf.SetAt(14,strangle[1]);
	databuf.SetAt(15,strangle[2]);
	databuf.SetAt(16,strangle[3]);
	commanddata=databuf[0];
	for(int i=1;i<=16;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("����Ŀ��ǶȲ�������!");
	}
}
void CturntableDlg::PositionStart()
{
	BYTE commanddata;
	CByteArray databuf;
	char crc[3];
	databuf.SetSize(19);//��λ����
	databuf.SetAt(0,64);
	databuf.SetAt(1,48);
	databuf.SetAt(2,49);
	databuf.SetAt(3,75);
	databuf.SetAt(4,83);
	databuf.SetAt(5,67);
	databuf.SetAt(6,73);
	databuf.SetAt(7,79);
	databuf.SetAt(8,32);
	databuf.SetAt(9,48);
	databuf.SetAt(10,48);
	databuf.SetAt(11,53);
	databuf.SetAt(12,48);
	databuf.SetAt(13,48);
	databuf.SetAt(14,57);
	commanddata=databuf[0];
	for(int i=1;i<=14;i++)
	{
		commanddata^=databuf[i];
	}
	sprintf_s(crc,"%02X",commanddata);
	databuf.SetAt(15,crc[0]);
	databuf.SetAt(16,crc[1]);
	databuf.SetAt(17,42);
	databuf.SetAt(18,13);
	m_mscom.put_Output(COleVariant(databuf));
	Sleep(200);
	VARIANT retVal=m_mscom.get_Input();
	CString str;
	str=retVal.bstrVal;
	if(str.Mid(5,2)!="00")
	{
		AfxMessageBox("��λ������������!");
	}
}
void CturntableDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	if(m_mscom.get_PortOpen())
		m_mscom.put_PortOpen(false); 
	MessageBox("����2�ѹر�");
	CDialogEx::OnOK();
}
void CturntableDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	SetManual();
	GetDlgItemTextA(IDC_BUTTON1,str);
	if(str=="˳ʱ��ת")
	{
		RotateRight();
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("˳ʱ��ͣ");
	}
	else if(str=="˳ʱ��ͣ")
	{
		StopRotateRight();
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("˳ʱ��ת");
	}
}
void CturntableDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	SetManual();
	GetDlgItemTextA(IDC_BUTTON2,str);
	if(str=="��ʱ��ת")
	{
		RotateLeft();
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA("��ʱ��ͣ");
	}
	else if(str=="��ʱ��ͣ")
	{
		StopRotateLeft();
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA("��ʱ��ת");
	}
}
void CturntableDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopRotate();
}


void CturntableDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CancelCurrentZero();
	SetCurrentPosZero();
}


void CturntableDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopRotateBacktoZero();
	RotateBacktoZero();
}


void CturntableDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}


void CturntableDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	SetAuto();
	StopRotate();
	SetSpeed(m_speed);
	SetTargetAngle(m_targetangle);
	PositionStart();
}
