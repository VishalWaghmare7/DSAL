#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;
class Student
{
    char Name[10], Address[20];
    int Roll_No;
    char Div;

public:
    Student()
    {
        Name[0] = '\0';
        Address[0] = '\0';
        Roll_No = -1;
        Div = '\0';
    }
    void get_Data();
    void show_data();
    int return_Roll() { return Roll_No; } 
};

void Student::get_Data()
{
    cout << "\nEnter Student Data";
    cout << "\nName: ";
    cin >> Name;
    cout << "\nAddress: ";
    cin >> Address;
    cout << "\nRoll Number: ";
    cin >> Roll_No;
    cout << "\nDiv(A/B/C): ";
    cin >> Div;
}
void Student::show_data()
{
    cout << "\n";
    cout << Div << "\t" << Roll_No << "\t" << Name << "\t" << Address << endl;
}

class Seq_File

{
    char File_Name[15];

public:
    void Create();
    void Display();
    void Insert();
    void Delete();
    int Search(int);
};

void Seq_File::Create()
{
    ofstream ofs;
    Student S;
    int i, n;
    cout << "Enter File Name\t";
    cin >> File_Name;
    ofs.open(File_Name, ios::app);

    if (ofs)
    {
        cout << "\nHow many student you have to add\n";
        cin >> n;
        for (i = 0; i < n; i++)
        {
            S.get_Data();
            ofs.write((char *)(&S), sizeof(S)); 
        }

        ofs.close();
    }
    else
        cout << "\nFile creation Error";
}
void Seq_File::Delete()
{
    int Roll;
    cout << "Enter roll number that you want to delete: " << endl;
    cin >> Roll;
    ifstream ifs;
    ofstream ofs;
    Student S;
    int Flag = 0;
    ifs.open(File_Name);  
    ofs.open("Temp.Txt"); 
    if (ifs && ofs)      
    {
        ifs.read((char *)(&S), sizeof(S)); 
        while (!ifs.eof())
        {
            if (Roll == S.return_Roll())
            {
                S.show_data();
                Flag = 1;
            }
            else
            {
                ofs.write((char *)(&S), sizeof(S)); 
            }
            ifs.read((char *)(&S), sizeof(S));
        }
        if (Flag == 0)
        {
            cout << "Roll No. " << Roll << " does not present \n";
        }

        ifs.close(); 
        ofs.close();
        remove(File_Name);             
        rename("Temp.Txt", File_Name); 
    }
    else
        cout << "File opening Error";
}
void Seq_File::Display()
{
    ifstream ifs;
    Student S;
    ifs.open(File_Name);
    if (ifs)
    {

        cout << "__________________________________________\n";
        cout << "Div\tRollNo\tName\tAddress" << endl;
        cout << "__________________________________________\n";
        ifs.read((char *)(&S), sizeof(S));
        while (!ifs.eof())
        {
            S.show_data();
            ifs.read((char *)(&S), sizeof(S));
        }
        ifs.close();
    }
    else
        cout << "\nFile opening Error";
}
void Seq_File::Insert()
{
    ofstream File;
    Student S;
    File.open(File_Name, ios::app); 
    if (File)
    {
        S.get_Data();                       
        File.write((char *)(&S), sizeof(S)); 
        File.close();
    }
    else
        cout << "File opening Error";
}
int Seq_File::Search(int Roll)
{
    ifstream File;
    Student S;
    int Flag = 0;
    File.open(File_Name);
    if (File)
    {
        File.read((char *)(&S), sizeof(S)); 
        while (!File.eof())
        {
            if (Roll == S.return_Roll())
            {
                S.show_data(); 
                Flag = 1;
            }
            File.read((char *)(&S), sizeof(S));
        }
        File.close();
    }
    else
        cout << "\nFile opening Error";
    return Flag;
}
int main()
{
    Seq_File sFile;
    int key, Choice;
    int flag = true;
    while (flag)
    {

        cout << "\n1: Create Database\n2: Display Database\n3: Insert a record\n4: Delete a Record\n5: Search a record\n7: Exit\nEnter your choice: ";
        cin >> Choice;
        switch (Choice)
        {
        case 1:
            sFile.Create();
            break;
        case 2:
            sFile.Display();
            break;
        case 3:
            sFile.Insert();
            break;
        case 4:
            sFile.Delete();
            break;
        case 5:
            cout << "\nEnter Roll No to Search";
            cin >> key;
            if (!sFile.Search(key))
                cout << "\nRecord does not present";
            break;

        case 6:
            return 0;
        }
        char flag2;
        cout << endl;
        cout << "Do you want to continue(y or n) :" << endl;
        cin >> flag2;
        if (flag2 == 'n')
        {
            flag = false;
        }
    }
}

