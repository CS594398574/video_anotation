
// MFC_VideoPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_VideoPlayer.h"
#include "MFC_VideoPlayerDlg.h"
#include "afxdialogex.h"
#include "core/core.hpp"
#include<cv.h>
#include<cxcore.h>
#include<highgui.h>
#include<opencv2\opencv.hpp>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<windows.h>
#include<iterator>
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

//ȫ���ַ������ڴ洢����ע���ı���
std::string global_name;
std::string global_name_copy;  //����copy��ע�ı�·��
int index_color = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_VideoPlayerDlg �Ի���



CMFC_VideoPlayerDlg::CMFC_VideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_VIDEOPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_VideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, n_edit1);
	DDX_Control(pDX, IDC_EDIT2, n_edit2);
	//DDX_Control(pDX, IDC_EDIT3, n_edit3);
	DDX_Control(pDX, IDC_COMBO1, n_cbx);  //�����б��Ĺ���
	DDX_Control(pDX, IDC_COMBO2, n_cbx1);
}

BEGIN_MESSAGE_MAP(CMFC_VideoPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_VideoPlayerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_VideoPlayerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_VideoPlayerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC_VideoPlayerDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMFC_VideoPlayerDlg::OnBnClickedButton5)
//	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFC_VideoPlayerDlg::OnCbnSelchangeCombo2)
ON_CBN_SELCHANGE(IDC_COMBO2, &CMFC_VideoPlayerDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CMFC_VideoPlayerDlg ��Ϣ�������

BOOL CMFC_VideoPlayerDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//Ĭ�ϵ�һ���༭������
	n_cbx.AddString(TEXT("���ѡ��"));
	n_edit1.SetWindowTextA(TEXT("0"));   //x64bit
	n_edit2.SetWindowTextA(TEXT("0"));
	n_cbx1.AddString(TEXT("������"));
	n_cbx1.AddString(TEXT("������"));
	n_cbx1.AddString(TEXT("������"));
	n_cbx1.AddString(TEXT("������"));
	//n_edit1.SetWindowTextW(TEXT("0"));
	//n_edit2.SetWindowTextW(TEXT("0"));
	//n_edit3.SetWindowTextA(TEXT("0"));	
	n_cbx.AddString(TEXT("ȡ"));
	n_cbx.AddString(TEXT("ץ"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��")); 
	n_cbx.AddString(TEXT("ѹ"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("ת"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("����ѹ��"));
	n_cbx.AddString(TEXT("�Ų�"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("��"));
	n_cbx.AddString(TEXT("����о��������"));
	n_cbx.AddString(TEXT("���ߣ�������"));
	n_cbx.AddString(TEXT("���ߣ�������"));
	n_cbx.AddString(TEXT("����Ƭ�������쳣��"));
	n_cbx.AddString(TEXT("���ߣ��쳣��"));
	n_cbx.AddString(TEXT("����̨̤�壨�쳣��"));
	n_cbx.AddString(TEXT("�����Ƭ���쳣��"));
	n_cbx.AddString(TEXT("ͣ���쳣��"));
	n_cbx.AddString(TEXT("�գ��쳣��"));
	
	//����Ĭ��
	n_cbx.SetCurSel(0);
	n_cbx1.SetCurSel(0);
	/*
	m_cbx.InsertString(4,TEXT("xxx")); //����
	m_cbx.DeleteString(3);       //ɾ��
	CString str;
	m_cbx.GetLBText(1,str);      //��ȡ1�������ľ���ֵ
	*/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC_VideoPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_VideoPlayerDlg::OnPaint()
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
HCURSOR CMFC_VideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_VideoPlayerDlg::OnBnClickedButton1()
{
		
	CFileDialog dlg(TRUE, _T("*.BMP|*.JPG"), NULL, NULL, _T("ȫ��|*.mp4;*.MP4;*.avi|*.MP4|*.mp4;*.MP4|*avi|*.avi||"));//����һ���Ի���
	CString strFilePath;
	char lpsz[50];
	if (dlg.DoModal() == IDOK)
	{
		strFilePath = dlg.GetPathName();//����ļ�·��
		strcpy(lpsz, strFilePath);  //x64
		global_name = lpsz;  //x64
		////x86
		//int nLength = strFilePath.GetLength();
		//int nBytes = WideCharToMultiByte(CP_ACP, 0, strFilePath, nLength, NULL, 0, NULL, NULL);
		//char* VoicePath = new char[nBytes + 1];
		//memset(VoicePath, 0, nLength + 1);
		//global_name = VoicePath;
		//WideCharToMultiByte(CP_OEMCP, 0, strFilePath, nLength, VoicePath, nBytes, NULL, NULL);
		//VoicePath[nBytes] = 0;		
		
	}
	else {  //û�е��ok��ť���������
		return;
	}
		int flag = 1, speed = 33;
		long count = 0;
		VideoCapture cap(lpsz);
		cvNamedWindow("avi", 0);	//�������壬����Ϊavi��
		resizeWindow("avi",960,720);		
		int frames_num = (int)cap.get(7);
		while (flag)
		{
			count++;
			Mat frame;
			cap >> frame;
			if (frame.empty()) break;					//�����ȡʧ�ܣ����˳���
			if (index_color == 0) {
				Scalar color(0, 255, 255);
				putText(frame, "W:  " + to_string(speed) + "ms", Point(20, 110), CV_FONT_HERSHEY_SIMPLEX, 1.5, color, 2.5, 8);
				putText(frame, "C:   " + to_string(count), Point(20, 150), CV_FONT_HERSHEY_SIMPLEX, 1.5, color, 2, 8);
				putText(frame, "T:   " + to_string(frames_num), Point(20, 190), CV_FONT_HERSHEY_SIMPLEX, 1.5, color, 2, 8);
			}
			if (index_color == 2) {
				Scalar color1(0,0,0);
				putText(frame, "W:  " + to_string(speed) + "ms", Point(20, 110), CV_FONT_HERSHEY_SIMPLEX, 1.5, color1, 2.5, 8);
				putText(frame, "C:   " + to_string(count), Point(20, 150), CV_FONT_HERSHEY_SIMPLEX, 1.5, color1, 2, 8);
				putText(frame, "T:   " + to_string(frames_num), Point(20, 190), CV_FONT_HERSHEY_SIMPLEX, 1.5, color1, 2, 8);
			}if (index_color == 1) {
				Scalar color2(0, 0, 255);
				putText(frame, "W:  " + to_string(speed) + "ms", Point(20, 110), CV_FONT_HERSHEY_SIMPLEX, 1.5, color2, 2.5, 8);
				putText(frame, "C:   " + to_string(count), Point(20, 150), CV_FONT_HERSHEY_SIMPLEX, 1.5, color2, 2, 8);
				putText(frame, "T:   " + to_string(frames_num), Point(20, 190), CV_FONT_HERSHEY_SIMPLEX, 1.5, color2, 2, 8);
			}
			if (index_color == 3) {
				Scalar color3(0, 255, 0);
				putText(frame, "W:  " + to_string(speed) + "ms", Point(20, 110), CV_FONT_HERSHEY_SIMPLEX, 1.5, color3, 2.5, 8);
				putText(frame, "C:   " + to_string(count), Point(20, 150), CV_FONT_HERSHEY_SIMPLEX, 1.5, color3, 2, 8);
				putText(frame, "T:   " + to_string(frames_num), Point(20, 190), CV_FONT_HERSHEY_SIMPLEX, 1.5, color3, 2, 8);
			}
			imshow("avi", frame);
			char c = cvWaitKey(speed);			//��ʾͼ���ʱ�䣬speed�ĵ�λΪms����speed=0����Ϊ��ͣ��
			if (!cvGetWindowName("avi")) {
				flag = 0;
				exit(0);
			}
			if (c == 27) break;					//��c=[Esc]�����˳���
			else if (c == ' ')					//��c=' '������ͣ��
			{
				while (1)
				{
					c = cvWaitKey(0);
					if (c == ' ') break; 
					if (c == 27) { flag = 0; break; }
				}
			}
			else if (c == 'j') { speed += 10; c = cvWaitKey(speed); }		//�˴�����speed��ֵ��������'j'����ʱ������3ms������Ƶ������
			else if (c == 'l') { speed -= 10; c = cvWaitKey(speed); }		//�˴�����speed��ֵ��������'l'����ʱ�����3ms������Ƶ��졣
			else if (c == 'u') { count = count + 15;
			if (count >= frames_num) count = frames_num;
			cap.set(CV_CAP_PROP_POS_FRAMES,count); } //����'u'�����30֡ǰ��30֡��
			else if (c == 'o') {     //����'o'�����30֡��
				count = count - 15; if (count < 0)count = 0;
			    cap.set(CV_CAP_PROP_POS_FRAMES, count); }

		}
		cap.release();
		cvDestroyWindow("avi");											//���ٴ��塣
}
int  switchdetection(CString category) {
	string str(category.GetBuffer(category.GetLength())); //x64
	//x86
	
	//CStringA stra(category.GetBuffer(0));
	//category.ReleaseBuffer();
	//string str(stra.GetBuffer(0));
	//stra.ReleaseBuffer();	
	if (str == "���ѡ��") {
		return 0;
	}
	else if(str =="ȡ") {
		return 1;
	}
	else if (str == "ץ") {
		return 2;
	}
	else if (str == "��") {
		return 3;
	}
	else if (str == "��") {
		return 4;					
	}
	else if (str == "��") {
		return 5;
	}
	else if (str == "��") {
		return 6;
	}
	else if (str == "��") {
		return 7;
	}
	else if (str == "��") {
		return 8;
	}
	else if (str == "��") {
		return 9;
	}
	else if (str == "��") {
		return 10;
	}
	else if (str == "ѹ") {
		return 11;
	}
	else if (str == "��") {
		return 12;
	}
	else if (str == "��") {
		return 13;
	}
	else if (str == "ת") {
		return 14;
	}
	else if (str == "��") {
		return 15;
	}
	else if (str == "��") {
		return 16;
	}
	else if (str == "����ѹ��") {
		return 17;
	}
	else if (str == "�Ų�") {
		return 18;
	}
	else if (str == "��") {
		return 19;
	}
	else if (str == "��") {
		return 20;
	}
	else if (str == "����о��������") {
		return 21;
	}
	else if (str == "���ߣ�������") {
		return 22;
	}
	else if (str == "���ߣ�������") {
		return 23;
	}
	else if (str == "����Ƭ�������쳣��") {
		return 24;
	}
	else if (str == "���ߣ��쳣��") {
		return 25;
	}
	else if (str == "����̨̤�壨�쳣��") {
		return 26;
	}
	else if (str == "�����Ƭ���쳣��") {
		return 27;
	}
	else if (str == "ͣ���쳣��") {
		return 28;
	}
	else if (str == "�գ��쳣��") {
		return 29;
	}	
}

void CMFC_VideoPlayerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡn_edit1��n_edit2������Ȼ��д�뵽txt�ı�
	CString str1;
	CString str2;	
	//CString str3;
	//win32
	//n_edit1.GetWindowTextW(str1);
	//n_edit1.GetWindowTextW(str2);
	//win64
	n_edit1.GetWindowTextA(str1);   //��n_edit1���ı����ݷ��뵽str1
	n_edit2.GetWindowTextA(str2);
	//n_edit3.GetWindowTextA(str3);
	int index = n_cbx.GetCurSel(); //�õ�����λ��int����
	CString str4;
	n_cbx.GetLBText(index, str4);  //ȡ�����ֵ��str4
	string class_name;
	int numb = switchdetection(str4);	

	switch (numb)
	{
	case 0:
		class_name = "���ѡ��";
		break;
	case 1:
		class_name = "ȡ";
		break;
	case 2:
		class_name = "ץ";
		break;
	case 3:
		class_name = "��";
		break;
	case 4:
		class_name = "��";
		break;
	case 5:
		class_name = "��";
		break;
	case 6:
		class_name = "��";
		break;
	case 7:
		class_name = "��";
		break;
	case 8:
		class_name = "��";
		break;
	case 9:
		class_name = "��";
		break;
	case 10:
		class_name = "��";
		break;
	case 11:
		class_name = "ѹ";
		break;
	case 12:
		class_name = "��";
		break;
	case 13:
		class_name = "��";
		break;
	case 14:
		class_name = "ת";
		break;
	case 15:
		class_name = "��";
		break;
	case 16:
		class_name = "��";
		break;
	case 17:
		class_name = "����ѹ��";
		break;
	case 18:
		class_name = "�Ų�";
		break;
	case 19:
		class_name = "��";
		break;
	case 20:
		class_name = "��";
		break;
	case 21:
		class_name = "����о��������";
		break;
	case 22:
		class_name = "���ߣ�������";
		break;
	case 23:
		class_name = "���ߣ�������";
		break;
	case 24:
		class_name = "����Ƭ�������쳣��";
		break;
	case 25:
		class_name = "���ߣ��쳣��";
		break;
	case 26:
		class_name = "����̨̤�壨�쳣��";
		break;
	case 27:
		class_name = "�����Ƭ���쳣��";
		break;
	case 28:
		class_name = "ͣ���쳣��";
		break;
	default:
		class_name = "�գ��쳣��";
		break;
	}


	if (global_name == "") {
		MessageBox(TEXT("�����Ƶ��"));
		return;
	}
	if (numb == 0) {
		MessageBox(TEXT("��ѡ�����"));
		return;
	}
	else {
		string str;
		str = global_name + "annotation.txt";
		global_name_copy = str;
		std::ofstream file(str, std::ios::app);
		file << str1 << '\t';
		file << str2 << '\t';
		file << numb << '\t';
		file << class_name << '\n';
		//int int_change = atoi(str2); //win64
		int int_change = _tstoi(LPCTSTR(str2));
		int_change++;
		CString Cstr;
		//Cstr.Format("%d", int_change);		//x64
		Cstr.Format(_T("%d"), int_change);
		n_edit1.SetWindowTextA(Cstr);
	/*	n_edit1.SetWindowTextW(Cstr);*/
		//��n_edit1���ı����ݷ��뵽str1
		//n_edit2.GetWindowTextA(str2);
		MessageBox(TEXT("��д�룡"));
		n_edit2.SetWindowTextA("");
		file.close();
	}
	//global_name.erase(global_name.end()-4,global_name.end());
	
}

void CMFC_VideoPlayerDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(TEXT("��ʱ���ã����Զ�ȡtxt�ĵ������ǩ��"));
	return;
//	CFileDialog dlg(TRUE, _T("*.txt|*.txt"), NULL, NULL, _T("ȫ��|*.txt;*.TXT;*.xls|*.xlxs|*.txt;*.txt|*txt|*.txt||"));//����һ���Ի���
//	CString strFilePath;
//	string stTemp;
//	char lpsz[400];
//	if (dlg.DoModal() == IDOK)
//	{
//		strFilePath = dlg.GetPathName();//����ļ�·��
//		strcpy(lpsz, strFilePath);
//		stTemp = lpsz;//stTemp�ļ�·��
//	}
//	ifstream readFile(stTemp); //��stTemp·�����ı��ļ�
//	char temp[1024];
////	int lines_nums = 0; //ͳ��txt������
//	string line;
//	string startframe;
//	string endframe;
//	string catogroy;
//	if (readFile) {
//		while (getline(readFile,line)) //���ζ�ȡtxtÿ���ļ�
//		{
//			stringstream words(line);
//			words >> startframe;  //��ȡ��ʼ֡
//			words >> endframe;    //��ȡ��ֹ֡
//			words >> catogroy;    //��ȡ���
//			MessageBox(TEXT(catogroy.c_str()));
//		}
//	}
//	readFile.getline(temp,1024,0);
//	MessageBox(TEXT(temp));

}


string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}

void CMFC_VideoPlayerDlg::OnBnClickedButton4()
{
	vector<string> tmp_files;
	ifstream winfile(global_name_copy);
	if (!winfile)
	{
		MessageBox(TEXT("û�ӱ�ע����ɾ��"));
		return ;
	}

	string lineContent;
	while (getline(winfile, lineContent, '\n')) {
		tmp_files.push_back(lineContent + '\n');
	}
	winfile.close();

	ofstream outfile(global_name_copy, ios::out);
	vector<string>::iterator siter = tmp_files.begin();
	copy(tmp_files.begin(), tmp_files.end() - 1, ostream_iterator<string>(outfile));
	cout << "ok!" << endl;
	outfile.close();



	/*string lineContent;
	while (getline(winfile, lineContent, '\n'))
	{
		tmp_files.push_back(lineContent + "\r");
	}
	ofstream offile(global_name_copy, ios::out);
	vector<string>::iterator siter = tmp_files.begin();
	copy(tmp_files.begin(), tmp_files.end() - 1, ostream_iterator<string>(offile));*/
	 
}


//void CMFC_VideoPlayerDlg::OnCbnSelchangeCombo1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//
//
//
//}


void CMFC_VideoPlayerDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CMFC_VideoPlayerDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	index_color = n_cbx1.GetCurSel(); //�õ�����λ��int����

	
	//CString Cstr;
	////Cstr.Format("%d", int_change);		//x64
	//Cstr.Format(_T("%d"), index_color);
	//n_edit1.SetWindowTextA(Cstr);

	//MessageBox(_T(Cstr));
	//CString strcolor;
	//n_cbx1.GetLBText(index_color, strcolor);  //ȡ�����ֵ��str4
	//string str(strcolor.GetBuffer(strcolor.GetLength()));
	//if (index_color == 0) {
	//	color = (0,255,255);  //������
	//}
	//else if (index_color == 1) {
	//	color = (255, 255,255);
	//}
	//else if(index_color == 2){
	//	color = (0, 0, 0);
	//}
}


