#include <Windows.h>
#include <string>

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam); // stdcall

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	WNDCLASSA wnd_class;

	wnd_class.cbClsExtra = 0;
	wnd_class.cbWndExtra = 0;
	wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR);
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = "First Window";
	wnd_class.lpszMenuName = nullptr;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassA(&wnd_class);

	HWND hwnd = CreateWindowA
	(
		"First Window",
		"Hello, Window",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1080,
		720,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindow(hwnd, nCmdShow);
	ShowCursor(TRUE);

	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	DestroyWindow(hwnd);
	UnregisterClassA("First Window", hInstance);

	return 0;
}

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT position;
	static bool isDrawing = false;
	HDC hdc;

	switch (message)
	{
#pragma region Mouse Point Printing
	case WM_LBUTTONDOWN:
	{
		position.x = LOWORD(lParam);
		position.y = HIWORD(lParam);
		isDrawing = true;

	}
	break;
	case WM_MOUSEMOVE:
	{
		if (isDrawing)
		{
			hdc = GetDC(handle);
			MoveToEx(hdc, position.x, position.y, NULL);
			position.x = LOWORD(lParam);
			position.y = HIWORD(lParam);
			LineTo(hdc, position.x, position.y);
			ReleaseDC(handle, hdc);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		isDrawing = false;
	}
	break;
#pragma endregion
#pragma region Two Rects isColide

#pragma endregion
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcA(handle, message, wParam, lParam);
	}
}

// 내일까지 그림판 만들기
// 브러시 사용해서 그리기
// + 화면에 네모 두개 띄우고 하나는 움직이게 함, 충돌하면 충돌했다는 메세지 띄우기