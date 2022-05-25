#include <iostream>
#include<cstdlib>
#include<fstream>
#include<conio.h>
#include<cstdio>
using namespace std;
//binary file project//

class emp1
{
	char en[20];
	int ec;
	float es;
	
	public:
	void input();
	void print();
	void modify();
	int getec();
};
	
void emp1::input()
{
    cout<<"enter employee code"<<endl;
	cin>>ec;
	fflush(stdin);
	
	cout<<"enter employee name"<<endl;
	cin>>en;
	fflush(stdin);
	
	cout<<"enter salary"<<endl;
	cin>>es;
	fflush(stdin);
	
}
void emp1:: print()
{
	cout<<"===================================================="<<endl;
	cout<<"\t \t employee record \t \t"<<endl;
	cout<<"===================================================="<<endl;
	cout<<"employee code \t employee name \t employee salary \t"<<endl;
	cout<<"****************************************************"<<endl;
	cout<<ec<<"\t \t"<<en<<"\t \t"<<es<<endl;
}
int emp1::getec()
{
	return ec;
}
void emp1::modify()
{
	cout<<"enter employee name"<<endl;
	cin>>en;
	fflush(stdin);
    cout<<"enter salary"<<endl;
	cin>>es;
	fflush(stdin);
}
void createemployee()
{
	ofstream fout;
	emp e;
	fout.open("emp1.txt",ios::app|ios::binary);
	e.input();
	fout.write((char*)&e,sizeof(e));
	fout.close();
}
void displayall()
{
	ifstream fin;
	emp e;
	fin.open("emp1.txt",ios::in|ios::binary);
	while(fin.read((char*)&e,sizeof(e)))
	{
		e.print();
	}
	fin.close();
}
void search()
{
	ifstream fin;
	emp e;
	fin.open("emp1.txt",ios::in|ios::binary);
	int x=0;
	int code;
	cout<<"enter search code"<<endl;
	cin>>code;
	
	while(fin.read((char*)&e,sizeof(e)))
	{
		if(e.getec()==code)
		{
			e.print();
			x=1;
			break;
		}
	}
	if(x==1)
	{
		cout<<"record found"<<endl;
	}
	else
	{
		cout<<"record not found"<<endl;
	}
	fin.close();
}
void delete1()
{
	ifstream fin;
	ofstream fout;
	emp e;
	int x=0;
	int code;
	fin.open("emp1.txt",ios::in|ios::binary);
	fout.open("temp.txt",ios::app|ios::binary);
	cout<<"enter delete code"<<endl;
	cin>>code;
	
	while(fin.read((char*)&e,sizeof(e)))
	{
		if(e.getec()==code)
		{
			x=1;
			continue;
		}
		else
		{
			fout.write((char*)&e,sizeof(e));
		}
	}
	fin.close();
	fout.close();
	remove("emp1.txt");
	rename("temp.txt","emp1.txt");
	
	if(x==1)
	{
		cout<<"record deleted"<<endl;
	}
	else
	{
		cout<<"record not found"<<endl;
	}
}
void update(int x)
{
	int y=0;
	emp e;
	ifstream fin;
	ofstream fout;
	fin.open("emp1.txt",ios::binary);
	fout.open("emp1.txt",ios::app|ios::binary);
	
	while(fin.read((char*)&e,sizeof(e)))
	{
		if(e.getec()==x)
		{
			e.modify();
			fout.write((char*)&e,sizeof(e));
			y=1;
		}
		else
		{
			fout.write((char*)&e,sizeof(e));
		}
	}
	fin.close();
	fout.close();
	remove("emp1.txt");
	rename("temp.txt","emp1.txt");
	
	if(y==1)
	{
		cout<<"record updated"<<endl;
	}
	else
	{
		cout<<"record not updated"<<endl;
	}
	
}
void intro()
{
	cout<<"welcome to my project"<<endl;
	cout<<"name is satwik"<<endl;
	cout<<"class is 12"<<endl;
}
	
int main()
{
	int ch;
	intro();
	
	
	do
	{
		getche();
		system("cls");
		cout<<"1:add new records \n";
		cout<<"2:display all records \n";
		cout<<"3:search any records \n";
		cout<<"4:delete any records \n";
		cout<<"5:update any records \n";
		cout<<"6:exit\n";
		
		cout<<"enter your choice \n";
		cin>>ch;
		
		switch(ch)
		{
			case 1:
			{
				createemployee();
				break;
			}
			case 2:
			{
				displayall();
				break;
			}
			case 3:
			{
				search();
				break;
			}
			case 4:
			{
				delete1();
				break;
			}
			case 5:
			{
				int code;
				cout<<"enter update code"<<endl;
				cin>>code;
				update(code);
				break;
			}
			case 6:
			{
				break;
			}
			default:
			{
				cout<<"wrong choice \n";
				break;
			}
		}
		
	}while(ch!=6);
	
	return 0;
}