// BattleShip.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "BattleShip.h"
#include <ctime>
#include <CommCtrl.h>
#include"resource.h"



// Глобальные переменные:
							                    // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

//INT** player1 = nullptr;
//INT** player2 = nullptr;                        // массивы игрового поля
struct TSettings {
	TCHAR name1[20];
	TCHAR name2[20];
	INT setShip;
	INT firstMove;
	INT playMode;
};

//Ship ship_pl[10], ship_comp[10];
TSettings* set = new TSettings;
INT SetMode = M_START;
HWND hWnd;
//HWND hWndSB;
INT x_pos, y_pos, ships = 0, move = 0;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NewGame(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BATTLESHIP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BATTLESHIP));

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

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BATTLESHIP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
	INT width = 550;   // ширина окна
	INT height = 400;  // высота окна
	INT wx = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;  //левый угол по x
	INT wy = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2; //левый угол по y
	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZE,
		wx, wy, width, height, nullptr, nullptr, hInstance, nullptr);

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
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	HDC hdc;
	HPEN hpen1;
	int x, y, x_pos1, y_pos1, hit;

	switch (message)
	{
	case M_START:

		hdc = GetDC(hWnd);
		RECT r;
		GetClientRect(hWnd, &r);
		InvalidateRect(hWnd, &r, 1);
		SendMessage(hWnd, WM_PAINT, NULL, NULL);
		SetDlgItemText(hWnd, ST1, set->name1);
		SetDlgItemText(hWnd, ST3, L"Режим:  Расставляю корабли");
		/*creatArray2D(player1, 10, 10);
		initArray2DNull(player1, 10, 10);*/
		/*creatArray2D(player2, 10, 10);
		initArray2DNull(player2, 10, 10);

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				player1[i][j] = player1[i][j] = 0;*/

		ships = 0;
		move = 0;
		/*ship_init(ship_comp);
		for (int i = 0; i < 10; i++)
			setShipAuto(player2, &ship_comp[i], 0);*/

			ship_init(ship_pl);
		if (set->setShip == 0)
		{
			for (int i = 0; i < 10; i++)
				setShipAuto(player1, &ship_pl[i], 1);
			for (int y = 0; y < 10; y++)
				for (int x = 0; x < 10; x++)
					if (player1[y][x] == 1)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x, y0 + 20 * y, x0 + 20 * x + 20, y0 + 20 * y + 20);
					}
			SetMode = M_PLAY;
			SetDlgItemText(hWnd, ST3, L"Режим: Игра");
			if (set->firstMove == 1)
			{
				move_comp(player1, ship_pl, hWnd);
				set->firstMove = 0;
			}
		}
		else
			SetMode = M_SET_SHIP;
		break;
	case M_STOP:
		TCHAR tmp[100];

		if (lParam == 1)
		{
			wsprintf(tmp, L"Режим: Конец игры     Победитель - %s", set->name1);
			SetDlgItemText(hWnd, ST3, tmp);
			MessageBox(NULL, L"Игрок победил!", L"Морской бой", MB_OK);
		}
		else
		{
			wsprintf(tmp, L"Режим: Конец игры     Победитель - Компьютер", set->name1);
			SetDlgItemText(hWnd, ST3, tmp);
			MessageBox(NULL, L"Коммпьютер победил!", L"Морской бой", MB_OK);
		}
		deleteArray2D(player1, 10);
		deleteArray2D(player2, 10);
		player1 = player2 = nullptr;
		break;
	case WM_CREATE:
		CreateWindowEx(0, L"STATIC", L"Игрок", WS_CHILD | WS_VISIBLE, 30, 10, 200, 20, hWnd, (HMENU)ST1, hInst, NULL);
		CreateWindowEx(0, L"STATIC", L"Компьютер", WS_CHILD | WS_VISIBLE, 310, 10, 200, 20, hWnd, (HMENU)ST2, hInst, NULL);
		CreateWindowEx(0, L"STATIC", L"Файл - Новая игра", WS_CHILD | WS_VISIBLE, 5, 320, 500, 360, hWnd, (HMENU)ST3, hInst, NULL);
		//hWndSB = CreateWindowEx(0,STATUSCLASSNAME, 0, WS_CHILD | WS_VISIBLE, 20, 310, 300, 350, hWnd, (HMENU)SW1, hInst, NULL);
		//SendMessage(hWnd, SB_SETTEXT, 0, (LPARAM)"Режим");
		//UpdateWindow(hWnd);
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_32771:
		{
			HANDLE hMutex, hThread;
			hMutex = CreateMutex(NULL, FALSE, NULL);
			hThread = CreateThread(NULL, 0, &threadFunc, &hMutex, 0, NULL);
			//MessageBox(NULL, TEXT("Create thread"), TEXT("start"), MB_OK);
			
			//MessageBox(NULL, TEXT("End thread"), TEXT("start"), MB_OK);
			CloseHandle(hThread);
			CloseHandle(hMutex);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, NewGame);
			WaitForSingleObject(hThread, INFINITE);

			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		TCHAR num[] = L"1   2   3   4   5   6   7   8   9  10";
		SetBkColor(hdc, GetSysColor(COLOR_MENU));
		TextOut(hdc, 37, 35, num, _tcsclen(num));
		TextOut(hdc, 37 + 280, 35, num, _tcsclen(num));
		TextOut(hdc, 18, 53, L"А", _tcsclen(L"А"));
		TextOut(hdc, 17, 73, L"Б", _tcsclen(L"Б"));
		TextOut(hdc, 18, 93, L"В", _tcsclen(L"В"));
		TextOut(hdc, 18, 113, L"Г", _tcsclen(L"Г"));
		TextOut(hdc, 17, 133, L"Д", _tcsclen(L"Д"));
		TextOut(hdc, 18, 153, L"Е", _tcsclen(L"Д"));
		TextOut(hdc, 16, 173, L"Ж", _tcsclen(L"Д"));
		TextOut(hdc, 18, 193, L"З", _tcsclen(L"Д"));
		TextOut(hdc, 18, 213, L"И", _tcsclen(L"Д"));
		TextOut(hdc, 18, 233, L"К", _tcsclen(L"Д"));
		for (int i = 0; i <= 200; i += 20)
		{
			MoveToEx(hdc, x0 + i, y0, NULL);
			LineTo(hdc, x0 + i, y0 + 200);
			MoveToEx(hdc, x0, y0 + i, NULL);
			LineTo(hdc, x0 + 200, y0 + i);

			MoveToEx(hdc, x0 + i + 280, y0, NULL);
			LineTo(hdc, x0 + i + 280, y0 + 200);
			MoveToEx(hdc, x0 + 280, y0 + i, NULL);
			LineTo(hdc, x0 + 480, y0 + i);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		switch (SetMode)
		{
		case M_START:
			break;
		case M_SET_SHIP:

			hdc = GetDC(hWnd);
			if (set->setShip == 1)
			{
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				x_pos = (x - 10) / 20 - 1;
				y_pos = (y - 30) / 20 - 1;
				if (x_pos < 0 || x_pos > 9 || y_pos < 0 || y_pos > 9)
					break;
				switch (ships)
				{
				case 0:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;
						move = 1;
						ship_pl[0].x = x_pos;
						ship_pl[0].y = y_pos;
					}
					else
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;


						if (y_pos == ship_pl[ships].y)
						{
							ship_pl[0].orient = true;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * (x_pos + 1), y0 + 20 * y_pos, x0 + 20 * (x_pos + 1) + 20, y0 + 20 * y_pos + 20);
							player1[y_pos][x_pos + 1] = 1;
							Rectangle(hdc, x0 + 20 * (x_pos + 2), y0 + 20 * y_pos, x0 + 20 * (x_pos + 2) + 20, y0 + 20 * y_pos + 20);
							player1[y_pos][x_pos + 2] = 1;
						}
						else
						{
							ship_pl[0].orient = false;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * (y_pos + 1), x0 + 20 * x_pos + 20, y0 + 20 * (y_pos + 1) + 20);
							player1[y_pos + 1][x_pos] = 1;
							Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * (y_pos + 2), x0 + 20 * x_pos + 20, y0 + 20 * (y_pos + 2) + 20);
							player1[y_pos + 2][x_pos] = 1;
						}
						move = 0;
						ships++;
					}
					break;
				case 1:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;
						move = 1;
						ship_pl[ships].x = x_pos;
						ship_pl[ships].y = y_pos;
					}
					else
					{

						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						if (y_pos == ship_pl[ships].y)
						{
							ship_pl[ships].orient = true;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * (x_pos + 1), y0 + 20 * y_pos, x0 + 20 * (x_pos + 1) + 20, y0 + 20 * y_pos + 20);
							player1[y_pos][x_pos + 1] = 1;
						}
						else
						{
							ship_pl[ships].orient = false;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * (y_pos + 1), x0 + 20 * x_pos + 20, y0 + 20 * (y_pos + 1) + 20);
							player1[y_pos + 1][x_pos] = 1;
						}
						move = 0;
						ships++;
					}
					break;
				case 2:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;
						move = 1;
						ship_pl[ships].x = x_pos;
						ship_pl[ships].y = y_pos;
					}
					else
					{

						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						if (y_pos == ship_pl[ships].y)
						{
							ship_pl[ships].orient = true;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * (x_pos + 1), y0 + 20 * y_pos, x0 + 20 * (x_pos + 1) + 20, y0 + 20 * y_pos + 20);
							player1[y_pos][x_pos + 1] = 1;
						}
						else
						{
							ship_pl[ships].orient = false;
							hbrush = CreateSolidBrush(RGB(0, 255, 255));
							SelectObject(hdc, hbrush);
							Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * (y_pos + 1), x0 + 20 * x_pos + 20, y0 + 20 * (y_pos + 1) + 20);
							player1[y_pos + 1][x_pos] = 1;
						}
						move = 0;
						ships++;
					}
					break;
				case 3:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						move = 1;
						ship_pl[ships].x = x_pos;
						ship_pl[ships].y = y_pos;
					}
					else
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						if (y_pos == ship_pl[ships].y)
							ship_pl[ships].orient = true;
						else
							ship_pl[ships].orient = false;
						move = 0;
						ships++;
					}
					break;
				case 4:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						move = 1;
						ship_pl[ships].x = x_pos;
						ship_pl[ships].y = y_pos;
					}
					else
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						if (y_pos == ship_pl[ships].y)
							ship_pl[ships].orient = true;
						else
							ship_pl[ships].orient = false;
						move = 0;
						ships++;
					}
					break;
				case 5:
					if (move == 0)
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						move = 1;
						ship_pl[ships].x = x_pos;
						ship_pl[ships].y = y_pos;
					}
					else
					{
						hbrush = CreateSolidBrush(RGB(0, 255, 255));
						SelectObject(hdc, hbrush);
						Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
						player1[y_pos][x_pos] = 1;

						if (y_pos == ship_pl[ships].y)
							ship_pl[ships].orient = true;
						else
							ship_pl[ships].orient = false;
						move = 0;
						ships++;
					}
					break;
				case 6:
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					SelectObject(hdc, hbrush);
					Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
					player1[y_pos][x_pos] = 1;
					ship_pl[ships].x = x_pos;
					ship_pl[ships].y = y_pos;
					ship_pl[ships].orient = true;
					ships++;
					break;
				case 7:
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					SelectObject(hdc, hbrush);
					Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
					player1[y_pos][x_pos] = 1;
					ship_pl[ships].x = x_pos;
					ship_pl[ships].y = y_pos;
					ship_pl[ships].orient = true;
					ships++;
					break;
				case 8:
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					SelectObject(hdc, hbrush);
					Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
					player1[y_pos][x_pos] = 1;
					ship_pl[ships].x = x_pos;
					ship_pl[ships].y = y_pos;
					ship_pl[ships].orient = true;
					ships++;
					break;
				case 9:
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					SelectObject(hdc, hbrush);
					Rectangle(hdc, x0 + 20 * x_pos, y0 + 20 * y_pos, x0 + 20 * x_pos + 20, y0 + 20 * y_pos + 20);
					player1[y_pos][x_pos] = 1;
					ship_pl[ships].x = x_pos;
					ship_pl[ships].y = y_pos;
					ship_pl[ships].orient = true;
					ships++;
					break;
				default:
					break;
				}
			}

			if (ships > 9)
			{
				SetMode = M_PLAY;
				SetDlgItemText(hWnd, ST3, L"Режим: Игра");
				if (set->firstMove == 1)
				{
					move_comp(player1, ship_pl, hWnd);
					set->firstMove = 0;
				}
			}

			break;
		case M_PLAY:
			if (set->firstMove == 0)
			{
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				x_pos = (x - 290) / 20 - 1;
				y_pos = (y - 30) / 20 - 1;
				hdc = GetDC(hWnd);
				if (x_pos < 0 || x_pos > 9 || y_pos < 0 || y_pos > 9)
					break;
				else
				{
					hit = move_pl(player2, ship_comp, hWnd, x_pos, y_pos);
					if (wins(ship_comp) == 10)
					{
						SetMode = M_STOP;
						SendMessage(hWnd, M_STOP, NULL, 1);
						break;
					}
					if (hit == 2)
						break;
					else
					{
						move_comp(player1, ship_pl, hWnd);
						set->firstMove = 0;
						if (wins(ship_pl) == 10)
						{
							SetMode = M_STOP;
							SendMessage(hWnd, M_STOP, NULL, 0);
							break;
						}
					}
				}
			}
			break;
		default:
			break;
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

// Обработчик сообщений для окна "О программе".
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


// Обработчик сообщений для окна "Новая игра".
INT_PTR CALLBACK NewGame(HWND nDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(nDlg, IDC_RADIO1, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		SendDlgItemMessage(nDlg, IDC_RADIO3, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		SendDlgItemMessage(nDlg, IDC_RADIO5, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		EnableWindow(GetDlgItem(nDlg, IDC_IPADDRESS1), 0);
		EnableWindow(GetDlgItem(nDlg, IDC_EDIT2), 0);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			if (SendMessage(GetDlgItem(nDlg, IDC_RADIO1), BM_GETCHECK, 0, 0) == BST_CHECKED)
				set->setShip = 0;
			else
				set->setShip = 1;
			if (SendMessage(GetDlgItem(nDlg, IDC_RADIO3), BM_GETCHECK, 0, 0) == BST_CHECKED)
				set->firstMove = 0;
			else
				set->firstMove = 1;
			if (SendMessage(GetDlgItem(nDlg, IDC_RADIO5), BM_GETCHECK, 0, 0) == BST_CHECKED)
				set->playMode = 0;
			else
				set->playMode = 1;
			int len = GetWindowTextLength(GetDlgItem(nDlg, IDC_EDIT1));
			GetDlgItemText(nDlg, IDC_EDIT1, set->name1, len + 1);
			//SendMessage(hWnd, WM_PAINT, NULL, NULL);

			PostMessage(hWnd, M_START, NULL, NULL);
			EndDialog(nDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		case IDCANCEL:
			EndDialog(nDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		case IDC_RADIO5:
			EnableWindow(GetDlgItem(nDlg, IDC_IPADDRESS1), 0);
			EnableWindow(GetDlgItem(nDlg, IDC_EDIT2), 0);
			break;
		case IDC_RADIO6:
			EnableWindow(GetDlgItem(nDlg, IDC_IPADDRESS1), 1);
			EnableWindow(GetDlgItem(nDlg, IDC_EDIT2), 1);
			if (MessageBox(NULL, L"Эта функция будет доступна в следующей версии!", L"Морской бой", MB_OK))
			{
				EnableWindow(GetDlgItem(nDlg, IDC_IPADDRESS1), 0);
				EnableWindow(GetDlgItem(nDlg, IDC_EDIT2), 0);
				SendDlgItemMessage(nDlg, IDC_RADIO5, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
				SendDlgItemMessage(nDlg, IDC_RADIO6, BM_SETCHECK, WPARAM(BST_UNCHECKED), 0);
			}
			break;
		default:
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}