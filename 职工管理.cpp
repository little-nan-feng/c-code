#include <iostream>
using namespace std;

//�Լ�������ͷ�ļ�-����ͷ�ļ��� ""
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


int main()
{
	//ʵ��������
	WorkerManager wm;

	//����չʾ�˵��ĳ�Ա����
	//��֧����
	int choice = 0;
	while (1)
	{
		wm.ShowMenu();
		cout << "���������ѡ�";
		cin >> choice;
		switch (choice)
		{
		case 0:  //�˳�����
			//�����˳���Ա����
			wm.ExitSystem();
			break;
		case 1:  //���ְ��
			wm.Add_Emp();
			break;
		case 2:  //��ʾ��Ϣ
			wm.Show_Emp();
			break;
		case 3:  //ɾ����Ϣ
			wm.Del_Emp();
			break;
		case 4:  //�޸���Ϣ
			wm.Mod_Emp();
			break;
		case 5:  //����ְ��
			wm.Find_Emp();
			break;
		case 6:  //ְ������
			wm.Sort_Emp();
			break;
		case 7:  //����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}


	}



	return 0;
}