#include <windows.h>

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX); //size of the structure
	wc.style = 0; //class styles (cs_*), not to be confused with Window Styles (ws_*). Can usually be set to 0.
	wc.lpfnWndProc = WndProc; //pointer to the window procedure for this window class.
	wc.cbClsExtra = 0; //amount of extra data allocated for this class in memory. Usually 0.
	wc.cbWndExtra = 0; //amount of extra data allocated in memory per window of this type. Usually 0.
	wc.hInstance = hInstance; //handle to application instance (that we got in the first parameter of WinMain())
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //large icon shown when user presses alt+tab
	wc.hCursor = LoadCursor(NULL, IDC_HAND); // cursor that will be displayed over our window
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //background brush to set the color of our window
	wc.lpszMenuName = NULL; //name of a menu resource to use for the windows with this class
	wc.lpszClassName = g_szClassName; //name to identify the class with
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //small icon to show in the taskbar and in the top left corner of the window

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}