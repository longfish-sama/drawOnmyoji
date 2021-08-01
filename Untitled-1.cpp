/*
 * @Author: 长鱼
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
	const COORD buff_size_cmd = {49, 600}; //{列，行}
	system(size_cmd);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buff_size_cmd);
	srand((unsigned int)time(0));
	char cmd;
	POINT screen_org_point, screen_ref_point_1, screen_ref_point_2, draw_org_point;
	int distance = 0;					//移动步长（像素）
	const string filename = "locs.txt"; //文件名
	vector<POINT> points;				//绘制坐标点
	int recovery_time = 10;				//恢复时间（秒）
	int cold_time = 10;					//冷却时间（秒）
	int residue_count = 0;				//剩余次数

	//select color first
	cout << curTime() << "颜色选好了嘛？（Enter 继续）" << endl;
	system("pause");

	//read file
	while (true)
	{
		ifstream file(filename);
		if (file.is_open())
		{
			int loop_count = 0;
			while (!file.eof()) //逐行读入
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
			cout << curTime() << "参数已读入（Enter 继续 / r 重新读取）" << endl;
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
			cout << curTime() << "无法打开文件 " << filename << " ，请检查文件名与文件位置" << endl;
			system("pause");
		}
	}

	//settings
	while (true)
	{
		//set screen org point
		cout << curTime() << "设置屏幕原点（Enter 确定）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_org_point))
				{
					cout << curTime() << "屏幕原点 ["
						 << screen_org_point.x << ","
						 << screen_org_point.y << "]" << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() 错误" << endl;
					exit(-1);
				}
			}
		}

		//set draw_org_point
		cout << curTime() << "输入绘图原点横坐标（Enter 确定）：" << endl;
		cin >> draw_org_point.x;
		cout << curTime() << "输入绘图原点纵坐标（Enter 确定）：" << endl;
		cin >> draw_org_point.y;
		clearBuf();
		cout << curTime() << "绘图原点 ["
			 << draw_org_point.x << "," << draw_org_point.y << "]" << endl;

		//set screen ref point 1
		cout << curTime() << "设置屏幕参考点1（Enter 确定）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_ref_point_1))
				{
					cout << curTime() << "屏幕参考点1位置 x=" << screen_ref_point_1.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() 错误" << endl;
					exit(-1);
				}
			}
		}

		//set screen ref point 2
		cout << curTime() << "设置屏幕参考点2（Enter 确定）" << ends;
		while (true)
		{
			cmd = cin.get();
			if (cmd == '\n')
			{
				if (GetCursorPos(&screen_ref_point_2))
				{
					cout << curTime() << "屏幕参考点2位置 x=" << screen_ref_point_2.x << endl;
					break;
				}
				else
				{
					cout << curTime() << "GetCursorPos() 错误" << endl;
					exit(-1);
				}
			}
		}

		//calculate screen distance
		while (true)
		{
			int gird_count = 1;
			cout << curTime() << "输入横向间隔数（Enter 确定）：" << endl;
			cin >> gird_count;
			clearBuf();
			if (gird_count > 0)
			{
				distance = abs(screen_ref_point_1.x - screen_ref_point_2.x) / gird_count;
				cout << curTime() << "间隔距离 " << distance << " 像素" << endl;
				break;
			}
		}

		//set residue
		while (true)
		{
			cout << curTime() << "输入剩余次数（Enter 确定）：" << endl;
			cin >> residue_count;
			clearBuf();
			if (residue_count >= 0)
			{
				residue_count = min(residue_count, (int)points.size()); //取较小值避免后续相减负值
				cout << curTime() << "当前剩余次数 " << residue_count << endl;
				break;
			}
		}

		//set colddown time
		while (true)
		{
			cout << curTime() << "输入恢复时间（秒）（Enter 确定）：" << endl;
			cin >> recovery_time;
			clearBuf();
			if (recovery_time > 0)
			{
				cold_time = (int)ceil(((double)points.size() - (double)residue_count) * (double)recovery_time / (double)points.size());
				cout << curTime() << "恢复时间 " << recovery_time << " 秒" << endl;
				cout << curTime() << "冷却时间 " << cold_time << " 秒" << endl;
				break;
			}
		}

		//need reset?
		cout << curTime() << "设置完成（Enter 开始绘制 / r 重新设置）" << endl;
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
	cout << curTime() << "共 " << points.size() << " 点，预估时间 "
		 << max(cold_time / 60, 1) //预估时间最小显示1
		 << " 分钟" << endl;
	cout << curTime() << "开始后只能通过【关闭程序】来终止绘制" << endl;
	cout << curTime() << "请【保持绘图窗口的当前位置和大小】" << endl;
	cout << curTime() << "并在5秒延时结束前将绘图窗口【置于顶层】并【保持激活】" << endl;
	system("pause");
	cout << curTime() << "延时5秒" << endl;
	Sleep(5 * 1000);
	cout << curTime() << "开始绘制" << endl;

	//start
	for (size_t i = 0; i < points.size(); i++)
	{
		cout << curTime() << "冷却 " << cold_time << " 秒" << endl;
		Sleep(1000 * cold_time + rand() % 3000);
		cout << curTime() << "绘图位置 " << i + 1
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
	cout << curTime() << "完成"
		 << "\a" << endl;
	/*
	while (true)
	{
		GetCursorPos(&p);
		//system("cls"); //包含在cstdlib中
		cout << p.x << " " << p.y << endl;
		char c = getchar();
		cout << c << endl;
		Sleep(1000);
	}
	SetCursorPos(100, 100);							//移动到指定位置
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);	//按下左键
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);	//松开左键
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //按下右键
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);	//松开右键
	*/
	system("pause");
}
