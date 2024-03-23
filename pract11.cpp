// pract11.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "pract11.h"
#include <commdlg.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
COLORREF dColors[16];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Test(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACT11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACT11));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACT11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRACT11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
  
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

#define IDC_COMBOBOX 2001
#define IDC_TEXT 2002
#define IDC_HOTKEY 2003
#define IDC_CHECKBOX 2004
#define IDC_COLORBUTTON 2005
#define IDC_REPLACEBUTTON 2006

HWND hDlg = NULL;
HWND hReplaceDialog = NULL;
FINDREPLACE replaceDlg;
UINT uReplaceMessageString = 0;
TCHAR szBuffer[100] = TEXT("");
bool rbuttonup = false;
bool rbttondown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };
    FINDREPLACE fr = { sizeof(FINDREPLACE) };
    
    switch (message)
    {
    case WM_KEYUP:
        MessageBox(hWnd, L"WM_KEYUP", L"WM_KEYUP", MB_OK);
        break;

    case WM_CHAR:
        MessageBox(hWnd, L"WM_CHAR", L"WM_CHAR", MB_OK);
        break;

    case WM_MOUSEWHEEL:
        MessageBox(hWnd, L"WM_MOUSEWHEEL", L"WM_MOUSEWHEEL", MB_OK);
        break;

    case WM_MOVING:
        MessageBox(hWnd, L"WM_MOVING", L"WM_MOVING", MB_OK);        
        break;

    case WM_RBUTTONDBLCLK:
        MessageBox(hWnd, L"WM_RBUTTONDBLCLK", L"WM_RBUTTONDBLCLK", MB_OK);
        break;

    case WM_RBUTTONDOWN:
        if (rbttondown == false) {
            MessageBox(hWnd, L"WM_RBUTTONDOWN", L"WM_RBUTTONDOWN", MB_OK);
            rbttondown = true;
        }
        break;

        case WM_RBUTTONUP:
            if (rbuttonup == false) {
                MessageBox(hWnd, L"WM_RBUTTONUP", L"WM_RBUTTONUP", MB_OK);
                rbuttonup = true;
            }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT: {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Test);
                break;
            }
            case IDC_COLORBUTTON:
                cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                cc.hInstance = NULL;
                cc.hwndOwner = hWnd;
                cc.lCustData = 0L;
                cc.lpCustColors = dColors; //массив пользовательских цветов
                cc.lpfnHook = NULL;
                cc.lpTemplateName = NULL;
                cc.lStructSize = sizeof(cc); //sizeof() - возвращает размер любой структуры данных - часть языка СИ
                cc.rgbResult = RGB(255, 0, 0); //цвет, заданный для диалога по умолчанию
                if (ChooseColor(&cc) != FALSE) {

                }
                break;
            case IDC_REPLACEBUTTON:
                if (0 == uReplaceMessageString) {
                    uReplaceMessageString = RegisterWindowMessage(FINDMSGSTRING);
                }
                if (IsWindow(hReplaceDialog) == FALSE) {
                    replaceDlg.lStructSize = sizeof(FINDREPLACE);
                    replaceDlg.hInstance = hInst;
                    replaceDlg.hwndOwner = hWnd;
                    replaceDlg.lpstrReplaceWith = szBuffer;
                    replaceDlg.lpstrFindWhat = szBuffer;
                    replaceDlg.wFindWhatLen = _countof(szBuffer);
                    replaceDlg.wReplaceWithLen = _countof(szBuffer);
                    hReplaceDialog = ReplaceText(&replaceDlg);
                }
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
       
        CreateWindowEx(0, TEXT("COMBOBOX"), TEXT("MyCombo"),
            CBS_DROPDOWN | WS_CHILD | WS_VISIBLE,
            70,30, 100, 20, hWnd, (HMENU)IDC_COMBOBOX, hInst, NULL);

        CreateWindowEx(0, TEXT("STATIC"), TEXT("HELLO WORLD"),
           SS_CENTER | WS_CHILD | WS_VISIBLE,200,30,200,25,hWnd,(HMENU)IDC_TEXT,hInst,NULL);

        CreateWindowEx(0, TEXT("msctls_hotkey32"), TEXT("myHotkey"),
            SS_CENTER | WS_CHILD | WS_VISIBLE,
            70, 80, 100, 40, hWnd, (HMENU)IDC_HOTKEY, hInst, NULL);

        CreateWindowEx(0, TEXT("Button"), TEXT("MyCheckbox"),
            BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
            190, 70, 120, 40, hWnd, (HMENU)IDC_CHECKBOX, hInst, NULL);

        CreateWindowEx(0, TEXT("Button"), TEXT("ReplaceButton"),
            BS_CENTER | WS_CHILD | WS_VISIBLE,
            350, 70, 120, 40, hWnd, (HMENU)IDC_REPLACEBUTTON, hInst, NULL);

        CreateWindowEx(0, TEXT("Button"), TEXT("ColorButton"),
            BS_CENTER | WS_CHILD | WS_VISIBLE,
            500, 70, 120, 40, hWnd, (HMENU)IDC_COLORBUTTON, hInst, NULL);

            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



INT_PTR CALLBACK Test(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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



