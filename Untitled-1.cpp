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
	string tmp;
	POINT z, l1, l2;

	cout << curTime() << "����ԭ�㣨y ��� / n �˳���" << endl;
	cin >> tmp;
	if (isYes(tmp))
	{
		/* code */
		if (GetCursorPos(&z))
		{
			cout << curTime() << "ԭ��λ�� x=" << z.x << " y=" << z.y << endl;
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
