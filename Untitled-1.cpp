#include <iostream>
#include <windows.h>
#include <ctime>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
using namespace std;
//string形式返回当前时间
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
		cout << curTime() << "设置原点（Enter 继续）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&org_point))
				{
					cout << curTime() << "原点位置 x=" << org_point.x << " y=" << org_point.y << endl;
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
		cout << curTime() << "设置参考点1（Enter 继续）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_1))
				{
					cout << curTime() << "参考点1位置 x=" << ref_point_1.x << " y=" << ref_point_1.y << endl;
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
		cout << curTime() << "设置参考点2（Enter 继续）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&ref_point_2))
				{
					cout << curTime() << "参考点2位置 x=" << ref_point_2.x << " y=" << ref_point_2.y << endl;
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

	//获取鼠标位置
	/*
	while (true)
	{
		GetCursorPos(&p);
		//system("cls"); //包含在cstdlib中
		cout << p.x << " " << p.y << endl;
		char c = getchar();
		cout << c << endl;
		Sleep(1000);
	}*/
	SetCursorPos(100, 100);							//移动到指定位置
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);	//按下左键
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//松开左键
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //按下右键
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);	//松开右键
	system("pause");
}
