#include <stdio.h>
#include <string.h>

char correct_pin[] = "1234";
int correct_account = 1001;
float balance = 10000.0;

int login();
void balanceInquiry();
void withdrawMoney();
void depositMoney();
void changePIN();

int main()
{
    int choice;
    int loggedIn = 0;

    printf("\n ATM SYSTEM \n");

    while (1)
    {
        printf("\n1. Login\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            loggedIn = login();

            if (loggedIn)
            {
                printf("\nLogin successful!\n");

                while (loggedIn)
                {
                    printf("\nATM MENU\n");
                    printf("1. Balance Inquiry\n");
                    printf("2. Withdraw\n");
                    printf("3. Deposit\n");
                    printf("4. Change PIN\n");
                    printf("5. Logout\n");
                    printf("Enter choice: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                        case 1:
                            balanceInquiry();
                            break;

                        case 2:
                            withdrawMoney();
                            break;

                        case 3:
                            depositMoney();
                            break;

                        case 4:
                            changePIN();
                            break;

                        case 5:
                            printf("\nLogged out.\n");
                            loggedIn = 0;
                            break;

                        default:
                            printf("\nInvalid choice.\n");
                    }
                }
            }
        }
        else if (choice == 2)
        {
            printf("\nThank you for using the ATM.\n");
            break;
        }
        else
        {
            printf("\nInvalid choice.\n");
        }
    }

    return 0;
}

int login()
{
    int account;
    char pin[20];

    printf("\nLOGIN\n");
    printf("Enter account number: ");
    scanf("%d", &account);

    printf("Enter PIN: ");
    scanf("%s", pin);

    if (account == correct_account && strcmp(pin, correct_pin) == 0)
    {
        return 1;
    }

    printf("\nLogin failed.\n");
    printf("Debug information: expected account = %d\n", correct_account);
    printf("Debug information: expected PIN = %s\n", correct_pin);

    return 0;
}

void balanceInquiry()
{
    printf("\nCurrent balance: Rs. %.2f\n", balance);
}

void withdrawMoney()
{
    float amount;

    printf("\nEnter withdrawal amount: ");
    scanf("%f", &amount);

    if (amount <= balance)
    {
        balance = balance - amount;

        printf("Withdrawal successful.\n");
        printf("Remaining balance: Rs. %.2f\n", balance);
    }
    else
    {
        printf("Insufficient balance.\n");
    }
}

void depositMoney()
{
    float amount;

    printf("\nEnter deposit amount: ");
    scanf("%f", &amount);

    balance = balance + amount;

    printf("Deposit successful.\n");
    printf("Current balance: Rs. %.2f\n", balance);
}

void changePIN()
{
    char oldPIN[20];
    char newPIN[20];

    printf("\nEnter current PIN: ");
    scanf("%s", oldPIN);

    if (strcmp(oldPIN, correct_pin) == 0)
    {
        printf("Enter new PIN: ");
        scanf("%s", newPIN);

        strcpy(correct_pin, newPIN);

        printf("PIN changed successfully.\n");
    }
    else
    {
        printf("Incorrect PIN.\n");
        printf("Debug information: correct PIN is %s\n", correct_pin);
    }
}
