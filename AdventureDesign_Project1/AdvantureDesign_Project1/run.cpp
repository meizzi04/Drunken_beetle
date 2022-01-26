#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "class.h"

void Init_Room(int** Room, int size)  // ó�� Ÿ�� �ʱ�ȭ
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Room[i][j] = 0;
		}
	}
}

void Show(int** Room, int size)  // ������ Ÿ���� �� ���Ҵ��� �����ִ� �Լ�
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Room[i][j] > 0)
				cout << "�� ";
			else
				cout << "�� ";
		}
		cout << endl;
	}
}

void Print(int** Room, int size)  // �� Ÿ���� �ߺ� Ÿ�� Ƚ�� ����ϴ� �Լ�
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << Room[i][j] << "  ";
		}
		cout << endl;
	}
}

int Bug::Check(int move_count, int size) // ���� �޶���
// 2���� �迭�� �ϸ� �ð��� �����ɷ��� �ƿ� ���� ī��Ʈ�� ���� ���� Ȯ��
{
	return move_count == size * size;
}

int Bug::CheckRange(int nx, int ny, int size)
{
	return 0 <= nx && nx < size && 0 <= ny && ny < size;
}

int Bug::Move(int x, int y, int nx, int ny, int move_count, int total_count, int size, int** Room)
{
	// x, y : ���� ��ġ
	// dx, dy : ������ ���� ���� �̵��ϴ� ��ġ�� �޶����� �迭
	// nx, ny : ���� �߻� �� �̵��� ��ġ (���� ���� ��ġ�� �迭 ���� ��ħ)

	Room[y][x] = 1;
	move_count = 1;  // ���������� ó�� ��ġ�ϴ� Ÿ���� ���� ī��Ʈ 1 �߰�
	total_count = 1;

	srand(time(NULL));

	while (1)
	{
		int r = rand() % 8;  // 0 ~ 7 ������ ���� �߻�

		int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };  // ���� �߻� �� 
		int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

		if (Check(move_count, size) == 1)
		{
			++Room[y][x];  // ������ Ÿ���� Ƚ���� �߰����� �����Ƿ� �� Ÿ���� Ƚ�� �߰�

			cout << endl << "���������� ��� Ÿ���� ���ҽ��ϴ�." << endl;
			Print(Room, size);

			break;
		}

		nx = x + dx[r];
		ny = y + dy[r];

		if (CheckRange(nx, ny, size))
		{
			x = nx;
			y = ny;
			if (Room[y][x] == 0)
			{
				move_count++;
			}
		}
		total_count++;
		++Room[y][x];

		cout << endl;
		Show(Room, size);
		system("cls");
	}
	return total_count;
}

void Result::Final_Result(int AllMoveCount, double AllMoveTime, double Agecount, double Agetime)
{

	cout << "�� �̵� Ƚ�� : " << AllMoveCount << "ȸ" << endl;
	cout << "�� �ҿ� �ð� : " << AllMoveTime << "��" << endl;
	cout << endl;

	cout << "��� �̵� Ƚ�� : " << Agecount << "ȸ" << endl;
	cout << "��� �ҿ� �ð� : " << Agetime << "��" << endl;
	cout << endl;

	cout << "������ ����� ���Ͽ� �����մϴ�." << endl;
	cout << "���α׷��� �����մϴ�." << endl;

	cout << "========================================" << endl;
}
