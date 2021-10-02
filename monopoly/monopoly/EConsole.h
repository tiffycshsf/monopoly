#ifndef _ECONSOLE_
#define _ECONSOLE_
#include <windows.h>

void _SetConsoleTitle(const char* title);
void _GetConsoleTitle(char* title, DWORD nSize);
void gotoxy(int x, int  y);
void getxy(int &x, int &y);
void SetCursorVisible(BOOL Visible, DWORD Size);
void Clr();
void SetColor(int color = -1); // ���������w�]
BOOL SetConsoleSize(int W, int H);
void ConsoleFullScreen();
BOOL IsConsoleFullScreen();
void GetConsoleWindowSize(DWORD &W, DWORD &H);
void _GetLargestConsoleWindowSize(DWORD &W, DWORD &H);
// ============================================
// �禡�G ConsoleTitle
// �����G �]�w Consle �W��
// ===========================================


// ============================================
// �禡�G GetConsoleTitle
// �����G ���o Consle �W��
// ===========================================



// =============================================
// �禡�G gotoxy
// �����G ���ʴ�Цܫ��w��m
// ============================================


// =============================================
// �禡�G getxy
// �����G ���o�ثe��Ц�m
// ============================================


// ============================================
// �禡�G SetCursorVisible, �]�w�����ܤ��
// �����G ���N�O�]�w��Цh�Τj,�ʤ��� 1~100
// ===========================================


// ============================================
// �禡�G Clr, �M���ù�
// �����G �ѨM�ϥ� system("cls") �|���{�{���D
//        �ƹ�W�o�u�O��C���I����W�ťզӤw
// ����G CodeGurn
// ===========================================


// ============================================
// �禡�G SetColor, �]�w��r�C��P�I���C��
// �����G �o�̪��C��n�� macro,�ƹ�W���ܦh�զX
//        �u�O�o�̵� 0~15 ���s��²�ƲզX
// ����G CodeGurn
// ===========================================



// ============================================
// �禡�G SetConsoleSize
// �����G �]�w Console �����j�p
//        // x ���n��.
// ===========================================


// ============================================
// �禡�G ConsoleFullScreen
// �����G Console�]�����ù�
//        VK_MENU -> ALT, VK_RETURN -> Enter
//        ���N�O alt + Enter 
// ����G CodeGurn
// ===========================================


// ============================================
// �禡�G IsConsoleFullScreen()
// �����G �P�_�O�_�����ù�
// ===========================================



// ============================================
// �禡�G GetConsoleWindowSize
// �����G ���o�ثe�����j�p
// ===========================================




// ============================================
// �禡�G _GetLargestConsoleWindowSize
// �����G ���o�̤j�����j�p


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

#endif