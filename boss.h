#pragma once
#include<iostream>
using namespace std;

#include"worker.h"

class Boss:public Worker
{
public:

	Boss(int id, string name, int Did);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ø�λ��Ϣ
	virtual string getDeptName();
};