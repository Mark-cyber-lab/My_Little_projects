#include "User Interface.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct products{
    int serial_number;
    int amount;
    float price;
    char product_name[31];
};

struct order{
    int serial_number, amount;
    float price, original_price;
    char name[31];
    struct order *next_order;
};

void ordering();
void print_order_or_exit();
void print_list(struct order *head, float *total_amount);
void closing_file(struct products *product, int number_of_products, int counter);
void check_out(struct order *head, float total_amount, int number_of_orders);
struct order* edit_amount(struct order *head, int *number_of_orders, struct products *product, int length, int *number_of_products);
struct order* add_order(struct order *head, struct products *product, int right, int *number_of_orders, int *number_of_products);
struct order* remove_order(struct order *head, int *number_of_orders, struct products *product, int length, int *number_of_products);
void accept_amount(struct products *product, int middle);

int main(){
    float choice;
    do{
        print_order_or_exit();
        if(scanf("%f", &choice) == 0 || (getchar()) != '\n'){
            choice = 4;
            fflush(stdin);
        }
        else if(choice != (int) choice){
            choice = 4;
        }

        switch ((int) choice){
        case 1:
            ordering();
            break;
        case 2:
            power_off();
            exit(0);
            break;
        default:
            print_invalid();
            break;
        }
    }while(choice != 1 || choice != 0);
}

void ordering(){
    FILE *store_database;

    if((store_database = fopen("Stock's record.txt", "r")) == NULL)
        file_not_found();
    else{
        int number_of_products, i;

        //Scans for the total amount of the products in the store's database
        fscanf(store_database,"%d", &number_of_products);

        //this will act as a storage that will allow for the sudden change of the number of the product in the stocks
        int temp_number_of_products = number_of_products;

        //declare the structures based on how many products are in the store's database
        struct products product[number_of_products];

        //read the whole record of the products
        for(i = 0; i < number_of_products; i++)
            fscanf(store_database,"%d %d %f %[^\n]s", &product[i].serial_number, &product[i].amount, &product[i].price, product[i].product_name);

        fclose(store_database);

        int /*This is the determinant of how many is the amount of the orders*/ number_of_orders = 0;
        float total_amount, choice;
        struct order /*This is the key for linked list*/ *head = NULL, *temp;

        //The ordering of the product
        do{
            on_the_ordering();

            total_amount = 0;   //assign the head to the temp variable so that the temp will act as a head when printing the orders

            //If there is no order/s then the output will be -empty-
            print_list(head, &total_amount);

            //Decides what will be the next case
            gotoxy(18, 14);
            if(scanf("%f", &choice) == 0 || (getchar()) != '\n'){
                choice = 6;
                fflush(stdin);
            }
            else if(choice != (int) choice){
                choice = 6;
            }

            //What will happen
            switch((int) choice){
                case 1:
                    head = add_order(head, &product[0], number_of_products - 1, &number_of_orders, &temp_number_of_products);
                    break;
                case 2:
                    if(head == NULL)
                        no_product();
                    else
                        head = remove_order(head, &number_of_orders,  &product[0], number_of_products - 1, &temp_number_of_products);
                    break;
                case 3:
                    if(head == NULL)
                        no_product();
                    else
                        head = edit_amount(head, &number_of_orders,  &product[0], number_of_products - 1, &temp_number_of_products);
                    break;
                case 4:
                    if(head == NULL)
                        no_product();
                    else{
                        do{
                            check_out_confirmation();
                            if(scanf("%f", &choice) == 0 || (getchar()) != '\n')
                                fflush(stdin);
                            else if((choice == (int) choice) && (choice == 1 || choice == 0))
                                break;
                            
                            print_invalid();
                        }while(1);

                        if(choice == 1){
                            check_out(head, total_amount, number_of_orders);     //Finalize the order
                            closing_file(&product[0], temp_number_of_products, number_of_products); //will record the changes in the product as the new record
                            return;
                        }
                    }
                    break;
                case 5:
                    order_cancelled();
                    return;
                default:
                    print_invalid();
                    break;
            }
        }while(1);
    }
}

void closing_file(struct products *product, int number_of_products, int counter){
    int i;
    FILE *store_database = fopen("Stock's record.txt","w"); //will rewrite the record of the stocks database

    fprintf(store_database,"%d", number_of_products);   //will print the new number of quantity of the product

    for(i = 0; i < counter; i++){    //printing products
        if((product + i)->amount == 0)  //if the amount of a certain product is zero then the product is considered face out
            continue;   //will skip the printing of the product that is face out

        fprintf(store_database,"\n%d %d %.2f %s", (product + i)->serial_number, (product + i)->amount, (product + i)->price, (product + i)->product_name);  //prints the product
    }
    fclose(store_database); //closing the file
}

struct order* add_order(struct order *head, struct products *product, int right, int *number_of_orders, int *number_of_products){
    float serial_number;  //used for searching a certain product using its serial number
    bool found = false, same = false;   //used as a gear of the function
    struct order *temp = head;  //this will enable to access the contents of the linked list
    int left = 0, middle = right / 2;   //used for binary search

    do{
        add_product(); //asks for the serial number of the product that will be ordered
        
        if(scanf("%f", &serial_number) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else if(serial_number != (int) serial_number){
            print_invalid();
        }
        else
            break;
    }while(1);

    while(temp != NULL){    //will activate if there's already been a linked list
        if(serial_number == temp->serial_number){   //will find the same serial number in the list if the product has already been in the list of the orders
            same = true;
            break;
        }
        temp = temp->next_order;
    }

    if(same == true)   //if the product is already in the list
        product_already_exist();
    else{
        while(middle <= right && middle >= 0 && left <= right){ //binary ssearch
            if(serial_number == (product + middle)->serial_number){
                found = true;
                break;
            }
            else if(serial_number < (product + middle)->serial_number){
                right = middle - 1;
                middle = (left + right) / 2;
            }
            else if(serial_number > (product + middle)->serial_number){
                left = middle + 1;
                middle = (left + right) / 2;
            }
        }

        if(found == false)
            product_not_found();
        else{
            struct order *new_order = (struct order*) malloc(sizeof(struct order)); //will declare a struct dynamically
            float damn;

            do{
                accept_amount(product, middle);  //will ask the amount of the product that will be ordered

                if(scanf("%f", &damn) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                }
                else if(damn != (int) damn)
                    print_invalid();
                else if((int) damn <= (product + middle)->amount){    //these will determine if the amount surpasses the amount of the product in the stocks
                    (product + middle)->amount -= (int) damn;
                    left = (int) damn;
                    break;
                }
                else
                    exceed();
            }while(1);

           if(left != 0){
                new_order->serial_number = (product + middle)->serial_number;   //assign the info of the product in the structure
                strcpy(new_order->name, (product + middle)->product_name);
                new_order->amount = left;
                new_order->original_price = (product + middle)->price;  //the uncalculated price
                new_order->price = (product + middle)->price * (float) left;   //the calculated price


                if(head == NULL){   //if there is no existing linked list
                    new_order->next_order = head;
                    head = new_order;
                }
                else{      //if there is already an existing one
                    temp = head;

                    while(temp->next_order != NULL)
                        temp = temp->next_order;

                    new_order->next_order = temp->next_order;
                    temp->next_order = new_order;

                }

                if((product + middle)->amount == 0) //if the product's amount is zero then the number of product will be decremented because the user has ordered the entirety of the product making it a faced out product
                    *number_of_products -= 1;

                *number_of_orders += 1; //increments the quantity of the orders
            }
        }
    }
    return head;    //returns the linked list

}

void accept_amount(struct products *product, int middle){
    input_box();
    gotoxy(72, 10);
    color(3);
    printf("Add Product");
    color(2);
    gotoxy(57, 16);
    printf("Enter Quantity:");
    gotoxy(59, 14);
    printf("Product Name: ");
    color(7);
    printf("%s", (product + middle)->product_name);
    gotoxy(73, 16);

}

struct order* remove_order(struct order *head, int *number_of_orders, struct products *product, int right, int *number_of_products){
    float choice;

    do{
        remove_product();  //will ask the number of the product  you want to delete

        if(scanf("%f", &choice) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else if(choice != (int) choice || (choice < 1 || choice > *number_of_orders)){
            print_invalid();
        }
        else
            break;
    }while(1);   //will activate if the user input is out of bounds

    struct order *temp = head, *temp2 = NULL;   //serves as the gear for removing the certain product

    int i;

    for(i = 1; i < choice; i++){    //will loop in a certain amount
        temp2 = temp;
        temp = temp->next_order;
    }

    if(temp2 == NULL) //if temp2 is NULL then that means that the chosen is the first product on the list
        head = temp->next_order;
    else       //The product is chosen somewhere in the list except for the first
        temp2->next_order = temp->next_order;

    int left = 0, middle = right / 2;   //gears for binary search

    while(middle <= right && middle >= 0 && left <= right){ //binary search
        if(temp->serial_number == (product + middle)->serial_number)
            break;
        else if(temp->serial_number < (product + middle)->serial_number){
            right = middle - 1;
            middle = (left + right) / 2;
        }
        else if(temp->serial_number > (product + middle)->serial_number){
            left = middle + 1;
            middle = (left + right) / 2;
        }
    }

    if((product + middle)->amount == 0) //if the product's amount is zero then the number of product will be incremented because the user has ordered to remove a certain product
        *number_of_products += 1;

    (product + middle)->amount += temp->amount; // the order amount of a certain product will be added to the product amount in the stocks

    free(temp); //freeing a product that is chosen to be removed in the linked list

    *number_of_orders -= 1; //the quantity of the orders will be decremented

    successfully_removed();

    return head;    //returns the linked list
}

struct order* edit_amount(struct order *head, int *number_of_orders, struct products *product, int right, int *number_of_products){
    float choice, new_amoount;

    do{
        edit_quantity();    //asks for the placement of the product in the list

        if(scanf("%f", &choice) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else if(choice != (int) choice || (choice < 1 || choice > *number_of_orders)){
            print_invalid();
        }
        else
            break;
    }while(1);   //will execute if the user input is out of bounds

    struct order *temp = head, *temp2 = NULL;  //for the accessing the contents of the linked list

    int i; //the gear and the new amount

    for(i = 1; i < choice; i++){    //will loop in order to arrive at the certain destination
        temp2 = temp;
        temp = temp->next_order;
    }

    int left = 0, middle = right / 2;   //for the binary search

    while(middle <= right && middle >= 0 && left <= right){ //binary search
        if(temp->serial_number == (product + middle)->serial_number)
            break;
        else if(temp->serial_number < (product + middle)->serial_number){
            right = middle - 1;
            middle = (left + right) / 2;
        }
        else if(temp->serial_number > (product + middle)->serial_number){
            left = middle + 1;
            middle = (left + right) / 2;
        }
    }

    do{
        input_box();
        gotoxy(71, 10);
        color(3);
        printf("Edit Quantity");
        gotoxy(65, 13);
        color(2);
        printf("Product:");
        gotoxy(56, 15);
        printf("Current quantity:");
        gotoxy(54, 17);
        printf("Enter new quantity:");
        color(7);
        gotoxy(74, 13);
        printf("%s", temp->name);
        gotoxy(74, 15);
        printf("%d", temp->amount);
        gotoxy(74, 17); //asks for the new amount
        
        if(scanf("%f", &new_amoount) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else if(new_amoount != (int) new_amoount){
            print_invalid();
        }
        else if((product + middle)->amount + temp->amount >= new_amoount)    //determines if the amount doesn't surpass the amount of a product in the stocks and the current amount combined
            break;
        else
            exceed();
    }while(1);

    (product + middle)->amount += temp->amount - (int) new_amoount;   //will aither add or subtract to the amount of a product in the stocks
    temp->amount =(int) new_amoount;
    temp->price = temp->original_price * temp->amount;

    if(temp->amount == 0){
        if(temp2 == NULL)
            head = temp->next_order;
        else
            temp2->next_order = temp->next_order;

        free(temp);
        *number_of_orders -= 1;
    }

    if((product + middle)->amount == 0) //if the amount of the product in the stocks is zero then the number of products in the stocks will be decremented
        *number_of_products -= 1;

    return head;    //returns the linked list

}

void check_out(struct order *head, float total_amount, int number_of_orders){
    float cash; //needed for the cash
    struct order *temp = head;  //needed for accessing the contents of the linked list
    time_t right_now = time(NULL);
    struct tm *time_right_now = localtime(&right_now);

    do{
        input_box();
        gotoxy(73, 10);
        color(3);
        printf("Check out");
        gotoxy(64, 14);
        color(2);
        printf("Total amount:");
        gotoxy(66, 16);
        printf("Enter cash:");
        gotoxy(78, 14);
        color(7);
        printf("%.2f", total_amount);
        gotoxy(78, 16); //asks for the cash
        
        if(scanf("%f", &cash) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else
            break;
    }while(1);

    int quantity = 0, i = 16;   //the quantity of the product ordered
    gotoxy(34, 9);
    color(8);
    printf("+=====================================================================================+");
    gotoxy(34, 10);
    printf("|                                      ");
    color(3);
    printf(" Receipt");
    color(8);
    printf("                                       |");
    gotoxy(34, 11);
    printf("+=====================================================================================+");
    gotoxy(34, 12);
    printf("|    ");
    color(2);
    printf("   Date:                                                   Time:                 ");
    color(8);
    printf("|");
    gotoxy(34, 13);
    printf("|                                                                                     |");
    gotoxy(43, 13);
    color(7);
    printf("     %02d/%02d/%02d", time_right_now->tm_mon + 1, time_right_now->tm_mday, time_right_now->tm_year + 1900);
    gotoxy(94, 13);
    
    if(time_right_now->tm_hour > 12)
        time_right_now->tm_hour -= 12;

    printf("          %02d:%02d:%02d", time_right_now->tm_hour, time_right_now->tm_min, time_right_now->tm_sec);
    color(8);
    gotoxy(34, 14);
    printf("|                                                                                     |");
    gotoxy(34, 15);
    printf("|    ");
    color(2);
    printf(" Item/s:                                                                         ");
    color(8);
    printf("|");
    

    while(temp != NULL){    //prints the orders and its info that is contained in the linked list
        gotoxy(34, i);
        color(8);
        printf("|                                                                                     |");
        gotoxy(48, i);
        color(7);
        printf("%s", temp->name);
        i++;
        gotoxy(34, i);
        color(8);
        printf("|                                                                                     |");
        gotoxy(52, i);
        color(7);
        printf("         %4d               %7.2f               %7.2f", temp->amount, temp->original_price, temp->price);
        i++;
        quantity += temp->amount;   //adds the amount of the ordered product
        temp = temp->next_order;
    }
    color(8);
    gotoxy(34, i);
    printf("|                                                                                     |");
    gotoxy(34, i + 1);
    printf("+=====================================================================================+");
    gotoxy(34, i + 2);
    printf("|                                                                                     |");
    gotoxy(40, i + 2);
    color(2);
    printf("Quantity: ");
    color(7);
    printf("%d",quantity);    //prints the quantity of the orders
    color(8);
    gotoxy(34, i + 3);
    printf("|                                                           ");
    color(2);
    printf("Total:                    ");
    color(8);
    printf("|");
    gotoxy(104, i + 3);
    color(7);
    printf("%7.2f",total_amount);
    gotoxy(34, i + 4);
    color(8);
    printf("|                                                            ");
    color(2);
    printf("Cash:                    ");
    color(8);
    printf("|");
    gotoxy(104, i + 4);
    color(7);
    printf("%7.2f", cash);
    color(8);
    gotoxy(34, i + 5);
    printf("|                                                          ");
    color(2);
    printf("Change:                    ");
    color(8);
    printf("|");
    gotoxy(104, i + 5);
    color(7);
    printf("%7.2f", cash - total_amount);//prints the transaction
    gotoxy(34, i + 6);
    color(8);
    printf("|                                                                                     |");
    gotoxy(34, i + 7);
    printf("+=====================================================================================+");
    gotoxy(79, i + 12);
    getch();

    float print;

    do{
        receipt();

        if(scanf("%f", &print) == 0 || (getchar()) != '\n'){
            print_invalid();
            fflush(stdin);
        }
        else if(print != (int) print || (print != 1 && print != 0)){
            print_invalid();
        }
        else
            break;
    }while(1);

    finishing_remarks();

    if(print == 1){
        temp = head;

        FILE *receipt = fopen("Receipt.txt", "w");
        quantity = 0;   //the quantity of the product ordered
        fprintf(receipt,"=======================================================================================\n");
        fprintf(receipt,"                                        Receipt                                        \n");
        fprintf(receipt,"=======================================================================================\n");
        if(time_right_now->tm_hour > 12)
            time_right_now->tm_hour -= 12;

        fprintf(receipt,"       Date:                                                      Time:\n             %02d/%02d/%02d                                                 %02d:%02d:%02d\n\n", time_right_now->tm_mon + 1, time_right_now->tm_mday, time_right_now->tm_year + 1900, time_right_now->tm_hour, time_right_now->tm_min, time_right_now->tm_sec);
        fprintf(receipt,"      Items:                                                                           \n");
        while(temp != NULL){    //prints the orders and its info that is contained in the linked list
            fprintf(receipt,"             %s\n", temp->name);
            fprintf(receipt,"                      %4d               %7.2f               %7.2f\n", temp->amount, temp->original_price, temp->price);
            quantity += temp->amount;   //adds the amount of the ordered product
            temp = temp->next_order;
        }
        fprintf(receipt,"\n\n=======================================================================================\n");
        fprintf(receipt,"  Quantity: %d\n",quantity);    //prints the quantity of the orders
        fprintf(receipt,"                                                            Total: ");
        fprintf(receipt,"%7.2f\n",total_amount);
        fprintf(receipt,"                                                             Cash: ");
        fprintf(receipt,"%7.2f\n", cash);
        fprintf(receipt,"                                                           Change: ");
        fprintf(receipt,"%7.2f\n", cash - total_amount);//prints the transaction
        fprintf(receipt,"=======================================================================================");
        fclose(receipt);
    }
}

void print_list(struct order *head, float *total_amount){
    int i = 1, y = 9;
    color(7);
    if(head == NULL){
        gotoxy(95, y + i);
        printf("-Empty-");
    }

    //if theres an order then it will print the current orders
    while(head != NULL){
        gotoxy(35, y + i);
        printf("[%02d]                     %7.2f                      %4d                  %7.2f                 %s", i, head->original_price, head->amount, head->price, head->name);
        *total_amount += head->price;   //The next node will be assigned to current node
        head = head->next_order;    //this process serve as moving forward
        i++;
    }
    gotoxy(90, y + i + 2);
    color(8);
    printf("Total amount: ");
    color(7);
    printf("%.2f", *total_amount);
}

void print_order_or_exit(){
    clear
    color(2);
    printf("\n\n\n\n+                                                           +==========================================+                                                     +");
    printf("\n                                                            |                  ");
    color(3);
    printf("Cashier                 ");
    color(2);
    printf("|");
    printf("\n                                                            +------------------------------------------+");
    printf("\n                                                            |                                          |");
    printf("\n                                                            |                ");
    color(8);
    printf("[1] Order                 ");
    color(2);
    printf("|");
    printf("\n                                                            |                ");
    color(8);
    printf("[2] Exit                  ");
    color(2);
    printf("|");
    printf("\n                                                            |                                          |");
    printf("\n                                                            +==========================================+");
    color(7);
    printf("\n\n                                                                           Enter here: ");
}