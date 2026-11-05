#include <stdio.h>

int main(void)
{
    int balance = 11000;
    int choice;
    int amount;
    int pin = 1234;
    int newpin;
    int entered;
    int attempts = 0;
    FILE *pin_file = fopen("atm_pin.txt", "r");

    if (pin_file != NULL) {
        if (fscanf(pin_file, "%d", &pin) != 1 || pin < 0 || pin > 9999) {
            fclose(pin_file);
            printf("Could not read a valid PIN from atm_pin.txt.\n");
            return 1;
        }

        fclose(pin_file);
    }

    while (attempts < 3) {
        printf("Enter PIN: ");
        scanf("%d", &entered);

        if (entered == pin) {
            printf("Access granted.\n");
            break;
        }

        printf("Incorrect PIN! Try again.\n");
        attempts++;
        if (attempts >= 3) {
            printf("Card blocked!\n");
            return 0;
        }
    }

    do {
        printf("\n--- ATM MENU ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Change PIN\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Balance: %d\n", balance);
        } else if (choice == 2) {
            printf("Enter deposit amount: ");
            scanf("%d", &amount);
            balance += amount;
            printf("Deposit successful. New balance: %d\n", balance);
        } else if (choice == 3) {
            printf("Enter withdrawal amount: ");
            scanf("%d", &amount);

            if (amount > balance || amount <= 0) {
                printf("Insufficient funds or invalid amount.\n");
            } else {
                balance -= amount;
                printf("Withdrawal successful. New balance: %d\n", balance);
            }
        } else if (choice == 4) {
            printf("Enter current PIN: ");
            scanf("%d", &entered);

            if (entered == pin) {
                printf("Enter new PIN: ");
                scanf("%d", &newpin);

                if (newpin < 0 || newpin > 9999) {
                    printf("PIN must be no more than 4 digits.\n");
                } else {
                    pin_file = fopen("atm_pin.txt", "w");
                    if (pin_file == NULL) {
                        printf("Could not save the new PIN.\n");
                    } else {
                        int save_failed = fprintf(pin_file, "%d\n", newpin) < 0;

                        if (fclose(pin_file) != 0) {
                            save_failed = 1;
                        }

                        if (save_failed) {
                            printf("Could not save the new PIN.\n");
                        } else {
                            pin = newpin;
                            printf("PIN changed successfully.\n");
                        }
                    }
                }
            } else {
                printf("Incorrect current PIN! Cannot change PIN.\n");
            }
        } else if (choice == 5) {
            printf("Exiting... Thank you!\n");
        } else {
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
