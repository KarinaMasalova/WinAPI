#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {

	MSG msg = { 0 };
	HWND hwnd; //дескриптор главного окна программы
	WNDCLASSW wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0; //число дополнительных байт, которые размещаются вслед за структурой класса
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Grid";
	wc.hInstance = hInst; //установка экземпляра программы
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE - 4);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WindowProcedure;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, L"Grid",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		250, 100, 600, 400, NULL, NULL, hInst, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg); //функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); //посылает сообщение функции WndProc()
	}
	return (int)msg.wParam; //код завершения возвращается в систему
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	static int sX, sY;
	int a, b;
	static HPEN hPen1, hPen2;
	static HBRUSH hBrush;

	switch (msg) {
		case WM_CREATE:
			CreateWindowW(L"Static", L"0", WS_VISIBLE | WS_CHILD | SS_CENTER, 270, 190, 12, 15, hwnd, NULL, NULL, NULL);
			CreateWindowW(L"Static", L"x", WS_VISIBLE | WS_CHILD | SS_CENTER, 560, 190, 12, 15, hwnd, NULL, NULL, NULL);
			CreateWindowW(L"Static", L"y", WS_VISIBLE | WS_CHILD | SS_CENTER, 270, 10, 12, 15, hwnd, NULL, NULL, NULL);
			break;

		case WM_SIZE:
			sX = LOWORD(lParam); //ширина окна
			sY = HIWORD(lParam); //высота окна
			break;

		case WM_CTLCOLORSTATIC:
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (BOOL)GetStockObject(NULL_BRUSH);
			break;


		case WM_PAINT:
			hDC = BeginPaint(hwnd, &ps);
			hPen1 = CreatePen(PS_SOLID, 3, RGB(111, 45, 135));
			hPen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			hBrush = CreateHatchBrush(HS_CROSS, RGB(156, 202, 255));

			SelectObject(hDC, hBrush);
			Rectangle(hDC, 0, 0, sX, sY);

			a = sX / 2;
			b = sY / 2;

			SelectObject(hDC, hPen1);
			MoveToEx(hDC, 0, b, NULL);
			LineTo(hDC, sX, b);
			MoveToEx(hDC, a, 0, NULL);
			LineTo(hDC, a, sY);
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:
			DeleteObject(hPen1);
			DeleteObject(hPen2);
			DeleteObject(hBrush);
			PostQuitMessage(0);
			break;
		}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}