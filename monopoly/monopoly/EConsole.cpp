#include"EConsole.h"


void _SetConsoleTitle(const char* title)
{
	SetConsoleTitle(title);
}

// ============================================
// 函式： GetConsoleTitle
// 說明： 取得 Consle 名稱
// ===========================================
void _GetConsoleTitle(char* title, DWORD nSize)
{
	GetConsoleTitle(title, nSize);
}


// =============================================
// 函式： gotoxy
// 說明： 移動游標至指定位置
// ============================================
void gotoxy(int x, int  y)
{
	COORD point;
	point.X = x, point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// =============================================
// 函式： getxy
// 說明： 取得目前游標位置
// ============================================
void getxy(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}

// ============================================
// 函式： SetCursorVisible, 設定游標顯示比例
// 說明： 其實就是設定游標多肥大,百分比 1~100
// ===========================================
void SetCursorVisible(BOOL Visible, DWORD Size)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = Visible; // 是否可視
	cci.dwSize = Size; // 設定大小,1~100
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

// ============================================
// 函式： Clr, 清除螢幕
// 說明： 解決使用 system("cls") 會有閃爍問題
//        事實上這只是把每個點都填上空白而已
// 轉載： CodeGurn
// ===========================================
void Clr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '),
		dwConSize,
		coordScreen,
		&cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole,
		csbi.wAttributes,
		dwConSize,
		coordScreen,
		&cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);

}

// ============================================
// 函式： SetColor, 設定文字顏色與背景顏色
// 說明： 這裡的顏色要看 macro,事實上有很多組合
//        只是這裡給 0~15 的編號簡化組合
// 轉載： CodeGurn
// ===========================================

void SetColor(int color) // 直接先給預設
{
	switch (color)
	{
	case 0:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 1:    // Red on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case 2:    // Green on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case 3:    // Yellow on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN);
		break;
	case 4:    // Blue on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case 5:    // Magenta on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_BLUE);
		break;
	case 6:    // Cyan on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	case 7:    // Black on Gray
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		break;
	case 8:    // Black on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE);
		break;
	case 9:    // Red on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE |
			FOREGROUND_RED);
		break;
	case 10:    // Green on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_GREEN);
		break;
	case 11:    // Yellow on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_GREEN);
		break;
	case 12:    // Blue on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_BLUE);
		break;
	case 13:    // Magenta on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_BLUE);
		break;
	case 14:    // Cyan on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	case 15:    // White on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}

// ============================================
// 函式： SetConsoleSize
// 說明： 設定 Console 視窗大小
//        // x 不好用.
// ===========================================
BOOL SetConsoleSize(int W, int H)
{
	BOOL ret;
	SMALL_RECT SR;
	SR.Top = 0;
	SR.Left = 0;
	SR.Bottom = H - 1;
	SR.Right = W - 1;
	ret = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &SR);
	if (!ret) return ret;

	COORD Sz;
	Sz.X = W;
	Sz.Y = H;

	return SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), Sz);
}

// ============================================
// 函式： ConsoleFullScreen
// 說明： Console設為全螢幕
//        VK_MENU -> ALT, VK_RETURN -> Enter
//        其實就是 alt + Enter 
// 轉載： CodeGurn
// ===========================================

void ConsoleFullScreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	/* 原版是寫下面這樣,但根據 scan code 送出之訊息, 較不好
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
	*/

}

// ============================================
// 函式： IsConsoleFullScreen()
// 說明： 判斷是否為全螢幕
// ===========================================
BOOL IsConsoleFullScreen()
{
	// CONSOLE_FULLSCREEN(1), CONSOLE_FULLSCREEN_HARDWARE(2)
	DWORD mode;
	GetConsoleDisplayMode(&mode);
	if ((mode&CONSOLE_FULLSCREEN) == CONSOLE_FULLSCREEN) return TRUE;
	return FALSE;
}


// ============================================
// 函式： GetConsoleWindowSize
// 說明： 取得目前視窗大小
// ===========================================


void GetConsoleWindowSize(DWORD &W, DWORD &H)
{
	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	W = cfi.dwFontSize.X;
	H = cfi.dwFontSize.Y;
}

// ============================================
// 函式： _GetLargestConsoleWindowSize
// 說明： 取得最大視窗大小
// ===========================================

void _GetLargestConsoleWindowSize(DWORD &W, DWORD &H)
{
	COORD c = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	W = c.X;
	H = c.Y;
}

// ============================================
// 函式： SetConsoleWindowSize
// 說明： 設定目前視窗大小
//        x 找不到進入點問題, 無法測試
//        SetCurrentConsoleFontEx 需於 Vista 以上才支援,無法進行測試撰寫
// ===========================================
/*

void SetConsoleWindowSize(SHORT x, SHORT y)
{
		CONSOLE_FONT_INFOEX cfi;
		cfi.dwFontSize.X = x;
		cfi.dwFontSize.Y = y;
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),
				FALSE, &cfi);
}
*/

// ============================================
// GetNumberOfEvent, 從 buffer 取得還有多少沒讀
// GetNumberOfConsoleMouseButtons, 多少mouse事件沒讀
// WriteConsole(hStdOut,szPrintBuffer,lstrlen(szPrintBuffer),&nCharsWritten,NULL);
// ReadConsole(hStdIn,read_buff,1,&nBytesRead,NULL))
// ===========================================
