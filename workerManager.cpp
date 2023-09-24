#include "workerManager.h"


//构造函数--初始化数据
WorkerManager::WorkerManager()
{
	//初始化数据

	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件


	if (!ifs.is_open())
	{
		//cout << "文件不存在！！！" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针--置为空指针
		this->m_EmpArray = nullptr;
		//初始化文件是否为空
		this->FileEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，但是文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空！！！" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = nullptr;
		//初始化文件是否为空
		this->FileEmpty = true;
		ifs.close();
		return;
	}

	//3、文件存在，并且有数据
	int num = this->Get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	this->FileEmpty = false;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将读到的数据存到数组中
	this->init_Emp();
}


//展示菜单--函数
void WorkerManager::ShowMenu()
{
	cout << "************************************" << endl;
	cout << "********欢迎使用职工管理系统********" << endl;
	cout << "********** 0.退出管理系统 **********" << endl;
	cout << "********** 1.增加职工信息 **********" << endl;
	cout << "********** 2.显示职工信息 **********" << endl;
	cout << "********** 3.删除离职职工 **********" << endl;
	cout << "********** 4.修改职工信息 **********" << endl;
	cout << "********** 5.查找职工信息 **********" << endl;
	cout << "********** 6.按照编号排序 **********" << endl;
	cout << "********** 7.清空所有文档 **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//退出系统--函数
void WorkerManager::ExitSystem()
{
	cout << " * 退出系统，欢迎下次使用！*" << endl;
	cout << endl;
	exit(0);
}

//添加职工--函数
void WorkerManager::Add_Emp()
{
	cout << "请输入要添加的职工数量：";
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小--新空间的大小=原来记录的人数+新增人数
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker ** newSpace = new Worker* [newSize+4];

		//将原来的空间下数据拷贝到新空间
		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个新职工的编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工的姓名：" << endl;
			cin >> name;

			cout << "请输入该职工的岗位选择：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			//将创建的职工指针，保存到新开辟的空间的数组中
			newSpace[this->m_EmpNum + i] = worker;

		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改原空间的指向--指向新开辟的空间地址
		this->m_EmpArray = newSpace;

		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->FileEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名职工" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	//按任意键清屏，回到上级目录
	system("pause");
	system("cls");
}


//保存文件--函数
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件 -- 写文件

	//将每个数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->w_ID << "\t"
			<< this->m_EmpArray[i]->w_Name << "\t"
			<< this->m_EmpArray[i]->w_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}


//统计文件人数--函数
int WorkerManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件   读出
	{
		int id;
		string name;
		int dId;

		int num = 0;

		while (ifs >> id && ifs >> name && ifs >> dId)
		{
			//统计人数的标志
			num++;
		}
		ifs.close();

		return num;
	}
}


//初始化员工--判断文件内数据后进行初始化赋值
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//打开文件

	int id;	
	string name;
	int dId;

	//从文件中读到职工信息
	while (ifs>>id && ifs>>name && ifs>>dId)
	{
		Worker* worker = nullptr;
		int index = 0;

		if (dId == 1)//员工
		{
			worker = new Employee(id,name,dId);
		}
		else if(dId==2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else//老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}


//显示员工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
		system("pause");
		system("cls");
	}
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入一个编号：" << endl;
		int id = 0;
		cin >> id;

		int index=this->IsExisti(id);

		if (index != -1)
		{
			//说明职工存在，可执行删除操作，删除index位置上的这个职工
			//数据前移--删除操作
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新删除后数组内职工的数量
			//数据同步到文件中
			this->save();
			cout << "删除成功" << endl;

		}
		else
		{
			//未找到职工
			cout << "未找到职工，删除失败" << endl;
		}
	}

	system("pause");
	system("cls");
}

//判断职工是否存在--如果存在，就返回职工所在数组的位置，不存在返回-1
int WorkerManager::IsExisti(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->w_ID == id)
		{
			//找到职工
			index = i;

			break;
		}
	}
	return index;
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->FileEmpty)
	{
		cout << "文件不存在或文件为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExisti(id);
		if (ret != -1)
		{
			//查找到了职工的编号

			delete this->m_EmpArray[ret];
			int NewId = 0;
			string NewName = " ";
			int dSelect = 0;

			cout << "查找到" << id << "号职工，请输入新职工号：" << endl;
			cin >> NewId;

			cout << "请输入新姓名：" << endl;
			cin >> NewName;

			cout << "请输入新岗位：" << endl;
			cout << "1、员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//更新数据到数组中
			this->m_EmpArray[ret] = worker;

			cout << "更新成功！" << endl;

			//保存到文件中
			this->save();

		}
		else
		{
			cout << "修改失败，查无此人！！！" << endl;
		}
	}

	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->FileEmpty)
	{
		cout << "文件不存在或者数据为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找：" << endl;
		cout << "2、按职工姓名查找：" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按照编号查
			int id;
			cout << "请输入要查找的职工编号是：" << endl;
			cin >> id;

			int ret = IsExisti(id);
			if (ret != -1)
			{
				//找到职工
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败！！！" << endl;

			}

		}
		else if(select==2)
		{
			//按照姓名查
			string name;
			cout << "请输入要查找的姓名：" << endl;
			cin >> name;

			//判断是否查找到的标志
			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->w_Name == name)
				{
					cout << "查找成功，职工编号为："
						<< this->m_EmpArray[i]->w_ID << endl
						<<this->m_EmpArray[i]->w_ID
						<< "号职工信息如下：" << endl;

					flag = true;

					//调用显示信息接口函数
					this->m_EmpArray[i]->showInfo();
				}
				
			}
			if (flag == false)
			{
				cout << "查找失败！！！" << endl;
			}
		}
		else
		{
			cout << "输入有误！！！" << endl;
		}

	}

	system("pause");
	system("cls");
}

//职工排序
void WorkerManager::Sort_Emp()
{
	if (this->FileEmpty)
	{
		cout << "文件不存在或者记录为空！！！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择一种排序方式：" << endl;
		cout << "1、按职工编号升序" << endl;
		cout << "2、按职工编号降序" << endl;

		int Select = 0;
		cin >> Select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值或最大值的下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{

				if (Select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->w_ID > this->m_EmpArray[j]->w_ID)
					{
						minOrMax = j;
					}
				}
				else//降序
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

		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//排序后的结果存到文件中
		this->Show_Emp();//展示排序后的职工
	}
}

//清空数据
void WorkerManager::Clean_File()
{
	cout << "确定清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、取消" << endl;

	int Select = 0;
	cin >> Select;

	if (Select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区的数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->FileEmpty = true;
		}
		cout << "清空成功！！！" << endl;

	}
	system("pause");
	system("cls");

}

//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}