#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include "transaction.h"
#define NO_OF_THREADS 5
pthread_t thread[NO_OF_THREADS];
using namespace std;

int main()
{
    init();
    int choice;

    while(1)
    {
        cout<<"\t\t\t *** WELCOME TO QUERY EVALUATION PROGRAM *** \n\n"<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"Query 1: insert into account values(account_number, name, balance);"<<endl;
        cout<<"Query 2: select * from account where account_number=dummy;" <<endl;
        cout<<"Query 3: select * from account;"<<endl;
        cout<<"Query 4: delete from account where account_number=dummy;"<<endl;
        cout<<"Query 5: update account set name=dummy, balance=dummy where account_number=dummy;"<<endl;
        cout<<"(---) 6: EXIT"<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\n\n";
        cout<<"Please enter Query choice: \n"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
                cout<<"THREAD : INSERT RECORD QUERY IN EXECUTION...\n"<<endl;
                pthread_create(&thread[1],NULL,insert_record,NULL);
                pthread_join(thread[1],NULL);
                cout<<"\n\n";
                break;
            }
        case 2:
            {
                account k;
                int a;
                cout<<"THREAD : SELECT RECORD QUERY IN EXECUTION...\n"<<endl;
                pthread_create(&thread[2],NULL,display_record,NULL);
                pthread_join(thread[2],NULL);
                cout<<"\n\n";
                break;
            }
        case 3:
            {
                account k;
                cout<<"THREAD : SELECT ALL RECORDS QUERY IN EXECUTION...\n"<<endl;
                pthread_create(&thread[3],NULL,display_record_all,NULL);
                pthread_join(thread[3],NULL);
                cout<<"\n\n";
                break;
            }
        case 4:
            {
                account k;
                int a;
                cout<<"DELETE RECORD QUERY IN EXECUTION...\n"<<endl;
                pthread_create(&thread[4],NULL,delete_record,NULL);
                pthread_join(thread[4],NULL);
//                k.delete_record(a);
                cout<<"\n\n";
                break;
            }
        case 5:
            {
                account k;
                int a;
                cout<<"UPDATE RECORD QUERY IN EXECUTION..."<<endl;
                pthread_create(&thread[5],NULL,update_record,NULL);
                pthread_join(thread[5],NULL);
                cout<<"\n\n";
                break;
            }
        case 6:
            {
                exit(0);
                break;
            }
        }
        cout<<"\nEnter any key to continue...";
        cin.get();
        cin.get();
        system("cls");
    }
}
