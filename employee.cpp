#include"employee.h"

//���캯��
Employee::Employee(int id , string name, int Did)
{
	this->w_ID = id;
	this->w_Name = name;
	this->w_DeptId = Did;
}

//��ʾ������Ϣ
void Employee::showInfo()
{
	cout << "ְ����ţ�"<< this->w_ID << "\t"
		 << "ְ��������"<< this->w_Name << "\t"
		 << "��λ��" << this->getDeptName() << "\t"
		 << "��λ������" << endl;
}

//��ø�λ��Ϣ
string Employee::getDeptName()
{
	return string("Ա��");
}