#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

class Criminal
{
 int admno;
 char name[20];
 char gender;
 int dob;
 char crime[20];
 
 public:
  void getData();
  void showData();
  int getAdmno()
  {
    return admno;
   }
}s;

void Criminal::getData()
{
    cout<<"\n\nEnter Criminal Details...\n";
    
    cout<<"Enter Prison No.     : ";
    cin>>admno;
    
    cout<<"Enter Criminal's Full Name         : ";
    cin.ignore(); cin.getline(name,20);
    
    cout<<"Enter Gender (M/F)      : ";
    cin>>gender;
    
    cout<<"Enter Date of Birth          : ";
    cin>>dob;
    
    cout<<"Enter crime commited           : ";
    cin.ignore(); cin.getline(crime,20);
    
    cout<<endl;
    
}

void Criminal::showData()
{
 cout<<"\n\n.......CRIMINAL DETAILS......\n";
 cout<<"Admission No.     : "<<admno<<endl;
 cout<<"Full Name         : "<<name<<endl;
 cout<<"Gender            : "<<gender<<endl;
 cout<<"Date of Birth          : "<<dob<<endl;
 cout<<"Crime Commited       : "<<crime<<endl;
 cout<<endl;

}

void addData()
{
 ofstream fout;
 fout.open("Criminal.dat",ios::binary|ios::out|ios::app);
 s.getData();
 fout.write((char*)&s,sizeof(s));
 fout.close();
 cout<<"Data Successfully Saved to File...\n";
 //s.showData();
 cout<<"press enter to continue..";
    cin.get();
}

void displayData()
{
 ifstream fin;
 fin.open("Criminal.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showData();
 }
 fin.close();
 cout<<"Data Reading from File Successfully Done...\n";
 cout<<"press enter to continue..";
    cin.get();
}

void searchData()
{
 int n, flag=0;
 ifstream fin;
 fin.open("Criminal.dat",ios::in|ios::binary);
 cout<<"Enter Inmate number : ";
 cin>>n;
 
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getAdmno())
  {
   cout<<"The Details of Inmate No. "<<n<<" are as follows:\n";
   s.showData();
   flag++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Inmate No. "<<n<<" not found....\n\n";
 cout<<"press enter to continue..";
    cin.get();
}

void deleteData()
{
 int n, flag=0;
 ifstream fin;
 ofstream fout,tout;

 fin.open("Criminal.dat",ios::in|ios::binary);
 fout.open("TempCrim.dat",ios::out|ios::app|ios::binary);
 tout.open("TrashCrim.dat",ios::out|ios::app|ios::binary);

 cout<<"Enter Inmate No. : ";
 cin>>n;
 
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getAdmno())
  {
   cout<<"The Following Inmate No. "<<n<<" has been moved to trash:\n";
   s.showData();
   tout.write((char*)&s,sizeof(s));
   flag++;
  }
  else
  {
   fout.write((char*)&s,sizeof(s));
  }
 }
 fout.close();
 tout.close();
 fin.close();
 if(flag==0)
  cout<<"The Inmate No. "<<n<<" not found....\n\n";
 remove("Criminal.dat");
 rename("TempCrim.dat","Criminal.dat");
}

void getTrash()
{
 ifstream fin;
 fin.open("TrashCrim.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showData();
 }
 fin.close();
 cout<<"Data Reading from Trash File Successfully Done....\n";
 cout<<"press enter to continue..";
    cin.get();
}

void modifyData()
{
 int n, flag=0, pos;
 fstream fio;

 fio.open("Criminal.dat",ios::in|ios::out|ios::binary);
 
 cout<<"Enter Inmate No. : ";
 cin>>n;
 
 while(fio.read((char*)&s,sizeof(s)))
 {
  pos=fio.tellg();
  if(n==s.getAdmno())
  {
   cout<<"The Following Inmate No. "<<n<<" will be modified with new data:\n";
   s.showData();
   cout<<"\n\nNow Enter the New Details....\n";
   s.getData();
   fio.seekg(pos-sizeof(s));
   fio.write((char*)&s,sizeof(s));
   flag++;
  }
 }
 fio.close();
 
 if(flag==0)
  cout<<"The Inmate No. "<<n<<" not found....\n\n";
}

void project()
{
 int ch;

  cout<<R"(
 _____      _           _             _  ______                       _   _____           _                 
/  __ \    (_)         (_)           | | | ___ \                     | | /  ___|         | |                
| /  \/_ __ _ _ __ ___  _ _ __   __ _| | | |_/ /___  ___ ___  _ __ __| | \ `--. _   _ ___| |_ ___ _ __ ___  
| |   | '__| | '_ ` _ \| | '_ \ / _` | | |    // _ \/ __/ _ \| '__/ _` |  `--. \ | | / __| __/ _ \ '_ ` _ \
| \__/\ |  | | | | | | | | | | | (_| | | | |\ \  __/ (_| (_) | | | (_| | /\__/ / |_| \__ \ ||  __/ | | | | |
 \____/_|  |_|_| |_| |_|_|_| |_|\__,_|_| \_| \_\___|\___\___/|_|  \__,_| \____/ \__, |___/\__\___|_| |_| |_|
                                                                                 __/ |                      
                                                                                |___/                       
------------------------------------------------By: Kinjal Joshi----------------------------------------------
    
)" << "\n\n";

 cout << "PRESS ENTER TO START\n";
    
 do
 {
  
  cin.get();
  cout<<"\n\n1. Enter Records to File\n";
  cout<<"2. Read Records From File\n";
  cout<<"3. Search Records From File\n";
  cout<<"4. Delete Records From File\n";
  cout<<"5. Get Deleted Records from Trash file\n";
  cout<<"6. Modify Records in File\n";
  cout<<"7. Exit from Program?\n";
  cout<<"Enter your choice  : ";
  cin>>ch;
  
  switch(ch)
  {
   case 1: addData();
   break;
   
   case 2: displayData();
   break;
   
   case 3: searchData();
   break;
   
   case 4: deleteData();
   break;
   
   case 5: getTrash();
   break;
   
   case 6: modifyData();
   break;

   case 7:
   exit(0);
  }
  
 }while(ch);
}

int main()
{
 project();
}
