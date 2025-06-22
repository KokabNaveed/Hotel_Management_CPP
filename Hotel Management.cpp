#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include <conio.h>
using namespace std;
class room{
	protected:
		char FullName[15],IDcardNumber[15],CheckInDate[20],CheckOutDate[20],
		CheckInTime[20],CheckOutTime[20],RoomType[10],Gender[6];
		int Age,Balance,FloorNumber,TotalDays,RoomNumber;
	public:
		void Menu();
		void RoomsType();
		void CustomerData();
		bool CheckRoom(int);
		string CurrentDate();
		string CurrentTime();
		void ToCheckin();
		void ToCheckOut();
		void ToView();
		void ToSee();
		virtual void ReserveRoom(){
		}
};
void room::Menu(){
	system("color A");
	system("cls");
	cout<<"[\t\tHOTEL MANAGEMENT SYSTEM -> Menu\t\t]"
	<<"\n1. Press 1 To Reserve a Room"
	<<"\n2. Press 2 To Check-in a Customer"
	<<"\n3. Press 3 To View Reserved Rooms"
	<<"\n4. Press 4 To Check-out a Customer"
	<<"\n5. Press 5 To Exit"
	<<"\n\nPlease Enter Your Choice: ";
}
void room::RoomsType(){
	system("cls");
	cout<<"[\t\tRoom Types -> Menu\t\t]"
	<<"\n1. Press 1 For Standard"
	<<"\n2. Press 2 For Moderate"
	<<"\n3. Press 3 For Superior"
	<<"\n4. Press 4 For Junior Suite"
	<<"\n5. Press 5 For Suite"
	<<"\n\nPlease Enter Your Choice: ";
}
void room::CustomerData(){
	system("cls");
	cout<<"\n\tEnter Full Name: ";
	cin>>FullName;
	cin.ignore();
	cout<<"\tEnter Age: ";
	cin>>Age;
	cin.ignore();
	cout<<"\tEnter Gender: ";
	cin>>Gender;
	cin.ignore();
	cout<<"\tEnter ID Card Number: ";
	cin>>IDcardNumber;
	cin.ignore();
	cout<<"\tTotal Days To Reserve: ";
	cin>>TotalDays;
	strcpy(CheckInDate,"----------");
	strcpy(CheckInTime,"----------");
	strcpy(CheckOutDate,"-----------");
	strcpy(CheckOutTime,"-----------");
}
bool room::CheckRoom(int rn){
	bool flag=0;
	fstream file("data.txt",ios::in);
	while(file.read((char*)this,sizeof(room))){
		if(RoomNumber==rn){
		    flag=1;
		    break;
		}
	}
	file.close();
	return flag;
}
string room::CurrentDate(){
	time_t curr_time;
	tm * curr_tm;
	char date_string[50];
	time(&curr_time);
	curr_tm=localtime(&curr_time);
	strftime(date_string, 50, "%B %d, %Y", curr_tm);
	return date_string;
}
string room::CurrentTime(){
	time_t curr_time;
	tm * curr_tm;
	char time_string[100];
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(time_string, 50, "%H:%M:%S", curr_tm);
	return time_string;
}
void room::ToCheckin(){
	system("cls");
	cout<<"\n******************** Enter Data To Check-in ********************\n";
	int rn;
	bool flag=0;
	cout<<"\n\tEnter Room Number: ";
	cin>>rn;
    long pos;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
    		file.seekg(0);
		    while(!file.eof())
		    {
		        pos=file.tellg();
		        file.read((char*)this,sizeof(room));
		        if(RoomNumber==rn){
					strcpy(CheckInDate, CurrentDate().c_str());
					strcpy(CheckInTime, CurrentTime().c_str());
		            cout<<"\n\t***Checked In Successfully***";
		            cout<<"\n\tDate: "<<CheckInDate
		            <<"\n\tTime: "<<CheckInTime;
					file.seekg(pos);
		            file.write((char*)this,sizeof(room));
		            flag=1;
		            break;
				}
		    }
		    if(flag==0)
		    cout<<"\n\tEntered Room is Not reserved";
    		file.close();
}
void room::ToCheckOut(){
	system("cls");
	int rn;
	cout<<"\n\tEnter Room No: ";
	cin>>rn;
	long pos;
	bool flag=0;
    fstream file("data.txt",ios::in|ios::out|ios::binary);
    fstream file1("temp.txt",ios::in|ios::out|ios::binary);
    file.seekg(0);
	    while(!file.eof()){
		    pos=file.tellg();
		    file.read((char*)this,sizeof(room));
		    if(RoomNumber==rn){
					strcpy(CheckOutDate, CurrentDate().c_str());
					strcpy(CheckOutTime, CurrentTime().c_str());
		            cout<<"\n\t***Checked Out Successfully***";
		            cout<<"\n\tDate: "<<CheckOutDate;
		            cout<<"\n\tTime: "<<CheckOutTime;
					file.seekg(pos);
		            file1.write((char*)this,sizeof(room));
		            flag=1;
		            break;
				}
		    }
		    if(flag==0)
		    cout<<"\n\tEntered Room is not Reserved";
    		file.close();
    		remove("data.txt");
    		rename("temp.txt","data.text");
}
void room::ToView(){
	system("cls");
	cout<<"\n******************** Reserved Rooms ********************\n";
	    fstream file("data.txt",ios::in);
	    while(file.read((char*)this,sizeof(room)))
	    {
	    	cout<<"\n\tRoom Number: "<<RoomNumber<<"\n\tName: "<<FullName<<"\n\tAge: "<<Age
	    	<<"\n\tID Card Number: "<<IDcardNumber<<"\n\tTotal Days: "<<TotalDays
	    	<<"\n\tRoom Type: "<<RoomType<<"\n\tBalance: "<<Balance<<"\n\tCheck-in Date: "
			<<CheckInDate<<"\n\tCheck-in Time: "<<CheckInTime;
	    }
	    file.close();
}
void room::ToSee(){
	system("cls");
	cout<<"\n******************** Report ********************\n";
}
class standard:public room{
	public:
		
		void RoomNumbers(){
			system("cls");
			cout<<"\n1. Press 1 For Ground Floor"
	        <<"\n2. Press 2 For 1st Floor"
	        <<"\n3. Press 3 For 2nd Floor"
	        <<"\n4. Press 4 For 3rd Floor"
	        <<"\n5. Press 5 For 4th Floor"
	        <<"\n\nPlease Enter Your Choice: ";}
		void ReserveRoom(){
			int fn=0,rn=0;
			bool flag=0;
			RoomNumbers();
    		cin>>fn;
    		if(fn<1||fn>6){
			cout<<"\n\t***Choose from Given***";
			cout<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
		cout<<"\n\tSelect Room Number";
		switch(fn){
		case 1:
			{
			cout<<"\n\tRoom Number: 1 to 10";
			break;
			}
		case 2:
			{
			cout<<"\n\tRoom Number: 51 to 60";
			break;
			}	
		case 3:
			{
			cout<<"\n\tRoom Number: 101 to 110";
			break;
			}	
		case 4:
			{
			cout<<"\n\tRoom Number: 151 to 160";
			break;
			}
		case 5:
			{
			cout<<"\n\tRoom Number: 200 to 210";
			break;	
			}
        }cout<<endl;
        cin>>rn;
        if(rn<1||rn>=11&&rn<=50||rn>=60&&rn<=100||rn>=111&&rn<=150||rn>=161&&rn<=200||rn>211){
			cout<<"\n\tChoose Only from Given";
			cout<<"\n\tPress Any key to Continue...";
			getch();
			ReserveRoom();
			}
    		flag=CheckRoom(rn);
    		if(flag){
			cout<<"\n\t***Room is already Reserved***"
			<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
			system("cls");
			cout<<"\n\t1- For New Customer"
			<<"\n\t2- For Old Customer"
			<<"\n\tEnter Your Choice: ";
			int choice;
			cin>>choice;
		    if (choice==1)
		    {
		    	RoomNumber=rn;
				room::CustomerData();
				strcpy(RoomType, "Standard");
				Balance=300*TotalDays;
				ofstream file;
				file.open("data.txt",ios::app);
				file.write((char*)this,sizeof(standard));
				file.close();
				system("cls");
				cout<<"\n\tYour Room is Reserved Successfully\n";
			}
			else if(choice==2)
			{
			flag=OldCustomerData(rn);
			    if(flag==0){
				cout<<"\n\tYour Data is not Available"
				<<"\n\tEnter Details Again\n";	
	    	    }
			}
			else cout<<"\n\tInvalid Input\n";
			}
		bool OldCustomerData(int rn){
			system("cls");
			string name;
			cout<<"\n\tEnter Your Name: ";
			cin>>name;
			long pos;
			bool flag=0;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
		    while(file.read((char*)this,sizeof(standard)))
		    {
		        pos=file.tellg();
		        if(FullName==name)
		        {
		        	RoomNumber=rn;
		        	cout<<"\tEnter Total Days to Reserve Room: ";
					cin>>TotalDays;
					strcpy(RoomType, "Standard");
					Balance=300*TotalDays;
					file.seekg(pos);
		            file.write((char*)this,sizeof(standard));
		            cout<<"\n\tYour Room is Reserved Successfully";
		            flag=1;
		            break;
				}
		    }
		    file.close();
		    return flag;
		}
};
class moderate:public room{
	public:
		void RoomNumbers(){
			system("cls");
			cout<<"\n1. Press 1 For Ground Floor"
	        <<"\n2. Press 2 For 1st Floor"
	        <<"\n3. Press 3 For 2nd Floor"
	        <<"\n4. Press 4 For 3rd Floor"
	        <<"\n5. Press 5 For 4th Floor"
	        <<"\n\nPlease Enter Your Choice: ";}
		void ReserveRoom(){
			int fn=0,rn=0;
			bool flag=0;
			RoomNumbers();
    		cin>>fn;
    		if(fn<1||fn>6){
			cout<<"\n\t***Choose from Given***";
			cout<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
		switch(fn){
		case 1:
			{
			cout<<"\n\tRoom Number: 11 to 20";
			break;
			}
		case 2:
			{
			cout<<"\n\tRoom Number: 61 to 70";
			break;
			}	
		case 3:
			{
			cout<<"\n\tRoom Number: 111 to 120";
			break;
			}	
		case 4:
			{
			cout<<"\n\tRoom Number: 161 to 170";
			break;
			}
		case 5:
			{
			cout<<"\n\tRoom Number: 210 to 220";
			break;	
			}
        }cout<<"\nSelect Room Number: ";
        cin>>rn;
        if(rn<11||rn>=21&&rn<=60||rn>=70&&rn<=110||rn>=121&&rn<=160||rn>=171&&rn<=210||rn>221){
			cout<<"\n\tChoose Only from Given";
			cout<<"\n\tPress Any key to Continue...";
			getch();
			ReserveRoom();
			}
    		flag=CheckRoom(rn);
    		if(flag){
			cout<<"\n\t***Room is already Reserved***"
			<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
			system("cls");
			cout<<"\n\t1- For New Customer"
			<<"\n\t2- For Old Customer"
			<<"\n\tEnter Your Choice: ";
			int choice;
			cin>>choice;
		    if (choice==1)
		    {
		    	RoomNumber=rn;
				room::CustomerData();
				strcpy(RoomType, "Moderate");
				Balance=500*TotalDays;
				ofstream file;
				file.open("data.txt",ios::app);
				file.write((char*)this,sizeof(moderate));
				file.close();
				system("cls");
				cout<<"\n\tYour Room is Reserved Successfully\n";
			}
			else if(choice==2)
			{
			flag=OldCustomerData(rn);
			    if(flag==0){
				cout<<"\n\tYour Data is not Available"
				<<"\n\tEnter Details Again\n";	
	    	    }
			}
			else cout<<"\n\tInvalid Input\n";
			}
		bool OldCustomerData(int rn){
			system("cls");
			string name;
			cout<<"\n\tEnter Your Name: ";
			cin>>name;
			long pos;
			bool flag=0;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
		    while(file.read((char*)this,sizeof(moderate)))
		    {
		        pos=file.tellg();
		        if(FullName==name)
		        {
		        	RoomNumber=rn;
		        	cout<<"\tEnter Total Days to Reserve Room: ";
					cin>>TotalDays;
					strcpy(RoomType, "Moderate");
					Balance=500*TotalDays;
					file.seekg(pos);
		            file.write((char*)this,sizeof(moderate));
		            cout<<"\n\tYour Room is Reserved Successfully";
		            flag=1;
		            break;
				}
		    }
		    file.close();
		    return flag;
		}
};
class superior:public room{
		public:
		void RoomNumbers(){
			system("cls");
			cout<<"\n1. Press 1 For Ground Floor"
	        <<"\n2. Press 2 For 1st Floor"
	        <<"\n3. Press 3 For 2nd Floor"
	        <<"\n4. Press 4 For 3rd Floor"
	        <<"\n5. Press 5 For 4th Floor"
	        <<"\n\nPlease Enter Your Choice: ";}
		void ReserveRoom(){
			int fn=0,rn=0;
			bool flag=0;
			RoomNumbers();
    		cin>>fn;
    		if(fn<1||fn>6){
			cout<<"\n\t***Choose from Given***";
			cout<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
		cout<<"\n\tSelect Room Number";
		switch(fn){
		case 1:
			{
			cout<<"\n\tRoom Number: 21 to 30";
			break;
			}
		case 2:
			{
			cout<<"\n\tRoom Number: 71 to 80";
			break;
			}	
		case 3:
			{
			cout<<"\n\tRoom Number: 121 to 130";
			break;
			}	
		case 4:
			{
			cout<<"\n\tRoom Number: 171 to 180";
			break;
			}
		case 5:
			{
			cout<<"\n\tRoom Number: 220 to 230";
			break;	
			}
        }cout<<"\nSelect Room Number: ";
        cin>>rn;
        if(rn<21||rn>=31&&rn<=70||rn>=80&&rn<=120||rn>=131&&rn<=170||rn>=181&&rn<=220||rn>231){
			cout<<"\n\tChoose Only from Given";
			cout<<"\n\tPress Any key to Continue...";
			getch();
			ReserveRoom();
			}
    		flag=CheckRoom(rn);
    		if(flag){
			cout<<"\n\t***Room is already Reserved***"
			<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
			system("cls");
			cout<<"\n\t1- For New Customer"
			<<"\n\t2- For Old Customer"
			<<"\n\tEnter Your Choice: ";
			int choice;
			cin>>choice;
		    if (choice==1)
		    {
		    	RoomNumber=rn;
				room::CustomerData();
				strcpy(RoomType, "Superior");
				Balance=1000*TotalDays;
				ofstream file;
				file.open("data.txt",ios::app);
				file.write((char*)this,sizeof(superior));
				file.close();
				system("cls");
				cout<<"\n\tYour Room is Reserved Successfully\n";
			}
			else if(choice==2)
			{
			flag=OldCustomerData(rn);
			    if(flag==0){
				cout<<"\n\tYour Data is not Available"
				<<"\n\tEnter Details Again\n";	
	    	    }
			}
			else cout<<"\n\tInvalid Input\n";
			}
		bool OldCustomerData(int rn){
			system("cls");
			string name;
			cout<<"\n\tEnter Your Name: ";
			cin>>name;
			long pos;
			bool flag=0;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
		    while(file.read((char*)this,sizeof(superior)))
		    {
		        pos=file.tellg();
		        if(FullName==name)
		        {
		        	RoomNumber=rn;
		        	cout<<"\tEnter Total Days to Reserve Room: ";
					cin>>TotalDays;
					strcpy(RoomType, "Superior");
					Balance=1000*TotalDays;
					file.seekg(pos);
		            file.write((char*)this,sizeof(superior));
		            cout<<"\n\tYour Room is Reserved Successfully";
		            flag=1;
		            break;
				}
		    }
		    file.close();
		    return flag;
		}
};
class junior_suite:public room{
		public:
		void RoomNumbers(){system("cls");
			cout<<"\n1. Press 1 For Ground Floor"
	        <<"\n2. Press 2 For 1st Floor"
	        <<"\n3. Press 3 For 2nd Floor"
	        <<"\n4. Press 4 For 3rd Floor"
	        <<"\n5. Press 5 For 4th Floor"
	        <<"\n\nPlease Enter Your Choice: ";
		}
		void ReserveRoom(){
			int fn=0,rn=0;
			bool flag=0;
			RoomNumbers();
    		cin>>fn;
    		if(fn<1||fn>6){
			cout<<"\n\t***Choose from Given***";
			cout<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
		cout<<"\n\tSelect Room Number";
		switch(fn){
		case 1:
			{
			cout<<"\n\tRoom Number: 31 to 40";
			break;
			}
		case 2:
			{
			cout<<"\n\tRoom Number: 81 to 90";
			break;
			}	
		case 3:
			{
			cout<<"\n\tRoom Number: 131 to 140";
			break;
			}	
		case 4:
			{
			cout<<"\n\tRoom Number: 181 to 190";
			break;
			}
		case 5:
			{
			cout<<"\n\tRoom Number: 231 to 240";
			break;	
			}
        }cout<<"\nSelect Room Number: ";
        cin>>rn;
        if(rn<31||rn>=41&&rn<=80||rn>=90&&rn<=130||rn>=141&&rn<=180||rn>=191&&rn<=230||rn>241){
			cout<<"\n\tChoose Only from Given";
			cout<<"\n\tPress Any key to Continue...";
			getch();
			ReserveRoom();
			}
    		flag=CheckRoom(rn);
    		if(flag){
			cout<<"\n\t***Room is already Reserved***"
			<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
			system("cls");
			cout<<"\n\t1- For New Customer"
			<<"\n\t2- For Old Customer"
			<<"\n\tEnter Your Choice: ";
			int choice;
			cin>>choice;
		    if (choice==1)
		    {
		    	RoomNumber=rn;
				room::CustomerData();
				strcpy(RoomType, "Junior Suite");
				Balance=2000*TotalDays;
				ofstream file;
				file.open("data.txt",ios::app);
				file.write((char*)this,sizeof(junior_suite));
				file.close();
				system("cls");
				cout<<"\n\tYour Room is Reserved Successfully\n";
			}
			else if(choice==2)
			{
			flag=OldCustomerData(rn);
			    if(flag==0){
				cout<<"\n\tYour Data is not Available"
				<<"\n\tEnter Details Again\n";	
	    	    }
			}
			else cout<<"\n\tInvalid Input\n";
			}
		bool OldCustomerData(int rn){
			system("cls");
			string name;
			cout<<"\n\tEnter Your Name: ";
			cin>>name;
			long pos;
			bool flag=0;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
		    while(file.read((char*)this,sizeof(junior_suite)))
		    {
		        pos=file.tellg();
		        if(FullName==name)
		        {
		        	RoomNumber=rn;
		        	cout<<"\tEnter Total Days to Reserve Room: ";
					cin>>TotalDays;
					strcpy(RoomType, "Junior Suite");
					Balance=500*TotalDays;
					file.seekg(pos);
		            file.write((char*)this,sizeof(junior_suite));
		            cout<<"\n\tYour Room is Reserved Successfully";
		            flag=1;
		            break;
				}
		    }
		    file.close();
		    return flag;
		}
};
class suite:public room{
		public:
		void RoomNumbers(){
			system("cls");
			cout<<"\n1. Press 1 For Ground Floor"
	        <<"\n2. Press 2 For 1st Floor"
	        <<"\n3. Press 3 For 2nd Floor"
	        <<"\n4. Press 4 For 3rd Floor"
	        <<"\n5. Press 5 For 4th Floor"
	        <<"\n\nPlease Enter Your Choice: ";}
		void ReserveRoom(){
			int fn=0,rn=0;
			bool flag=0;
			RoomNumbers();
    		cin>>fn;
    		if(fn<1||fn>6){
			cout<<"\n\t***Choose from Given***";
			cout<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
		cout<<"\n\tSelect Room Number";
		switch(fn){
		case 1:
			{
			cout<<"\n\tRoom Number: 41 to 50";
			break;
			}
		case 2:
			{
			cout<<"\n\tRoom Number: 91 to 100";
			break;
			}	
		case 3:
			{
			cout<<"\n\tRoom Number: 141 to 150";
			break;
			}	
		case 4:
			{
			cout<<"\n\tRoom Number: 191 to 200";
			break;
			}
		case 5:
			{
			cout<<"\n\tRoom Number: 241 to 250";
			break;	
			}
        }cout<<"\nSelect Room Number: ";
        cin>>rn;
        if(rn<41||rn>=51&&rn<=90||rn>=101&&rn<=140||rn>=151&&rn<=190||rn>=201&&rn<=240||rn>251){
			cout<<"\n\tChoose Only from Given";
			cout<<"\n\tPress Any key to Continue...";
			getch();
			ReserveRoom();
			}
    		flag=CheckRoom(rn);
    		if(flag){
			cout<<"\n\t***Room is already Reserved***"
			<<"\n\tPress Any Key to Continue...";
			getch();
			ReserveRoom();
			}
			system("cls");
			cout<<"\n\t1- For New Customer"
			<<"\n\t2- For Old Customer"
			<<"\n\tEnter Your Choice: ";
			int choice;
			cin>>choice;
		    if (choice==1)
		    {
		    	RoomNumber=rn;
				room::CustomerData();
				strcpy(RoomType, "Suite");
				Balance=5000*TotalDays;
				ofstream file;
				file.open("data.txt",ios::app);
				file.write((char*)this,sizeof(suite));
				file.close();
				system("cls");
				cout<<"\n\tYour Room is Reserved Successfully\n";
			}
			else if(choice==2)
			{
			flag=OldCustomerData(rn);
			    if(flag==0){
				cout<<"\n\tYour Data is not Available"
				<<"\n\tEnter Details Again\n";	
	    	    }
			}
			else cout<<"\n\tInvalid Input\n";
			}
		bool OldCustomerData(int rn){
			system("cls");
			string name;
			cout<<"\n\tEnter Your Name: ";
			cin>>name;
			long pos;
			bool flag=0;
    		fstream file("data.txt",ios::in|ios::out|ios::binary);
		    while(file.read((char*)this,sizeof(suite)))
		    {
		        pos=file.tellg();
		        if(FullName==name)
		        {
		        	RoomNumber=rn;
		        	cout<<"\tEnter Total Days to Reserve Room: ";
					cin>>TotalDays;
					strcpy(RoomType, "Suite");
					Balance=5000*TotalDays;
					file.seekg(pos);
		            file.write((char*)this,sizeof(suite));
		            cout<<"\n\tYour Room is Reserved Successfully";
		            flag=1;
		            break;
				}
		    }
		    file.close();
		    return flag;
		}
};
main(){
	room r;
	room *r_ptr;
	int slct;
	do{
	r.Menu();
	cin>>slct;
	switch(slct){
		case 1:
			{
				int choice;
				r.RoomsType();
				cin>>choice;
				if(choice==1)
				{	
					r_ptr= new standard;
					r_ptr->ReserveRoom();
				}
				else if(choice==2)
				{	
					r_ptr= new moderate;
					r_ptr->ReserveRoom();
				}
				else if(choice==3)
				{	
					r_ptr= new superior;
					r_ptr->ReserveRoom();
				}
				else if(choice==4)
				{	
					r_ptr= new junior_suite;
					r_ptr->ReserveRoom();
				}
				else if(choice==5)
				{	
					r_ptr= new suite;
					r_ptr->ReserveRoom();
				}
				break;
			}
		case 2:
			{
				r.ToCheckin();
				break;	
			}	
		case 3:
			{
				r.ToView();
				break;
			}
		case 4:
			{
				r.ToCheckOut();
				break;
			}
		case 5:
		break;
		default:
		cout<<"\n\t***Invalid Input***\n";
	}
	cout<<"\n\tPress Any Key to Continue...";
	getch();
	}while(slct!=5);
}
