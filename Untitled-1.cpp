#include <iostream>
#include <windows.h>
#include <ctime>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
using namespace std;
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
	string str;
	char cmd;
	POINT org_point, ref_point_1, ref_point_2;
	int loop_count = 0;

	while (true)
	{
		cout << curTime() << "����ԭ�㣨Enter ������" << ends;
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
		cout << curTime() << "���òο���1��Enter ������" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_1))
				{
					cout << curTime() << "�ο���1λ�� x=" << ref_point_1.x << " y=" << ref_point_1.y << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
			else if (loop_count == 0 && (cmd == 'b' || cmd == 'B'))
			{
				break;
			}
			loop_count++;
		}
		if (cmd == 'b' || cmd == 'B')
		{
			cin.clear();
			cin.ignore(INT8_MAX, '\n');
			continue;
		}
		//set ref point 2
		loop_count = 0;
		cout << curTime() << "���òο���2��Enter ������" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_2))
				{
					cout << curTime() << "�ο���2λ�� x=" << ref_point_2.x << " y=" << ref_point_2.y << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() error" << endl;
					exit(-1);
				}
			}
			else if (loop_count == 0 && (cmd == 'b' || cmd == 'B'))
			{
				break;
			}
			loop_count++;
		}
		if (cmd == 'b' || cmd == 'B')
		{
			cin.clear();
			cin.ignore(INT8_MAX, '\n');
			continue;
		}
	}
	system("pause");

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
	}*/
	SetCursorPos(100, 100);							//�ƶ���ָ��λ��
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);	//�������
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//�ɿ����
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //�����Ҽ�
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);	//�ɿ��Ҽ�
	system("pause");
}
