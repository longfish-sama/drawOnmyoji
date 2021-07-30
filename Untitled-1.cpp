#include <iostream>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
using namespace std;

//������뻺��
void clearBuf()
{
	cin.clear();
	cin.ignore(INT16_MAX, '\n');
	return;
}

//string��ʽ���ص�ǰʱ��
string curTime()
{
	time_t now = time(0);
	char timechar[26] = {0}, tempchar[26] = {0};
	ctime_s(timechar, sizeof timechar, &now);
	timechar[24] = 0;
	copy(&timechar[11], &timechar[19], begin(tempchar));
	string timestr = tempchar;
	return "[" + timestr + "]" + " ";
}

int main()
{
	char size_cmd[32] = "MODE CON: COLS=52 LINES=15";
	COORD buff_size_cmd = {52, 600}; //{�У���}
	system(size_cmd);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buff_size_cmd);
	srand((unsigned int)time(0));
	char cmd;
	POINT screen_org_point, screen_ref_point_1, screen_ref_point_2, draw_org_point;
	int distance = 0;
	string filename = "locs.txt";
	vector<POINT> points;
	int cold_time = 10;

	//select color first
	cout << curTime() << "��ɫѡ�������Enter ������" << endl;
	system("pause");
	//read file
	while (true)
	{
		ifstream file(filename);
		if (file.is_open())
		{
			int loop_count = 0;
			while (!file.eof()) //���ж���
			{
				string temp_str;
				size_t split_loc = 0;
				POINT temp_point;
				getline(file, temp_str);
				if (!temp_str.empty() && temp_str.substr(0, 1) != "/")
				{

					split_loc = temp_str.find_first_of(",");
					if (split_loc < temp_str.length() - 1 && split_loc > 0)
					{
						temp_point.x = stoi(temp_str.substr(0, split_loc));
						temp_point.y = stoi(temp_str.substr(split_loc + 1));
						points.push_back(temp_point);
						cout << curTime() << "point " << loop_count << " [" << points[loop_count].x << " " << points[loop_count].y << "]" << endl;
						loop_count++;
					}
				}
			}
			file.close();
			cout << curTime() << "�����Ѷ��루y ���¶�ȡ / Enter ������" << ends;
			cmd = cin.get();
			if (cmd == '\n')
			{
				break;
			}
			else
			{
				clearBuf();
				continue;
			}
		}
		else
		{
			cout << curTime() << "can not open file: " << filename << " press any key to retry" << endl;
			system("pause");
		}
	}

	while (true)
	{
		//set org point
		cout << curTime() << "������Ļԭ�㣨Enter ȷ����" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_org_point))
				{
					cout << curTime() << "��Ļԭ��λ�� x=" << screen_org_point.x << " y=" << screen_org_point.y << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
		}
		//set draw_org_point
		cout << curTime() << "�����ͼԭ������꣨Enter ȷ������" << endl;
		cin >> draw_org_point.x;
		cout << curTime() << "�����ͼԭ�������꣨Enter ȷ������" << endl;
		cin >> draw_org_point.y;
		clearBuf();
		cout << curTime() << "��ͼԭ�� [" << draw_org_point.x << " " << draw_org_point.y << "]" << endl;

		//set ref point 1
		cout << curTime() << "������Ļ�ο���1��Enter ȷ����" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_ref_point_1))
				{
					cout << curTime() << "��Ļ�ο���1λ�� x=" << screen_ref_point_1.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
		}
		//set ref point 2
		cout << curTime() << "������Ļ�ο���2��Enter ȷ����" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_ref_point_2))
				{
					cout << curTime() << "��Ļ�ο���2λ�� x=" << screen_ref_point_2.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
		}
		//calculate distance
		while (true)
		{
			int gird_count = 1;
			cout << curTime() << "�������������Enter ȷ������" << endl;
			cin >> gird_count;
			clearBuf();
			if (gird_count > 0)
			{
				distance = abs(screen_ref_point_1.x - screen_ref_point_2.x) / gird_count;
				cout << curTime() << "������� " << distance << endl;
				break;
			}
		}
		//set colddown time
		while (true)
		{
			cout << curTime() << "������ȴʱ�䣨�룩��Enter ȷ������" << endl;
			cin >> cold_time;
			clearBuf();
			if (cold_time > 0)
			{
				break;
			}
		}
		cout << curTime() << "������ɣ�Enter ��ʼ���� / r �������ã�" << endl;
		cmd = cin.get();
		if (cmd == 'r' || cmd == 'R')
		{
			clearBuf();
			continue;
		}
		else
		{
			break;
		}
	}
	cout << curTime() << "�� " << points.size() << " �㣬Ԥ��ʱ�� " << max(points.size() * cold_time / 60, 1) << " ����" << endl;
	cout << curTime() << "�롾���ֻ�ͼ���ڵĵ�ǰλ�úʹ�С��������7����ʱ����ǰ����ͼ���ڡ����ڶ��㡿�������ּ��" << endl;
	system("pause");
	cout << curTime() << "��ʱ7��" << endl;
	Sleep(7 * 1000);
	cout << curTime() << "��ʼ����" << endl;
	for (size_t i = 0; i < points.size(); i++)
	{
		cout << curTime() << "��ȴ " << cold_time << " ��" << endl;
		Sleep(1000 * cold_time + rand() % 2000);
		cout << curTime() << "����λ�� " << i + 1 << " [" << points[i].x << " " << points[i].y << "]" << endl;
		SetCursorPos(screen_org_point.x + (points[i].x - draw_org_point.x) * distance, screen_org_point.y + (points[i].y - draw_org_point.y) * distance);
		Sleep(100 + rand() % 500);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(10 + rand() % 100);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	cout << curTime() << "�������"
		 << "\a" << endl;
	//��ȡ���λ��
	/*
	while (true)
	{
		GetCursorPos(&p);
		//system("cls"); //������cstdlib��
		cout << p.x << " " << p.y << endl;
		char c = getchar();
		cout << c << endl;
		Sleep(1000);
	}
	SetCursorPos(100, 100);							//�ƶ���ָ��λ��
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);	//�������
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//�ɿ����
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //�����Ҽ�
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);	//�ɿ��Ҽ�
	*/
	system("pause");
}
