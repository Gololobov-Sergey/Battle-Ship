#pragma once

#include "resource.h"
#include <ctime>

INT x0 = 30, y0 = 50;
HINSTANCE hInst;
HBRUSH hbrush;
HPEN hpen1;

INT** player1 = nullptr;
INT** player2 = nullptr;                        // массивы игрового поля

struct Ship
{
	int x;       // начальная позиция
	int y;
	int p;       // количество палуб
	bool orient; // ориентация в пространстве (0-вертикальное (false), 1-горизонтальное (true))
	int pp;      // количество подбитых палуб
};

Ship ship_pl[10], ship_comp[10];
void creatArray2D(int** &array, int x, int y)
{
	array = new int*[y];
	for (int j = 0; j < y; j++)
		array[j] = new int[x];
}

void initArray2DNull(int **array, int x, int y)
{
	for (int j = 0; j < y; j++)
		for (int i = 0; i < x; i++)
			array[j][i] = 0;
}
void deleteArray2D(int** &array, int y)
{
	for (int j = 0; j < y; j++)
		delete[] array[j];
	delete[] array;
}

Ship ship_init(Ship *ship_)
{
	ship_[0] = { 0, 0, 4, 0, 0 };
	ship_[1] = ship_[2] = { 0, 0, 3, 1, 0 };
	ship_[3] = ship_[4] = ship_[5] = { 0, 0, 2, 1, 0 };
	ship_[6] = ship_[7] = ship_[8] = ship_[9] = { 0, 0, 1, 1, 0 };
	return *ship_;
}

int wins(Ship *ship_)
{
	int count = 0;
	for (int i = 0; i < 10; i++)
		if (ship_[i].p == ship_[i].pp)
			count++;
	return count;
}



Ship setShipAuto(INT **map_, Ship *ship, int visual) {

	srand(time(NULL));
	ship->orient = rand() % 2;

	if (ship->orient) //горизонтальное
		{
beg1:
			ship->x = rand() % (10 - ship->p);
			ship->y = rand() % 10;
			for (int y = ship->y - 1; y < ship->y + 2; y++)
				if (y < 0 || y > 9)
					continue;
				else
					for (int x = ship->x - 1; x < ship->x + ship->p + 1; x++)
						if (x < 0 || x > 9 || map_[y][x] == 0)
							continue;
						else
							goto beg1;
		}
		else  // верикальное
		{
beg2:		
			ship->x = rand() % 10;
			ship->y = rand() % (10 - ship->p);
			for (int y = ship->y - 1; y < ship->y + ship->p + 1; y++)
				if (y < 0 || y > 9)
					continue;
				else
					for (int x = ship->x - 1; x < ship->x + 2; x++)
						if (x < 0 || x > 9 || map_[y][x] == 0)
							continue;
						else
							goto beg2;
		}

	if (ship->orient == true)
		for (int i = 0; i < ship->p; i++)
			map_[ship->y][ship->x + i] = 1;
	else
		for (int i = 0; i < ship->p; i++)
			map_[ship->y + i][ship->x] = 1;
	return *ship;
}

DWORD WINAPI threadFunc(CONST LPVOID lParam) {
	CONST HANDLE hMutex = (HANDLE)lParam;
	srand(time(NULL));
	INT i;
	WaitForSingleObject(hMutex, INFINITE);
	creatArray2D(player1, 10, 10);
	initArray2DNull(player1, 10, 10);
	creatArray2D(player2, 10, 10);
	initArray2DNull(player2, 10, 10);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			player1[i][j] = player1[i][j] = 0;
	ship_init(ship_comp);
	for (int i = 0; i < 10; i++)
		setShipAuto(player2, &ship_comp[i], 0);
	ReleaseMutex(hMutex);
	ExitThread(0);
}
void set_ship_kill(int **map_, Ship *ship_, int n_ship, int pos_x, HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	if (ship_[n_ship].orient == 0)
	{
		for (int j = ship_[n_ship].y - 1; j < ship_[n_ship].y + ship_[n_ship].p + 1; j++)
		{
			if (j < 0 || j > 9)
				continue;
			else
			{
				for (int i = ship_[n_ship].x - 1; i < ship_[n_ship].x + 2; i++)
				{
					if (i < 0 || i > 9)
						continue;
					else
					{
						if (map_[j][i] == 0)
						{
							map_[j][i] = 3;
							hbrush = CreateSolidBrush(RGB(0, 0, 255));
							hpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
							SelectObject(hdc, hbrush);
							SelectObject(hdc, hpen1);
							Ellipse(hdc, x0 + pos_x + 20 * i + 5, y0 + 20 * j + 5, x0 + pos_x + 20 * i + 15, y0 + 20 * j + 15);
							Sleep(150);
						}
					}
				}
			}

		}
	}
	else
	{
		for (int j = ship_[n_ship].y - 1; j < ship_[n_ship].y + 2; j++)
		{
			if (j < 0 || j > 9)
				continue;
			else
			{
				for (int i = ship_[n_ship].x - 1; i < ship_[n_ship].x + ship_[n_ship].p + 1; i++)
				{
					if (i < 0 || i > 9)
						continue;
					else
					{
						if (map_[j][i] == 0)
						{
							map_[j][i] = 3;
							hbrush = CreateSolidBrush(RGB(0, 0, 255));
							hpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
							SelectObject(hdc, hbrush);
							SelectObject(hdc, hpen1);
							Ellipse(hdc, x0 + pos_x + 20 * i + 5, y0 + 20 * j + 5, x0 + pos_x + 20 * i + 15, y0 + 20 * j + 15);
							Sleep(150);
						}
					}
				}
			}

		}
	}
}

void move_comp(int **map_, Ship *ship_pl, HWND hWnd) {
	int x, y, x_p, y_p, hit, n_ship = 99;
	HDC hdc = GetDC(hWnd);

	for (int i = 0; i < 10; i++)
	{
		if (ship_pl[i].pp > 0 && ship_pl[i].pp != ship_pl[i].p)
			n_ship = i;
	}
	do
	{
		hit = 0;

		if (n_ship != 99)
		{
			if (ship_pl[n_ship].orient == 0)
			{
				for (int i = 0; i < ship_pl[n_ship].p; i++)
				{
					if (map_[ship_pl[n_ship].y + i][ship_pl[n_ship].x] == 2)
					{
						x_p = ship_pl[n_ship].x;
						y_p = ship_pl[n_ship].y + i;
					}
				}
			}
			if (ship_pl[n_ship].orient == 1)
			{
				for (int i = 0; i < ship_pl[n_ship].p; i++)
				{
					if (map_[ship_pl[n_ship].y][ship_pl[n_ship].x + i] == 2)
					{
						x_p = ship_pl[n_ship].x + i;
						y_p = ship_pl[n_ship].y;
					}
				}
			}

			if (ship_pl[n_ship].pp == 1)
			{
l1:				int nap = rand() % 4;
				switch (nap)
				{
				case 0:
					x = x_p - 1;
					y = y_p;
					if (x == -1 || map_[y][x] == 2 || map_[y][x] == 3)
					{
						x = x + 2;
					}
					break;
				case 1:
					x = x_p;
					y = y_p - 1;
					if (y == -1 || map_[y][x] == 2 || map_[y][x] == 3)
					{
						y = y + 2;
					}
					break;
				case 2:
					x = x_p + 1;
					y = y_p;
					if (x == 10 || map_[y][x] == 2 || map_[y][x] == 3)
					{
						x = x - 2;
					}
					break;
				case 3:
					x = x_p;
					y = y_p + 1;
					if (y == 10 || map_[y][x] == 2 || map_[y][x] == 3)
					{
						y = y - 2;
					}
					break;
				default:
					break;
				}

			}
			if (ship_pl[n_ship].pp > 1)
			{
				if (ship_pl[n_ship].orient == 1)
				{
					x = x_p + 1;
					y = y_p;
					if (map_[y][x] == 3 && map_[y][x - 3] == 2)
					{
						x -= 4;
					}
					else
					{
						if (map_[y][x] == 3 || x == 10)
						{
							x -= 3;
						}
						else
							x = x_p + 1;
					}
				}
				if (ship_pl[n_ship].orient == 0)
				{
					x = x_p;
					y = y_p + 1;
					if (map_[y][x] == 3 && map_[y - 3][x] == 2)
					{
						y -= 4;
					}
					else
					{
						if (map_[y][x] == 3 || y == 10)
						{
							y -= 3;
						}
						else
							y = y_p + 1;
					}
				}
			}
		}
		else
		{
			x = rand() % 10;
			y = rand() % 10;
		}
		if (x < 0 || x > 9 || y < 0 || y > 9)
			goto l1;
		if (map_[y][x] == 2 || map_[y][x] == 3)
		{
			hit = 0;
		}

		if (map_[y][x] == 1)
		{
			map_[y][x] = 2;
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
			hpen1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			SelectObject(hdc, hpen1);
			MoveToEx(hdc, x0 + x * 20 + 2, y0 + y * 20 + 2, NULL);
			LineTo(hdc, x0 + x * 20 + 18, y0 + y * 20 + 18);
			MoveToEx(hdc, x0 + x * 20 + 18, y0 + y * 20 + 2, NULL);
			LineTo(hdc, x0 + x * 20 + 2, y0 + y * 20 + 18);
			hit = 2;

			// какому кораблю принадлежит удар
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < ship_pl[i].p; j++)
				{
					if (ship_pl[i].orient == 0)
					{
						if (ship_pl[i].x == x && ship_pl[i].y + j == y)
						{
							ship_pl[i].pp++;
							n_ship = i;
						}
					}
					if (ship_pl[i].orient == 1)
					{
						if (ship_pl[i].x + j == x && ship_pl[i].y == y)
						{
							ship_pl[i].pp++;
							n_ship = i;
						}
					}
				}

			}

			if (ship_pl[n_ship].pp < ship_pl[n_ship].p)
			{
				SetDlgItemText(hWnd, ST3, L"Режим: Игра     Игрок: ранил!");
				Sleep(1000);
			}
			if (ship_pl[n_ship].pp == ship_pl[n_ship].p)
			{
				SetDlgItemText(hWnd, ST3, L"Режим: Игра     Игрок: убил!");
				set_ship_kill(map_, ship_pl, n_ship, 0, hWnd);
				n_ship = 99;
			}
		}
		if (map_[y][x] == 0)
		{
			map_[y][x] = 3;
			hpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hbrush);
			SelectObject(hdc, hpen1);
			Ellipse(hdc, x0 + 20 * x + 5, y0 + 20 * y + 5, x0 + 20 * x + 15, y0 + 20 * y + 15);
			DeleteObject(hpen1);
			DeleteObject(hbrush);
			hit = 3;
			SetDlgItemText(hWnd, ST3, L"Режим: Игра     Игрок:  мимо!");
		}
	} while (hit != 3);
}

int move_pl(int **map_, Ship *ship_comp, HWND hWnd, int x_pos, int y_pos) {
	HDC hdc = GetDC(hWnd);
	int x = 34, y = 3, hit, n_ship;
	hit = 0;

	if (map_[y_pos][x_pos] == 3 || map_[y_pos][x_pos] == 2)
		MessageBox(NULL, L"Не верный выбор!", L"Морской бой", MB_OK);

	if (map_[y_pos][x_pos] == 1)
	{
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		hpen1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		SelectObject(hdc, hpen1);
		MoveToEx(hdc, x0 + 280 + x_pos * 20 + 2, y0 + y_pos * 20 + 2, NULL);
		LineTo(hdc, x0 + 280 + x_pos * 20 + 18, y0 + y_pos * 20 + 18);
		MoveToEx(hdc, x0 + 280 + x_pos * 20 + 18, y0 + y_pos * 20 + 2, NULL);
		LineTo(hdc, x0 + 280 + x_pos * 20 + 2, y0 + y_pos * 20 + 18);
		DeleteObject(hpen1);
		DeleteObject(hbrush);
		map_[y_pos][x_pos] = 2;
		hit = 2;
		// какому кораблю принадлежит удар
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < ship_comp[i].p; j++)
			{
				if (ship_comp[i].orient == 0)
				{
					if (ship_comp[i].x == x_pos && ship_comp[i].y + j == y_pos)
					{
						ship_comp[i].pp++;
						n_ship = i;
					}
				}
				if (ship_comp[i].orient == 1)
				{
					if (ship_comp[i].x + j == x_pos && ship_comp[i].y == y_pos)
					{
						ship_comp[i].pp++;
						n_ship = i;
					}
				}
			}

		}

		if (ship_comp[n_ship].pp < ship_comp[n_ship].p)
		{
			SetDlgItemText(hWnd, ST3, L"Режим: Игра     Компьютер: ранил!");
		}
		if (ship_comp[n_ship].pp == ship_comp[n_ship].p)
		{
			SetDlgItemText(hWnd, ST3, L"Режим: Игра     Компьютер: убил!");
			set_ship_kill(map_, ship_comp, n_ship, 280, hWnd);
		}
	}
	if (map_[y_pos][x_pos] == 0)
	{
		hpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		hbrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hbrush);
		SelectObject(hdc, hpen1);
		Ellipse(hdc, x0 + 280 + 20 * x_pos + 5, y0 + 20 * y_pos + 5, x0 + 280 + 20 * x_pos + 15, y0 + 20 * y_pos + 15);
		DeleteObject(hpen1);
		DeleteObject(hbrush);
		map_[y_pos][x_pos] = 3;
		hit = 3;
		SetDlgItemText(hWnd, ST3, L"Режим: Игра     Компьютер: мимо!");
	}
	return hit;
}