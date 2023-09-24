#include"boss.h"

Boss::Boss(int id, string name, int Did)
{
	this->w_ID = id;
	this->w_Name = name;
	this->w_DeptId = Did;
}

//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号："<< this->w_ID << "\t"
		 << "职工姓名："<< this->w_Name << "\t"
		 << "岗位："<< this->getDeptName() << "\t"
		 << "定位：资本家" << endl;
}

//获得岗位信息
string Boss::getDeptName()
{
	return string("老板");
}