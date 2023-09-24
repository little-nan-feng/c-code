#include "workerManager.h"


//���캯��--��ʼ������
WorkerManager::WorkerManager()
{
	//��ʼ������

	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�


	if (!ifs.is_open())
	{
		//cout << "�ļ������ڣ�����" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��--��Ϊ��ָ��
		this->m_EmpArray = nullptr;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->FileEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڣ������ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ�գ�����" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = nullptr;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->FileEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ����ڣ�����������
	int num = this->Get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	this->FileEmpty = false;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//�����������ݴ浽������
	this->init_Emp();
}


//չʾ�˵�--����
void WorkerManager::ShowMenu()
{
	cout << "************************************" << endl;
	cout << "********��ӭʹ��ְ������ϵͳ********" << endl;
	cout << "********** 0.�˳�����ϵͳ **********" << endl;
	cout << "********** 1.����ְ����Ϣ **********" << endl;
	cout << "********** 2.��ʾְ����Ϣ **********" << endl;
	cout << "********** 3.ɾ����ְְ�� **********" << endl;
	cout << "********** 4.�޸�ְ����Ϣ **********" << endl;
	cout << "********** 5.����ְ����Ϣ **********" << endl;
	cout << "********** 6.���ձ������ **********" << endl;
	cout << "********** 7.��������ĵ� **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ--����
void WorkerManager::ExitSystem()
{
	cout << " * �˳�ϵͳ����ӭ�´�ʹ�ã�*" << endl;
	cout << endl;
	exit(0);
}

//���ְ��--����
void WorkerManager::Add_Emp()
{
	cout << "������Ҫ��ӵ�ְ��������";
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//��������¿ռ��С--�¿ռ�Ĵ�С=ԭ����¼������+��������
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker ** newSpace = new Worker* [newSize+4];

		//��ԭ���Ŀռ������ݿ������¿ռ�
		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			cout << "�������" << i + 1 << "����ְ���ı�ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ����������" << endl;
			cin >> name;

			cout << "�������ְ���ĸ�λѡ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = nullptr;
			switch (dSelect)
			{case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:	
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//��������ְ��ָ�룬���浽�¿��ٵĿռ��������
			newSpace[this->m_EmpNum + i] = worker;

		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//����ԭ�ռ��ָ��--ָ���¿��ٵĿռ��ַ
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->FileEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "��ְ��" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}

	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}


//�����ļ�--����
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//������ķ�ʽ���ļ� -- д�ļ�

	//��ÿ������д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->w_ID << "\t"
			<< this->m_EmpArray[i]->w_Name << "\t"
			<< this->m_EmpArray[i]->w_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}


//ͳ���ļ�����--����
int WorkerManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�   ����
	{
		int id;
		string name;
		int dId;

		int num = 0;

		while (ifs >> id && ifs >> name && ifs >> dId)
		{
			//ͳ�������ı�־
			num++;
		}
		ifs.close();

		return num;
	}
}


//��ʼ��Ա��--�ж��ļ������ݺ���г�ʼ����ֵ
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//���ļ�

	int id;	
	string name;
	int dId;

	//���ļ��ж���ְ����Ϣ
	while (ifs>>id && ifs>>name && ifs>>dId)
	{
		Worker* worker = nullptr;
		int index = 0;

		if (dId == 1)//Ա��
		{
			worker = new Employee(id,name,dId);
		}
		else if(dId==2)//����
		{
			worker = new Manager(id, name, dId);
		}
		else//�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


//��ʾԱ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
		system("pause");
		system("cls");
	}
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "������һ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index=this->IsExisti(id);

		if (index != -1)
		{
			//˵��ְ�����ڣ���ִ��ɾ��������ɾ��indexλ���ϵ����ְ��
			//����ǰ��--ɾ������
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//����ɾ����������ְ��������
			//����ͬ�����ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;

		}
		else
		{
			//δ�ҵ�ְ��
			cout << "δ�ҵ�ְ����ɾ��ʧ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����--������ڣ��ͷ���ְ�����������λ�ã������ڷ���-1
int WorkerManager::IsExisti(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->w_ID == id)
		{
			//�ҵ�ְ��
			index = i;

			break;
		}
	}
	return index;
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->FileEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExisti(id);
		if (ret != -1)
		{
			//���ҵ���ְ���ı��

			delete this->m_EmpArray[ret];
			int NewId = 0;
			string NewName = " ";
			int dSelect = 0;

			cout << "���ҵ�" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> NewId;

			cout << "��������������" << endl;
			cin >> NewName;

			cout << "�������¸�λ��" << endl;
			cout << "1��Ա��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(NewId, NewName, dSelect);
			case 2:
				worker = new Manager(NewId, NewName, dSelect);
			case 3:
				worker = new Boss(NewId, NewName, dSelect);

			default:
				break;
			}

			//�������ݵ�������
			this->m_EmpArray[ret] = worker;

			cout << "���³ɹ���" << endl;

			//���浽�ļ���
			this->save();

		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�����" << endl;
		}
	}

	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->FileEmpty)
	{
		cout << "�ļ������ڻ�������Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų��ң�" << endl;
		cout << "2����ְ���������ң�" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "������Ҫ���ҵ�ְ������ǣ�" << endl;
			cin >> id;

			int ret = IsExisti(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ�����" << endl;

			}

		}
		else if(select==2)
		{
			//����������
			string name;
			cout << "������Ҫ���ҵ�������" << endl;
			cin >> name;

			//�ж��Ƿ���ҵ��ı�־
			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->w_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< this->m_EmpArray[i]->w_ID << endl
						<<this->m_EmpArray[i]->w_ID
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;

					//������ʾ��Ϣ�ӿں���
					this->m_EmpArray[i]->showInfo();
				}
				
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ�����" << endl;
			}
		}
		else
		{
			cout << "�������󣡣���" << endl;
		}

	}

	system("pause");
	system("cls");
}

//ְ������
void WorkerManager::Sort_Emp()
{
	if (this->FileEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�����" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ��һ������ʽ��" << endl;
		cout << "1����ְ���������" << endl;
		cout << "2����ְ����Ž���" << endl;

		int Select = 0;
		cin >> Select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ�����ֵ���±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{

				if (Select == 1)//����
				{
					if (this->m_EmpArray[minOrMax]->w_ID > this->m_EmpArray[j]->w_ID)
					{
						minOrMax = j;
					}
				}
				else//����
				{
					if (this->m_EmpArray[minOrMax]->w_ID < this->m_EmpArray[j]->w_ID)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();//�����Ľ���浽�ļ���
		this->Show_Emp();//չʾ������ְ��
	}
}

//�������
void WorkerManager::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;

	int Select = 0;
	cin >> Select;

	if (Select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ������������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->FileEmpty = true;
		}
		cout << "��ճɹ�������" << endl;

	}
	system("pause");
	system("cls");

}

//��������
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}