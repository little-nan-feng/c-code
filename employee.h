#pragma once
//��ͨԱ���ļ�
#include<iostream>
using namespace std;

#include"worker.h"

class Employee :public Worker
{
public:

	Employee(int id, string name, int Did);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ø�λ��Ϣ
	virtual string getDeptName();
};