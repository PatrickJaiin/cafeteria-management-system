//cafeteria management software by Shiv Gupta
#include <iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include <ctime>
#include <cstdio>
using namespace std;
 
class People
{
    char Name[50];
    int barcode;
public:
    int food;
    int flag;
    People(){food=0; flag=1;}
    int flagr;//used to store day when food is given
    void Getdata();
    void Showdata();
    int  Check1(char nm[]);
    int  Check2(int br);
    void Edit();
};
 
//getdata inputs the data
 
void People::Getdata()
{
    cin.ignore();
    cout<<"\n\nEnter Name : "; cin.getline(Name,sizeof(Name));
    cout<<"Enter Barcode : "; cin>>barcode;
}
 
//displays the data
 
void People::Showdata()
{
    cout<<"\n\nName : "<<Name<<endl;
    cout<<"Barcode : "<<barcode<<endl;
    cout<<"Food taken this month is "<<food<<" times\n"<<endl<<endl;
}
 
//compares name of input with name of object
 
int People::Check1(char nm[])
{
    
    if (strcmp(nm,Name) == 0)
        return 1;
    else
        return 0;
}
 
//compares input barcode with barcode of object
 
int People::Check2(int br)
{
    if (br == barcode)
        return 1;
    else
        return 0;
}
 
//edits the particulars of a record
 
void People::Edit()
{
    char ch;
    do{
        cout<<"Detail of the Record :\n\n";
        Showdata();
        cout<<"\n\nPress A if you want to change Name \n";
        cout<<"Press B if you want to change Barcode \n";
        cout<<"Press C if you want no more change \n";
        cout<<"Enter your option :";
        ch=getchar();
        switch(ch)
        {
            case 'A':
            case 'a':     cout<<"\nEnter new Name : ";
                cin.ignore();
                cin.getline(Name,sizeof(Name));
                break;
            case 'B':
            case 'b':     cout<<"\nEnter new Barcode : ";
                cin>>barcode;
                break;
            case 'C':
            case 'c':     break;
                break;
            default :    cout<<"\nWrong Option !! Try Again !!";
        }
    }while(ch!='C' && ch!='c');
}
 
//used to add a new record
 
void Append()
{
    
    People P;
    cout<<"\nEnter the Detail of the Record : \n";
    P.Getdata();
    
    fstream f1;
    f1.open("DATA.DAT",ios::binary|ios::app);
    
    f1.write((char*) &P, sizeof(P));
    
    f1.close();
    
}
 
//used to display all the records
 
void DisplayAll()
{
    
    People P;
    
    fstream f1;
    f1.open("DATA.DAT",ios::binary|ios::in);
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        P.Showdata();
    }
    
    f1.close();
    
}
 
//used to search by name
 
void Search1()
{
    
    char sn[50];
    People P;
    int Found = 0;
    
    cout<<"\n\nEnter the Name to be searched : ";
    cin.ignore();
    cin.getline(sn,sizeof(sn));
    
    fstream f1;
    f1.open("DATA.DAT",ios::binary|ios::in);
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        if(P.Check1(sn)==1)
        {
            Found++ ;
            P.Showdata();
            
        }
    }
    
    f1.close();
    
    if (Found == 0)
        cout<<"\n\n NO MATCH FOUND !! \n\n";
    else
        cout<<"\n\n TOTAL "<< Found << " RECORD(S) FOUND !! \n\n";
}
 
//used to search by barcode
 
void Search2()
{
    
    int stn;
    People P;
    int Found = 0;
    
    cout<<"\n\nEnter the Barcode to be searched : ";
    cin>>stn;
    
    fstream f1;
    f1.open("DATA.DAT",ios::binary|ios::in);
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        if(P.Check2(stn)==1)
        {
            Found++ ;
            P.Showdata();
            
        }
    }
    
    f1.close();
    
    if (Found == 0)
        cout<<"\n\n NO MATCH FOUND !! \n\n";
    else
        cout<<"\n\n TOTAL "<< Found << " RECORD(S) FOUND !! \n\n";
    
}
 
//used to modify a record
 
void Modify()
{
    
    char sn[50];
    People P;
    int Modified = 0;
    
    cout<<"\n\nEnter the Name to be modified : ";
    cin.ignore();
    cin.getline(sn,sizeof(sn));
    
    fstream f1,f2;
    f1.open("DATA.DAT",ios::binary|ios::in);
    f2.open("TEMP.DAT",   ios::binary|ios::out);
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        if(P.Check1(sn)==1)
        {
            Modified++ ;
            P.Edit();
        }
        f2.write((char *) &P, sizeof(P));
    }
    
    f1.close();
    f2.close();
    
    
    if (Modified == 0)
        cout<<"\n\n NO MATCH FOUND !! \n\n";
    else
    {
        remove("DATA.DAT");
        rename("TEMP.DAT" , "DATA.DAT");
    }
}
 
//used to delete a record
 
void Delete()
{
    char sn[50];
    People P;
    int Deleted = 0;
    cout<<"\n\nEnter the Name to be deleted : ";
    cin.ignore();
    cin.getline(sn,sizeof(sn));
    
    fstream f1,f2;
    f1.open("DATA.DAT",ios::binary|ios::in);
    f2.open("TEMP.DAT",   ios::binary|ios::out);
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        if(P.Check1(sn)==1){
            Deleted ++ ;
        cout<<"The following record has been deleted:";
        P.Showdata();
        }
        else
            f2.write((char *) &P, sizeof(P));
    }
    
    f1.close();
    f2.close();
    
    
    
    if (Deleted == 0)
        cout<<"\n\n NO MATCH FOUND !! \n\n";
    else
    {
        remove("DATA.DAT");
        rename("TEMP.DAT" , "DATA.DAT");
    }
    
}
 
//used to distribute food
 
void Food(){
    int DD,MM,YYYY;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    YYYY=1900 + ltm->tm_year;
    MM= 1 + ltm->tm_mon;
    DD= ltm->tm_mday ;
    int stn;
    People P;
    int sr=0;
    do{
    fstream f1,f2;
    f1.open("DATA.DAT",ios::binary|ios::in);
    f2.open("TEMP.DAT",ios::binary|ios::out);
    cout<<"\n\nEnter the Barcode to be searched : ";
    cin>>stn;
    
    while( f1.read((char*) &P, sizeof(P)) )
    {
        if(P.flag==0){
            if(P.flagr!=DD)
                P.flag=1;
        }
 
        if(P.Check2(stn)==1){
            sr++;
            P.Showdata();
            if (P.flag==1) {
                P.food++;
                cout<<"\nYes, give him/her food";
                P.flagr=DD;
                P.flag=0;
            }
            else
                cout<<"\nNo, has already taken food today";
        }
            f2.write((char *) &P, sizeof(P));
    }
    
    if(sr==0)cout<<"\nCall security! NOT AN EMPLOYEE";
    f1.close();
    f2.close();
    remove("DATA.DAT");
        rename("TEMP.DAT","DATA.DAT");}while (stn!=0000);
}
 
 
int main()
{
            cout<<"Welcome to Cafeteria Software!\n ";
    time_t now = time(0);
 
    char* dt = ctime(&now);
    
    cout << "The date and time is: " << dt << endl;
    char choice;
    do{
        cout<<"Menu\n";
        cout<<"Press 1 for APPEND A RECORD \n";
        cout<<"Press 2 for DISPLAY ALL RECORDS \n";
        cout<<"Press 3 for SEARCH BY NAME \n";
        cout<<"Press 4 for SEARCH BY BARCODE \n";
        cout<<"Press 5 for MODIFY A RECORD \n";
        cout<<"Press 6 for DELETE A RECORD \n";
        cout<<"Press 7 for food distribution \n";
        cout<<"Press 8 to exit\n";
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case '1': Append();     break;
            case '2': DisplayAll(); break;
            case '3': Search1();    break;
            case '4': Search2();    break;
            case '5': Modify();     break;
            case '6': Delete();     break;
            case '7': Food();       break;
            case '8': cout<<"Thank You for using this program\n";break;
            default :cout<<"\nWrong Choice Entered !!\n\n";
        }
        getchar();
    }while(choice!='8');
}
