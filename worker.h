#pragma once
#include <iostream>
using namespace std;
#include <string>

//职工抽象类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo()=0;

	//获得岗位信息
	virtual string getDeptName()=0;

	//员工属性
	int w_ID;  //职工编号
	string w_Name;  //职工姓名
	int w_DeptId;  //部门编号
};