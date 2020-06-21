
#include<stdio.h>
int printSell(int value, int product, int numPro[], int pPrice[]){
    char status[3] = {' ', 'O','X'};
    int sNum[6] = {0, 0, 0, 0, 0, 0};
    char pro[6] = {'=', 'A', 'B', 'C', 'D', 'E'};
    printf("*---------------------------*\n");
    printf("|      Vending Machine      |\n");
    printf("*---------------------------*\n");
    printf("|   A    B    C    D    E   |\n");
    printf("|  $%d  $ %d  $ %d  $ %d  $ %d  |\n",pPrice[0], pPrice[1], pPrice[2], pPrice[3], pPrice[4]);
        for(int i = 1; i <= 5; i++){
            if (value < pPrice[i-1])
                sNum[i] = 0;
            else if (numPro[i] > 0 && value >= pPrice[i-1])
                sNum[i] = 1;
            if (numPro[i] == 0)
                sNum[i] = 2;
        }
    printf("|  [%c]  [%c]  [%c]  [%c]  [%c]  |\n", status[sNum[1]], status[sNum[2]], status[sNum[3]], status[sNum[4]], status[sNum[5]]);
    printf("*---------------------------*\n");
    printf("|                    [$%2d]  |\n", value);
    printf("|                           |\n");
    if (product == -1)
        product = 0;
    printf("|           [=%c=]           |\n", pro[product]);
    printf("*---------------------------*\n");
    return value;
}

int askChoice(){
    int fChoice = -1;
    printf("\nWhat would you like to do?\n1. Read product information\n2. Insert coin\n3. Press product button\n4. Press return button\n9. Open service menu (code required)\n0. Quit\nYour choice:");
    scanf("%d", &fChoice);

    while(!(fChoice >= 0 && fChoice <= 4) && fChoice != 9){
        printf("Invalid choice!\n\n");
        printf("What would you like to do?\n1. Read product information\n2. Insert coin\n3. Press product button\n4. Press return button\n9. Open service menu (code required)\n0. Quit\nYour choice:");
        scanf("%d", &fChoice);
    }
    return fChoice;
}

int askSChoice(){
    int input = -1;
    printf("\n(9) What would you like to do?\n");
    printf("1. Inspect machine status\n");
    printf("2. Withdraw all money\n");
    printf("3. Refill product\n");
    printf("4. Change product\n");
    printf("0. Go back\n");
    printf("Your choice:");
    scanf("%d", &input);
    return input;
}

int refill(){
    int p = -1;
    printf("(9-3) Which product would you like to refill?\n");
    printf("1. A\n");
    printf("2. B\n");
    printf("3. C\n");
    printf("4. D\n");
    printf("5. E\n");
    printf("0. Go back\n");
    printf("Your choice:");
    scanf("%d", &p);
    return p;
}

int change(){
    int p = -1;
    printf("(9-4) Which product would you like to change?\n");
    printf("1. A\n");
    printf("2. B\n");
    printf("3. C\n");
    printf("4. D\n");
    printf("5. E\n");
    printf("0. Go back\n");
    printf("Your choice:");
    scanf("%d", &p);
    return p;
}

int main(void){
    int choice = -1;
    int sChoice = -1;
    int input = -1;
    int value = 0;
    int product = -1;
    int price[] = {10, 6, 5 , 8, 7};
    int proLeft[] = {0, 5, 1, 2, 1, 9};
    int rProduct = -1;
    int cProduct = -1;
    int accessCode = 0;
    int revenue = 0, insertCoin = 0;
    char proName[6] = {' ', 'A', 'B', 'C', 'D', 'E'};
    char fullName[6][99] = { "\0", "Juice", "Cola", "Tea", "Water", "Coffee" };


    value = printSell(value, -1, proLeft, price);
    choice = askChoice();

    while(choice != 0){
        switch (choice) {
          
            case 1:
                printf("\n");
                printf("(1) The displayed products are:\n");
                printf("A. %s ($%d)\n",fullName[1] ,price[0]);
                printf("B. %s ($%d)\n",fullName[2] ,price[1]);
                printf("C. %s ($%d)\n",fullName[3] ,price[2]);
                printf("D. %s ($%d)\n",fullName[4] ,price[3]);
                printf("E. %s ($%d)\n",fullName[5] ,price[4]);
                choice = askChoice();
                break;
                
            case 2:
                while(1){
                    printf("\n");
                    printf("(2) Which coin would you like to insert?\n1. $1\n2. $2\n3. $5\n4. $10\n0. Go back\nYour choice:");
                    scanf("%d", &input);
                    if (input == 0){
                        printf("Going back!\n\n");
                        value = printSell(value, -1, proLeft, price);
                        choice = askChoice();
                        break;
                        
                    }else{
                      
                        if (input < 0 || input > 4){
                            printf("Invalid choice!\n");
                            break;
                        }
                        if (input == 3)
                            input = 5;
                        if (input == 4)
                            input = 10;
                        value += input;
                        printf("You have inserted $%d.\n\n", input);
                        value = printSell(value, -1, proLeft, price);
                    }
                }
                break;
                
            case 3:
                printf("\n");
                printf("(3) Which product button would you like to press?\n1. A\n2. B\n3. C\n4. D\n5. E\n0. Go back\nYour choice:");
                scanf("%d", &product);
                if (product == 0){
                    printf("Going back!\n\n");  
                    value = printSell(value, -1, proLeft, price);
                    choice = askChoice();
                    break;
                }
                if (product > 0 && product < 6){
                    if (value >= price[product-1] && proLeft[product] > 0){
                    //To sell product, revenue increase, number of product decrease
                        printf("You have pressed button %c\n", proName[product]);
                        printf("\n");
                        value -= price[product-1];
                        proLeft[product]--;
                        value = printSell(value, product, proLeft, price);
                        revenue += price[product-1];
                        choice = askChoice();
                        break;
                    }
                    else{
                        //not eunough money || not enough product
                        printf("You have pressed button %c\n\n", proName[product]);
                        value = printSell(value, 0, proLeft, price);
                        choice = askChoice();
                        break;
                    }
                    break;
                }
                if (!(product > 0 && product < 6)){
                    printf("Invalid choice!\n");
                    break;
                }
                break;
            
            case 4:
                printf("\n(4) Return button is pressed.\n");
                printf("$%d has been returned.\n\n", value);
                //printFront(0);
                value = printSell(0, -1, proLeft, price);
                choice = askChoice();
                break;
                
            case 9:
                printf("\n");
                printf("(9) Opening service menu. Access code is required.\n");
                printf("Enter access code:");
                scanf("%d", &accessCode);
                if (accessCode != 1110){
                    printf("Incorrect code!\n\n\n");
                    value = printSell(value, -1, proLeft, price);
                    choice = askChoice();
                    break;
                } else{
                    printf("Correct code!\n");
                    sChoice = askSChoice();
                    
                    while(1){
                        if (sChoice == 0){
                            printf("Going back!\n\n");
                            value = printSell(value, -1, proLeft, price);
                            choice = askChoice();
                            break;
                        }
                        if (sChoice < 0 || sChoice > 4){
                            printf("Invalid choice!\n");
                            sChoice = askSChoice();
                            break;
                        }
                        else{
                            switch (sChoice) {
                                case 1:
                                    printf("\n");
                                    printf("(9-1) Machine status\n");
                                    printf("Amount of revenue: $%d\n", revenue);
                                    printf("Amount of inserted coins: $%d\n", value);
                                    printf("Product information:\n");
                                    for (int i = 1; i <= 5; i++){
                                        if (proLeft[i] == 0)
                                            printf("%c. %s ($%d) (sold out)\n",proName[i] ,fullName[i] ,price[i-1]);
                                        else
                                            printf("%c. %s ($%d) (%d left)\n",proName[i] ,fullName[i] ,price[i-1],proLeft[i]);
                                    }
                                    sChoice = askSChoice();
                                    break;
                                    
                                case 2:
                                    printf("\n");
                                    printf("(9-2) All money is being withdrawn.\n");
                                    printf("$%d is withdrawn.\n", revenue + value);
                                    value = 0;
                                    revenue = 0;
                                    sChoice = askSChoice();
                                    break;
                                    
                                case 3:
                                    printf("\n");
                                    rProduct = refill();
                                    if (rProduct == 0){
                                        printf("Going back!\n");
                                    }
                                    else if (rProduct < 0 || rProduct > 5){
                                        printf("Invalid choice!\n");
                                        break;
                                    }
                                    else if (rProduct >=  0 && rProduct <= 5){
                                        printf("You have refilled product %c to full.\n", proName[rProduct]);
                                        proLeft[rProduct] = 10;
                                    }
                                    sChoice = askSChoice();
                                    break;
                                
                                case 4:
                                    printf("\n");
                                    cProduct = change();
                                    if (cProduct == 0){
                                        printf("Going back!\n");
                                    } else if (cProduct < 0 || cProduct > 5){
                                        printf("Invalid choice!\n");
                                        break;
                                    } else {
                                        printf("You are changing product %c.\n\n", proName[cProduct]);
                                        printf("Enter new product name:");
                                        scanf("%s", fullName[cProduct]);
                                        printf("Enter new product price:");
                                        scanf("%d", &price[cProduct-1]);
                                        proLeft[cProduct] = 10;
                                        printf("The new product %c has been filled to full.\n", proName[cProduct]);
                                    }
                                    
                                    sChoice = askSChoice();
                                    break;
                                
                            }
                        }
                    }
                }
                break;
        }
    }
    return 0;
}