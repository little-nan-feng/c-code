#include"boss.h"

Boss::Boss(int id, string name, int Did)
{
	this->w_ID = id;
	this->w_Name = name;
	this->w_DeptId = Did;
}

//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ����ţ�"<< this->w_ID << "\t"
		 << "ְ��������"<< this->w_Name << "\t"
		 << "��λ��"<< this->getDeptName() << "\t"
		 << "��λ���ʱ���" << endl;
}

//��ø�λ��Ϣ
string Boss::getDeptName()
{
	return string("�ϰ�");
}