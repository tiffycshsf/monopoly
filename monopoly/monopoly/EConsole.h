#ifndef _ECONSOLE_
#define _ECONSOLE_
#include <windows.h>

void _SetConsoleTitle(const char* title);
void _GetConsoleTitle(char* title, DWORD nSize);
void gotoxy(int x, int  y);
void getxy(int &x, int &y);
void SetCursorVisible(BOOL Visible, DWORD Size);
void Clr();
void SetColor(int color = -1); // 直接先給預設
BOOL SetConsoleSize(int W, int H);
void ConsoleFullScreen();
BOOL IsConsoleFullScreen();
void GetConsoleWindowSize(DWORD &W, DWORD &H);
void _GetLargestConsoleWindowSize(DWORD &W, DWORD &H);
// ============================================
// 函式： ConsoleTitle
// 說明： 設定 Consle 名稱
// ===========================================


// ============================================
// 函式： GetConsoleTitle
// 說明： 取得 Consle 名稱
// ===========================================



// =============================================
// 函式： gotoxy
// 說明： 移動游標至指定位置
// ============================================


// =============================================
// 函式： getxy
// 說明： 取得目前游標位置
// ============================================


// ============================================
// 函式： SetCursorVisible, 設定游標顯示比例
// 說明： 其實就是設定游標多肥大,百分比 1~100
// ===========================================


// ============================================
// 函式： Clr, 清除螢幕
// 說明： 解決使用 system("cls") 會有閃爍問題
//        事實上這只是把每個點都填上空白而已
// 轉載： CodeGurn
// ===========================================


// ============================================
// 函式： SetColor, 設定文字顏色與背景顏色
// 說明： 這裡的顏色要看 macro,事實上有很多組合
//        只是這裡給 0~15 的編號簡化組合
// 轉載： CodeGurn
// ===========================================



// ============================================
// 函式： SetConsoleSize
// 說明： 設定 Console 視窗大小
//        // x 不好用.
// ===========================================


// ============================================
// 函式： ConsoleFullScreen
// 說明： Console設為全螢幕
//        VK_MENU -> ALT, VK_RETURN -> Enter
//        其實就是 alt + Enter 
// 轉載： CodeGurn
// ===========================================


// ============================================
// 函式： IsConsoleFullScreen()
// 說明： 判斷是否為全螢幕
// ===========================================



// ============================================
// 函式： GetConsoleWindowSize
// 說明： 取得目前視窗大小
// ===========================================




// ============================================
// 函式： _GetLargestConsoleWindowSize
// 說明： 取得最大視窗大小


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

#endif