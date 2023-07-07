// WinAPI 쪽 다루려면
// 솔루션 우클릭 -> 구성속성 -> 링커 -> 시스템 -> 하위시스템 --->>> 창으로 바꿔준다.
// API : application program interface(연결고리 느낌)
// 요즘은 윈도우 창을 띄우기 위한 용도
// API의 집합 : 다렉X
//
// 구성요소
// 메세지
// - 윈도우에서 발생하는 모든 이벤트
// 
// 메세지 큐 -> 먼저 들어온 메세지를 순차적으로 처리(FIFO)
// - 메세지들이 매크로 상수로 변환되서 메세지 큐에 저장
// 
// 메세지 루프
// - 메세지를 알맞은 형태로 변환
// 
// 윈도우 프로시져(*) 중요
// - 사전에 정의된 내용(개발자가 만든 내용) 에 맞게 처리하는 함수

// LPSTR - long pointer str = char*
// LPCSTR - const char*
// LPWSTR - wchar_t*
// LPCWSTR - const wchar_t*

#include <Windows.h>
#include <cassert>
#include <string>

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam); // stdcall
// 윈도우에서 직접 호출

int APIENTRY WinMain // APIENTRY : 시작점 명시
// WinMain : 메세지 처리용
(
	HINSTANCE hInstance, // HINSTANCE : 윈도우 창 의미
	HINSTANCE prevInstance,
	LPSTR lpszCmdParam, // 문자열로 넘겨준다
	int nCmdShow // 어떻게 보여줄건가
	// 써주지 않아도 자동으로 잡힘
)
{
	WNDCLASSA wnd_class; // 설명창(기본값)

	wnd_class.cbClsExtra = 0; // 클래스를 위한 확장된 공간 사용할것인지
	wnd_class.cbWndExtra = 0; // 윈도우를 위한 확장된 공간 사용할것인지
	wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));// 배경 뒷쪽 색을 사용할것인지
	// 우클릭 -> 정의로 이동 사용하면 좋음
	wnd_class.hCursor = LoadCursor(nullptr, IDC_CROSS); // 커서 지정
	wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR); // 작업표시창 지정
	wnd_class.hInstance = hInstance;
	wnd_class.lpfnWndProc = WndProc; // 윈도우 프로시져 연결
	wnd_class.lpszClassName = "First Window"; // 문서화 한 이름
	wnd_class.lpszMenuName = nullptr;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassA(&wnd_class); // 위에 만든 내용들 저장

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
	// assert 쓰면 디버깅 편함
	assert(hwnd != nullptr);

	ShowWindow(hwnd, nCmdShow);
	ShowCursor(TRUE);

	MSG message;
	ZeroMemory(&message, sizeof(MSG)); // 안전한 초기화

	while (GetMessage(&message, nullptr, 0, 0))
	// GetMessage : 동기식(메세지가 들어올때까지 기다림)
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
		static POINT position; // x,y 좌표 들어있음
#pragma region Message Box
	//case WM_LBUTTONDOWN:
	//	MessageBoxA(nullptr, "Hello, Window!", "ERROR!", MB_OKCANCEL); // 확인, 취소 창
	//	break;
#pragma endregion
#pragma region Text
	//case WM_LBUTTONDOWN:
	//{
	//	std::string str = "Mouse Clicked!!";

	//	HDC hdc = GetDC(handle); // handle device context -> 그래픽 작업 수행할때 사용
	//	TextOutA(hdc, 500, 300, str.c_str(), str.length());
	//	ReleaseDC(handle, hdc);
	//}
	//break; // -> 화면이 갱신되는 일(다시 그려지면) 이 발생하면 메세지가 사라짐
	//// 밑에는 문자열은 안사라짐
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
	//  // 화면 갱신이 필요한 상황에 사용(WM_PAINT 호출)

	//	break;

	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(handle, &ps);
	//	TextOut(hdc, position.x, position.y, "※", 2); // 에러나면 솔루션 우클릭 -> 속성 -> 고급속성 -> 문자집합
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

	case WM_PAINT: // 최소화 하거나 가려졌을때 다시 그려주는 메세지
	{
		std::string str = "";
		str += std::to_string(position.x); // 정수 -> 문자열
		str += ", ";
		str += std::to_string(position.y);

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);
		TextOutA(hdc, position.x, position.y, str.c_str(), str.length());

		MoveToEx(hdc, 100, 100, nullptr);
		LineTo(hdc, 500, 500); // 선 그어짐

		Rectangle(hdc, 500, 500, 600, 600);
		Ellipse(hdc, 300, 300, 400, 400);
		// 깜빡이는 부분은 나중에 버퍼 두개 쓰면서 해결할거임

		EndPaint(handle, &ps); 
	}
	break;
#pragma endregion
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0); // 올바르게 종료됨 --> 윈도우 종료
		break;

	default:
		return DefWindowProcA(handle, message, wParam, lParam);
	}

	return 0;
}

// 내일까지 그림판 만들기
// 브러시 사용해서 그리기
// + 화면에 네모 두개 띄우고 하나는 움직이게 함, 충돌하면 충돌했다는 메세지 띄우기