#include <iostream>
using namespace std;

//自己创建的头文件-包含头文件用 ""
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


int main()
{
	//实例化对象
	WorkerManager wm;

	//调用展示菜单的成员函数
	//分支函数
	int choice = 0;
	while (1)
	{
		wm.ShowMenu();
		cout << "请输入你的选项：";
		cin >> choice;
		switch (choice)
		{
		case 0:  //退出程序
			//调用退出成员函数
			wm.ExitSystem();
			break;
		case 1:  //添加职工
			wm.Add_Emp();
			break;
		case 2:  //显示信息
			wm.Show_Emp();
			break;
		case 3:  //删除信息
			wm.Del_Emp();
			break;
		case 4:  //修改信息
			wm.Mod_Emp();
			break;
		case 5:  //查找职工
			wm.Find_Emp();
			break;
		case 6:  //职工排序
			wm.Sort_Emp();
			break;
		case 7:  //清空文件
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}


	}



	return 0;
}