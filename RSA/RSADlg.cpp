
// RSADlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"
//#include "zip.h"
#include <afx.h>
#include <vector>
#include <cstdlib>
#include <random>
#include <fstream>
#include <wincrypt.h>
#include <string>
#include <iostream>
#include <bitset>
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int q,p, a, b, n, t;
CString check_ =_T("");

std::string HexToBinary(const CString& hexString) {
    std::string binaryString;
    int hexLength = hexString.GetLength();

    for (int i = 0; i < hexLength; i++) {
        TCHAR hexChar = hexString.GetAt(i);

        switch (hexChar) {
            case _T('0'):
                binaryString += "0000";
                break;
            case _T('1'):
                binaryString += "0001";
                break;
            case _T('2'):
                binaryString += "0010";
                break;
            case _T('3'):
                binaryString += "0011";
                break;
            case _T('4'):
                binaryString += "0100";
                break;
            case _T('5'):
                binaryString += "0101";
                break;
            case _T('6'):
                binaryString += "0110";
                break;
            case _T('7'):
                binaryString += "0111";
                break;
            case _T('8'):
                binaryString += "1000";
                break;
            case _T('9'):
                binaryString += "1001";
                break;
            case _T('A'):
            case _T('a'):
                binaryString += "1010";
                break;
            case _T('B'):
            case _T('b'):
                binaryString += "1011";
                break;
            case _T('C'):
            case _T('c'):
                binaryString += "1100";
                break;
            case _T('D'):
            case _T('d'):
                binaryString += "1101";
                break;
            case _T('E'):
            case _T('e'):
                binaryString += "1110";
                break;
            case _T('F'):
            case _T('f'):
                binaryString += "1111";
                break;
            default:
                std::cerr << "Invalid hex character: " << hexChar << std::endl;
                return "";
        }
    }

    return binaryString;
}


int binaryToDecimal(const std::string& binaryString) {
    int decimalNumber = 0;
    int power = binaryString.length() - 1;
    for (int i = 0; i < binaryString.length(); i++) {
        if (binaryString[i] == '1') {
            decimalNumber += pow(2, power);
        }
        power--;
    }
    return decimalNumber;
}


std::string decToBin(long int decimal, int k) {
    if (decimal == 0) 
    {
        return "0";
    }

    std::string binary = "";
    while (decimal > 0) {
        binary = std::to_string(decimal % 2) + binary;
        decimal /= 2;
    }

    std::string paddedBinaryString = binary;
    int nZero = k-binary.length();
    if (nZero > 0)
    {
        for (int i = 0; i < nZero; i++)
        {
            paddedBinaryString = "0" + paddedBinaryString;
        }
    }

    return paddedBinaryString;
}


CString CalculateMD5(const CString& input)
{
    HCRYPTPROV hProv = NULL;
    HCRYPTPROV hHash = NULL;
    BYTE hash[16];
    DWORD hashLength = 16;

    CString md5String;

    // Acquire a handle to the default cryptographic service provider
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        // Handle error
        return md5String;
    }

    // Create a hash object
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        // Handle error
        CryptReleaseContext(hProv, 0);
        return md5String;
    }

    // Hash the input data
    if (!CryptHashData(hHash, (BYTE*)(LPCTSTR)input, input.GetLength() * sizeof(TCHAR), 0))
    {
        // Handle error
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return md5String;
    }

    // Get the hash value
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLength, 0))
    {
        // Handle error
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return md5String;
    }

    // Convert the hash value to a string
    for (int i = 0; i < hashLength; i++)
    {
        CString byte;
        byte.Format(_T("%02x"), hash[i]);
        md5String += byte;
    }

    // Clean up
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return md5String;
}



//tìm 2 số nguyên tố ngẫu nhiên
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

void getRandomPrimes(int start, int end, int& a, int& b) {
    std::vector<int> primes;
    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            primes.push_back(num);
        }
    }

    std::random_device rd;
    std::uniform_int_distribution<> dis(0, primes.size() - 1);

    int randomIndex1 = dis(rd);
    int randomIndex2 = dis(rd);
    while (randomIndex1 == randomIndex2) {
        randomIndex2 = dis(rd);
    }


    a = primes.at(randomIndex1);
    b= primes.at(randomIndex2);
 
}
int GenerateRandomPrime()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(100, 10000);

    int n = dist(gen);

    while (!isPrime(n))
    {
        n = dist(gen);
    }

    return n;
}

// tìm gcd

int gcd (int a, int b)
{
	if(a==0) return b;
	if(b==0) return a;
	if(a==b) return a;
	if(a>b) return gcd(a-b,b);
	return gcd(a, b-a);
}
// chọn số ngẫu nhien
int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

//
int modinverse(int a , int m )
{
	int mo = m ;
	int y=0, x=1;
	if(m==1)return 0;
	while(a>1 && m!=0)
	{
		int q = a/m ; 
		int t = m ;


		m = a%m ;
        a = t ;
		t=y ;

		y= x-q*y ;
		x=t ;

	}
	if(x<0) x+=mo;
	return x;

}

//tính x^a mod n

long int exponentiation (long int base , long int exp, long int n)
{
	if(exp ==0) return 1;
	if(exp ==1) return base % n;
	long int t = exponentiation(base , exp/2, n);
	t= (t*t) %n;
	if(exp %2==0){
		return t;
	} 
	else
	{
		return ((base %  n) * t ) % n;
	
	}
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CRSADlg dialog



CRSADlg::CRSADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRSADlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_FILE_INPUT, edt_file_input);
    DDX_Control(pDX, IDC_LIST_SIGN, list_box_sign);
    DDX_Control(pDX, IDC_LIST_SIGN_P, list_box_sign_p);
    DDX_Control(pDX, IDC_LIST_SIGN_Q, list_box_sign_q);
    //   DDX_Control(pDX, IDC_LIST_FILE_TEXT, list_box_file_text);
    //DDX_Control(pDX, IDC_LIST_FILE_SIGN, list_box_file_sign);
    //DDX_Control(pDX, IDC_LIST_CHECK, list_box_check);
    DDX_Control(pDX, IDC_BTN_FILE, btn_file);
    DDX_Control(pDX, IDC_BTN_SIGN, btn_sign);
    //DDX_Control(pDX, IDC_BTN_SEND, btn_send);
    DDX_Control(pDX, IDC_BTN_SAVE, btn_save);
    DDX_Control(pDX, IDC_BTN_FILE_TEXT, btn_file_text);
    DDX_Control(pDX, IDC_BTN_FILE_SIGN, btn_file_sign);
    DDX_Control(pDX, IDC_BTN_CHECK, btn_check);
    DDX_Control(pDX, IDC_EDT_FILE_SIGN, list_file_sign);
    DDX_Control(pDX, IDC_LIST_SIGN, list_box_sign);
    DDX_Control(pDX, IDC_BTN_GENERATE_KEY, btn_generate_key);
}

BEGIN_MESSAGE_MAP(CRSADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SIGN, &CRSADlg::OnBnClickedBtnSign)
	//ON_BN_CLICKED(IDC_BTN_SEND, &CRSADlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CRSADlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_FILE, &CRSADlg::OnBnClickedBtnFile)
	ON_BN_CLICKED(IDC_BTN_FILE_TEXT, &CRSADlg::OnBnClickedBtnFileText)
	ON_BN_CLICKED(IDC_BTN_CHECK, &CRSADlg::OnBnClickedBtnCheck)
    ON_BN_CLICKED(IDC_BTN_FILE_SIGN, &CRSADlg::OnBnClickedBtnFileSign)
    ON_BN_CLICKED(IDC_BTN_GENERATE_KEY, &CRSADlg::OnBnClickedBtnGenerateKey)
    ON_BN_CLICKED(IDC_BUTTON1, &CRSADlg::OnBnClickedButton1)
    ON_EN_CHANGE(IDC_LIST_SIGN_P, &CRSADlg::OnEnChangeListSignP)
    ON_EN_CHANGE(IDC_LIST_SIGN, &CRSADlg::OnEnChangeListSign)
    ON_EN_CHANGE(IDC_EDT_FILE_INPUT, &CRSADlg::OnEnChangeEdtFileInput)
    ON_BN_CLICKED(IDC_BUTTON2, &CRSADlg::OnBnClickedButton2)
    ON_EN_CHANGE(IDC_EDT_FILE_TEXT, &CRSADlg::OnEnChangeEdtFileText)
    ON_BN_CLICKED(IDOK, &CRSADlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRSADlg message handlers

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// lấy giá trị ký thủ công
/*
void CRSADlg::OnBnClickedBtnManualKey()
{
    CString pT, qT, bT;
    // Lấy giá trị p từ control có ID là IDC_EDIT_P
    GetDlgItemText(IDC_LIST_SIGN_P, pT);
    p = _ttoi(pT);
    // Kiểm tra tính nguyên tố của p (có thể thực hiện kiểm tra ở đây)

    // Lấy giá trị q từ control có ID là IDC_EDIT_Q
    GetDlgItemText(IDC_LIST_SIGN_Q, qT);
    q = _ttoi(qT);
    // Lấy giá trị e từ control có ID là IDC_EDIT_E
    GetDlgItemText(IDC_LIST_SIGN_E, bT);
    b = _ttoi(bT);
    // Kiểm tra tính nguyên tố của q (có thể thực hiện kiểm tra ở đây)

}*/

// tư động sinh p, q, b

void CRSADlg::OnBnClickedBtnGenerateKey()
{
    p = GenerateRandomPrime();
    q = GenerateRandomPrime();
    CString message;
    // dưa p q random vao ô input
    CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_LIST_SIGN_P);
    CString str1;
    str1.Format(_T("%d"), p);
    pEdit1->SetWindowText(str1);
    CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_LIST_SIGN_Q);
    CString str2;
    str2.Format(_T("%d"), q);
    pEdit2->SetWindowText(str2);
}

//button ký 

void CRSADlg::OnBnClickedBtnSign()
{
	UpdateData(TRUE);
    CString str_, strValue1, strValue2, strValueE;
	edt_file_input.GetWindowText(str_);
    GetDlgItemText(IDC_LIST_SIGN_Q, strValue1);
    GetDlgItemText(IDC_LIST_SIGN_P, strValue2);
    q = _ttoi(strValue1);
    p = _ttoi(strValue2);
    // Kiểm tra q và p có phải số nguyên tố không
    if (!isPrime(q) || !isPrime(p)) {
        MessageBox(_T("q hoặc p không hợp lệ. Vui lòng nhập số nguyên tố."), _T("Lỗi"), MB_OK | MB_ICONERROR);
        return;
    }

    // Kiểm tra q và p có nhỏ hơn 100 không
    if (q < 100 || p < 100) {
        MessageBox(_T("q và p quá nhỏ. Vui lòng nhập số lớn hơn."), _T("Lỗi"), MB_OK | MB_ICONERROR);
        return;
    }
    t = (q - 1) * (p - 1);
	n = q*p;
    // chọn b ngẫu nhiên (số nguyên tố e trong dialog)
    do {
        b = getRandomNumber(2, t - 1);

        if (gcd(b, t) == 1 && isPrime(b)) {

            break; // Thoát khỏi vòng lặp nếu tìm được giá trị b phù hợp
        }
    } while (true);
    //tính a
    a = modinverse(b, t);
    //băm dữ liệu
    CString hash_ = CalculateMD5(str_);
    std::string binaryString = HexToBinary(hash_);
    check_ = binaryString.c_str();

    //std::string binaryString=("00000110");
    int binaryLength = binaryString.length();
    CString kq = _T("");
    for (int i = 0; i < binaryString.length(); i += 8) {
        std::string tempBinaryString = binaryString.substr(i, 8);
        int x = binaryToDecimal(tempBinaryString);
        long int tam = exponentiation((long int)x, (long int)a, (long int)n);

        std::string decimalString = decToBin(tam, 16);
        CString temp(decimalString.c_str());
        kq += temp;
    }

    int length_ = kq.GetLength();
    CStringT<WCHAR, StrTraitMFC_DLL<WCHAR>> cstr(kq.GetString());

    // Get a pointer to the text box control
    CEdit* pTextBox = (CEdit*)GetDlgItem(IDC_LIST_SIGN);

    if (pTextBox) {
        pTextBox->SetWindowTextW(cstr);
    }
}

/*//button chuyển
void CRSADlg::OnBnClickedBtnSend()
{
	 list_box_file_sign.ResetContent();

    // Lấy số lượng mục trong ListBox nguồn
    int itemCount = list_box_sign.GetCount();

    // Lặp qua từng mục trong ListBox nguồn
    for (int i = 0; i < itemCount; i++)
    {
        CString itemText;
        list_box_sign.GetText(i, itemText); // Lấy nội dung của mục tại vị trí i trong ListBox nguồn
        list_box_file_sign.AddString(itemText); // Thêm nội dung vào ListBox đích
    }



	 list_box_file_text.ResetContent();

	
	CString str_ ;
	edt_file_input.GetWindowText(str_);

	list_box_file_text.AddString(str_);
	UpdateData(FALSE);

}
*/
// button save

void CRSADlg::OnBnClickedBtnSave()
{
    CString thongDiep3;
    GetDlgItemText(IDC_LIST_SIGN, thongDiep3);

    // Chuyển đổi sang std::wstring
    std::wstring wstr(thongDiep3);

    // Chuyển đổi sang std::string
    std::string msgstr(wstr.begin(), wstr.end());

    // Yêu cầu người dùng chọn đường dẫn cho tệp tin
    CFileDialog fileDialog(FALSE, _T("txt"), NULL, OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
    if (fileDialog.DoModal() == IDOK)
    {
        CString filePath = fileDialog.GetPathName();

        // Mở file để ghi dữ liệu
        CFile file;
        if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite))
        {
            // Ghi dữ liệu vào file
            file.Write(msgstr.c_str(), msgstr.size());

            file.Close();
            AfxMessageBox(_T("Lưu thành công!"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            AfxMessageBox(_T("Không thể mở tệp tin để ghi dữ liệu"), MB_OK | MB_ICONERROR);
        }
    }
}






void CRSADlg::OnBnClickedBtnFile()
{
    CFileDialog fileDialog(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
    if (fileDialog.DoModal() == IDOK) {
        CString filePath = fileDialog.GetPathName();

        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Convert fileContent to CString
            CString cstr(fileContent.c_str());

            // Get a pointer to the text box control
            CEdit* pTextBox = (CEdit*)GetDlgItem(IDC_EDT_FILE_INPUT);

            if (pTextBox) {
                pTextBox->SetWindowText(cstr);
            }

            file.close();
        }
        else {
            AfxMessageBox(_T("Unable to open file"), MB_OK | MB_ICONERROR);
        }
    }
}


void CRSADlg::OnBnClickedBtnFileText()
{
    CFileDialog fileDialog(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
    if (fileDialog.DoModal() == IDOK) {
        CString filePath = fileDialog.GetPathName();

        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Convert fileContent to CString
            CString cstr(fileContent.c_str());

            // Get a pointer to the text box control
            CEdit* pTextBox = (CEdit*)GetDlgItem(IDC_EDT_FILE_TEXT);

            if (pTextBox) {
                pTextBox->SetWindowText(cstr);
            }

            file.close();
        }
        else {
            AfxMessageBox(_T("Unable to open file"), MB_OK | MB_ICONERROR);
        }
    }
}

//kiểm tra chữ kí

void CRSADlg::OnBnClickedBtnCheck()
{
    // Lấy văn bản từ Edit Control
    CString vanBanKy;
    edt_file_input.GetWindowText(vanBanKy);

    CString vanBanXacNhan;
    GetDlgItemText(IDC_EDT_FILE_TEXT, vanBanXacNhan);

    // Kiểm tra văn bản cần ký và văn bản cần xác nhận
    if (vanBanKy != vanBanXacNhan)
    {
        MessageBox(_T("Văn bản cần ký và văn bản cần xác nhận không khớp!"), _T("Lỗi"), MB_OK | MB_ICONERROR);
        return;
    }

    // Lấy chữ ký từ Edit Control
    CString chuKyXacNhan;
    GetDlgItemText(IDC_EDT_FILE_SIGN, chuKyXacNhan);

    CString chuKyFake;
    GetDlgItemText(IDC_LIST_SIGN, chuKyFake);


    // Hiển thị kết quả
    if (chuKyXacNhan != chuKyFake) 
    {
        MessageBox(_T("Chữ ký không tồn tại hoặc không chính xác!"), _T("Kết quả"), MB_OK | MB_ICONERROR);
        
    }
    else
    {
        MessageBox(_T("Chữ ký đã tồn tại và chính xác!"), _T("Kết quả"), MB_OK | MB_ICONINFORMATION);
    }
}


//button file_chữ_ký 

void CRSADlg::OnBnClickedBtnFileSign()
{
    CFileDialog fileDialog(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
    if (fileDialog.DoModal() == IDOK) {
        CString filePath = fileDialog.GetPathName();

        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Convert fileContent to CString
            CString cstr(fileContent.c_str());

            // Get a pointer to the text box control
            CEdit* pTextBox = (CEdit*)GetDlgItem(IDC_EDT_FILE_SIGN);

            if (pTextBox) {
                pTextBox->SetWindowText(cstr);
            }

            file.close();
        }
        else {
            AfxMessageBox(_T("Unable to open file"), MB_OK | MB_ICONERROR);
        }
    }
}

void CRSADlg::OnBnClickedButton1()
{
    CString thongDiep4;
    GetDlgItemText(IDC_EDT_FILE_INPUT, thongDiep4);

    // Chuyển đổi sang std::wstring
    std::wstring wstr(thongDiep4);

    // Chuyển đổi sang std::string
    std::string msgstr(wstr.begin(), wstr.end());

    // Yêu cầu người dùng chọn đường dẫn cho tệp tin
    CFileDialog fileDialog(FALSE, _T("txt"), NULL, OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
    if (fileDialog.DoModal() == IDOK)
    {
        CString filePath = fileDialog.GetPathName();

        // Mở file để ghi dữ liệu
        CFile file;
        if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite))
        {
            // Ghi dữ liệu vào file
            file.Write(msgstr.c_str(), msgstr.size());

            file.Close();
            AfxMessageBox(_T("Lưu thành công!"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            AfxMessageBox(_T("Không thể mở tệp tin để ghi dữ liệu"), MB_OK | MB_ICONERROR);
        }
    }
}


void CRSADlg::OnEnChangeListSignP()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CRSADlg::OnEnChangeListSign()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CRSADlg::OnEnChangeListSignE()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CRSADlg::OnEnChangeEdtFileInput()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CRSADlg::OnBnClickedButton2()
{
    
}


void CRSADlg::OnEnChangeEdtFileText()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


void CRSADlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CDialogEx::OnOK();
}


void CRSADlg::OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult)
{
    // This feature requires Windows XP or greater.
    // The symbol _WIN32_WINNT must be >= 0x0501.
    // TODO: Add your control notification handler code here
    *pResult = 0;
}
