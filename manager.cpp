#include"manager.h"

Manager::Manager(int id, string name, int Did)
{
	this->w_ID = id;
	this->w_Name = name;
	this->w_DeptId = Did;
}

//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号："<< this->w_ID << "\t"
		 << "职工姓名："<< this->w_Name << "\t"
		 << "岗位：" << this->getDeptName()<< "\t"
		 << "定位：小康人" << endl;
}

//获得岗位信息
string Manager::getDeptName()
{
	return string("经理");
}