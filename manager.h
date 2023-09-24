#pragma once
#include<iostream>
using namespace std;
#include<string>

#include"worker.h"

class Manager:public Worker
{
public:
	Manager(int id, string name, int Did);

	//显示个人信息
	virtual void showInfo();

	//获得岗位信息
	virtual string getDeptName();
};