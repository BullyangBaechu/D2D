#include "pch.h"
#include "framework.h"
#include "Client.h"

#include <crtdbg.h>

#include <Engine/Engine.h>
#include <Engine/Device.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine\\Engine_D.lib")
#else
#pragma comment(lib, "Engine\\Engine.lib")
#endif

#include <Engine/Ptr.h>
#include <Engine/Entity.h>

#include "ImGuiMgr.h"
#include "ImGui/imgui.h"

void TestFunc();

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{ 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName = L"Client";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    HWND hWnd = CreateWindowW(L"Client", L"Client", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    if (FAILED(Engine::GetInst()->Init(hWnd, 1600, 900)))
    {
        MessageBox(nullptr, L"Engine 초기화 실패", L"초기화 실패", MB_OK);
        return 0;
    }


    // ImGui 부분 초기화 (전용 Mgr 만들어서 코드 간략화)
    ImGuiMgr::GetInst()->Init();
    




    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    MSG msg = {};

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            Engine::GetInst()->Progress();

            ImGuiMgr::GetInst()->Progress();

            // ImGui로 사용할 UI들도 RenderTarget으로서 present 해줘야하므로 호출
            // 여기서 안 해주면 ImGui로 사용할 UI는 rendertarget으로 잡히기만 할 뿐 present는 안 되어서 화면에 안 보임 (Engine 쪽 렌더 타겟만 present됨)
            Device::GetInst()->Present();
        }       
    }

    return (int) msg.wParam;
}


// ImGui sample에서 제공되는 함수 갖고 오기

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(nullptr, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break; 
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

// 함수템플릿 + 특수화
template<typename T>
int TestTemplateFunc(T _Data)
{
    return 10;
}
template<> 
int TestTemplateFunc(float _Data)
{
    return 20;
}


// 변수 템플릿 선언
template<typename T1, typename T2>
int g_int = 100;
template<typename T1> // tempalte 타입 두개가 동일한 경우에 대한 부분 특수화
int g_int<T1, T1> = 200;


// 변수 템플릿 + constexpr +  부분특수화(타입이 동일하게 지정된 경우)
template<typename T1, typename T2>
constexpr bool IsSame = false;
template<typename T1>
constexpr bool IsSame<T1, T1> = true;


void TestFunc()
{    
    // =========================
    // 1. constexpr (엄격한 상수)
    // =========================
    int i = 100;

    // 런타임 상수, 프로그램이 실행된 이후에 a 에 입력될 값을 알 수 있음
    const int a = i; 

    // const 보더 더 엄격한 기준의 상수
    // 컴파일 타임 상수, 컴파일 시간안에 b 에 들어갈 값이 무엇인지 알 수 있어야 함
    constexpr int b = 100; 


    // ===============
    // 2. 템플릿 특수화
    // ===============
    int Value = TestTemplateFunc<float>(1);

    // =============
    // 3. 변수 템플릿
    // =============
    int k = g_int<int, float>;
    int g = g_int<char, short>;    
         
    // 3-1. 변수템플릿 부분 특수화
    int z = g_int<char, char>;
     
    // ===============
    // 4. if constexpr 
    // ===============
    // 컴파일 시간안에 조건 참 거짓 유무를 알 수 있어야 한다.
    // 컴파일 시, 조건이 참인 경우 if 내부 코드를 남겨두고, 거짓인 경우 if 구문을 지워버린다.
    int l = 0;
    if constexpr (10 == 200)
    {
        l = 100;
    }


    // ======================
    // 5. 타입 일치 조건 최적화
    // ======================
    if constexpr (IsSame<int, float>)
    {
        // 실행 코드
    }
}