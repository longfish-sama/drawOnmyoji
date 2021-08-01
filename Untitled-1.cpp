/*
 * @Author: ����
 * @Date: 2021-07-28 22:30:18
 * @LastEditTime: 2021-08-02 00:39:11
 * @FilePath: \drawOnmyoji\Untitled-1.cpp
 */

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

//clear cin buff
void clearBuf()
{
	cin.clear();
	cin.ignore(INT16_MAX, '\n');
	return;
}

//return current time
string curTime()
{
	time_t now = time(0);
	char timechar[26] = {0}, tempchar[26] = {0};
	ctime_s(timechar, sizeof timechar, &now);
	timechar[24] = 0;
	copy(&timechar[11], &timechar[19], begin(tempchar));
	string timestr = tempchar;
	return timestr + " ";
}

int main()
{
	const char size_cmd[32] = "MODE CON: COLS=49 LINES=12";
	const COORD buff_size_cmd = {49, 600}; //{�У���}
	system(size_cmd);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buff_size_cmd);
	srand((unsigned int)time(0));
	char cmd;
	POINT screen_org_point, screen_ref_point_1, screen_ref_point_2, draw_org_point;
	int distance = 0;					//�ƶ����������أ�
	const string filename = "locs.txt"; //�ļ���
	vector<POINT> points;				//���������
	int recovery_time = 10;				//�ָ�ʱ�䣨�룩
	int cold_time = 10;					//��ȴʱ�䣨�룩
	int residue_count = 0;				//ʣ�����

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

					split_loc = temp_str.find_first_of(".");
					if (split_loc < temp_str.length() - 1 && split_loc > 0)
					{
						temp_point.x = stoi(temp_str.substr(0, split_loc));
						temp_point.y = stoi(temp_str.substr(split_loc + 1));
						points.push_back(temp_point);
						cout << curTime() << "point " << loop_count << " ["
							 << points[loop_count].x << ","
							 << points[loop_count].y << "]" << endl;
						loop_count++;
					}
				}
			}
			file.close();
			cout << curTime() << "�����Ѷ��루Enter ���� / r ���¶�ȡ��" << endl;
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
			cout << curTime() << "�޷����ļ� " << filename << " �������ļ������ļ�λ��" << endl;
			system("pause");
		}
	}

	//settings
	while (true)
	{
		//set screen org point
		cout << curTime() << "������Ļԭ�㣨Enter ȷ����" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_org_point))
				{
					cout << curTime() << "��Ļԭ�� ["
						 << screen_org_point.x << ","
						 << screen_org_point.y << "]" << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() ����" << endl;
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
		cout << curTime() << "��ͼԭ�� ["
			 << draw_org_point.x << "," << draw_org_point.y << "]" << endl;

		//set screen ref point 1
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
					cout << curTime() << "GetCursorPos() ����" << endl;
					exit(-1);
				}
			}
		}

		//set screen ref point 2
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
					cout << curTime() << "GetCursorPos() ����" << endl;
					exit(-1);
				}
			}
		}

		//calculate screen distance
		while (true)
		{
			int gird_count = 1;
			cout << curTime() << "�������������Enter ȷ������" << endl;
			cin >> gird_count;
			clearBuf();
			if (gird_count > 0)
			{
				distance = abs(screen_ref_point_1.x - screen_ref_point_2.x) / gird_count;
				cout << curTime() << "������� " << distance << " ����" << endl;
				break;
			}
		}

		//set residue
		while (true)
		{
			cout << curTime() << "����ʣ�������Enter ȷ������" << endl;
			cin >> residue_count;
			clearBuf();
			if (residue_count >= 0)
			{
				residue_count = min(residue_count, (int)points.size()); //ȡ��Сֵ������������ֵ
				cout << curTime() << "��ǰʣ����� " << residue_count << endl;
				break;
			}
		}

		//set colddown time
		while (true)
		{
			cout << curTime() << "����ָ�ʱ�䣨�룩��Enter ȷ������" << endl;
			cin >> recovery_time;
			clearBuf();
			if (recovery_time > 0)
			{
				cold_time = (int)ceil(((double)points.size() - (double)residue_count) * (double)recovery_time / (double)points.size());
				cout << curTime() << "�ָ�ʱ�� " << recovery_time << " ��" << endl;
				cout << curTime() << "��ȴʱ�� " << cold_time << " ��" << endl;
				break;
			}
		}

		//need reset?
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

	//show info
	cout << curTime() << "�� " << points.size() << " �㣬Ԥ��ʱ�� "
		 << max(cold_time / 60, 1) //Ԥ��ʱ����С��ʾ1
		 << " ����" << endl;
	cout << curTime() << "��ʼ��ֻ��ͨ�����رճ�������ֹ����" << endl;
	cout << curTime() << "�롾���ֻ�ͼ���ڵĵ�ǰλ�úʹ�С��" << endl;
	cout << curTime() << "����5����ʱ����ǰ����ͼ���ڡ����ڶ��㡿�������ּ��" << endl;
	system("pause");
	cout << curTime() << "��ʱ5��" << endl;
	Sleep(5 * 1000);
	cout << curTime() << "��ʼ����" << endl;

	//start
	for (size_t i = 0; i < points.size(); i++)
	{
		cout << curTime() << "��ȴ " << cold_time << " ��" << endl;
		Sleep(1000 * cold_time + rand() % 3000);
		cout << curTime() << "��ͼλ�� " << i + 1
			 << " [" << points[i].x << "," << points[i].y << "]" << endl;
		SetCursorPos(screen_org_point.x + (points[i].x - draw_org_point.x) * distance,
					 screen_org_point.y + (points[i].y - draw_org_point.y) * distance);
		Sleep(100 + rand() % 500);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(10 + rand() % 100);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	cout << curTime() << "���"
		 << "\a" << endl;
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
