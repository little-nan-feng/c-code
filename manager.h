#pragma once
#include<iostream>
using namespace std;
#include<string>

#include"worker.h"

class Manager:public Worker
{
public:
	Manager(int id, string name, int Did);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ø�λ��Ϣ
	virtual string getDeptName();
};