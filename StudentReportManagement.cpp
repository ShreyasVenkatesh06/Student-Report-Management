

#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>




class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	float per;
	char grade;
	void calculate();	
public:
	void getdata();	
	void getdata1();
	void showdata();	
	void show_tabular();
	int retrollno();
}; 


void student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nConfirm The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin>>name;
	cout<<"\nEnter The marks in Cryptography out of 100      : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in File Structure out of 100    : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Software Testing out of 100  : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in Operating System out of 100  : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Python out of 100            : ";
	cin>>cs_marks;
	while(!((p_marks<=100)&&(c_marks<=100)&&(m_marks<=100)&&(e_marks<=100)&&(cs_marks<=100)))
	{
	cout<<"\nMarks out of range,enter all marks correctly\n";
	
	cout<<"\nEnter The marks in Cryptography out of 100      : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in File Structure out of 100    : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Software Testing out of 100  : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in Operating System out of 100  : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Python out of 100            : ";
	cin>>cs_marks;
	}
	calculate();
}

void student::showdata()
{
	cout<<"\nRoll number of student\t 	: "<<rollno;
	cout<<"\nName of the Student\t 		: "<<name;
	cout<<"\nMarks in Cryptography\t 		: "<<p_marks;
	cout<<"\nMarks in File Structure\t 	: "<<c_marks;
	cout<<"\nMarks in Software Testing\t  : "<<m_marks;
	cout<<"\nMarks in Operating System\t  : "<<e_marks;
	cout<<"\nMarks in Python\t 			:"<<cs_marks;
	cout<<"\nPercentage of student is\t  	:"<<per;
	cout<<"\nGrade of Student is\t 		:"<<grade;
}

void student::show_tabular()
{
	cout<<rollno<<setw(12)<<name<<setw(10)<<""<<p_marks<<setw(4)<<""<<c_marks<<setw(3)<<""<<m_marks<<setw(3)<<""<<e_marks<<setw(3)<<""<<cs_marks<<setw(3)<<""<<per<<setw(3)<<" "<<grade<<endl;
}

int  student::retrollno()
{
	return rollno;
}




void write_student();	
void display_all();		
void display_sp(int);	
int pkey(int);
void modify_student(int);	
void delete_student(int);	
void class_result();	
void result();	
void intro();	
void entry_menu();	




int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}



void write_student()
{
	student st;
	int nu,fla=0;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	cout<<"Enter roll number";
	cin>>nu;
	cout<<"Checking for constraint violation......";
	fla=pkey(nu);
	if(fla==0){
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();}
	else
		cout<<"\n\nPRIMARY KEY CONSTRAINT VIOLATED\n";
	getch();
}
int pkey(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
    int flag=0;
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()==n)
		{
			cout<<"\nERROR!!!\n ";
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\nClear to insert the record\n";
	return flag;


}



void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
		getch();
	}
	inFile.close();

	getch();
}



void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	int flag=0;
	while(inFile.read((char *)&st, sizeof(student)))
	{
		if(st.retrollno()==n)
		{
			clrscr();
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nrecord not exist";
	getch();


}



void modify_student(int n)
{
	int found=0;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
    while(File.read((char *) &st, sizeof(student)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata1();
		    int pos=(-1)*sizeof(st);
		    File.seekp(pos,ios::cur);
		    File.write((char *) &st, sizeof(student));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


void student::getdata1()
{
	
	cout<<"\n\nEnter The Name of student ";
	cin>>name;
	cout<<"\nEnter The marks in Cryptography out of 100      : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in File Structure out of 100    : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Software Testing out of 100  : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in Operating System out of 100  : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Python out of 100            : ";
	cin>>cs_marks;
	while(!((p_marks<=100)&&(c_marks<=100)&&(m_marks<=100)&&(e_marks<=100)&&(cs_marks<=100)))
	{
	cout<<"\nMarks out of range,enter all marks correctly\n";
	
	cout<<"\nEnter The marks in Cryptography out of 100      : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in File Structure out of 100    : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Software Testing out of 100  : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in Operating System out of 100  : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Python out of 100            : ";
	cin>>cs_marks;
	}
	calculate();
}



void delete_student(int n)
{
    int no,found=0;
	student st;
    clrscr();
    cout<<"\n\nPlease Enter The roll number of student You Want To Delete : ";
    cin>>no;

    fstream fp,fp2;
    fp.open("student.dat",ios::binary|ios::in|ios::out);

    fp2.open("Temp.dat",ios::out|ios::binary);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,  sizeof(student)))
    {
	if(st.retrollno()!=no)
	{
	    fp2.write((char*)&st,sizeof(student));
	}
		else
			found=1;
    }
	if(found==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\n\tRecord not found !!!!";
    fp.close();
	fp2.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    getch();
}



void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=============================================================\n";
	cout<<"R.No       Name        Cry   FS   ST   OS   Py   %age   Grade"<<endl;
	cout<<"=============================================================\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.show_tabular();
	}

	getch();
	inFile.close();
}



void result()
{
	char ch;
	int rno;
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}



void intro()
{
	cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	cout<<"\n\n\t\t  PROJECT";
	
	getch();
}



void entry_menu()
{
	char ch;
	int num;
	clrscr();
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				modify_student(num);break;
	case '5':	//cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

