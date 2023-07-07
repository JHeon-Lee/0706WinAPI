// WinAPI �� �ٷ����
// �ַ�� ��Ŭ�� -> �����Ӽ� -> ��Ŀ -> �ý��� -> �����ý��� --->>> â���� �ٲ��ش�.
// API : application program interface(����� ����)
// ������ ������ â�� ���� ���� �뵵
// API�� ���� : �ٷ�X
//
// �������
// �޼���
// - �����쿡�� �߻��ϴ� ��� �̺�Ʈ
// 
// �޼��� ť -> ���� ���� �޼����� ���������� ó��(FIFO)
// - �޼������� ��ũ�� ����� ��ȯ�Ǽ� �޼��� ť�� ����
// 
// �޼��� ����
// - �޼����� �˸��� ���·� ��ȯ
// 
// ������ ���ν���(*) �߿�
// - ������ ���ǵ� ����(�����ڰ� ���� ����) �� �°� ó���ϴ� �Լ�

// LPSTR - long pointer str = char*
// LPCSTR - const char*
// LPWSTR - wchar_t*
// LPCWSTR - const wchar_t*

#include <Windows.h>
#include <cassert>
#include <string>

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam); // stdcall
// �����쿡�� ���� ȣ��

int APIENTRY WinMain // APIENTRY : ������ ���
// WinMain : �޼��� ó����
(
	HINSTANCE hInstance, // HINSTANCE : ������ â �ǹ�
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam, // ���ڿ��� �Ѱ��ش�
	int nCmdShow // ��� �����ٰǰ�
	// ������ �ʾƵ� �ڵ����� ����
)
{
	WNDCLASSA wnd_class; // ����â(�⺻��)

	wnd_class.cbClsExtra = 0; // Ŭ������ ���� Ȯ��� ���� ����Ұ�����
	wnd_class.cbWndExtra = 0; // �����츦 ���� Ȯ��� ���� ����Ұ�����
	wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));// ��� ���� ���� ����Ұ�����
	// ��Ŭ�� -> ���Ƿ� �̵� ����ϸ� ����
	wnd_class.hCursor = LoadCursor(nullptr, IDC_CROSS); // Ŀ�� ����
	wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR); // �۾�ǥ��â ����
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc; // ������ ���ν��� ����
	wnd_class.lpszClassName = "First Window"; // ����ȭ �� �̸�
	wnd_class.lpszMenuName = nullptr;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassA(&wnd_class); // ���� ���� ����� ����

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
	// assert ���� ����� ����
	assert(hwnd != nullptr);

	ShowWindow(hwnd, nCmdShow);
	ShowCursor(TRUE);

	MSG message;
	ZeroMemory(&message, sizeof(MSG)); // ������ �ʱ�ȭ

	while (GetMessage(&message, nullptr, 0, 0))
	// GetMessage : �����(�޼����� ���ö����� ��ٸ�)
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
	switch (message)
	{
		static POINT position; // x,y ��ǥ �������
#pragma region Message Box
	//case WM_LBUTTONDOWN:
	//	MessageBoxA(nullptr, "Hello, Window!", "ERROR!", MB_OKCANCEL); // Ȯ��, ��� â
	//	break;
#pragma endregion
#pragma region Text
	//case WM_LBUTTONDOWN:
	//{
	//	std::string str = "Mouse Clicked!!";

	//	HDC hdc = GetDC(handle); // handle device context -> �׷��� �۾� �����Ҷ� ���
	//	TextOutA(hdc, 500, 300, str.c_str(), str.length());
	//	ReleaseDC(handle, hdc);
	//}
	//break; // -> ȭ���� ���ŵǴ� ��(�ٽ� �׷�����) �� �߻��ϸ� �޼����� �����
	//// �ؿ��� ���ڿ��� �Ȼ����
	//
	//case WM_PAINT:
	//{
	//	std::string str = "WM_PAINT message occurred!";

	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(handle, &ps);
	//	TextOutA(hdc, 500, 350, str.c_str(), str.length());

	//	EndPaint(handle, &ps);
	//}
	//break;

#pragma endregion
#pragma region Text Moving
	//case WM_KEYDOWN:
	//	if (wParam == VK_UP) position.y -= 10;
	//	else if (wParam == VK_DOWN) position.y += 10;
	//	if (wParam == VK_RIGHT) position.x += 10;
	//	else if (wParam == VK_LEFT) position.x -= 10;

	//	InvalidateRect(handle, nullptr, TRUE);
	//  // ȭ�� ������ �ʿ��� ��Ȳ�� ���(WM_PAINT ȣ��)

	//	break;

	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(handle, &ps);
	//	TextOut(hdc, position.x, position.y, "��", 2); // �������� �ַ�� ��Ŭ�� -> �Ӽ� -> ��޼Ӽ� -> ��������
	//	EndPaint(handle, &ps);
	//}
	//break;

#pragma endregion
#pragma region Mouse Moving
	case WM_MOUSEMOVE:
		position.x = LOWORD(lParam);
		position.y = HIWORD(lParam);

		InvalidateRect(handle, nullptr, TRUE);
		break;

	case WM_PAINT: // �ּ�ȭ �ϰų� ���������� �ٽ� �׷��ִ� �޼���
	{
		std::string str = "";
		str += std::to_string(position.x); // ���� -> ���ڿ�
		str += ", ";
		str += std::to_string(position.y);

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);
		TextOutA(hdc, position.x, position.y, str.c_str(), str.length());

		MoveToEx(hdc, 100, 100, nullptr);
		LineTo(hdc, 500, 500); // �� �׾���

		Rectangle(hdc, 500, 500, 600, 600);
		Ellipse(hdc, 300, 300, 400, 400);
		// �����̴� �κ��� ���߿� ���� �ΰ� ���鼭 �ذ��Ұ���

		EndPaint(handle, &ps); 
	}
	break;
#pragma endregion
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0); // �ùٸ��� ����� --> ������ ����
		break;

	default:
		return DefWindowProcA(handle, message, wParam, lParam);
	}

	return 0;
}

// ���ϱ��� �׸��� �����
// �귯�� ����ؼ� �׸���
// + ȭ�鿡 �׸� �ΰ� ���� �ϳ��� �����̰� ��, �浹�ϸ� �浹�ߴٴ� �޼��� ����