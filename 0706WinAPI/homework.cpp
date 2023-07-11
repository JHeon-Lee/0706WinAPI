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

bool Intersect(const RECT& lhs, const RECT& rhs)
{
	bool is_check = true;

	is_check &= lhs.left <= rhs.right;
	is_check &= lhs.right >= rhs.left;
	is_check &= lhs.top <= rhs.bottom;
	is_check &= lhs.bottom >= rhs.top;

	return is_check;
}

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT position;
	static BOOL is_clicked;

	static POINT start;
	static POINT end;

	static RECT rect1 = { 100, 100, 200, 200 };
	static RECT rect2 = { 300, 300, 400, 400 };

	static BOOL is_intersect = FALSE;
	switch (message)
	{
#pragma region Mouse Point Printing
	//case WM_LBUTTONDOWN:
	//{
	//	position.x = LOWORD(lParam);
	//	position.y = HIWORD(lParam);
	//	is_clicked = true;

	//}
	//break;
	//case WM_MOUSEMOVE:
	//{
	//	if (is_clicked)
	//	{
	//		HDC hdc = GetDC(handle);
	//		MoveToEx(hdc, position.x, position.y, NULL);
	//		position.x = LOWORD(lParam);
	//		position.y = HIWORD(lParam);
	//		LineTo(hdc, position.x, position.y);
	//		ReleaseDC(handle, hdc);
	//	}
	//}
	//break;
	//case WM_LBUTTONUP:
	//{
	//	is_clicked = false;
	//}
	//break;
#pragma endregion
#pragma region Draw Polygon
	//case WM_LBUTTONDOWN:
	//{
	//    start.x = LOWORD(lParam);
	//    start.y = HIWORD(lParam);
	//    is_clicked = TRUE;
	//
	//    break;
	//}
	//
	//case WM_MOUSEMOVE:
	//{
	//    if (is_clicked)
	//    {
	//        end.x = LOWORD(lParam);
	//        end.y = HIWORD(lParam);
	//        InvalidateRect(handle, nullptr, TRUE);
	//    }
	//    break;
	//}
	//
	//case WM_LBUTTONUP:
	//{
	//    is_clicked = FALSE;
	//    break;
	//}
	//
	//case WM_PAINT:
	//{
	//    PAINTSTRUCT ps;
	//    HDC hdc = BeginPaint(handle, &ps);
	//
	//    HPEN cur_pen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	//    HPEN old_pen = static_cast<HPEN>(SelectObject(hdc, cur_pen));
	//
	//    //HBRUSH cur_brush = CreateSolidBrush(RGB(0, 255, 255));
	//    HBRUSH cur_brush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 255));
	//    HBRUSH old_brush = static_cast<HBRUSH>(SelectObject(hdc, cur_brush));
	//
	//    Rectangle(hdc, start.x, start.y, end.x, end.y);
	//    SelectObject(hdc, old_pen);
	//    DeleteObject(cur_pen);
	//
	//    SelectObject(hdc, old_brush);
	//    DeleteObject(cur_brush);
	//
	//    EndPaint(handle, &ps);
	//}
	//break;

#pragma endregion
#pragma region Two Rects isColide
	case WM_KEYDOWN:
	{
		if (wParam == VK_UP)
		{
			rect1.top -= 10;
			rect1.bottom -= 10;
		}
		else if (wParam == VK_DOWN)
		{
			rect1.top += 10;
			rect1.bottom += 10;
		}
		if (wParam == VK_LEFT)
		{
			rect1.left -= 10;
			rect1.right -= 10;
		}
		else if (wParam == VK_RIGHT)
		{
			rect1.left += 10;
			rect1.right += 10;
		}

		is_intersect = Intersect(rect1, rect2);
		InvalidateRect(handle, nullptr, TRUE);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);

		Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
		Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

		if (is_intersect)
		{
			std::string str = "Intersect!!";
			TextOutA(hdc, 400, 410, str.c_str(), str.length());
		}

		EndPaint(handle, &ps);
	}
	break;
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