//  Created by Atharva Nadkar on 06/06/20.
//  Copyright © 2020 Atharva_Nadkar. All rights reserved.
//

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iomanip>

using namespace std;

int main()
{
    system("Color 03");
    FILE *fp, *ft;
    char another, choice;

    struct student
    {
        char first_name[15], last_name[15], dummy;
        string course;
        int year;
    } s;

    char xfirst_name[50], xlast_name[50];
    long int recsize;

    fp=fopen("dbms.txt", "rb+");

    if(fp == NULL)
    {
        fp = fopen("dbms.txt", "wb+");

        if(fp == NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }

    recsize = sizeof(s);

    while(1)
    {
        system("cls");

        cout<<"\t\t****** STUDENT DATABASE MANAGEMENT SYSTEM ****** \n";
        cout<<"\n \t\t\t\t MENU:\n";
        cout<<"\n \t\t\t 1. Add new records";
        cout<<"\n \t\t\t 2. View all records";
        cout<<"\n \t\t\t 3. Modify records";
        cout<<"\n \t\t\t 4. Delete records";
        cout<<"\n \t\t\t 5. Exit program";
        cout<<"\n\n \t\t\t Enter your choice: ";
        fflush(stdin);
        choice = getchar();

        switch(choice)
        {
        case '1':
            fseek(fp, 0, SEEK_END);
            another = 'Y';
            while(another == 'Y' || another == 'y')
            {
                system("cls");
                cout<<"\n \t *** Add a new record ***";
                cout<<"\n\n \t\t Enter first name: ";
                cin>>s.first_name;
                cout<<" \t\t Enter last name: ";
                cin>>s.last_name;
                cout<<" \t\t Enter course name: ";
                cin>>s.dummy;
                getline(cin, s.course);
                cout<<" \t\t Enter year: ";
                cin>>s.year;
                fwrite(&s, recsize, 1, fp);

                cout<<"\n \t\t Record added to database! \n";
                cout<<"\n \t\t Add another record? Y/N: ";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            cout<<"\n\n \t\t *** Records in Database ***\n\n";
            while(fread(&s, recsize, 1, fp) == 1)
            {
                cout<<"\n\n \t\t Name of student : "<<s.first_name<<setw(7)<<s.last_name;
                cout<<"\n \t\t Course and Year : "<<s.dummy<<s.course<<setw(7)<<", "<<s.year;
                cout<<(s.year == 1)? "st year\n" : (s.year == 2)? "nd year\n" : (s.year == 3)? "rd year\n" : "th year";
            }
            cout<<"\n\n";
            system("pause");
            break;
        case '3':
            system("cls");
            another = 'Y';
            while(another == 'Y' || another == 'y')
            {
                cout<<"\n\n \t *** Modify existing record *** \n";
                cout<<"\n \t Enter the last name of the student: ";
                cin>>xlast_name;

                rewind(fp);

                while(fread(&s, recsize,1,fp) == 1)
                {
                    if(strcmp(s.last_name, xlast_name) == 0)
                    {
                        cout<<"\n\n \t\t Enter new details:\n\n";
                        cout<<" \t\t First name? : ";
                        cin>>s.first_name;
                        cout<<" \t\t Last name? : ";
                        cin>>s.last_name;
                        cout<<" \t\t Course name? : ";
                        cin>>s.dummy;
                        getline(cin, s.course);
                        cout<<" \t\t Year? : ";
                        cin>>s.year;

                        fseek(fp, - recsize, SEEK_CUR);
                        fwrite(&s, recsize, 1, fp);

                        cout<<"\n\n \t\t Record modified! \n";

                        break;
                    }
                    else
                    {
                        cout<<"\n \t\t Record not found! \n";
                    }
                }
                cout<<"\n\n \t\t Modify another record? Y/N: ";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '4':
            system("cls");
            another = 'Y';
            cout<<"\n\n \t *** Delete existing record *** \n";
            while(another == 'y' || another == 'Y')
            {
                cout<<"\n \t Enter the last name of the student to delete the record: ";
                cin>>xlast_name;

                ft = fopen("temp.dat", "wb");
                rewind(fp);

                while(fread(&s, recsize, 1, fp) == 1)
                    if(strcmp(s.last_name, xlast_name) !=0)
                        {
                            fwrite(&s, recsize, 1, ft);
                        }

                fclose(fp);
                fclose(ft);

                remove("users.txt");
                rename("temp.dat", "users.txt");

                cout<<" \n\n \t\t Record deleted! \n";

                fp=fopen("users.txt", "rb+");

                cout<<"\n \t\t Delete another record? Y/N: ";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '5':
            cout<<"\n\n \t\t\t Exiting program... \n\n\n ";
            cout<<"\n \t\t\t Press x to quit.\n \t\t\t\t ";
            cin>>another;
            exit(0);
            break;
        default:
            cout<<"\n\n ERROR! Kindly choose from the given options.\n\n";
        }

    }
    system("pause");
    return 0;
}
