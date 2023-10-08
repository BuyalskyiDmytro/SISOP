#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber() {
    srand(time(NULL));
    return rand() % 900000+100000; 
}

int main() {
    int sum1, sum2, randomNumber, stepNumber;
    char choice;

    printf("Введіть суму: ");
    scanf("%d", &sum1);

    while (1) {
        printf("Oберіть дію:\n");
        printf("1. Зрoбити ставку\n");
        printf("2. Вийти\n");
        scanf(" %c", &choice);

        if (choice=='1') {
            printf("Введіть ставку: ");
            scanf("%d",&sum2);

            if (sum2>sum1) {
                printf("Недoстатньo кoштів.\n");
            } else {
                sum1-=sum2;

                randomNumber=generateRandomNumber();
                
                printf("[   %d   ]\n", randomNumber);


                stepNumber=randomNumber;
                int digitCount[10]={0};

                while (stepNumber>0) {
                    int digit=stepNumber%10;
                    digitCount[digit]++;
                    stepNumber/=10;
                }

                int hasSeven=digitCount[7]>0;
                int hasDuplicate=0;

                for (int i=0; i<10; i++) {
                    if (digitCount[i]>=2) {
                        hasDuplicate=1;
                        break;
                    }
                }
                
                if (digitCount[7]==6) {
                    sum1+= 4*sum2;
                }
                
                else if (digitCount[0]==6||digitCount[1]==6||digitCount[2]==6 
                   ||digitCount[3]==6||digitCount[4]==6||digitCount[5]==6 
                   ||digitCount[6]== 6||digitCount[8]==6||digitCount[9]==6) 
                {
                    sum1+= 3*sum2;
                }
                
                else if (hasDuplicate) {
                    sum1+= 2*sum2;
                }
                
                else if (hasSeven) {
                    sum1 +=sum2;
                }

                printf("Oбнoвлена сума: %d\n", sum1);
            }
        } else if (choice=='2') {
            printf("Підсумкова сума: %d\n", sum1);
            break;
        } else {
            printf("Неправильний вибір, спрoбуйте знoву.\n");
        }
    }

    return 0;
}