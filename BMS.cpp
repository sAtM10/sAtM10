# include "iostream"
# include "fstream"
# include "stdio.h"
# include "iomanip"
# include "ctype.h"
# include "stdlib.h"
# include "conio.h"

//Banking Management System//
using namespace std; 


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();   		//function to get new data from user
	void dep(int);			//function to accept amount and add to balance amount
	void draw(int);			//function to accept amount and subtract from balance amount
	void report();			//function to show data in tabular format
	int retacno();			//function to return account number
	int retdeposit();			//function to return balance amount
	char rettype();				//function to return type of account
};         						//class ends here


void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	fflush(stdin);
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	fflush(stdin);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	fflush(stdin);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	fflush(stdin);
	cout<<"\n\n\nAccount Created..";
}


void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nThe account No."<<acno;
	fflush(stdin);
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	fflush(stdin);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	fflush(stdin);
	cout<<"\nEnter The amount : ";
	cin>>deposit;
	fflush(stdin);

}


void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<deposit<<endl;
}


int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}

void account::dep(int x)
{
	deposit+=x;   // deposite=deposite+x
}

void account::draw(int x)
{
	deposit-=x;  // deposite=deposite-x
}



void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
    inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
			break;
		}
	}
    inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}




void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) )
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(ac);
			File.seekp(pos,ios::cur);
		    File.write((char *) &ac, sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}




void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);

	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}





void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) )
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}

		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }

			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
    File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : SATWIK MUKHERJEE";
	cout<<"\n\n COLLEGE : VIT BHOPAL";
	
}

int main(int argc, char const *argv[])
{
	char ch;
	int num;
	system("cls");
	intro();
	
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			intro();
			break;
		 default :cout<<"\a";
		}

		getche();
		
    }while(ch!='8');
	
	return 0;
}