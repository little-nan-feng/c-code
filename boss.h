#pragma once
#include<iostream>
using namespace std;

#include"worker.h"

class Boss:public Worker
{
public:

	Boss(int id, string name, int Did);

	//显示个人信息
	virtual void showInfo();

	//获得岗位信息
	virtual string getDeptName();
};