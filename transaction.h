#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include <semaphore.h>
#include<iomanip>
using namespace std;
sem_t sem;
void init()
{
    sem_init(&sem,0,1);
}
struct account
{
    int account_number;
    char name[50];
    int balance;

};

void* insert_record(void *);
void* delete_record(void *);
void* display_record_all(void *);
void* update_record(void *);
void setvalues(account *);
void getvalues();


void * insert_record(void *v)
{
    sem_wait(&sem);
    ifstream f;
    account k;
    account for_read;
    setvalues(&k);
    f.open("file.txt",ios::in);
    if(!f)
    {
        f.close();
        ofstream p;
        p.open("file.txt",ios::out);
        p.write((char *)&k,sizeof(k));
        p.close();
        sem_post(&sem);
        return v;

    }
    f.read((char *)&for_read,sizeof(k));
    while(!f.eof())
    {
        if(for_read.account_number==k.account_number)
        {
            cout<<"This record violates primary key constraint. Can't be added\n";
            sem_post(&sem);
            return v;
        }
        f.read((char *)&for_read,sizeof(k));
    }
    f.close();
    ofstream h;
    h.open("file.txt",ios::app);
    h.write((char *)&k,sizeof(k));
    h.close();
    sem_post(&sem);
}
void getvalues(account *acc)
{
    printf("|%-20d|%-30s|%-13d|\n",acc->account_number,acc->name,acc->balance);
    printf("-------------------------------------------------------------------\n");
}
void* display_record(void *v)
{
    sem_wait(&sem);
    int a;
    cout<<"Enter account number(dummy): "<<endl;
    cin>>a;
    printf("-------------------------------------------------------------------\n");
    printf("|%-20s|%-30s|%-13s|\n","ACCOUNT NUMBER","NAME","BALANCE");
    printf("-------------------------------------------------------------------\n");
    ifstream f;
    account k;
    f.open("file.txt",ios::in);
    if(!f)
    {
        cout<<"Error! No file exist\n";
        sem_post(&sem);
        return v;
    }
    f.read((char *)&k,sizeof(k));
//    cout<<"*******************************"<<endl;
    while(!f.eof())
    {
        if(k.account_number==a)
        {
            getvalues(&k);
 //           cout<<"*******************************"<<endl;
            sem_post(&sem);
            return v;
        }
        f.read((char *)&k,sizeof(k));
    }
    f.close();
    sem_post(&sem);
}


void * display_record_all(void *v)
{
    printf("-------------------------------------------------------------------\n");
    printf("|%-20s|%-30s|%-13s|\n","ACCOUNT NUMBER","NAME","BALANCE");
    printf("-------------------------------------------------------------------\n");
    sem_wait(&sem);
    ifstream k("file.txt");
    account l;
    if(!k)
    {
        cout<<"error"<<endl;
        sem_post(&sem);
        return v;
    }
    k.read((char *)&l,sizeof(l));
//    cout<<"*******************************"<<endl;
    while(!k.eof())
    {
        getvalues(&l);
        k.read((char *)&l,sizeof(l));
//        cout<<"*******************************"<<endl;
    }
    sem_post(&sem);
}
void setvalues(account *acc)
{
    cout<<"\nEnter account number: "<<endl;
    cin>>acc->account_number;
    cout<<"Enter account name: "<<endl;
    cin>>acc->name;
    cout<<"Enter account balance: "<<endl;
    cin>>acc->balance;
}

void * delete_record(void *v)
{
    sem_wait(&sem);
    int a;
    cout<<"Enter account number to delete(dummy): "<<endl;
    cin>>a;
    ifstream f("file.txt");
    ofstream l("file_1.txt");
    account k;
    int found=0;
    if(f.is_open())
    {
        f.read((char *)&k,sizeof(k));
        while(!f.eof())
        {
            if(k.account_number==a)
            {
               found=1;
            }
            else
            {
                l.write((char *)&k,sizeof(k));
            }
            f.read((char *)&k,sizeof(k));
        }
    }
    l.close();
    f.close();
    remove("file.txt");
    rename("file_1.txt","file.txt");
    if(found==0)
    {
        cout<<"No record exist"<<endl;
    }
    else
    {
        cout<<"Record Deleted"<<endl;
    }
    sem_post(&sem);
}

void* update_record(void *)
{
    sem_wait(&sem);
    int a;
    cout<<"Enter account number to update(dummy): "<<endl;
    cin>>a;
    ifstream f("file.txt");
    ofstream l("file_1.txt");
    account k;
    int found=0;
    if(f.is_open())
    {
        f.read((char *)&k,sizeof(k));
        while(!f.eof())
        {
            if(k.account_number==a)
            {
                char choice;
                found=1;
                cout<<"Printing record to be updated..."<<endl;
                printf("-------------------------------------------------------------------\n");
                printf("|%-20s|%-30s|%-13s|\n","ACCOUNT NUMBER","NAME","BALANCE");
                printf("-------------------------------------------------------------------\n");
                getvalues(&k);
                cout<<"Do you want to update account name: (y/n)"<<endl;
                cin>>choice;
                if(choice=='y')
                {
                    char new_name[50];
                    cout<<"Enter new account name: "<<endl;
                    cin>>new_name;
                    strcpy(k.name,new_name);
                }
                cout<<"Do you want to update account balance: (y/n)"<<endl;
                cin>>choice;
                if(choice=='y')
                {
                    int new_bal;
                    cout<<"Enter new account balance: "<<endl;
                    cin>>new_bal;
                    k.balance=new_bal;
                }
                l.write((char *)&k,sizeof(k));
            }
            else
            {
                l.write((char *)&k,sizeof(k));
            }
            f.read((char *)&k,sizeof(k));
        }
    }
    l.close();
    f.close();
    remove("file.txt");
    rename("file_1.txt","file.txt");
    if(found==0)
    {
        cout<<"No record exist"<<endl;
    }
    else
    {
        cout<<"Record updated"<<endl;
    }
    sem_post(&sem);
}

