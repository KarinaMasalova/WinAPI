#include <windows.h>
#include <gdiplus.h>
#include <math.h>
# define M_PI 3.14159265358979323846
#pragma comment(lib,"Gdiplus.lib")

using namespace Gdiplus;

VOID OnPaint(HDC hdc); // прототип

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP hBitmap;

int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
	HINSTANCE hPrevInst, // не используем
	LPSTR lpCmdLine, // не используем
	int nCmdShow) // режим отображения окошка
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wc;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect); // разрешение экрана
	int x = rect.right / 2 - 500;
	int y = rect.bottom / 2 - 370;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	/*РЕГИСТРАЦИЯ КЛАССА ОКНА*/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("EllipseExample");

	/*ПРОВЕРКА РЕГИСТРАЦИИ*/
	if (!RegisterClass(&wc))
	{
		// в случае отсутствия регистрации класса:
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}

	/*СОЗДАНИЕ ОКНА*/
	hWnd = CreateWindow(
		TEXT("EllipseExample"), TEXT("Ellipse Example"), WS_SYSMENU,
		x, y, 1000, 700,
		NULL, NULL, hInst, NULL);

	/*ПРОРИСОВКА*/
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/*ПРОСЛУШКА*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_INITDIALOG:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc);
		ValidateRect(hWnd, NULL); //обновление области
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	ReleaseDC(hWnd, hdc); //Освобождаем общий или оконный (не влияющий на класс или локальность) контекст устpойства, делая его доступным для дpугих пpикладных задач.
}

VOID OnPaint(HDC hdc)
{
	int x_scr, y_scr; // Экранные координаты шажков прорисовки
	double x, h = M_PI / 10; // частота прорисовки
	int ampl = 150; // амплитуда колебания

	MoveToEx(hdc, 0, ampl, (LPPOINT)NULL);

	/*ЗАТУХАЮЩИЙ СИНУСОИДАЛЬНЫЙ СИГНАЛ*/
	for (x = -M_PI, x_scr = 0; x < 5000; x += h)
	{
		if (sin(x) == -1) ampl -= 10; // уменьшение амплинуды каждый раз как синусоида достигает своего минимального значения
		x_scr = x * 5 * M_PI; // частота колебания
		y_scr = (ampl * sin(x) + 300); // +300 это смещение сигнала вниз по ОY
		LineTo(hdc, x_scr, y_scr);
	}
}