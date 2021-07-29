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
	char timechar[26];
	ctime_s(timechar, sizeof timechar, &now);
	timechar[24] = 0;
	string timestr = timechar;
	return "[" + timestr + "]" + " ";
}

bool isYes(string str)
{
	if (str == "y" || str == "Y")
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	char cmd;
	POINT org_point, ref_point_1, ref_point_2;
	int loop_count = 0;
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
			loop_count = 0;
			while (!file.eof())
			{
				string temp_str;
				size_t split_loc = 0;
				POINT temp_point;
				getline(file, temp_str);
				if (!temp_str.empty())
				{
					if (temp_str.substr(0, 1) != "/")
					{
						split_loc = temp_str.find_first_of(",");
						if (split_loc < temp_str.length() - 1)
						{
							temp_point.x = stoi(temp_str.substr(0, split_loc));
							temp_point.y = stoi(temp_str.substr(split_loc + 1));
							points.push_back(temp_point);
							cout << curTime() << "point " << loop_count << " [" << points[loop_count].x << " " << points[loop_count].y << "]" << endl;
							loop_count++;
						}
					}
				}
			}
			file.close();
			cout << curTime() << "�����Ѷ��룬���¶�ȡ����y ���¶�ȡ / Enter ������" << ends;
			cmd = cin.get();
			if (cmd == 'y' || cmd == 'Y')
			{
				clearBuf();

				continue;
			}
			else
			{
				break;
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
		cout << curTime() << "����ԭ�㣨Enter ȷ����" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&org_point))
				{
					cout << curTime() << "ԭ��λ�� x=" << org_point.x << " y=" << org_point.y << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
		}
		//set ref point 1
		loop_count = 0;
		cout << curTime() << "���òο���1��Enter ȷ�� / r �������ã�" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_1))
				{
					cout << curTime() << "�ο���1λ�� x=" << ref_point_1.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
			else if (loop_count == 0 && (cmd == 'r' || cmd == 'R'))
			{
				break;
			}
			loop_count++;
		}
		if (cmd == 'r' || cmd == 'R')
		{
			clearBuf();

			continue;
		}
		//set ref point 2
		loop_count = 0;
		cout << curTime() << "���òο���2��Enter ȷ�� / r �������ã�" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_2))
				{
					cout << curTime() << "�ο���2λ�� x=" << ref_point_2.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
			else if (loop_count == 0 && (cmd == 'r' || cmd == 'R'))
			{
				break;
			}
			loop_count++;
		}
		if (cmd == 'r' || cmd == 'R')
		{
			clearBuf();

			continue;
		}
		//calculate distance
		while (true)
		{
			int gird_count = 1;
			cout << curTime() << "�������������Enter ȷ������" << ends;
			cin >> gird_count;
			clearBuf();
			if (gird_count > 0)
			{
				distance = abs(ref_point_1.x - ref_point_2.x) / gird_count;
				cout << curTime() << "������� " << distance << endl;
				break;
			}
		}
		//set colddown time
		while (true)
		{
			cout << curTime() << "������ȴʱ�䣨�룩��Enter ȷ������" << ends;
			cin >> cold_time;
			clearBuf();
			if (cold_time > 0)
			{
				break;
			}
		}
		break;
	}
	cout << curTime() << "�������" << endl;
	system("pause");
	cout << curTime() << "��ʼ����" << endl;
	for (size_t i = 0; i < points.size(); i++)
	{
		cout << curTime() << "��ȴ " << cold_time << " ��" << endl;
		Sleep(1000 * cold_time);
		cout << curTime() << "����λ�� " << i + 1 << " [" << points[i].x << " " << points[i].y << "]" << endl;
		SetCursorPos(org_point.x + points[i].x * distance, org_point.y + points[i].y * distance);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	cout << "\a" << endl;
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
