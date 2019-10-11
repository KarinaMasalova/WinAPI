#include <windows.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMess[] = L"Hello, world!";
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
	wc.lpszClassName = L"My Windows Form";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, 
						L"My Windows Form",
						WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						450, 100, 450, 400, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	HDC hdc; //указатель на структуру контекста отображения
	PAINTSTRUCT ps; //структура, которая содержит информацию о рисовании окна
	RECT rect; //определяет прямоугольник, используя координаты его левого верхнего и нижнего правого углов
	COLORREF colorText = RGB(102, 204, 0);
	HWND textcontainer;
	/*HINSTANCE hInst;*/
	WNDCLASSW wc;
	static HWND hButton;

	wc.lpszClassName = L"My Windows Form";
	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps); //инициализация контекста устройства
			GetClientRect(hwnd, &rect); //получаем ширину и высоту области для рисования
			SetTextColor(hdc, colorText);
			DrawText(hdc, mainMess, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			break;

		case WM_CREATE:
			textcontainer = CreateWindow(L"EDIT",
									L"Hello, world!", WS_BORDER | WS_CHILD | WS_VISIBLE,
									170, 50, 90, 25, /*отступ слева, отступ сверху, ширина контейнера, высота контейнера*/
									hwnd, NULL, NULL, NULL);

			hButton = CreateWindow(L"button", L"Press the button",
									WS_CHILD | WS_VISIBLE | WS_BORDER,
									170, 300, 120, 30, hwnd, 0, 0, NULL);

			ShowWindow(hButton, SW_SHOWNORMAL); //SW_SHOWNORMAL активизирует и отображает окно
			break;

		case WM_COMMAND:
			if (lParam == (LPARAM)hButton) { //при нажатии на кнопку
				MessageBox(hwnd, mainMess, L"Button", MB_APPLMODAL);
			}
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