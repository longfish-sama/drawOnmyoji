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
	string tmp;
	POINT z, l1, l2;

	cout << curTime() << "设置原点（y 完成 / n 退出）" << endl;
	cin >> tmp;
	if (isYes(tmp))
	{
		/* code */
		if (GetCursorPos(&z))
		{
			cout << curTime() << "原点位置 x=" << z.x << " y=" << z.y << endl;
		}
		else
		{
			cout << curTime() << "GetCursorPos error" << endl;
			exit(-1);
		}
	}
	else
	{
		return 0;
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
