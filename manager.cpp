#include"manager.h"

Manager::Manager(int id, string name, int Did)
{
	this->w_ID = id;
	this->w_Name = name;
	this->w_DeptId = Did;
}

//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ�"<< this->w_ID << "\t"
		 << "ְ��������"<< this->w_Name << "\t"
		 << "��λ��" << this->getDeptName()<< "\t"
		 << "��λ��С����" << endl;
}

//��ø�λ��Ϣ
string Manager::getDeptName()
{
	return string("����");
}