
// MFC_VideoPlayerDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

//全局字符串用于存储生成注册文本名
std::string global_name;
std::string global_name_copy;  //用于copy标注文本路径
int index_color = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFC_VideoPlayerDlg 对话框



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
	DDX_Control(pDX, IDC_COMBO1, n_cbx);  //下拉列表框的关联
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


// CMFC_VideoPlayerDlg 消息处理程序

BOOL CMFC_VideoPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//默认第一个编辑框内容
	n_cbx.AddString(TEXT("类别选择"));
	n_edit1.SetWindowTextA(TEXT("0"));   //x64bit
	n_edit2.SetWindowTextA(TEXT("0"));
	n_cbx1.AddString(TEXT("黄字体"));
	n_cbx1.AddString(TEXT("红字体"));
	n_cbx1.AddString(TEXT("黑字体"));
	n_cbx1.AddString(TEXT("绿字体"));
	//n_edit1.SetWindowTextW(TEXT("0"));
	//n_edit2.SetWindowTextW(TEXT("0"));
	//n_edit3.SetWindowTextA(TEXT("0"));	
	n_cbx.AddString(TEXT("取"));
	n_cbx.AddString(TEXT("抓"));
	n_cbx.AddString(TEXT("握"));
	n_cbx.AddString(TEXT("按"));
	n_cbx.AddString(TEXT("放"));
	n_cbx.AddString(TEXT("合"));
	n_cbx.AddString(TEXT("对"));
	n_cbx.AddString(TEXT("翻"));
	n_cbx.AddString(TEXT("移"));
	n_cbx.AddString(TEXT("折")); 
	n_cbx.AddString(TEXT("压"));
	n_cbx.AddString(TEXT("剪"));
	n_cbx.AddString(TEXT("挑"));
	n_cbx.AddString(TEXT("转"));
	n_cbx.AddString(TEXT("点"));
	n_cbx.AddString(TEXT("烫"));
	n_cbx.AddString(TEXT("放下压脚"));
	n_cbx.AddString(TEXT("脚踩"));
	n_cbx.AddString(TEXT("脚"));
	n_cbx.AddString(TEXT("推"));
	n_cbx.AddString(TEXT("换线芯（正常）"));
	n_cbx.AddString(TEXT("穿线（正常）"));
	n_cbx.AddString(TEXT("剪线（正常）"));
	n_cbx.AddString(TEXT("看裁片调方向（异常）"));
	n_cbx.AddString(TEXT("补线（异常）"));
	n_cbx.AddString(TEXT("看机台踏板（异常）"));
	n_cbx.AddString(TEXT("整理裁片（异常）"));
	n_cbx.AddString(TEXT("停（异常）"));
	n_cbx.AddString(TEXT("空（异常）"));
	
	//设置默认
	n_cbx.SetCurSel(0);
	n_cbx1.SetCurSel(0);
	/*
	m_cbx.InsertString(4,TEXT("xxx")); //插入
	m_cbx.DeleteString(3);       //删除
	CString str;
	m_cbx.GetLBText(1,str);      //获取1号索引的具体值
	*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_VideoPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_VideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_VideoPlayerDlg::OnBnClickedButton1()
{
		
	CFileDialog dlg(TRUE, _T("*.BMP|*.JPG"), NULL, NULL, _T("全部|*.mp4;*.MP4;*.avi|*.MP4|*.mp4;*.MP4|*avi|*.avi||"));//弹出一个对话框
	CString strFilePath;
	char lpsz[50];
	if (dlg.DoModal() == IDOK)
	{
		strFilePath = dlg.GetPathName();//获得文件路径
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
	else {  //没有点击ok按钮则结束程序
		return;
	}
		int flag = 1, speed = 33;
		long count = 0;
		VideoCapture cap(lpsz);
		cvNamedWindow("avi", 0);	//创建窗体，名字为avi。
		resizeWindow("avi",960,720);		
		int frames_num = (int)cap.get(7);
		while (flag)
		{
			count++;
			Mat frame;
			cap >> frame;
			if (frame.empty()) break;					//如果读取失败，则退出。
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
			char c = cvWaitKey(speed);			//显示图像的时间，speed的单位为ms；若speed=0，则为暂停。
			if (!cvGetWindowName("avi")) {
				flag = 0;
				exit(0);
			}
			if (c == 27) break;					//若c=[Esc]，则退出。
			else if (c == ' ')					//若c=' '，则暂停。
			{
				while (1)
				{
					c = cvWaitKey(0);
					if (c == ' ') break; 
					if (c == 27) { flag = 0; break; }
				}
			}
			else if (c == 'j') { speed += 10; c = cvWaitKey(speed); }		//此处调整speed的值，若按下'j'，则时间增加3ms，即视频放慢。
			else if (c == 'l') { speed -= 10; c = cvWaitKey(speed); }		//此处调整speed的值，若按下'l'，则时间减少3ms，即视频变快。
			else if (c == 'u') { count = count + 15;
			if (count >= frames_num) count = frames_num;
			cap.set(CV_CAP_PROP_POS_FRAMES,count); } //按下'u'则后退30帧前进30帧。
			else if (c == 'o') {     //按下'o'则后退30帧。
				count = count - 15; if (count < 0)count = 0;
			    cap.set(CV_CAP_PROP_POS_FRAMES, count); }

		}
		cap.release();
		cvDestroyWindow("avi");											//销毁窗体。
}
int  switchdetection(CString category) {
	string str(category.GetBuffer(category.GetLength())); //x64
	//x86
	
	//CStringA stra(category.GetBuffer(0));
	//category.ReleaseBuffer();
	//string str(stra.GetBuffer(0));
	//stra.ReleaseBuffer();	
	if (str == "类别选择") {
		return 0;
	}
	else if(str =="取") {
		return 1;
	}
	else if (str == "抓") {
		return 2;
	}
	else if (str == "握") {
		return 3;
	}
	else if (str == "按") {
		return 4;					
	}
	else if (str == "放") {
		return 5;
	}
	else if (str == "合") {
		return 6;
	}
	else if (str == "对") {
		return 7;
	}
	else if (str == "翻") {
		return 8;
	}
	else if (str == "移") {
		return 9;
	}
	else if (str == "折") {
		return 10;
	}
	else if (str == "压") {
		return 11;
	}
	else if (str == "剪") {
		return 12;
	}
	else if (str == "挑") {
		return 13;
	}
	else if (str == "转") {
		return 14;
	}
	else if (str == "点") {
		return 15;
	}
	else if (str == "烫") {
		return 16;
	}
	else if (str == "放下压脚") {
		return 17;
	}
	else if (str == "脚踩") {
		return 18;
	}
	else if (str == "脚") {
		return 19;
	}
	else if (str == "推") {
		return 20;
	}
	else if (str == "换线芯（正常）") {
		return 21;
	}
	else if (str == "穿线（正常）") {
		return 22;
	}
	else if (str == "剪线（正常）") {
		return 23;
	}
	else if (str == "看裁片调方向（异常）") {
		return 24;
	}
	else if (str == "补线（异常）") {
		return 25;
	}
	else if (str == "看机台踏板（异常）") {
		return 26;
	}
	else if (str == "整理裁片（异常）") {
		return 27;
	}
	else if (str == "停（异常）") {
		return 28;
	}
	else if (str == "空（异常）") {
		return 29;
	}	
}

void CMFC_VideoPlayerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取n_edit1、n_edit2的内容然后写入到txt文本
	CString str1;
	CString str2;	
	//CString str3;
	//win32
	//n_edit1.GetWindowTextW(str1);
	//n_edit1.GetWindowTextW(str2);
	//win64
	n_edit1.GetWindowTextA(str1);   //将n_edit1的文本内容放入到str1
	n_edit2.GetWindowTextA(str2);
	//n_edit3.GetWindowTextA(str3);
	int index = n_cbx.GetCurSel(); //拿到索引位置int类型
	CString str4;
	n_cbx.GetLBText(index, str4);  //取出这个值给str4
	string class_name;
	int numb = switchdetection(str4);	

	switch (numb)
	{
	case 0:
		class_name = "类别选择";
		break;
	case 1:
		class_name = "取";
		break;
	case 2:
		class_name = "抓";
		break;
	case 3:
		class_name = "握";
		break;
	case 4:
		class_name = "按";
		break;
	case 5:
		class_name = "放";
		break;
	case 6:
		class_name = "合";
		break;
	case 7:
		class_name = "对";
		break;
	case 8:
		class_name = "翻";
		break;
	case 9:
		class_name = "移";
		break;
	case 10:
		class_name = "折";
		break;
	case 11:
		class_name = "压";
		break;
	case 12:
		class_name = "剪";
		break;
	case 13:
		class_name = "挑";
		break;
	case 14:
		class_name = "转";
		break;
	case 15:
		class_name = "点";
		break;
	case 16:
		class_name = "烫";
		break;
	case 17:
		class_name = "放下压脚";
		break;
	case 18:
		class_name = "脚踩";
		break;
	case 19:
		class_name = "脚";
		break;
	case 20:
		class_name = "推";
		break;
	case 21:
		class_name = "换线芯（正常）";
		break;
	case 22:
		class_name = "穿线（正常）";
		break;
	case 23:
		class_name = "剪线（正常）";
		break;
	case 24:
		class_name = "看裁片调方向（异常）";
		break;
	case 25:
		class_name = "补线（异常）";
		break;
	case 26:
		class_name = "看机台踏板（异常）";
		break;
	case 27:
		class_name = "整理裁片（异常）";
		break;
	case 28:
		class_name = "停（异常）";
		break;
	default:
		class_name = "空（异常）";
		break;
	}


	if (global_name == "") {
		MessageBox(TEXT("请打开视频！"));
		return;
	}
	if (numb == 0) {
		MessageBox(TEXT("请选择类别！"));
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
		//将n_edit1的文本内容放入到str1
		//n_edit2.GetWindowTextA(str2);
		MessageBox(TEXT("已写入！"));
		n_edit2.SetWindowTextA("");
		file.close();
	}
	//global_name.erase(global_name.end()-4,global_name.end());
	
}

void CMFC_VideoPlayerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(TEXT("暂时空置！可以读取txt文档输出标签！"));
	return;
//	CFileDialog dlg(TRUE, _T("*.txt|*.txt"), NULL, NULL, _T("全部|*.txt;*.TXT;*.xls|*.xlxs|*.txt;*.txt|*txt|*.txt||"));//弹出一个对话框
//	CString strFilePath;
//	string stTemp;
//	char lpsz[400];
//	if (dlg.DoModal() == IDOK)
//	{
//		strFilePath = dlg.GetPathName();//获得文件路径
//		strcpy(lpsz, strFilePath);
//		stTemp = lpsz;//stTemp文件路径
//	}
//	ifstream readFile(stTemp); //打开stTemp路径的文本文件
//	char temp[1024];
////	int lines_nums = 0; //统计txt总行数
//	string line;
//	string startframe;
//	string endframe;
//	string catogroy;
//	if (readFile) {
//		while (getline(readFile,line)) //依次读取txt每行文件
//		{
//			stringstream words(line);
//			words >> startframe;  //读取起始帧
//			words >> endframe;    //读取终止帧
//			words >> catogroy;    //读取类别
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
		MessageBox(TEXT("没加标注不能删！"));
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
//	// TODO: 在此添加控件通知处理程序代码
//
//
//
//
//}


void CMFC_VideoPlayerDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CMFC_VideoPlayerDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	index_color = n_cbx1.GetCurSel(); //拿到索引位置int类型

	
	//CString Cstr;
	////Cstr.Format("%d", int_change);		//x64
	//Cstr.Format(_T("%d"), index_color);
	//n_edit1.SetWindowTextA(Cstr);

	//MessageBox(_T(Cstr));
	//CString strcolor;
	//n_cbx1.GetLBText(index_color, strcolor);  //取出这个值给str4
	//string str(strcolor.GetBuffer(strcolor.GetLength()));
	//if (index_color == 0) {
	//	color = (0,255,255);  //黄字体
	//}
	//else if (index_color == 1) {
	//	color = (255, 255,255);
	//}
	//else if(index_color == 2){
	//	color = (0, 0, 0);
	//}
}


