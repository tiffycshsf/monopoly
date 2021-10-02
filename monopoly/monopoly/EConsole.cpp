#include"EConsole.h"


void _SetConsoleTitle(const char* title)
{
	SetConsoleTitle(title);
}

// ============================================
// �禡�G GetConsoleTitle
// �����G ���o Consle �W��
// ===========================================
void _GetConsoleTitle(char* title, DWORD nSize)
{
	GetConsoleTitle(title, nSize);
}


// =============================================
// �禡�G gotoxy
// �����G ���ʴ�Цܫ��w��m
// ============================================
void gotoxy(int x, int  y)
{
	COORD point;
	point.X = x, point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// =============================================
// �禡�G getxy
// �����G ���o�ثe��Ц�m
// ============================================
void getxy(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}

// ============================================
// �禡�G SetCursorVisible, �]�w�����ܤ��
// �����G ���N�O�]�w��Цh�Τj,�ʤ��� 1~100
// ===========================================
void SetCursorVisible(BOOL Visible, DWORD Size)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = Visible; // �O�_�i��
	cci.dwSize = Size; // �]�w�j�p,1~100
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

// ============================================
// �禡�G Clr, �M���ù�
// �����G �ѨM�ϥ� system("cls") �|���{�{���D
//        �ƹ�W�o�u�O��C���I����W�ťզӤw
// ����G CodeGurn
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
// �禡�G SetColor, �]�w��r�C��P�I���C��
// �����G �o�̪��C��n�� macro,�ƹ�W���ܦh�զX
//        �u�O�o�̵� 0~15 ���s��²�ƲզX
// ����G CodeGurn
// ===========================================

void SetColor(int color) // ���������w�]
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
// �禡�G SetConsoleSize
// �����G �]�w Console �����j�p
//        // x ���n��.
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
// �禡�G ConsoleFullScreen
// �����G Console�]�����ù�
//        VK_MENU -> ALT, VK_RETURN -> Enter
//        ���N�O alt + Enter 
// ����G CodeGurn
// ===========================================

void ConsoleFullScreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	/* �쪩�O�g�U���o��,���ھ� scan code �e�X���T��, �����n
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
	*/

}

// ============================================
// �禡�G IsConsoleFullScreen()
// �����G �P�_�O�_�����ù�
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
// �禡�G GetConsoleWindowSize
// �����G ���o�ثe�����j�p
// ===========================================


void GetConsoleWindowSize(DWORD &W, DWORD &H)
{
	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	W = cfi.dwFontSize.X;
	H = cfi.dwFontSize.Y;
}

// ============================================
// �禡�G _GetLargestConsoleWindowSize
// �����G ���o�̤j�����j�p
// ===========================================

void _GetLargestConsoleWindowSize(DWORD &W, DWORD &H)
{
	COORD c = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	W = c.X;
	H = c.Y;
}

// ============================================
// �禡�G SetConsoleWindowSize
// �����G �]�w�ثe�����j�p
//        x �䤣��i�J�I���D, �L�k����
//        SetCurrentConsoleFontEx �ݩ� Vista �H�W�~�䴩,�L�k�i����ռ��g
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
// GetNumberOfEvent, �q buffer ���o�٦��h�֨SŪ
// GetNumberOfConsoleMouseButtons, �h��mouse�ƥ�SŪ
// WriteConsole(hStdOut,szPrintBuffer,lstrlen(szPrintBuffer),&nCharsWritten,NULL);
// ReadConsole(hStdIn,read_buff,1,&nBytesRead,NULL))
// ===========================================
