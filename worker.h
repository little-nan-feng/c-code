#pragma once
#include <iostream>
using namespace std;
#include <string>

//ְ��������
class Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo()=0;

	//��ø�λ��Ϣ
	virtual string getDeptName()=0;

	//Ա������
	int w_ID;  //ְ�����
	string w_Name;  //ְ������
	int w_DeptId;  //���ű��
};