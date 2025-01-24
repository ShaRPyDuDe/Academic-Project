#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void input();
void writefile();
void search();
void output();
void displayAllCustomers();
void deleteAllCustomers();

struct date {
    int month;
    int day;
    int year;
};

struct account {
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;    
}customer; 
int tl, sl, ts;

void main()
{
    int i,n;
    char ch;
    system ("cls");
    printf("  CUSTOMER BILLING SYSTEM : \n\n");
    printf("==============================\n\n");
    printf("1:   ADD account on list\n");
    printf("2:   SEARCH customer account \n");
    printf("3:   DISPLAY all customer accounts\n");
    printf("4:   DELETE all customer accounts\n");
    printf("5:   EXIT\n");
    printf("==============================\n");

    do
    {
        printf("\n select what you want to do ?? \n");
        ch=getchar();
    }while(ch<='0' || ch>'5');

    switch(ch)
    {
        case '1':
        system("cls");
        printf("\n how many customer accounts:  ");
        scanf("%d", &n);
        getchar();
        for (i=0; i<n; i++){
            input();
            if(customer.payment > 0.0)
            customer.acct_type=(customer.payment < customer.oldbalance) ? 'O' : 'D';
            else
            customer.acct_type=(customer.oldbalance > 0) ? 'D' : 'C';
            customer.newbalance=customer.oldbalance - customer.payment;
            writefile();
        }
        main();
        
        case '2':
        getchar();
        system("cls");
        printf("search by what??\n\n");
        printf("1:------- search by customer number \n");
        printf("2:------- search by customer name \n");
        search();
        ch=getchar();
        main();

        case '3':
        displayAllCustomers();
        break;

        case '4':
        deleteAllCustomers();
        break;
        
        case '5':
        system("cls");             
        printf("A PROJECT BY KAWSAR, LABIB, EUSHA");
        exit(1);
    }    
}

void input()
{
    FILE *fp=fopen("file.txt", "ab+");
    fseek(fp, 0, SEEK_END);
    tl=ftell(fp);
    sl=sizeof(customer);
    ts=tl/sl;
    fseek(fp, (ts-1)*sl, SEEK_SET);
    fread(&customer, sizeof(customer), 1, fp);
    printf("\ncustomer no : %d \n", ++customer.number);
    fclose(fp);
    printf("      Account number:  ");
    scanf("%d", &customer.acct_no);
    getchar();
    printf("\n    Name:");
    scanf("%s", customer.name);
    getchar();
    printf("\n    mobile no:  ");
    scanf("%f",&customer.mobile_no);
    getchar();
    printf("\n    Street:  ");
    scanf("%s", customer.street);
    getchar();
    printf("\n    city:  ");
    scanf("%s", customer.city);
    getchar();
    printf("\n    Previous balance:  ");
    scanf("%f", &customer.oldbalance);
    getchar();
    printf("\n    Current payment:  ");
    scanf("%f", &customer.payment);
    getchar();
    printf("\n    Payment date (dd/mm/yyyy):  ");
    scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
    getchar();
}

void writefile()
{
    FILE *fp;
    fp=fopen("file.txt","ab+");
    fwrite(&customer,sizeof(customer), 1, fp);
    fclose(fp);
    return;
}

void search()
{
    char ch;
    char nam[100];
    int n,i,m=1;
    FILE *fp;
    fp=fopen("file.txt","r+");
    do
    {
        printf("\n enter your choice:  ");
        ch=getchar();

    }while(ch!='1' && ch!='2');
    switch(ch)
    {
        case '1':
        fseek(fp,0,SEEK_END);
        tl=ftell(fp);
        sl=sizeof(customer);
        ts=tl/sl;
        do
        {
            printf("\n choose customer number:  ");
            scanf("%d", &n);
            if(n<=0 || n>ts){
                printf("\n enter correct \n");
            }
            else
            {
                fseek(fp,(n-1)*sl, SEEK_SET);
                fread(&customer,sl,1,fp);
                output();
            }
            printf("\n\n again ? (y/n)");
            ch=getchar();
        }while(ch == 'y');
        fclose(fp);
        break;
        case '2':
        fseek(fp, 0, SEEK_END);
        tl=ftell(fp);
        sl=sizeof(customer);
        ts=tl/sl;
        fseek(fp, (ts-1)*sl, SEEK_SET);
        fread(&customer, sizeof(customer), 1, fp);
        n=customer.number;
        do
        {
            printf("\n enter the name:  ");
            scanf("%s", nam);
            fseek(fp, 0, SEEK_SET);
            for(i=1; i<=n; i++)
            {
                fread(&customer, sizeof(customer), 1, fp);
                if(strcmp(customer.name,nam)==0)
                {
                    output();
                    m=0;
                    break;
                }
            }
            if(m!=0)
            printf("\n\n doesn't exist \n");
            printf("\n another ?? (y/n)");
            ch=getchar();
        }while(ch=='y');
        fclose(fp);
    }
    return;
}

void displayAllCustomers() 
{
    FILE *fp = fopen("file.txt", "rb");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    printf("\n=== List of All Customers ===\n");
    while (fread(&customer, sizeof(customer), 1, fp)) {
        output();
    }
    fclose(fp);
}

void deleteAllCustomers()
{
    FILE *fp = fopen("file.txt", "w");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    fclose(fp);
    printf("\nAll customer information has been deleted successfully.\n");
}

void output()
{
    printf("\n\n Customer no : %d \n", customer.number);
    printf("   Name  :%s \n", customer.name);
    printf("   Mobile no  :%.f \n", customer.mobile_no);
    printf("   Account number  : %d \n", customer.acct_no);
    printf("   Street  : %s \n",customer.street);
    printf("   City  : %s \n",customer.city);
    printf("   Old balance  :%.2f \n",customer.oldbalance);
    printf("   Current payment  :%.2f \n",customer.payment);
    printf("   New balance  :%.2f \n",customer.newbalance);
    printf("   Payment date  : %d/%d/%d \n\n",customer.lastpayment.day, customer.lastpayment.month, customer.lastpayment.year);
    printf("        Account status :");
    
    switch(customer.acct_type)
    {
        case 'C':
        printf("CURRENT \n\n");
        break;
        case 'O':
        printf("OVERDUE \n\n");
        break;
        case 'D':
        printf("DELINQUENT \n\n");
        break;
        default:
        printf("ERROR \n\n");
    }
    return ;
}