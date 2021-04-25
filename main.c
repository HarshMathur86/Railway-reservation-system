#include <stdio.h>
#include <stdlib.h>
#include "rlyres.h"
#include "conio2.h"

int main()
{
    int choice, ticket_no, trainno, *arr_ticket_no;
    Passenger *pr;
    char  *mob_no, *train_no;
    add_trains();
    while(1)
    {
        choice = enterchoice();
        if(choice == 9)
        {
            bye_message();
            exit(0);
        }
        switch(choice)
        {
        case 1:
            view_trains();
            getch();
            system("cls");
            break;

        case 2:
            pr = get_passenger_details();
            if(pr == NULL)
            {
                system("cls");
                break;
            }
            textcolor(11);
            if((ticket_no = book_ticket(pr)) == -1)
                printf("\n\n\t\t\t\tBOOKING FAILED");
            else
            {
                printf("\n\n\n\nTicket booked successfully.");
                textcolor(14);
                printf("\n\n\t  Ticket number : %d", ticket_no);
            }
            textcolor(11);
            gotoxy(1, 23);
            printf("\n\nPress any key to go back to main menu.");
            getch();
            free(pr);
            system("cls");
            break;

        case 3:
            ticket_no = accept_ticket_no();
            if(ticket_no == 0)
            {
                system("cls");
                break;
            }
            view_ticket(ticket_no);
            system("cls");
            break;

        case 4:
            mob_no = accept_mob_no();
            if(mob_no == NULL)
            {
                system("cls");
                break;
            }
            arr_ticket_no = get_ticket_no(mob_no);
            view_all_tickets(mob_no, arr_ticket_no);
            system("cls");
            //get_ticket_no();
            break;

        case 5:
            view_all_bookings();
            system("cls");
            break;

        case 6:
            train_no = accept_train_no();
            if(train_no == NULL)
            {
                system("cls");
                break;
            }
            view_booking(train_no);
            system("cls");
            break;

        case 7:
            ticket_no = accept_ticket_no();
            if(ticket_no == 0)
            {
                system("cls");
                break;
            }
            if(cancel_ticket(ticket_no) == 0)
            {
                gotoxy(1, 25);
                textcolor(4);
                printf("Given ticket no does not exist press any key to go back to main menu.");
                getch();
            }
            else
            {
                gotoxy(1, 5);
                textcolor(13);
                printf("\tTicket cancellation is successful");
                gotoxy(1, 25);
                textcolor(11);
                printf("Press any key to go back to main menu");
                getch();
            }
            system("cls");
            break;

        case 8:
            train_no = accept_train_no();
            if(train_no == NULL)
            {
                system("cls");
                break;
            }
            if(check_train_no(train_no) == 0)
            {
                gotoxy(1, 25);
                textcolor(4);
                printf("Given train no does not exist press any key to go back to main menu.");
                getch();
            }
            else
            {
                del_all_ticket(train_no);
                gotoxy(1, 5);
                textcolor(13);
                printf("\Train cancellation is successful\nAnd all the tickets booked on train no. ");
                textcolor(10);
                printf("%s ",train_no);
                textcolor(13);
                printf("is also cancelled.");
                gotoxy(1, 25);
                textcolor(11);
                printf("Press any key to go back to main menu");
                getch();
            }
            system("cls");
            break;

        default:
            textcolor(4);
            printf("\nWrong choice! Try Again");
            getch();
            clrscr();
        }
    }
    return 0;
}
