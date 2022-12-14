/*
	Title			: Hotel Management System
	Language		: C++
	Author			: Tikam singh
	From            :1 AUGUST 2022
	TO              :18 SEPTEMBER 2022
*/
#include <bits/stdc++.h>
using namespace std;

void intro()
{
	cout << "\n\t\t\t\t****************************************************";
	cout << "\n\t\t\t\t*      C++ Project On Hotel Management System      *";
	cout << "\n\t\t\t\t****************************************************";
	cout << "\n\n\t\t\t\t\t\t*  MADE BY TIKAM SINGH  *";
	cout << "\n\n\t\t\t\t\t\t\t\t";
}
// ======================= Time for loading ===========================

void time()
{
	int i = 0;
	long long j;
	cout << "	\n\n\n	Please wait \n 	Loading";
	while (i < 10)
	{
		for (j = 5; j > 4; j++)
		{
			if (j == 99999999)
			{
				cout << ".";
				break;
			}
		}
		++i;
	}
}

// ================================Hotel Class=========================

class hotel
{
private:
	int room_no;
	char name[30];
	char address[50];
	char phone[15];
	int days;
	float fare;

public:
	void main_menu();	  // to display the main menu
	void add();			  // to book a room
	void display();		  // to display the customer record
	void rooms();		  // to display allotted rooms
	void edit();		  // to edit the customer record
	int check(int);		  // to check room status
	void modify(int);	  // to modify the record
	void delete_rec(int); // to delete the record
};

// ===========================what u want to do select=======================
void hotel::main_menu()
{
	int choice;
	while (choice != 5)
	{
		cout << "\n\t\t\t\t*************";
		cout << "\n\t\t\t\t* MAIN MENU *";
		cout << "\n\t\t\t\t*************";
		cout << "\n\n\n\t\t\t1.Book A Room";
		cout << "\n\t\t\t2.Customer Record";
		cout << "\n\t\t\t3.Rooms Allotted";
		cout << "\n\t\t\t4.Edit Record";
		cout << "\n\t\t\t5.Exit";
		cout << "\n\n\t\t\tEnter Your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			add();
			break;
		case 2:
			display();
			break;
		case 3:
			rooms();
			break;
		case 4:
			edit();
			break;
		case 5:
			break;
		default:
		{
			cout << "\n\n\t\t\tWrong choice.....!!!";
			cout << "\n\t\t\tEnter the UserName ....!!";
		}
		}
	}
}

// =====================1.Book A Room====================


void hotel::add()
{
	int r, flag;
	ofstream fout("Record.dat", ios::app);           //first open the textfile using ofstream class object in append mode
	cout << "\n Enter Customer Details";  
	cout << "\n ----------------------";
	cout << "\n\n Room no: ";               
	cin >> r;
	flag = check(r);                                //check availability of the room 
	if (flag)                      
		cout << "\n Sorry..!!!Room is already booked";
	else                                            //if room is available take the customer details 
	{
		room_no = r;
		cout << " Name: ";
		gets(name);
		cout << " Address: ";
		gets(address);
		cout << " Phone No: ";
		gets(phone);
		cout << "No of Days to Checkout:";
		cin >> days;
		fare = days * 900;                          // 900 is currently set as the
						                            // default price per day
		fout.write((char *)this, sizeof(hotel));   //we will add all the details in file using fout
		cout << "\n Room is booked...!!!";
	}
	cout << "\n Press any key to continue.....!!";
	fout.close();
}


// ======================2.Customer Record=====================
void hotel::display()
{
	ifstream fin("Record.dat", ios::in);        //we will open the file reading mode
	int r, flag;     
	cout << "\n Enter room no: ";               //room no. for which we want to check details
	cin >> r;
	while (!fin.eof())                          //read file till the end of the file 
	{
		fin.read((char *)this, sizeof(hotel));  //reading 
		if (room_no == r)                       //and will check if entered room no. is matching with stored room no. or not
		{
			cout << "\n Customer Details";      // matching give all print all the details of the customer
			cout << "\n ----------------";
			cout << "\n\n Room no: " << room_no;
			cout << "\n Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Phone no: " << phone;
			cout << "\n Days: " << days;
			cout << "\n Total Fare: " << fare;
			flag = 1;     
		}
	}
	if (flag == 0)
	cout << "\n Sorry Room no. not found or vacant....!!";
	cout << "\n\n Press any key to continue....!!";
	fin.close();
}
// ====================3.Rooms Allotted=====================
void hotel::rooms()
{
	ifstream fin("Record.dat", ios::in);                 //open the file in input mode
	cout << "\n\t\t\t    List Of Rooms Allotted";
	cout << "\n\t\t\t    ----------------------";
	while (!fin.eof())                                  // read the file till the end of the file          
	{
		fin.read((char *)this, sizeof(hotel));          //reading 
		                                                // and everytime we will give the details of the rooms
		cout << "\n Room no: " << room_no << "\n Name: " << name;
		cout << "\n Address: " << address << "\n Phone: " << phone;
		cout << "\n Days: " << days << "\n Total: " << fare;
		cout << "\n**********************************";
	}
	cout << "\n\n\n\t\t\tPress any key to continue.....!!";
	fin.close();
}

// ====================4.Edit Record===================
void hotel::edit()
{
	 int choice, r;                                    //first we will take choice whether he want   
	                                                    //to  modify or delete
	cout << "\n EDIT MENU";
	cout << "\n ---------";
	cout << "\n\n 1.Modify Customer Record";
	cout << "\n 2.Delete Customer Record";
	cout << "\n Enter your choice: ";
	cin >> choice;
	cout << "\n Enter room no: ";                     // then take rooom no. he want to edit details for
	cin >> r;        
	switch (choice)
	{
	case 1:
		modify(r);
		break;
	case 2:
		delete_rec(r);
		break;
	default:
		cout << "\n Wrong Choice.....!!";
	}
	cout << "\n Press any key to continue....!!!";
}

// ====================check availability of room======================

int hotel::check(int r)
{
	int flag = 0;
	ifstream fin("Record.dat", ios::in);           //open file using ifstream class object 
	while (!fin.eof())                             //till the end of the file
	{
		fin.read((char *)this, sizeof(hotel));     // read from the file 
		if (room_no == r)              
		{
			flag = 1;
			break;
		}
	}

	fin.close();
	return (flag);
}
// =========================4.1 Modify the Record=====================
void hotel::modify(int r)
{
	long pos, flag = 0;
	fstream file("Record.dat", ios::in | ios::out | ios::binary);   //open file in both modes input and output
	while (!file.eof())                                              
	{
		pos = file.tellg();
		file.read((char *)this, sizeof(hotel));
		if (room_no == r)
		{
			cout << "\n Enter New Details";
			cout << "\n -----------------";
			cout << "\n Name: ";
			gets(name);
			cout << " Address: ";
			gets(address);
			cout << " Phone no: ";
			gets(phone);
			cout << " Days: ";
			cin >> days;
			fare = days * 900;
			file.seekg(pos);
			file.write((char *)this, sizeof(hotel));
			cout << "\n Record is modified....!!";
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "\n Sorry Room no. not found or vacant...!!";
	file.close();
}

// =====================4.2 delete record=========================
void hotel::delete_rec(int r)
{
	int flag = 0;
	char ch;
	ifstream fin("Record.dat", ios::in);
	ofstream fout("temp.dat", ios::out);
	while (!fin.eof())
	{
		fin.read((char *)this, sizeof(hotel));
		if (room_no == r)
		{
			cout << "\n Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Phone No: " << phone;
			cout << "\n Days: " << days;
			cout << "\n Total Fare: " << fare;
			cout << "\n\n Do you want to delete this record(y/n): ";
			cin >> ch;
			if (ch == 'n')
				fout.write((char *)this, sizeof(hotel));
			flag = 1;
			break;
		}
		else
			fout.write((char *)this, sizeof(hotel));
	}
	fin.close();
	fout.close();
	if (flag == 0)
		cout << "\n Sorry room no. not found or vacant...!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat", "Record.dat");
	}
}

// MARK:- Main() Function Here =>
int main()
{
	hotel h;
	cout << "\n\n\n";
	intro();
	time();
	cout << "\n\n\n\t\t\tPress any key to continue....!!";
	char id[5], pass[7];
	cout << "\n\n\t\t\t\tusername => ";
	cin >> id;
	cout << "\n\t\t\t\tpassword => ";
	cin >> pass;
	cout << "\n\n\t";
	time();
	cout << "\t";
	if (strcmp(id, "tkm") == 0 && strcmp(pass, "1234") == 0)
		cout << "\n\n\t\t\t  !!!Login Successfull!!!";
	else
	{
		cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
		exit(-1);
	}
	h.main_menu();
	return 0;
}