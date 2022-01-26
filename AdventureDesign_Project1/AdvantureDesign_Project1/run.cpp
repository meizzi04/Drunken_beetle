#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "class.h"

void Init_Room(int** Room, int size)  // 처음 타일 초기화
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Room[i][j] = 0;
		}
	}
}

void Show(int** Room, int size)  // 벌레가 타일을 다 돌았는지 보여주는 함수
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Room[i][j] > 0)
				cout << "■ ";
			else
				cout << "□ ";
		}
		cout << endl;
	}
}

void Print(int** Room, int size)  // 각 타일의 중복 타일 횟수 출력하는 함수
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

int Bug::Check(int move_count, int size) // 설계 달라짐
// 2차원 배열로 하면 시간이 오래걸려서 아예 무브 카운트를 따로 만들어서 확인
{
	return move_count == size * size;
}

int Bug::CheckRange(int nx, int ny, int size)
{
	return 0 <= nx && nx < size && 0 <= ny && ny < size;
}

int Bug::Move(int x, int y, int nx, int ny, int move_count, int total_count, int size, int** Room)
{
	// x, y : 현재 위치
	// dx, dy : 난수의 값에 따라 이동하는 위치가 달라지는 배열
	// nx, ny : 난수 발생 후 이동할 위치 (위의 현재 위치와 배열 값을 합침)

	Room[y][x] = 1;
	move_count = 1;  // 딱정벌레가 처음 위치하는 타일의 무브 카운트 1 추가
	total_count = 1;

	srand(time(NULL));

	while (1)
	{
		int r = rand() % 8;  // 0 ~ 7 까지의 난수 발생

		int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };  // 난수 발생 시 
		int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

		if (Check(move_count, size) == 1)
		{
			++Room[y][x];  // 마지막 타일의 횟수가 추가되지 않으므로 현 타일의 횟수 추가

			cout << endl << "딱정벌레가 모든 타일을 돌았습니다." << endl;
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

	cout << "총 이동 횟수 : " << AllMoveCount << "회" << endl;
	cout << "총 소요 시간 : " << AllMoveTime << "초" << endl;
	cout << endl;

	cout << "평균 이동 횟수 : " << Agecount << "회" << endl;
	cout << "평균 소요 시간 : " << Agetime << "초" << endl;
	cout << endl;

	cout << "나머지 결과는 파일에 저장합니다." << endl;
	cout << "프로그램을 종료합니다." << endl;

	cout << "========================================" << endl;
}
