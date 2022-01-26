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
		cout << "<�� ���� ��������>" << endl;
		cout << "1. ���� ����" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� ����" << endl;
		cout << "���� �޴� �� �ϳ��� �����Ͻÿ�. ";
		cin >> menu_num;
		cout << endl;
		system("cls");  // â ȭ�� �����ϰ� ����
		Menu(menu_num);
	}
}

void Explanation()  // ���� ����
{
	cout << "// �� ���� ���������� ������ �޶����� ���� ���������� �� ���� ��� Ÿ���� �� �� �̻� �������� �� �ɸ��� �ð� �� ��� �ڷḦ ���ϴ� ���� �Դϴ�. " << endl;
	cout << "// ���� ������ ����ڰ� ������ ���� ũ��� ���������� ��� ��ġ" << endl << endl;
	cout << " - ��� ���� - " << endl;
	cout << "1. ���� ���� �޴��� �����Ѵ�." << endl;
	cout << "2. �־��� ������ �´� ���� ũ��� ���������� ��� ��ġ�� �Է��Ѵ�." << endl;
	cout << "3. ������ �Է��� �������� ���α׷��� �� �� �������� Ƚ���� �Է��Ѵ�." << endl;
	cout << "4. ���������� ��� ���� ����." << endl;
	cout << "5. ���α׷��� �� ����Ǹ� ������� ����Ѵ�." << endl;
	cout << "6. �ٽ� ó�� �޴��� �����鼭 ���� ����, ����, ���� �� �ϳ��� �����Ѵ�." << endl << endl;
	cout << "// ���� ���� : �� �޴� �� ���� ������ �ϳ��� ���ÿ�" << endl << endl;
	cout << "===========================================================" << endl;
}

void Setting()  // ���� ����   //���� - Second_Menu()
{
	int size; // ���� ũ��
	int count; //���α׷� ���� Ƚ��
	Bug bug;
	Result result;
	result.Acount = 0;
	result.Atime = 0.0;
	result.AllMoveCount = 0;
	result.AllMoveTime = 0.0;
	result.Agecount = 0.0;
	result.Agetime = 0.0;

	cout << "- ���� ũ��" << endl;
	cout << "5*5 / 6*6 / 7*7 / 8*8 / 9*9 / 10*10" << endl;
	cout << "- ���������� ��� ��ġ" << endl;
	cout << "1, 1 ~ 5, 5 / 1, 1 ~ 6, 6 / 1, 1 ~ 7, 7 / 1, 1 ~8, 8 / 1, 1 ~9, 9 / 1, 1 ~10, 10" << endl;
	cout << "//������ ���� ũ�⿡ ���� �˸��� ���� ������ ���� ����" << endl << endl;
	do {
		cout << "���� ũ��(ex. 5) : ";
		cin >> size;
		if (!cin)
		{
			cout << "// ���ڸ� �Է� �����մϴ�." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (size <= 4 || size >= 11)
		{
			cout << "// ���� ũ��� 5 ~ 10 ���� ���� �����մϴ�." << endl << endl;
		}
	} while (size < 5 || size > 10);

	do {
		cout << "���������� ��� ��ġ(ex. 1 1) : ";
		cin >> bug.y >> bug.x;
		if (!cin)
		{
			cout << "// ���ڸ� �Է� �����մϴ�." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		if (bug.x <= 0 || bug.y <= 0)
		{
			cout << "// 0���� ū ���� �Է����ּ���." << endl << endl;
		}
		else if (bug.x > size || bug.y > size)
		{
			cout << "// �־��� ������ �´� ���� �Է����ּ���." << endl << endl;
		}
	} while (bug.x > size || bug.y > size || bug.x <= 0 || bug.y <= 0);

	cout << "������ �������� ���α׷��� �� �� �����Ͻðڽ��ϱ�? ";
	cin >> count;
	cout << endl;

	cout << "���� ũ�� : " << size << "*" << size;
	cout << ", ��� ��ġ : (" << bug.y << ", " << bug.x << ")" << endl << endl;
	Sleep(1000);
	system("cls");

	bug.x -= 1; // ��ǥ�� 1, 1���� ������ �Ŷ� ����
	bug.y -= 1;

	int start_x = bug.x;  // �������� ���� ��� ��� �� ó�� ��ǥ�� �˱� ���� �ٸ� ������ ����
	int start_y = bug.y;

	int** Room = new int* [size];

	for (int i = 0; i < size; i++)  // 2���� �迭 �����Ҵ�
	{
		Room[i] = new int[size];
	}

	Init_Room(Room, size);

	int* Save_count = new int[count]; // �� ȸ���� �̵� Ƚ�� ����
	double* Save_time = new double[count]; // �� ȸ���� �ҿ� �ð� ����

	std::ofstream result_file;  // ���� ó��

	result_file.open("result.csv", ios::app);  // ios::app = ���α׷� ����۽� ���� ���� �ڿ� �̾ ����
	if (!result_file)                          // ���� ó��
	{
		cout << "���� ���� ����" << endl;
	}

	result_file << "ȸ��,���� ũ��,���� y ��ǥ,���� x ��ǥ,�̵� Ƚ��,�ҿ�ð�,�� �̵� Ƚ��,�� �ҿ�ð�,��� �̵� Ƚ��,��� �ҿ� �ð�" << endl;

	for (int i = 0; i < count; i++)
	{
		clock_t start = clock();
		result.Acount = bug.Move(bug.x, bug.y, bug.nx, bug.ny, bug.move_count, bug.total_count, size, Room);  // �̵� Ƚ��
		result.AllMoveCount += result.Acount;  // �� �̵� Ƚ��
		clock_t end = clock();

		result.Atime = (double)(end - start) / 1000.0;  // �ҿ� �ð�
		result.AllMoveTime += result.Atime;  // �� �ҿ� �ð�

		Save_count[i] = result.Acount;
		Save_time[i] = result.Atime;

		result.Agecount = (double)result.AllMoveCount / (double)count;  // ��� �̵� Ƚ��
		result.Agetime = (double)result.AllMoveTime / (double)count;   // ��� �ҿ� �ð�

		cout << endl << i + 1 << "ȸ�� �̵� Ƚ�� : " << result.Acount << "ȸ" << endl;
		cout << i + 1 << "ȸ�� �ҿ� �ð� : " << result.Atime << "��" << endl;
		cout << "������ ����� ���Ͽ� �����մϴ�." << endl;
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

	cout << "----- ���� ��� -----" << endl;
	result.Final_Result(result.AllMoveCount, result.AllMoveTime, result.Agecount, result.Agetime);
}

void Menu(int n) // ���迡�� first menu
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
		cout << "�� ���� �������� ������ �����ϰڽ��ϴ�." << endl;
		cout << "�ڼ��� ����� ���� ������ Ȯ���ϼ���." << endl;
		exit(0);
		break;
	}
}