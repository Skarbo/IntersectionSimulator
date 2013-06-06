// Exercise3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Exercise3.h"
#include "Traffic.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//	STATIC

static Traffic traffic;

//	/STATIC

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EXERCISE3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXERCISE3));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXERCISE3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EXERCISE3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc, MemDoubleBuffer;
	HBITMAP bmpDoubleBuffer;
	int size = 600;

	traffic.setX(0);
	traffic.setY(0);
	traffic.setSize(size);
	traffic.initIntersection();

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:

		switch(wParam) 
		{
		case TIMER_DRIVE:
			traffic.doDrive();
			InvalidateRect(hWnd, 0, false);
			break;
		case TIMER_LIGHT:
			traffic.doIncreaseTrafficLight();
			InvalidateRect(hWnd, 0, false);
			break;
		case TIMER_CAR_CREATE:
			traffic.doAddCar(STATE_NORTH + (rand() % 4));
			InvalidateRect(hWnd, 0, false);
			break;
		}

	case WM_PAINT:

		// Begins the paint operation
		hdc = BeginPaint(hWnd, &ps);

		// Create double buffer DC
		MemDoubleBuffer = CreateCompatibleDC(hdc);

		// Create double buffer bitmap
		bmpDoubleBuffer = CreateCompatibleBitmap(hdc, size, size);

		// Select the new bitmap
		SelectObject(MemDoubleBuffer, bmpDoubleBuffer);

		// Draw intersection
		traffic.draw(MemDoubleBuffer);

		// Copy virtual to original
		BitBlt(
			hdc, 
			0, 
			0, 
			size, 
			size, 
			MemDoubleBuffer, 
			0, 
			0, 
			SRCCOPY
			);

		// Delete DC
		DeleteDC(MemDoubleBuffer);
		// Delete Objects
		DeleteObject(bmpDoubleBuffer);

		// End paint
		EndPaint(hWnd, &ps);

		break;
	case WM_LBUTTONDOWN:
		traffic.doIncreaseTrafficLight();
		InvalidateRect(hWnd, 0, false);
		break;
	case WM_RBUTTONDOWN:
		traffic.doBreakpoint();
		break;
	case WM_KEYUP:

		switch(wParam) 
		{

		case VK_UP:
			SetTimer(hWnd, TIMER_DRIVE, 10, NULL);
			SetTimer(hWnd, TIMER_CAR_CREATE, 100, NULL);
			SetTimer(hWnd, TIMER_LIGHT, 2000, NULL);
			break;
		case VK_DOWN:
			KillTimer(hWnd, TIMER_DRIVE);
			KillTimer(hWnd, TIMER_LIGHT);
			KillTimer(hWnd, TIMER_CAR_CREATE);
			break;

		case VK_NUMPAD8:
			//traffic.doAddCar(STATE_NORTH);
			traffic.incProbability(STATE_NORTH, 5);
			break;
		case VK_NUMPAD9:
			//traffic.doAddCar(STATE_NORTH);
			traffic.decProbability(STATE_NORTH, 5);
			break;

		case VK_NUMPAD6:
			//traffic.doAddCar(STATE_EAST);
			traffic.incProbability(STATE_EAST, 5);
			break;
		case VK_NUMPAD3:
			//traffic.doAddCar(STATE_NORTH);
			traffic.decProbability(STATE_EAST, 5);
			break;

		case VK_NUMPAD2:
			//traffic.doAddCar(STATE_SOUTH);
			traffic.incProbability(STATE_SOUTH, 5);
			break;
		case VK_NUMPAD1:
			//traffic.doAddCar(STATE_NORTH);
			traffic.decProbability(STATE_SOUTH, 5);
			break;

		case VK_NUMPAD4:
			//traffic.doAddCar(STATE_WEST);
			traffic.incProbability(STATE_WEST, 5);
			break;
		case VK_NUMPAD7:
			//traffic.doAddCar(STATE_NORTH);
			traffic.decProbability(STATE_WEST, 5);
			break;

		}

		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
