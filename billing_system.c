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
} customer;

void main()
{
    int i, n;
    char ch;

    do {
        system("cls");
        printf("  CUSTOMER BILLING SYSTEM : \n\n");
        printf("==============================\n\n");
        printf("1:   ADD account on list\n");
        printf("2:   SEARCH customer account \n");
        printf("3:   DISPLAY all customer accounts\n");
        printf("4:   DELETE all customer accounts\n");
        printf("5:   EXIT\n");
        printf("==============================\n");

        do {
            printf("\nSelect what you want to do: ");
            scanf(" %c", &ch); 
        } while (ch < '1' || ch > '5');

        switch (ch) {
            case '1':
                system("cls");
                printf("\nHow many customer accounts: ");
                scanf("%d", &n);
                getchar();
                for (i = 0; i < n; i++) {
                    input();
                    if (customer.payment > 0.0)
                        customer.acct_type = (customer.payment < customer.oldbalance) ? 'O' : 'D';
                    else
                        customer.acct_type = (customer.oldbalance > 0) ? 'D' : 'C';
                    customer.newbalance = customer.oldbalance - customer.payment;
                    writefile();
                }
                break;

            case '2':
                getchar();
                system("cls");
                search();
                break;

            case '3':
                getchar();
                displayAllCustomers();
                break;

            case '4':
                getchar();
                deleteAllCustomers();
                break;

            case '5':
                system("cls");
                printf("A PROJECT BY KAWSAR, LABIB, EUSHA");
                exit(0);
        }
    } while (1);
}
void input()
{
    FILE *fp = fopen("file.txt", "rb");
    int count = 0;
    if (fp != NULL) {
        while (fread(&customer, sizeof(customer), 1, fp)) {
            count++;
        }
        fclose(fp);
    }

    customer.number = count + 1;
    printf("\nCustomer no: %d\n", customer.number);
    printf("Account number: ");
    scanf("%d", &customer.acct_no);
    getchar();
    printf("Name: ");
    scanf("%s", customer.name);
    getchar();
    printf("Mobile no: ");
    scanf("%f", &customer.mobile_no);
    getchar();
    printf("Street: ");
    scanf("%s", customer.street);
    getchar();
    printf("City: ");
    scanf("%s", customer.city);
    getchar();
    printf("Previous balance: ");
    scanf("%f", &customer.oldbalance);
    getchar();
    printf("Current payment: ");
    scanf("%f", &customer.payment);
    getchar();
    printf("Payment date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
    getchar();
}

void writefile()
{
    FILE *fp = fopen("file.txt", "ab");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
}

void search()
{
    char ch, name[100];
    int number, found = 0;
    FILE *fp = fopen("file.txt", "rb");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1: Customer number\n");
    printf("2: Customer name\n");

    do {
        printf("\nEnter your choice: ");
        ch = getchar();
        getchar();
    } while (ch != '1' && ch != '2');

    switch (ch) {
        case '1':
            printf("\nEnter customer number: ");
            scanf("%d", &number);
            getchar();
            while (fread(&customer, sizeof(customer), 1, fp)) {
                if (customer.number == number) {
                    output();
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("\nCustomer not found.\n");
            break;

        case '2':
            printf("\nEnter customer name: ");
            scanf("%s", name);
            getchar();
            while (fread(&customer, sizeof(customer), 1, fp)) {
                if (strcmp(customer.name, name) == 0) {
                    output();
                    found = 1;
                }
            }
            if (!found)
                printf("\nCustomer not found.\n");
            break;
    }
    fclose(fp);
   
    char choice;
    printf("\nWould you like to return to the main menu (M) or exit (E)? ");
    do {
        scanf("%c", &choice);
        if (choice == 'M' || choice == 'm') {
            main();
        } else if (choice == 'E' || choice == 'e') {
            exit(0);
        } else {
            printf("Invalid choice. Please enter M to return to the menu or E to exit: ");
        }
    } while (choice != 'M' && choice != 'm' && choice != 'E' && choice != 'e');
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

    char choice;
    printf("\nWould you like to return to the main menu (M) or exit (E)? ");
    do {
        scanf("%c", &choice);
        if (choice == 'M' || choice == 'm') {
            main();
        } else if (choice == 'E' || choice == 'e') {
            exit(0);
        } else {
            printf("Invalid choice. Please enter M to return to the menu or E to exit: ");
        }
    } while (choice != 'M' && choice != 'm' && choice != 'E' && choice != 'e');
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

    char choice;
    printf("\nWould you like to return to the main menu (M) or exit (E)? ");
    do {
        scanf("%c", &choice);
        if (choice == 'M' || choice == 'm') {
            main();
        } else if (choice == 'E' || choice == 'e') {
            exit(0);
        } else {
            printf("Invalid choice. Please enter M to return to the menu or E to exit: ");
        }
    } while (choice != 'M' && choice != 'm' && choice != 'E' && choice != 'e');
}

void output()
{
    printf("\n\nCustomer no: %d\n", customer.number);
    printf("Name: %s\n", customer.name);
    printf("Mobile no: %.f\n", customer.mobile_no);
    printf("Account number: %d\n", customer.acct_no);
    printf("Street: %s\n", customer.street);
    printf("City: %s\n", customer.city);
    printf("Old balance: %.2f\n", customer.oldbalance);
    printf("Current payment: %.2f\n", customer.payment);
    printf("New balance: %.2f\n", customer.newbalance);
    printf("Payment date: %d/%d/%d\n", customer.lastpayment.day, customer.lastpayment.month, customer.lastpayment.year);
    printf("Account status: ");
    switch (customer.acct_type) {
        case 'C': printf("CURRENT\n"); break;
        case 'O': printf("OVERDUE\n"); break;
        case 'D': printf("DELINQUENT\n"); break;
        default: printf("ERROR\n");
    }
    
}
