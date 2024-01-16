#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

#define clear system("cls");

void no_product();
void gotoxy(int x, int y);
void power_off();
void on_the_ordering();
void exceed();
void add_product();
void remove_product();
void successfully_removed();
void order_cancelled();
void product_not_found();
void print_invalid();
void check_out_confirmation();
void color(int color);
void file_not_found();
void product_already_exist();
void finishing_remarks();
void edit_quantity();
void receipt();
void System_box();
void input_box();
void system_notice();
void press_any_key();

void System_box(){
    gotoxy(34, 9);
    color(8);
    printf("+=====================================================================================+");
    gotoxy(34, 10);
    printf("|                                                                                     |");
    gotoxy(34, 11);
    printf("+=====================================================================================+");
    gotoxy(34, 12);
    printf("|                                                                                     |");
    gotoxy(34, 13);
    printf("|                                                                                     |");
    gotoxy(34, 14);
    printf("|                                                                                     |");
    gotoxy(34, 15);
    printf("|                                                                                     |");
    gotoxy(34, 16);
    printf("|                                                                                     |");
    gotoxy(34, 17);
    printf("|                                                                                     |");
    gotoxy(34, 18);
    printf("+=====================================================================================+");
    gotoxy(34, 19);
    printf("|                                                                                     |");
    gotoxy(34, 20);
    printf("+=====================================================================================+");
}

void system_notice(){
    color(3);
    gotoxy(71, 10);
    printf("System Notice!!");
}

void receipt(){
    System_box();
    system_notice();
    gotoxy(69, 13);
    color(8);
    printf("Print the receipt?");
    gotoxy(74, 15);
    printf("[1] Yes");
    gotoxy(74, 16);
    printf("[0] No");
    gotoxy(71, 19);
    color(7);
    printf("Enter here:");
    gotoxy(83, 19);
}

void press_any_key(){
    gotoxy(65, 19);
    color(2);
    printf("Press any key to continue");
    gotoxy(79, 22);
    getch();
}

void successfully_removed(){
    System_box();
    system_notice();
    gotoxy(63, 15);
    color(7);
    printf("Product Successfully Removed!!");
    press_any_key();
}

void finishing_remarks(){
    System_box();
    gotoxy(67, 10);
    color(3);
    printf("Transaction finished!!");
    gotoxy(73, 15);
    color(7);
    printf("Thank you!");
    press_any_key();
}

void product_already_exist(){
    System_box();
    system_notice();
    color(7);
    gotoxy(67, 15);
    printf("Product already exist!");
    press_any_key();
}

void order_cancelled(){
    System_box();
    system_notice();
    color(7);
    gotoxy(70, 15);
    printf("Order Cancelled!");
    press_any_key();
}

void product_not_found(){
    System_box();
    system_notice();
    color(7);
    gotoxy(69, 15);
    printf("Product not found!");
    press_any_key();
}

void file_not_found(){
    System_box();
    system_notice();
    gotoxy(67, 15);
    printf("File not found!");
    press_any_key();
}

void exceed(){
    System_box();
    system_notice();
    color(7);
    gotoxy(57, 15);
    printf("Quantity exceed to the number in the stock");
    press_any_key();
}

void input_box(){
    color(8);
    gotoxy(34, 9);
    printf("+=====================================================================================+");
    gotoxy(34, 10);
    printf("|                                                                                     |");
    gotoxy(34, 11);
    printf("+=====================================================================================+");
    gotoxy(34, 12);
    printf("|                                                                                     |");
    gotoxy(34, 13);
    printf("|                                                                                     |");
    gotoxy(34, 14);
    printf("|                                                                                     |");
    gotoxy(34, 15);
    printf("|                                                                                     |");
    gotoxy(34, 16);
    printf("|                                                                                     |");
    gotoxy(34, 17);
    printf("|                                                                                     |");
    gotoxy(34, 18);
    printf("|                                                                                     |");
    gotoxy(34, 19);
    printf("|                                                                                     |");
    gotoxy(34, 20);
    printf("+=====================================================================================+");
}

void add_product(){
    input_box();
    color(3);
    gotoxy(72, 10);
    printf("Add Product");
    gotoxy(52, 15);
    color(2);
    printf("Enter Serial Number:");
    color(7);
    gotoxy(73, 15);
}

void remove_product(){
    input_box();
    color(3);
    gotoxy(70, 10);
    printf("Remove Product");
    color(2);
    gotoxy(52, 15);
    printf("Enter number of product:");
    color(7);
    gotoxy(77, 15);
}

void edit_quantity(){
    input_box();
    color(3);
    gotoxy(71, 10);
    printf("Edit Quantity");
    color(2);
    gotoxy(52, 15);
    printf("Enter number of product:");
    color(7);
    gotoxy(77, 15);
}

void on_the_ordering(){
    clear
    color(2);
    printf("\n\n==============================================================================================================================================================\n");
    color(3);
    printf("                                                                                 Cashier                                                                      \n");
    color(2);
    printf("==============================================================================================================================================================\n");
    printf("                                 |                                                              ");
    color(3);
    printf("Order:                                                        \n");
    printf("            Menu                ");
    color(2);
    printf(" |============================================================================================================================\n");
    printf("                                 |  ");
    color(3);
    printf("No.                 Original-Price                  Amount                  Price                  Name                   \n");
    printf("         [1] Add                 ");
    color(2);
    printf("|\n");
    color(3);
    printf("         [2] Remove              ");
    color(2);
    printf("|\n");
    color(3);
    printf("         [3] Edit Quantity       ");
    color(2);
    printf("|\n");
    color(3);
    printf("         [4] Check Out           ");
    color(2);
    printf("|\n");
    color(3);
    printf("         [5] Cancel              ");
    color(2);
    printf("|\n");
    printf("                                 |\n");
    color(3);
    printf("           Enter:                ");
    color(2);
    printf("|\n");

}

void color(int color){
	HANDLE mycolor;

	mycolor = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(mycolor, color);

}

void print_invalid(){
    System_box();
    system_notice();
    gotoxy(71, 15);
    color(7);
    printf("Invalid Input!!");
    press_any_key();
}

void check_out_confirmation(){
    color(2);
    gotoxy(55, 10);
    printf("+==========================================+");
    gotoxy(55, 11);
    printf("|                                          |");
    gotoxy(55, 12);
    printf("+------------------------------------------+");
    gotoxy(55, 13);
    printf("|                                          |");
    gotoxy(55, 14);
    printf("|                                          |");
    gotoxy(55, 15);
    printf("|                                          |");
    gotoxy(55, 16);
    printf("|                                          |");
    gotoxy(55, 17);
    printf("|                                          |");
    gotoxy(55, 18);
    printf("|                                          |");
    gotoxy(55, 19);
    printf("+==========================================+");
    gotoxy(82, 17);

    color(3);
    gotoxy(73, 11);
    printf("Check Out");
    color(8);
    gotoxy(73, 14);
    printf("[1] Yes");
    gotoxy(73, 15);
    printf("[0] No");
    gotoxy(70, 17);
    printf("Enter here:");
    color(7);
    gotoxy(82, 17);
}

void power_off(){

    gotoxy(74, 7);
    color(3);
    printf("+--------------+");
    gotoxy(74, 8);
    printf("|  ");
    color(7);
    printf("Power Off!");
    color(3);
    printf("  |");
    gotoxy(74, 9);
    printf("| ");
    color(8);
    printf("+==========+");
    color(3);
    printf(" |");
    gotoxy(74, 10);
    printf("| ");
    color(8);
    printf("|          |");
    color(3);
    printf(" |");
    gotoxy(74, 11);
    printf("| ");
    color(8);
    printf("+==========+");
    color(3);
    printf(" |");
    gotoxy(74, 12);
    printf("+--------------+");
    gotoxy(77, 10);

    color(2);
    for(int i = 0; i < 10; i++){
        usleep(200000);
        printf("%c",219);
    }
    gotoxy(84, 20);
    color(7);
    exit(0);
}

void gotoxy(int x, int y){
    COORD coordinate;

    coordinate.X = x;
    coordinate.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}

void no_product(){
    System_box();
    system_notice();
    color(7);
    gotoxy(70, 15);
    printf("No product found!");
    press_any_key();
}
