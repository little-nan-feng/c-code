#pragma once   //��ֹͷ�ļ��ظ�����
#include<iostream> //�������������ͷ�ļ�
using namespace std; //ʹ�ñ�׼�����ռ�

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void ShowMenu();

	//�����˳�����
	void ExitSystem();

	//��¼ְ������-����
	int m_EmpNum;

	//ְ������ָ��-����
	Worker ** m_EmpArray;

	//���ְ������
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool FileEmpty;

	//ͳ���ļ�����
	int Get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾԱ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����--������ڣ��ͷ���ְ�����������λ�ã������ڷ���-1
	int IsExisti(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//ְ������
	void Sort_Emp();

	//�������
	void Clean_File();

	//��������
	~WorkerManager();
};