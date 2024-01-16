#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "SysNo.h"

struct product{
    int serial_number_of_product;
    char name_of_product[30];
    int amount_of_product;
    float product_price;
};

//Outputs the screen
void output_screen();

//The gear programs
void See_stocks();
void Add_product();
void Remove_product();
void Update_product();
void sort_product();

//Sub programs
int update_info(struct product *products, float choice);
void quicksort(struct product *pointer_to_array_struct, int left, int right);
int partition(struct product *pointer_to_array_struct, int left, int right);

int main(){
    float choice;
    bool disaster;

    do{
        //This will make sure that the input that will be accepted will be integer only
        do{
            disaster = false;
            output_screen();

            if(((scanf("%f", &choice)) == 0 || (getchar()) != '\n')){
                print_invalid();
                disaster = true;
                fflush(stdin);
            }
            else if(choice != (int) choice){
                print_invalid();
                disaster = true;
            }
        }while(disaster == true);

        switch ((int) choice){
            case 1:
                See_stocks();
                break;
            case 2:
                Add_product();
                sort_product();
                break;
            case 3:
                Remove_product();
                break;
            case 4:
                Update_product();
                break;
            case 5:
                poweroff();
                break;
            default:
                print_invalid();
                break;
        }
    }while(1);
}

void output_screen(){
    clear
    color(3);
    printf("\n                                                                                         Product Stocks\n");
    color(2);
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                                                                                                                  |\n");
    printf("|                                                                                             ");
    color(3);
    printf("Menu                                                                                 ");
    color(2);
    printf("|\n");
    printf("|                                                                                                                                                                                  |\n");
    printf("|                                                                                      ");
    color(7);
    printf("[1] See products                                                                            ");
    color(2);
    printf("|\n");
    printf("|                                                                                      ");
    color(7);
    printf("[2] Add products                                                                            ");
    color(2);
    printf("|\n");
    printf("|                                                                                      ");
    color(7);
    printf("[3] Remove products                                                                         ");
    color(2);
    printf("|\n");
    printf("|                                                                                      ");
    color(7);
    printf("[4] Update products                                                                         ");
    color(2);
    printf("|\n");
    printf("|                                                                                      ");
    color(7);
    printf("[5] Exit                                                                                    ");
    color(2);
    printf("|\n");
    printf("|                                                                                                                                                                                  |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("\n\n\n                                                                                         ");
    color(7);
    printf("Enter Here: ");
}

void See_stocks(){

    collect_data();
    clear
    FILE *record_of_stock;

    if((record_of_stock = fopen("Stock's record.txt" , "r")) == NULL)
        output_no_record();
    else{
        int i, number_of_existing_product;
        color(7);
        printf("\n                                                                                             Stocks\n");
        color(2);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        color(3);
        printf("                        Serial Number                 ");
        color(2);
        printf("|");
        color(3);
        printf("                  Amount                 ");
        color(2);
        printf("|               ");
        color(3);
        printf("price             ");
        color(2);
        printf("|           ");
        color(3);
        printf("Name of product\n");
        color(2);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        //acquire the exact number of the product
        fscanf(record_of_stock,"%d",&number_of_existing_product);

        if(number_of_existing_product == 0){
            color(7);
            printf("\n\n\n\n\n                                                                                             -Empty-");
            color(2);
        }

        //declare a struct variable that has the same amount of the products in the stocks
        struct product product_stocks;


        //Acquire the data of the record of the stocks
        for(i = 0; i < number_of_existing_product; i++){
            fscanf(record_of_stock,"%d %d %f %[^\n]s", &product_stocks.serial_number_of_product, &product_stocks.amount_of_product, &product_stocks.product_price, product_stocks.name_of_product);
            color(7);
            printf("                                      %15d ", product_stocks.serial_number_of_product);
            color(2);
            printf("|                         ");
            color(7);
            printf("%15d ",product_stocks.amount_of_product);
            color(2);
            printf("|");
            color(7);
            printf("                   %13.2f ", product_stocks.product_price);
            color(2);
            printf("|           ");
            color(7);
            if((strlen(product_stocks.name_of_product)) < 15)
                printf("%s\n", product_stocks.name_of_product);
            else{
                for(int j = 0; j < 15; j++)
                    printf("%c", product_stocks.name_of_product[j]);

                printf("...\n");
            }
            color(2);
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }

        //closes the file variable
        fclose(record_of_stock);
        printf("\n\n\nPress any key to continue...");
        getch();
    }
}

void Add_product(){
    clear
    FILE *stock;

    //important variables
    int number_of_product = 0, i;
    double serial_number, product_amount, product_price;
    char name[31];
    bool exist = false, disaster;

    //prompt's the user
    do{
        disaster = false;
        input_box();
        gotoxy(91, 5);
        color(3);
        printf("New Product");
        gotoxy(88, 8);
        color(8);
        printf("Enter the following");
        gotoxy(67, 10);
        printf("Enter the serial number: ");
        color(7);

        if((scanf("%lf", &serial_number)) == 0 || (getchar()) != '\n'){
            print_invalid();
            disaster = true;
            fflush(stdin);
        }
        else if(serial_number != (int) serial_number){
            print_invalid();
            disaster = true;
        }
        else{
            int receive = confirmation();
            if(receive == 2)
                disaster = true;
            else if(receive == 3){
                cancelled_operation();
                return;
            }
        }
    }while(disaster == true);

    //if tru then get the exact number of the product
    if((stock = fopen("Stock's record.txt" , "r")) != NULL)
        fscanf(stock,"%d", &number_of_product);
    else if(stock == NULL)
        number_of_product = 0;


        //Declare the receiver of the product
        struct product products[number_of_product];

        //access and compare existing product to the added ones
        for(i = 0; i < number_of_product; i++){
            fscanf(stock,"%d %d %f %[^\n]s", &products[i].serial_number_of_product, &products[i].amount_of_product, &products[i].product_price, products[i].name_of_product);

            if((int) serial_number == products[i].serial_number_of_product){
                dialogue_box();
                gotoxy(87, 5);
                color(3);
                printf("Product already exist!");
                gotoxy(83, 15);
                color(2);
                printf("Press any key to continue");
                gotoxy(81, 9);
                color(8);
                printf("Serial Number: ");
                gotoxy(88, 10);
                printf("Amount: ");
                gotoxy(89, 11);
                printf("Price: ");
                gotoxy(82, 12);
                printf("Product name: ");
                gotoxy(96, 9);
                color(7);
                printf("%d", products[i].serial_number_of_product);
                gotoxy(96, 10);
                printf("%d", products[i].amount_of_product);
                gotoxy(96, 11);
                printf("%.2f", products[i].product_price);
                gotoxy(96, 12);
                printf("%s", products[i].name_of_product);
                gotoxy(96, 20);
                getch();
                clear
                exist = true;
                break;

            }
        }
        fclose(stock);

    //decides wether the product will be appended to the record or not
    if(exist == true)
        return;
    else{
        do{
            disaster = false;
            input_box();
            gotoxy(91, 5);
            color(3);
            printf("New Product");
            gotoxy(88, 8);
            color(8);
            printf("Enter the following");
            gotoxy(67, 10);
            color(8);
            printf("Enter the serial number: ");
            color(7);
            printf("%d", (int) serial_number);
            gotoxy(56, 12);
            color(8);
            printf("Enter the name(30 characters only): ");
            color(7);
            scanf(" %30[^\n]s", name);

            if((getchar() != '\n'))
                disaster = buffer_overload();
            else{
                int receive = confirmation();
                if(receive == 2)
                    disaster = true;
                else if(receive == 3){
                    cancelled_operation();
                    return;
                }
            }
        }while(disaster == true);

        do{
            disaster = false;
            input_box();
            gotoxy(91, 5);
            color(3);
            printf("New Product");
            gotoxy(88, 8);
            color(8);
            printf("Enter the following");
            gotoxy(67, 10);
            color(8);
            printf("Enter the serial number: ");
            color(7);
            printf("%d", (int) serial_number);
            gotoxy(56, 12);
            color(8);
            printf("Enter the name(30 characters only): ");
            color(7);
            printf("%s", name);
            gotoxy(74, 14);
            color(8);
            printf("Enter the amount: ");
            color(7);
            if((scanf("%lf", &product_amount)) == 0 || (getchar()) != '\n'){
                print_invalid();
                fflush(stdin);
                disaster = true;
            }
            else if(product_amount != (int) product_amount){
                print_invalid();
                disaster = true;
            }
            else{
                int receive = confirmation();
                if(receive == 2)
                    disaster = true;
                else if(receive == 3){
                    cancelled_operation();
                    return;
                }
            }
        }while(disaster == true);
        fflush(stdin);

        do{
            disaster = false;
            input_box();
            gotoxy(91, 5);
            color(3);
            printf("New Product");
            gotoxy(88, 8);
            color(8);
            printf("Enter the following");
            gotoxy(67, 10);
            color(8);
            printf("Enter the serial number: ");
            color(7);
            printf("%d", (int) serial_number);
            gotoxy(56, 12);
            color(8);
            printf("Enter the name(30 characters only): ");
            color(7);
            printf("%s", name);
            gotoxy(74, 14);
            color(8);
            printf("Enter the amount: ");
            color(7);
            printf("%d", (int) product_amount);
            gotoxy(75, 16);
            color(8);
            printf("Enter the price: ");
            color(7);
            if((scanf("%lf", &product_price)) == 0 || (getchar()) != '\n'){
                print_invalid();
                while((getchar()) != '\n');
                disaster = true;
            }
            else{
                int receive = confirmation();
                if(receive == 2)
                    disaster = true;
                else if(receive == 3){
                    cancelled_operation();
                    return;
                }
            }
        }while(disaster == true);
        fflush(stdin);

        //for the file
        FILE *record_of_stock;

        //Overwrite the data for the new changes
        record_of_stock = fopen("Stock's record.txt" , "w");

        //Adds the number of product
        number_of_product++;

        //put it in the data as the new number of the products
        fprintf(record_of_stock,"%d", number_of_product);

        //print the existing ones
        if(number_of_product != 1){
            for(i = 0; i < number_of_product - 1; i++){
                fprintf(record_of_stock,"\n%d %d %.2f %s", products[i].serial_number_of_product, products[i].amount_of_product, products[i].product_price, products[i].name_of_product);
            }
        }

        //finally put the new product along with its specification
        fprintf(record_of_stock,"\n%d %d %.2f %s", (int) serial_number, (int)product_amount, product_price, name);

        //prompt the user that it successfully add the product

        successful();

        //close the file
        fclose(record_of_stock);
    }
}

void Remove_product(){
    clear;
    FILE *stocks;

    //determines if the record exists in the storage
    if((stocks = fopen("Stock's record.txt" , "r")) ==  NULL)
        output_no_record();
    else{
        int number_of_the_products;
        fscanf(stocks, "%d", &number_of_the_products);
        if(number_of_the_products == 0)
            no_product();
        else{
            double serial_number;
            int i;
            bool exist = false, disaster;

            //prompts the user to input the serial number to be deleted
            do{
                disaster = false;
                input_box();
                gotoxy(90, 5);
                color(3);
                printf("Remove Product");
                gotoxy(88, 8);
                color(8);
                printf("Enter the following");
                gotoxy(67, 10);
                printf("Enter the serial number: ");
                color(7);
                if((scanf("%lf", &serial_number)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(serial_number != (int) serial_number){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            struct product products[number_of_the_products];

            //get all the product's info
            for(i = 0; i < number_of_the_products && !(feof(stocks)); i++){
                fscanf(stocks,"%d %d %f %[^\n]s", &products[i].serial_number_of_product, &products[i].amount_of_product, &products[i].product_price, products[i].name_of_product);

                //if the product has been found
                if(serial_number == products[i].serial_number_of_product){
                    double choice;
                    do{
                        disaster = false;
                        //prompts the user for the option of the operations
                        input_box();
                        gotoxy(76, 5);
                        color(3);
                        printf("Do you really want to delete the product?");
                        gotoxy(82, 8);
                        color(8);
                        printf("Serial Number: ");
                        color(7);
                        printf("%d", products[i].serial_number_of_product);
                        gotoxy(89, 9);
                        color(8);
                        printf("Amount: ");
                        color(7);
                        printf("%d", products[i].amount_of_product);
                        gotoxy(90, 10);
                        color(8);
                        printf("Price: ");
                        color(7);
                        printf("%.2f", products[i].product_price);
                        gotoxy(83, 11);
                        color(8);
                        printf("Product Name: ");
                        color(7);
                        printf("%s", products[i].name_of_product);
                        gotoxy(94, 14);
                        color(8);
                        printf("[1] Yes");
                        gotoxy(94, 15);
                        printf("[0] No");
                        gotoxy(88, 16);
                        printf("Enter here:");
                        gotoxy(100, 16);

                        color(7);
                        if((scanf("%lf", &choice)) == 0 || (getchar()) != '\n'){
                            print_invalid();
                            fflush(stdin);
                            disaster = true;
                        }
                        else if(choice != (int) choice){
                            print_invalid();
                            disaster = true;
                        }
                        else if(choice != 1 && choice !=0){
                            print_invalid();
                            disaster = true;
                        }
                    }while(disaster == true);

                    if(choice == 0){
                        //didn't delete the product
                        cancelled_operation();
                        fclose(stocks);
                        return;
                    }
                    else{
                        //rewrite the existing data of the structure
                        fscanf(stocks,"%d %d %f %[^\n]s", &products[i].serial_number_of_product, &products[i].amount_of_product, &products[i].product_price, products[i].name_of_product);
                    }

                    //it is the determinant if the product to be deleted is found at the stocks
                    exist = true;

                    //the number of the products has been decremented
                    number_of_the_products--;
                }
            }
            //closes the file
            fclose(stocks);

            if(exist == false){
                //that means that the product does not exist in the stocks
                product_not_found();
            }
            else{
                //the infos that the operation has changed will be saved to the file as the new record of the stocks
                FILE *record = fopen("Stock's record.txt" , "w");

                fprintf(record,"%d", number_of_the_products);

                for(i = 0; i < number_of_the_products; i++)
                    fprintf(record,"\n%d %d %.2f %s", products[i].serial_number_of_product, products[i].amount_of_product, products[i].product_price, products[i].name_of_product);

                fclose(record);
                dialogue_box();
                gotoxy(89, 5);
                color(3);
                printf("System Notice!");
                gotoxy(82, 10);
                color(7);
                printf("Product successfully removed!");
                gotoxy(83, 15);
                color(2);
                printf("Press any key to continue");
                gotoxy(96, 20);
                getch();
                clear
            }
        }
    }
    clear
}

void Update_product(){
    FILE *stocks;

    //determines if the record exists in the storage
    if((stocks = fopen("Stock's record.txt" , "r")) ==  NULL)
        output_no_record();
    else{
        int number_of_the_products;
        fscanf(stocks, "%d", &number_of_the_products);
        if(number_of_the_products == 0)
            no_product();
        else{
            int i, receive;
            double serial_number;
            bool exist = false, disaster;
            clear
            //prompts the user to input the serial number of the product to be updated
            do{
                disaster = false;
                input_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(88, 8);
                color(8);
                printf("Enter the following");
                gotoxy(67, 10);
                printf("Enter the serial number: ");
                color(7);
                if((scanf("%lf", &serial_number)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(serial_number != (int) serial_number){
                    print_invalid();
                    disaster = true;
                }
                else{
                    receive = confirmation();
                    if(receive == 2)
                        disaster = true;
                    else if(receive == 3){
                        cancelled_operation();
                        fclose(stocks);
                        return;
                    }
                }
            }while(disaster == true);

            struct product products[number_of_the_products];

            //get all the product's info
            for(i = 0; i < number_of_the_products && !(feof(stocks)); i++){
                fscanf(stocks,"%d %d %f %[^\n]s", &products[i].serial_number_of_product, &products[i].amount_of_product, &products[i].product_price, products[i].name_of_product);

                //if the product has been found
                if(serial_number == products[i].serial_number_of_product){
                    float choice;
                    do{
                        //prompts the user for the option of the operations
                        clear
                        disaster = false;
                        input_box();
                        gotoxy(89, 5);
                        color(3);
                        printf("Update Product");
                        gotoxy(82, 7);
                        color(8);
                        printf("Serial Number: ");
                        color(7);
                        printf("%6d", products[i].serial_number_of_product);
                        gotoxy(89, 8);
                        color(8);
                        printf("Amount: ");
                        color(7);
                        printf("%d", products[i].amount_of_product);
                        gotoxy(90, 9);
                        color(8);
                        printf("Price: ");
                        color(7);
                        printf("%.2f", products[i].product_price);
                        gotoxy(83, 10);
                        color(8);
                        printf("Product Name: ");
                        color(7);
                        printf("%s", products[i].name_of_product);
                        gotoxy(74, 12);
                        color(8);
                        printf("Choose what info of the product to be updated:\n\n");
                        gotoxy(91, 13);
                        printf("[1] Serial Number");
                        gotoxy(91, 14);
                        printf("[2] Amount");
                        gotoxy(91, 15);
                        printf("[3] Price");
                        gotoxy(91, 16);
                        printf("[4] Product name");
                        gotoxy(91, 17);
                        printf("[5] Cancel");
                        gotoxy(88, 18);
                        printf("Enter here:");
                        gotoxy(100, 18);
                        color(7);
                        if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
                            print_invalid();
                            fflush(stdin);
                            disaster = true;
                        }
                        else if(choice != (int) choice){
                            print_invalid();
                            disaster = true;
                        }
                        else if(choice < 1 || choice > 5){
                            print_invalid();
                            disaster = true;
                        }
                    }while(disaster == true);

                    if(choice == 5){
                        //Cancell the updating of the product
                        cancelled_operation();
                        fclose(stocks);
                        return;
                    }
                    else{
                        //rewrite the existing data of the product
                        receive = update_info(&products[i], choice);
                    }

                    //it is the determinant if the product to be deleted is found at the stocks
                    exist = true;

                    //the number of the products has been decremented
                }
            }
            //closes the file
            fclose(stocks);

            if(receive == 3){
                return;
            }


            if(exist == false)
                product_not_found();
            else{
                //the infos that the operation has changed will be saved to the file as the new record of the stocks
                FILE *record = fopen("Stock's record.txt" , "w");

                fprintf(record,"%d", number_of_the_products);

                for(i = 0; i < number_of_the_products; i++)
                    fprintf(record,"\n%d %d %.2f %s", products[i].serial_number_of_product, products[i].amount_of_product, products[i].product_price, products[i].name_of_product);

                fclose(record);
            }
        }

    }
}

int update_info(struct product *products,float choice){
    bool disaster;

    if(choice == 1){
        float new_serial_no;
        do{
            do{
                disaster = false;
                dialogue_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(79, 9);
                color(8);
                printf("Current serial no.: ");
                gotoxy(73, 11);
                printf("Enter the new serial no.: ");
                color(7);
                gotoxy(99, 9);
                printf("%d", products->serial_number_of_product);
                gotoxy(99, 11);
                if((scanf("%f", &new_serial_no)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(new_serial_no != (int) new_serial_no){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            do{
                disaster = false;
                input_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(83, 8);
                color(8);
                printf("Old serial no.:");
                gotoxy(79, 10);
                printf("The new serial no.:");
                gotoxy(91, 13);
                printf("[1] Continue");
                gotoxy(91, 14);
                printf("[2] Change Again");
                gotoxy(91, 15);
                printf("[3] Cancel");
                gotoxy(88, 17);
                printf("Enter here: ");
                gotoxy(99, 8);
                color(7);
                printf("%d", products->serial_number_of_product);
                gotoxy(99, 10);
                printf("%d", (int) new_serial_no);
                gotoxy(100, 17);
                if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(choice != (int) choice){
                    print_invalid();
                    disaster = true;
                }
                else if(choice < 1 || choice > 3){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            if(choice == 1){
                products->serial_number_of_product = (int) new_serial_no;
                update_complete();
                return choice;
            }
            else if(choice == 3){
                cancelled_operation();
                return choice;
            }
        }while(choice == 2);
    }
    else if(choice == 2){
        float new_amount;
        do{
            do{
                disaster = false;
                dialogue_box();
                gotoxy(89, 5);
                color(8);
                printf("Update Product");
                gotoxy(83, 9);
                printf("Current amount:");
                gotoxy(77, 11);
                printf("Enter the new amount: ");
                gotoxy(99, 9);
                color(7);
                printf("%d", products->amount_of_product);
                gotoxy(99, 11);
                if((scanf("%f", &new_amount)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(new_amount != (int) new_amount){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            do{
                disaster = false;
                input_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(87, 8);
                color(8);
                printf("Old Amount:");
                gotoxy(83, 10);
                printf("The new amount:");
                gotoxy(91, 13);
                printf("[1] Continue");
                gotoxy(91, 14);
                printf("[2] Change Again");
                gotoxy(91, 15);
                printf("[3] Cancel");
                gotoxy(88, 17);
                printf("Enter here: ");
                gotoxy(99, 8);
                color(7);
                printf("%d", products->amount_of_product);
                gotoxy(99, 10);
                printf("%d", (int) new_amount);
                gotoxy(100, 17);
                if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(choice != (int) choice){
                    print_invalid();
                    disaster = true;
                }
                else if(choice < 1 || choice > 3){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            if(choice == 1){
                products->amount_of_product = (int) new_amount;
                update_complete();
                return choice;
            }
            else if(choice == 3){
                cancelled_operation();
                return choice;
            }
        }while(choice == 2);
    }
    else if(choice == 3){
        float new_price;
        do{
            do{
                disaster = false;
                dialogue_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(84, 9);
                color(8);
                printf("Current price:");
                gotoxy(78, 11);
                printf("Enter the new price:");
                gotoxy(99, 9);
                color(7);
                printf("%.2f", products->product_price);
                gotoxy(99, 11);
                if((scanf("%f", &new_price)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
            }while(disaster == true);

            do{
                disaster = false;
                input_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(88, 8);
                color(8);
                printf("Old Price:");
                gotoxy(84, 10);
                printf("The new price:");
                gotoxy(91, 13);
                printf("[1] Continue");
                gotoxy(91, 14);
                printf("[2] Change Again");
                gotoxy(91, 15);
                printf("[3] Cancel");
                gotoxy(88, 17);
                printf("Enter here: ");
                gotoxy(99, 8);
                color(7);
                printf("%.2f", products->product_price);
                gotoxy(99, 10);
                printf("%.2f", new_price);
                gotoxy(100, 17);
                if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(choice != (int) choice){
                    print_invalid();
                    disaster = true;
                }
                else if(choice < 1 || choice > 3){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            if(choice == 1){
                products->product_price = new_price;
                update_complete();
                return choice;
            }
            else if(choice == 3){
                cancelled_operation();
                return choice;
            }
        }while(choice == 2);
    }
    else if(choice == 4){
        char new_name[31];
        do{
            do{
                disaster = false;
                dialogue_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(85, 9);
                color(8);
                printf("Current name:");
                gotoxy(79, 11);
                printf("Enter the new name: ");
                gotoxy(99, 9);
                color(7);
                printf("%s...", products->name_of_product);
                gotoxy(99, 11);
                scanf(" %30[^\n]s", new_name);
                if((getchar() != '\n'))
                    disaster = buffer_overload();
            }while(disaster == true);

            do{
                disaster = false;
                input_box();
                gotoxy(89, 5);
                color(3);
                printf("Update Product");
                gotoxy(89, 8);
                color(8);
                printf("Old Name:");
                gotoxy(85, 10);
                printf("The new name:");
                gotoxy(91, 13);
                printf("[1] Continue");
                gotoxy(91, 14);
                printf("[2] Change Again");
                gotoxy(91, 15);
                printf("[3] Cancel");
                gotoxy(88, 17);
                printf("Enter here: ");
                gotoxy(99, 8);
                color(7);
                printf("%s...", products->name_of_product);
                gotoxy(99, 10);
                printf("%s...", new_name);
                gotoxy(100, 17);
                if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
                    print_invalid();
                    fflush(stdin);
                    disaster = true;
                }
                else if(choice != (int) choice){
                    print_invalid();
                    disaster = true;
                }
                else if(choice < 1 || choice > 3){
                    print_invalid();
                    disaster = true;
                }
            }while(disaster == true);

            if(choice == 1){
                strcpy(products->name_of_product, new_name);
                update_complete();
                return choice;
            }
            else if(choice == 3){
                cancelled_operation();
                return choice;
            }
        }while(choice == 2);
    }
}

void sort_product(){
    //for the file
    FILE *record_of_stocks = fopen("Stock's record.txt" , "r");

        int number_of_products;

        //Get the number of the products in the stock
        fscanf(record_of_stocks,"%d", &number_of_products);

        int i;
        //declare a struct base on the number of the products
        struct product products[number_of_products];

        //get the product
        for(i = 0; i < number_of_products; i++)
            fscanf(record_of_stocks,"%ld %d %f %[^\n]s", &products[i].serial_number_of_product, &products[i].amount_of_product, &products[i].product_price, products[i].name_of_product);

        //closes the file
        fclose(record_of_stocks);

        //seed for the random numbers
        srand(time(NULL));

        //call the quicksort function
        quicksort(&products[0], 0, number_of_products - 1);

        //declare for the writing of the file
        FILE *stocks;

        stocks = fopen("Stock's record.txt" , "w");

        //put the number of product first
        fprintf(stocks,"%d", number_of_products);

        //now put the sorted products in the file
        for(i = 0; i < number_of_products; i++)
            fprintf(stocks,"\n%ld %d %.2f %s", products[i].serial_number_of_product, products[i].amount_of_product, products[i].product_price, products[i].name_of_product);

        //close the file
        fclose(stocks);
}

void quicksort(struct product *pointer_to_array_struct, int left, int right){
    //Base case
    if(right <= left)
        return;

    //for randomized index
    int index = (rand() % (right - left)) + left;

    if(index != right){
        //Temporary variable
        struct product *temp = (struct product*) malloc(sizeof(struct product));

        //from right to temp
        temp->serial_number_of_product = (pointer_to_array_struct + right)->serial_number_of_product;
        temp->amount_of_product = (pointer_to_array_struct + right)->amount_of_product;
        temp->product_price = (pointer_to_array_struct + right)->product_price;
        strcpy(temp->name_of_product, (pointer_to_array_struct + right)->name_of_product);

        //from randomized index to right
        (pointer_to_array_struct + right)->serial_number_of_product = (pointer_to_array_struct + index)->serial_number_of_product;
        (pointer_to_array_struct + right)->amount_of_product = (pointer_to_array_struct + index)->amount_of_product;
        (pointer_to_array_struct + right)->product_price = (pointer_to_array_struct + index)->product_price;
        strcpy((pointer_to_array_struct + right)->name_of_product, (pointer_to_array_struct + index)->name_of_product);
        //from temp to randomized index
        (pointer_to_array_struct + index)->serial_number_of_product = temp->serial_number_of_product;
        (pointer_to_array_struct + index)->amount_of_product = temp->amount_of_product;
        (pointer_to_array_struct + index)->product_price = temp->product_price;
        strcpy((pointer_to_array_struct + index)->name_of_product, temp->name_of_product);
        free(temp);
    }
    //getting the pivot
    int pivot = partition(pointer_to_array_struct, left, right);

    //recursion for divide and conquer
    quicksort(pointer_to_array_struct, left, pivot - 1);
    quicksort(pointer_to_array_struct, pivot + 1, right);
}

int partition(struct product *pointer_to_array_struct, int left, int right){
    //serial number inside
    int pivot = (pointer_to_array_struct + right)->serial_number_of_product;

    //the anchor of the sorting
    int i = left, j;

    //important variable for swapping
    struct product *temp = (struct product*) malloc(sizeof(struct product));

    //sorting based on the serial number
    for(j = left; j <= right - 1; j++){
        if((pointer_to_array_struct + j)->serial_number_of_product < pivot){

            //from j to temp
            temp->serial_number_of_product = (pointer_to_array_struct + j)->serial_number_of_product;
            temp->amount_of_product = (pointer_to_array_struct + j)->amount_of_product;
            temp->product_price = (pointer_to_array_struct + j)->product_price;
            strcpy(temp->name_of_product, (pointer_to_array_struct + j)->name_of_product);

            //from i to j
            (pointer_to_array_struct + j)->serial_number_of_product = (pointer_to_array_struct + i)->serial_number_of_product;
            (pointer_to_array_struct + j)->amount_of_product = (pointer_to_array_struct + i)->amount_of_product;
            (pointer_to_array_struct + j)->product_price = (pointer_to_array_struct + i)->product_price;
            strcpy((pointer_to_array_struct + j)->name_of_product, (pointer_to_array_struct + i)->name_of_product);

            //from temp to i
            (pointer_to_array_struct + i)->serial_number_of_product = temp->serial_number_of_product;
            (pointer_to_array_struct + i)->amount_of_product = temp->amount_of_product;
            (pointer_to_array_struct + i)->product_price = temp->product_price;
            strcpy((pointer_to_array_struct + i)->name_of_product, temp->name_of_product);
            //increment
            i++;
        }
    }

    //from i to temp
    temp->serial_number_of_product = (pointer_to_array_struct + i)->serial_number_of_product;
    temp->amount_of_product = (pointer_to_array_struct + i)->amount_of_product;
    temp->product_price = (pointer_to_array_struct + i)->product_price;
    strcpy(temp->name_of_product, (pointer_to_array_struct + i)->name_of_product);

    //from right to i
    (pointer_to_array_struct + i)->serial_number_of_product = (pointer_to_array_struct + right)->serial_number_of_product;
    (pointer_to_array_struct + i)->amount_of_product = (pointer_to_array_struct + right)->amount_of_product;
    (pointer_to_array_struct + i)->product_price = (pointer_to_array_struct + right)->product_price;
    strcpy((pointer_to_array_struct + i)->name_of_product, (pointer_to_array_struct + right)->name_of_product);

    //from temp to right
    (pointer_to_array_struct + right)->serial_number_of_product = temp->serial_number_of_product;
    (pointer_to_array_struct + right)->amount_of_product = temp->amount_of_product;
    (pointer_to_array_struct + right)->product_price = temp->product_price;
    strcpy((pointer_to_array_struct + right)->name_of_product, temp->name_of_product);
    //free the memory of the temp variable
    free(temp);

    //serves as the pivot of the quicksort
    return i;
}
