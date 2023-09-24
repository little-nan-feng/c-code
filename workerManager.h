#pragma once   //防止头文件重复包含
#include<iostream> //包含输入输出流头文件
using namespace std; //使用标准命名空间

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//展示菜单
	void ShowMenu();

	//声明退出函数
	void ExitSystem();

	//记录职工人数-属性
	int m_EmpNum;

	//职工数组指针-属性
	Worker ** m_EmpArray;

	//添加职工函数
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空
	bool FileEmpty;

	//统计文件人数
	int Get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示员工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断职工是否存在--如果存在，就返回职工所在数组的位置，不存在返回-1
	int IsExisti(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//职工排序
	void Sort_Emp();

	//清空数据
	void Clean_File();

	//析构函数
	~WorkerManager();
};