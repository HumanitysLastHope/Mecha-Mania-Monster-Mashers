#include <Windows.h>
#include <wchar.h>
#include <string>
#include <conio.h>
#include <iostream>

void set_console_size(HANDLE screen_buffer, SHORT width, SHORT height)
{
	COORD const size = { width, height };
	BOOL success;

	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	success = SetConsoleWindowInfo(screen_buffer, TRUE, &minimal_window);

	success = SetConsoleScreenBufferSize(screen_buffer, size);

	SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
	success = SetConsoleWindowInfo(screen_buffer, TRUE, &window);
}

void setFontSize(int FontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, sizeof(L"Lucida Console"), L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

int main()
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_console_size(Handle, 150, 50);

	int iFontSize = 18;
	setFontSize(iFontSize);

	std::cout << "Font: Consolas, Size: " << iFontSize << std::endl;

	_getch();
}