#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "class.h"
using namespace std;

void Menu(int n);
void Init_Room(int** Room, int size);
void Show(int** Room, int size);
void Print(int** Room, int size);

int main()
{
	int menu_num = 0;
	int Room[2][4]{};

	while (1)
	{
		cout << "<술 취한 딱정벌레>" << endl;
		cout << "1. 게임 설명" << endl;
		cout << "2. 게임 시작" << endl;
		cout << "3. 게임 종료" << endl;
		cout << "위의 메뉴 중 하나를 선택하시오. ";
		cin >> menu_num;
		cout << endl;
		system("cls");  // 창 화면 깨끗하게 해줌
		Menu(menu_num);
	}
}

void Explanation()  // 게임 설명
{
	cout << "// 술 취한 딱정벌레는 조건이 달라짐에 따라 딱정벌레가 방 안의 모든 타일을 한 번 이상 지나가는 데 걸리는 시간 및 통계 자료를 구하는 문제 입니다. " << endl;
	cout << "// 위의 조건은 사용자가 선택한 방의 크기와 딱정벌레의 출발 위치" << endl << endl;
	cout << " - 사용 절차 - " << endl;
	cout << "1. 게임 시작 메뉴를 선택한다." << endl;
	cout << "2. 주어진 범위에 맞는 방의 크기와 딱정벌레의 출발 위치를 입력한다." << endl;
	cout << "3. 위에서 입력한 조건으로 프로그램을 몇 번 실행할지 횟수를 입력한다." << endl;
	cout << "4. 딱정벌레가 모든 방을 돈다." << endl;
	cout << "5. 프로그램이 다 실행되면 결과값을 출력한다." << endl;
	cout << "6. 다시 처음 메뉴가 나오면서 게임 설명, 시작, 종료 중 하나를 선택한다." << endl << endl;
	cout << "// 주의 사항 : 각 메뉴 당 선택 사항을 하나씩 고르시오" << endl << endl;
	cout << "===========================================================" << endl;
}

void Setting()  // 게임 시작   //설계 - Second_Menu()
{
	int size; // 방의 크기
	int count; //프로그램 실행 횟수
	Bug bug;
	Result result;
	result.Acount = 0;
	result.Atime = 0.0;
	result.AllMoveCount = 0;
	result.AllMoveTime = 0.0;
	result.Agecount = 0.0;
	result.Agetime = 0.0;

	cout << "- 방의 크기" << endl;
	cout << "5*5 / 6*6 / 7*7 / 8*8 / 9*9 / 10*10" << endl;
	cout << "- 딱정벌레의 출발 위치" << endl;
	cout << "1, 1 ~ 5, 5 / 1, 1 ~ 6, 6 / 1, 1 ~ 7, 7 / 1, 1 ~8, 8 / 1, 1 ~9, 9 / 1, 1 ~10, 10" << endl;
	cout << "//선택한 방의 크기에 따라 알맞은 범위 내에서 선택 가능" << endl << endl;
	do {
		cout << "방의 크기(ex. 5) : ";
		cin >> size;
		if (!cin)
		{
			cout << "// 숫자만 입력 가능합니다." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (size <= 4 || size >= 11)
		{
			cout << "// 방의 크기는 5 ~ 10 까지 선택 가능합니다." << endl << endl;
		}
	} while (size < 5 || size > 10);

	do {
		cout << "딱정벌레의 출발 위치(ex. 1 1) : ";
		cin >> bug.y >> bug.x;
		if (!cin)
		{
			cout << "// 숫자만 입력 가능합니다." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (bug.x <= 0 || bug.y <= 0)
		{
			cout << "// 0보다 큰 값을 입력해주세요." << endl << endl;
		}
		else if (bug.x > size || bug.y > size)
		{
			cout << "// 주어진 범위에 맞는 값을 입력해주세요." << endl << endl;
		}
	} while (bug.x > size || bug.y > size || bug.x <= 0 || bug.y <= 0);

	cout << "선택한 조건으로 프로그램을 몇 번 실행하시겠습니까? ";
	cin >> count;
	cout << endl;

	cout << "방의 크기 : " << size << "*" << size;
	cout << ", 출발 위치 : (" << bug.y << ", " << bug.x << ")" << endl << endl;
	Sleep(1000);
	system("cls");

	bug.x -= 1; // 좌표를 1, 1부터 설정할 거라 빼줌
	bug.y -= 1;

	int start_x = bug.x;  // 마지막에 최종 결과 출력 시 처음 좌표를 알기 위해 다른 변수에 저장
	int start_y = bug.y;

	int** Room = new int* [size];

	for (int i = 0; i < size; i++)  // 2차원 배열 동적할당
	{
		Room[i] = new int[size];
	}

	Init_Room(Room, size);

	int* Save_count = new int[count]; // 각 회차별 이동 횟수 저장
	double* Save_time = new double[count]; // 각 회차별 소요 시간 저장

	std::ofstream result_file;  // 파일 처리

	result_file.open("result.csv", ios::app);  // ios::app = 프로그램 재시작시 앞의 내용 뒤에 이어서 저장
	if (!result_file)                          // 에러 처리
	{
		cout << "파일 열기 에러" << endl;
	}

	result_file << "회차,방의 크기,시작 y 좌표,시작 x 좌표,이동 횟수,소요시간,총 이동 횟수,총 소요시간,평균 이동 횟수,평균 소요 시간" << endl;

	for (int i = 0; i < count; i++)
	{
		clock_t start = clock();
		result.Acount = bug.Move(bug.x, bug.y, bug.nx, bug.ny, bug.move_count, bug.total_count, size, Room);  // 이동 횟수
		result.AllMoveCount += result.Acount;  // 총 이동 횟수
		clock_t end = clock();

		result.Atime = (double)(end - start) / 1000.0;  // 소요 시간
		result.AllMoveTime += result.Atime;  // 총 소요 시간

		Save_count[i] = result.Acount;
		Save_time[i] = result.Atime;

		result.Agecount = (double)result.AllMoveCount / (double)count;  // 평균 이동 횟수
		result.Agetime = (double)result.AllMoveTime / (double)count;   // 평균 소요 시간

		cout << endl << i + 1 << "회차 이동 횟수 : " << result.Acount << "회" << endl;
		cout << i + 1 << "회차 소요 시간 : " << result.Atime << "초" << endl;
		cout << "나머지 결과는 파일에 저장합니다." << endl;
		cout << "========================================" << endl;
		Sleep(1000);

		Init_Room(Room, size);

		result_file << i+1 << "," <<size << "," << bug.y+1 << "," << bug.x+1 << "," << result.Acount << "," << result.Atime;

		if (i != count - 1) {
			result_file << endl;
		}
	}

	result_file << "," << result.AllMoveCount << "," << result.AllMoveTime << "," << result.Agecount << "," << result.Agetime << endl;
	result_file.close();

	cout << "----- 최종 결과 -----" << endl;
	result.Final_Result(result.AllMoveCount, result.AllMoveTime, result.Agecount, result.Agetime);
}

void Menu(int n) // 설계에서 first menu
{
	switch (n)
	{
	case 1:
		Explanation();
		break;

	case 2:
		Setting();
		break;

	case 3:
		cout << "술 취한 딱정벌레 게임을 종료하겠습니다." << endl;
		cout << "자세한 결과는 엑셀 파일을 확인하세요." << endl;
		exit(0);
		break;
	}
}