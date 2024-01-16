#include <windows.h>
#include <stdio.h>
#include <unistd.h>

void dialogue_box();
void gotoxy(int x, int y);
void color(int color);
void print_invalid();
void poweroff();
void output_no_record();
void cancelled_operation();
void product_not_found();
int confirmation();
void collect_data();
bool buffer_overload();
void successful();
void system_notice();

#define clear system("cls");

void color(int color){
	HANDLE mycolor;

	mycolor = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(mycolor, color);

}

void collect_data(){
    gotoxy(84, 7);
    color(3);
    printf("+--------------------+");
    gotoxy(84, 8);
    printf("|  ");
    color(7);
    printf("Collecting Data!  ");
    color(3);
    printf("|");
    gotoxy(84, 9);
    printf("| ");
    color(8);
    printf("+================+ ");
    color(3);
    printf("|");
    gotoxy(84, 10);
    printf("| ");
    color(8);
    printf("|                | ");
    color(3);
    printf("|");
    gotoxy(84, 11);
    printf("| ");
    color(8);
    printf("+================+ ");
    color(3);
    printf("|");
    gotoxy(84, 12);
    printf("+--------------------+");
    gotoxy(87, 10);
    color(2);
    for(int i = 0; i < 16; i++){
        usleep(200000);
        printf("%c",219);
    }
}

void gotoxy(int x, int y){
    //a variable type that is responsible for the coordinates where the texts will be printed
    COORD coordinate;
    //the member x and y
    coordinate.X = x;
    coordinate.Y = y;
    //the function forexecuting the command
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);

}

void system_notice(){
    gotoxy(89, 5);
    color(3);
    printf("System Notice!");
    gotoxy(83, 15);
    color(2);
    printf("Press any key to continue");
}

void dialogue_box(){
    color(4);
    gotoxy(44, 4);
    printf("+-----------------------------------------------------------------------------------------------------+");
    gotoxy(44, 5);
    printf("|                                                                                                     |");
    gotoxy(44, 6);
    printf("|-----------------------------------------------------------------------------------------------------|");
    gotoxy(44, 7);
    printf("|                                                                                                     |");
    gotoxy(44, 8);
    printf("|                                                                                                     |");
    gotoxy(44, 9);
    printf("|                                                                                                     |");
    gotoxy(44, 10);
    printf("|                                                                                                     |");
    gotoxy(44, 11);
    printf("|                                                                                                     |");
    gotoxy(44, 12);
    printf("|                                                                                                     |");
    gotoxy(44, 13);
    printf("|                                                                                                     |");
    gotoxy(44, 14);
    printf("|-----------------------------------------------------------------------------------------------------|");
    gotoxy(44, 15);
    printf("|                                                                                                     |");
    gotoxy(44, 16);
    printf("+-----------------------------------------------------------------------------------------------------+");
}

void input_box(){
    color(2);
    gotoxy(44, 4);
    printf("+-----------------------------------------------------------------------------------------------------+");
    gotoxy(44, 5);
    printf("|                                                                                                     |");
    gotoxy(44, 6);
    printf("|-----------------------------------------------------------------------------------------------------|");
    gotoxy(44, 7);
    printf("|                                                                                                     |");
    gotoxy(44, 8);
    printf("|                                                                                                     |");
    gotoxy(44, 9);
    printf("|                                                                                                     |");
    gotoxy(44, 10);
    printf("|                                                                                                     |");
    gotoxy(44, 11);
    printf("|                                                                                                     |");
    gotoxy(44, 12);
    printf("|                                                                                                     |");
    gotoxy(44, 13);
    printf("|                                                                                                     |");
    gotoxy(44, 14);
    printf("|                                                                                                     |");
    gotoxy(44, 15);
    printf("|                                                                                                     |");
    gotoxy(44, 16);
    printf("|                                                                                                     |");
    gotoxy(44, 17);
    printf("|                                                                                                     |");
    gotoxy(44, 18);
    printf("|                                                                                                     |");
    gotoxy(44, 19);
    printf("+-----------------------------------------------------------------------------------------------------+");
}

void print_invalid(){
    dialogue_box();
    system_notice();
    color(7);
    gotoxy(89, 10);
    printf("Input Invalid!!");
    gotoxy(96, 20);
    getch();
}

void poweroff(){

    gotoxy(88, 7);
    color(3);
    printf("+--------------+");
    gotoxy(88, 8);
    printf("|  ");
    color(7);
    printf("Power Off!");
    color(3);
    printf("  |");
    gotoxy(88, 9);
    printf("| ");
    color(8);
    printf("+==========+");
    color(3);
    printf(" |");
    gotoxy(88, 10);
    printf("| ");
    color(8);
    printf("|          |");
    color(3);
    printf(" |");
    gotoxy(88, 11);
    printf("| ");
    color(8);
    printf("+==========+");
    color(3);
    printf(" |");
    gotoxy(88, 12);
    printf("+--------------+");
    gotoxy(91, 10);

    color(2);
    for(int i = 0; i < 10; i++){
        usleep(200000);
        printf("%c",219);
    }
    gotoxy(96, 20);
    exit(0);
    color(7);
}

void no_product(){
    dialogue_box();
    system_notice();
    gotoxy(85, 10);
    color(7);
    printf("No existing product!!");
    gotoxy(96, 20);
    getch();
}

void cancelled_operation(){
    dialogue_box();
    system_notice();
    gotoxy(80, 10);
    color(7);
    printf("The operation has been cancelled!");
    gotoxy(96, 20);
    getch();
}

void product_not_found(){
    dialogue_box();
    system_notice();
    gotoxy(86, 10);
    color(7);
    printf("Product not found!");
    gotoxy(96, 20);
    getch();
}

void update_complete(){
    dialogue_box();
    system_notice();
    gotoxy(87, 10);
    color(7);
    printf("Update Complete!");
    gotoxy(96, 20);
    getch();
}

int confirmation(){
    bool disaster;
    float choice;
    do{
        disaster = false;
        dialogue_box();
        gotoxy(89, 5);
        color(3);
        printf("System Notice!");
        gotoxy(90, 8);
        color(8);
        printf("Continue?");
        gotoxy(91, 10);
        color(7);
        printf("[1] Yes");
        gotoxy(91, 11);
        printf("[2] Redo");
        gotoxy(91, 12);
        printf("[3] Cancel");
        gotoxy(89, 15);
        printf("Enter here: ");

        if((scanf("%f", &choice)) == 0 || (getchar()) != '\n'){
            disaster = true;
            print_invalid();
            fflush(stdin);
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
    return (int) choice;
}

void output_no_record(){
    dialogue_box();
    system_notice();
    gotoxy(88, 10);
    color(7);
    printf("File not found!");
    gotoxy(96, 20);
    getch();
}

bool buffer_overload(){
    dialogue_box();
    system_notice();
    gotoxy(87, 10);
    color(7);
    printf("30 characters only!");
    gotoxy(96, 20);
    fflush(stdin);
    getch();
    return true;
}

void successful(){
    dialogue_box();
    system_notice();
    gotoxy(83, 10);
    color(7);
    printf("Product successfully added!");
    gotoxy(96, 20);
    getch();
}