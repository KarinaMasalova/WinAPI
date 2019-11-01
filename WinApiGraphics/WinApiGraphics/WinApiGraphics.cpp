#include <windows.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //дескриптор окна, инфа о сообщении, доп инфа о сообщении (*2)

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow) {

	WNDCLASSW wc;
	MSG msg;
	HWND hwnd;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"My Windows API Graphics";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE - 9);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName,
		L"My Windows API Graphics",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		450, 100, 340, 500, /*отступ слева, отступ сверху, ширина контейнера, высота контейнера*/
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc; //указатель на структуру контекста отображения
	PAINTSTRUCT ps; //структура, которая содержит информацию о рисовании окна
	RECT rect;
	HFONT hFont;
	static LOGFONT lf1, lf2, lf3, lf4;  //создание экземпляров LOGFONT
	WNDCLASSW wc;
	HPEN hPen1, hPen2, hPen3, hPen4, hPen5, hPen6;
	HBRUSH hBrush, hBrush1; //кисть

	wc.lpszClassName = L"My Windows API Graphics";
	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps); //инициализация контекста устройства
			GetClientRect(hwnd, &rect); //получаем ширину и высоту области для рисования

			hPen1 = CreatePen(PS_SOLID, 5, RGB(255, 255, 51));//задание стиля пера
			hPen2 = CreatePen(PS_SOLID, 5, RGB(102, 255, 102));
			hPen3 = CreatePen(PS_SOLID, 5, RGB(102, 255, 255));
			hPen4 = CreatePen(PS_SOLID, 5, RGB(255, 153, 153));

			/*косые линии (наклон вправо)*/
			SelectObject(hdc, hPen1);
			MoveToEx(hdc, 35, 85, NULL);
			LineTo(hdc, 110, 10);

			SelectObject(hdc, hPen2);
			MoveToEx(hdc, 85, 85, NULL);
			LineTo(hdc, 160, 10);

			SelectObject(hdc, hPen3);
			MoveToEx(hdc, 135, 85, NULL);
			LineTo(hdc, 210, 10);

			SelectObject(hdc, hPen4);
			MoveToEx(hdc, 185, 85, NULL);
			LineTo(hdc, 260, 10);

			/*косые линии (наклон влево)*/
			SelectObject(hdc, hPen1);
			MoveToEx(hdc, 35, 10, NULL);
			LineTo(hdc, 110, 85);
			DeleteObject(hPen1);

			SelectObject(hdc, hPen2);
			MoveToEx(hdc, 85, 10, NULL);
			LineTo(hdc, 160, 85);
			DeleteObject(hPen2);

			SelectObject(hdc, hPen3);
			MoveToEx(hdc, 135, 10, NULL);
			LineTo(hdc, 210, 85);
			DeleteObject(hPen3);

			SelectObject(hdc, hPen4);
			MoveToEx(hdc, 185, 10, NULL);
			LineTo(hdc, 260, 85);
			DeleteObject(hPen4);

			hPen5 = CreatePen(PS_SOLID, 6, RGB(255, 247, 3));
			SelectObject(hdc, hPen5);
			Ellipse(hdc, 95, 100, 195, 200);
			DeleteObject(hPen5);

			/*закрашивание круга*/
			hBrush1 = CreateSolidBrush(RGB(96, 96, 96));
			SelectObject(hdc, hBrush1);
			Ellipse(hdc, 95, 100, 195, 200); /*веpхний левый угол, пpавый нижний*/
			DeleteObject(hBrush1);

			hPen6 = CreatePen(PS_SOLID, 6, RGB(204, 153, 255));
			SelectObject(hdc, hPen6);
			Ellipse(hdc, 40, 220, 250, 280);
			DeleteObject(hPen6);

			/*закрашивание эллипса*/
			hBrush = CreateSolidBrush(RGB(204, 153, 255));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 40, 220, 250, 280);
			DeleteObject(hBrush);

			lf1.lfCharSet = DEFAULT_CHARSET;
			lf1.lfPitchAndFamily = DEFAULT_PITCH;
			lf1.lfHeight = 20;
			lf1.lfWidth = 8;
			lf1.lfWeight = 40; //толщина

			lf2.lfCharSet = DEFAULT_CHARSET;
			lf2.lfPitchAndFamily = DEFAULT_PITCH;
			lf2.lfHeight = 20;
			lf2.lfWidth = 8;
			lf2.lfWeight = 40;
			lf2.lfItalic = 1;
			lf2.lfStrikeOut = 1;

			lf3.lfCharSet = DEFAULT_CHARSET;
			lf3.lfPitchAndFamily = DEFAULT_PITCH;
			lf3.lfHeight = 28;
			lf3.lfWidth = 8;
			lf3.lfWeight = 40;

			lf4.lfCharSet = DEFAULT_CHARSET;
			lf4.lfPitchAndFamily = FF_MODERN;
			lf4.lfHeight = 20;
			lf4.lfWidth = 8;
			lf4.lfWeight = 40;

			hFont = CreateFontIndirect(&lf1); //создание шрифта
			SelectObject(hdc, hFont); //выбираем шрифт
			SetTextColor(hdc, RGB(229, 34, 174));
			SetBkColor(hdc, RGB(255, 204, 229));
			SelectObject(hdc, hFont);
			::TextOut(hdc, 25, 300, L"Не гляди на ее запястья", 24);

			hFont = CreateFontIndirect(&lf2);
			SelectObject(hdc, hFont);
			SetTextColor(hdc, RGB(229, 34, 174));
			SetBkColor(hdc, RGB(255, 204, 229));
			SelectObject(hdc, hFont);
			::TextOut(hdc, 25, 330, L"И с плечей ее льющийся шёлк.", 29);

			hFont = CreateFontIndirect(&lf3);
			SelectObject(hdc, hFont);
			SetTextColor(hdc, RGB(229, 34, 174));
			SetBkColor(hdc, RGB(255, 204, 229));
			SelectObject(hdc, hFont);
			::TextOut(hdc, 25, 360, L"Я искал в этой женщине счастья,", 32);

			hFont = CreateFontIndirect(&lf4);
			SelectObject(hdc, hFont);
			SetTextColor(hdc, RGB(229, 34, 174));
			SetBkColor(hdc, RGB(255, 204, 229));
			SelectObject(hdc, hFont);
			::TextOut(hdc, 25, 390, L"А нечаянно гибель нашел.", 25);

			ValidateRect(hwnd, NULL);//пpовеpяет достовеpность области пользователя, удаляя Rect из области обновления окна
			EndPaint(hwnd, &ps);
			break;

	case WM_DESTROY: //сообщение отправляется тогда, когда окно разрушается
		PostQuitMessage(0); //указывает системе, что поток сделал запрос на то, чтобы завершить свою работу
		break;

	default:
		return DefWindowProcW(hwnd, msg, wParam, lParam); /*гарантирует обработку каждого сообщения (hwnd получает сообщение,
														  msg определяет сообщение,
														  wParam и lParam определяют доп. инфу о сообщении*/
	}
	return 0;
}