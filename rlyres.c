#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"

int enterchoice()
{
    int choice;
    textcolor(9);
    gotoxy(26, 2);
    printf("WELCOME TO INDIAN RAILWAYS");
    gotoxy(26, 3);
    textcolor(6);
    printf("Railway Reservation System");
    textcolor(14);
    printf("\n________________________________________________________________________________");
    textcolor(6);
    printf("\n\nSelect an option");
    printf("\n\t1- View Trains");
    printf("\n\t2- Book Ticket");
    printf("\n\t3- View Ticket");
    printf("\n\t4- Search Ticket by Contact no");
    printf("\n\t5- View All Bookings");
    printf("\n\t6- View Train Bookings");
    printf("\n\t7- Cancel Ticket");;
    printf("\n\t8- Cancel Train");
    printf("\n\t9- Quit");

    gotoxy(55, 25);
    textcolor(10);
    printf("Created By - Harsh Mathur");
    gotoxy(1, 16);
    textcolor(11);
    printf("\n\nEnter Choice : ");
    scanf("%d", &choice);

    return choice;
}

void add_trains()
{
    gotoxy(1, 25);
    Train alltrains[4]={
        {"123","BPL","GWA",2100,1500},
        {"546","BPL","DEL",3500,2240},
        {"345","HBJ","AGR",1560,1135},
        {"896","HBJ","MUM",4500,3360}
    };
    FILE *fp = fopen("alltrains.dat", "rb");
    if(fp == NULL)
    {
        fp = fopen("alltrains.dat", "wb");
        fwrite(alltrains, 4 * sizeof(Train), 1, fp);
        printf("File created and saved successfully!");
    }
    else
        printf("File already present");
    fclose(fp);
}

void view_trains()
{
    system("cls");
    printf("\n");
    textcolor(3);
    printf("\n TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    textcolor(14);
    printf("________________________________________________________________________________\n");
    FILE *fp = fopen("alltrains.dat", "rb");
    Train tr;
    textcolor(11);
    while(fread(&tr, sizeof(Train), 1, fp) == 1)
    {
        printf("\n   %s\t\t%s\t%s\t    %d\t    %d", tr.train_no, tr.from, tr.to, tr.fac_fare, tr.sac_fare);
    }
    textcolor(14);
    printf("\n________________________________________________________________________________");
    gotoxy(50, 1);
    textcolor(10);
    printf("Press any key to continue");
    fclose(fp);
}

int check_train_no(char * trainno)
{
    FILE *fp = fopen("alltrains.dat", "rb");
    Train tr;
    while(fread(&tr, sizeof(Train), 1, fp) != NULL)
    {
        if(strcmp(tr.train_no, trainno) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int check_mob_no(char *p_mob)
{
    if(strlen(p_mob) != 10)
        return 0;
    while(*p_mob != '\0')
    {
        if(isdigit(*p_mob) == 0)//Headerfile ctype.h if given character is digit then non zero number otherwise returns zero
            return 0;
        p_mob++;
    }
    return 1;
}

//Error validation of the following function can also be performed in do{...   }while loop and done by sir
Passenger * get_passenger_details()
{
    Passenger * pass_detail;
    int i;
    pass_detail = (Passenger *)malloc(sizeof(Passenger));
    system("cls");
    gotoxy(63, 1);
    textcolor(10);
    printf("Press 0 to exit");
    gotoxy(1, 1);
    textcolor(3);
    fflush(stdin);

    printf("Enter passenger name: ");
    fgets(pass_detail->p_name, 20, stdin);
    i = strlen(pass_detail->p_name) - 1;
    pass_detail->p_name[i] = '\0';
    if(strcmp(pass_detail->p_name, "0") == 0)
        return NULL;

    printf("Enter gender(M/F): ");
    gender:
        scanf(" %c", &pass_detail->gender);
        fflush(stdin);
        if(pass_detail->gender == '0')
            return NULL;
        if(pass_detail->gender != 'M' && pass_detail->gender != 'F')
        {
            gotoxy(1, 25);
            textcolor(4);
            printf("Error! Gender should be M or F (in uppercase)");
            gotoxy(19, 2);
            printf("          ");
            gotoxy(20, 2);
            textcolor(3);
            goto gender;
        }
        else
        {
            gotoxy(1,25);
            printf("                                                                ");
            gotoxy(1,3);
        }

        printf("Enter train number: ");
        train_no:
            fgets(pass_detail->train_no, 9, stdin);
            i = strlen(pass_detail->train_no) - 1;
            pass_detail->train_no[i] = '\0';
            if(strcmp(pass_detail->train_no, "0") == 0)
                return NULL;
            if(check_train_no(pass_detail->train_no) == 0)
            {
                gotoxy(1, 25);
                textcolor(4);
                printf("Error! Given train number doesn't exist");
                gotoxy(20, 3);
                printf("                     ");
                gotoxy(21, 3);
                textcolor(3);
                goto train_no;
            }
            else
            {
                gotoxy(1,25);
                printf("                                                                ");
                gotoxy(1,4);
            }

            printf("Enter traveling class(First AC-F ,Second AC-S): ");
            p_class:
                scanf(" %c", &pass_detail->p_class);
                if(pass_detail->p_class == '0')
                    return NULL;
                fflush(stdin);
                if(pass_detail->p_class != 'S' && pass_detail->p_class != 'F')
                {
                    gotoxy(1, 25);
                    textcolor(4);
                    printf("Error! Traveling class should be F or S (in uppercase)");
                    gotoxy(49, 4);
                    printf("          ");
                    gotoxy(49, 4);
                    textcolor(3);
                    goto p_class;
                }
                else
                {
                    gotoxy(1,25);
                    printf("                                                                ");
                    gotoxy(1,5);
                }

                printf("Enter address: ");
                fgets(pass_detail->address, 30, stdin);
                i = strlen(pass_detail->address) - 1;
                pass_detail->address[i] = '\0';
                if(strcmp(pass_detail->address, "0") == 0)
                    return NULL;

                printf("Enter age: ");
                age:
                    scanf("%d", &pass_detail->age);
                    if(pass_detail->age == 0)
                        return;
                    if(pass_detail->age < 1 || pass_detail->age > 120)
                    {
                        gotoxy(1, 25);
                        textcolor(4);
                        printf("Error! please enter valid age");
                        gotoxy(12, 6);
                        printf("          ");
                        gotoxy(12, 6);
                        textcolor(3);
                        goto age;
                    }
                    else
                    {
                        gotoxy(1,25);
                        printf("                                                                ");
                        gotoxy(1,7);
                    }

                    printf("Enter contact number: ");
                    fflush(stdin);
                    num:
                        fgets(pass_detail->mob_no,12,stdin);
                        i = strlen(pass_detail->mob_no) - 1;
                        pass_detail->mob_no[i] = '\0';
                        if(strcmp(pass_detail->mob_no, "0") == 0)
                            return NULL;
                        if(check_mob_no(pass_detail->mob_no) == 0)
                        {
                                gotoxy(1, 25);
                                textcolor(4);
                                printf("Error! please enter valid number");
                                gotoxy(22, 7);
                                printf("                  ");
                                gotoxy(23, 7);
                                textcolor(3);
                                goto num;
                        }
                        gotoxy(1,25);
                        printf("                                                                ");
                        gotoxy(13,11);
                        textcolor(13);
                        printf("Details taken Successfully! Press any key to continue");

                        /*printf("\nyour given details\n");
                        printf("\nname -%s", pass_detail->p_name);
                        printf("\ngender - %c", pass_detail->gender);
                        printf("\ntrain no - %s", pass_detail->train_no);
                        printf("\nclss - %c", pass_detail->p_class);
                        printf("\nadd - %s", pass_detail->address);
                        printf("\nage - %d", pass_detail->age);
                        printf("\nmob no - %s", pass_detail->mob_no);
                        printf("\n________________________________");*/
    getch();
    return pass_detail;
}

int get_booked_ticket_count(char *train_no, char tc)
{
    FILE * fp = fopen("allbookings.dat", "rb");
    int count;
    Passenger pr;
    if(fp == NULL)
        return 0;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.train_no, train_no) == 0 && pr.p_class == tc)
            count++;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE * fp = fopen("allbookings.dat", "rb");
    Passenger pr;
    if(fp == NULL)
        return 0;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger * pr)
{
    int ticket_no;
    if(get_booked_ticket_count(pr->train_no,pr->p_class) == 2)
    {
        textcolor(4);
        printf("\n\n\n\n\t\tAll seats are full in train no. %s in %s class!", pr->train_no, pr->p_class=='F'?"First":"Second");
        return -1;
    }
    ticket_no = last_ticket_no() + 1;
    pr->ticketno = ticket_no;
    FILE * fp = fopen("allbookings.dat", "ab");//ab mode create file if not present in the case of first ticket getting booked
    fwrite(pr,sizeof(Passenger),1,fp);
    fclose(fp);
    return pr->ticketno;
}

int accept_ticket_no()
{
    int ticket_no;
    system("cls");
    gotoxy(63, 1);
    textcolor(10);
    printf("Press 0 to exit");
    gotoxy(1, 2);
    textcolor(3);
    printf("Enter the ticket number : ");
    ticket:
        scanf("%d",&ticket_no);
        if(ticket_no == 0)
                return 0;
        if(ticket_no < 0)
            {
                gotoxy(1, 25);
                textcolor(4);
                printf("Error! Given ticket number is invalid");
                gotoxy(27, 2);
                printf("                     ");
                gotoxy(27, 2);
                textcolor(3);
                goto ticket;
            }
            else
            {
                gotoxy(1,25);
                printf("                                                                ");
                gotoxy(1,4);
            }
            return ticket_no;
}

void view_ticket(int ticket_no)
{
    Passenger pr;
    FILE * fp = fopen("allbookings.dat", "rb");
    if(fp == NULL)
        return;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(pr.ticketno == ticket_no)
        {
            textcolor(14);
            printf("\n\n\tDetails of given ticket number\n");
            textcolor(11);
            printf("\n\tName \t\t-   %s", pr.p_name);
            printf("\n\tGender \t\t-   %s", pr.gender == 'M'?"Male":"Female");
            printf("\n\tTrain no \t-   %s", pr.train_no);
            printf("\n\tClass \t\t-   %s AC", pr.p_class=='F'?"First":"Second");
            printf("\n\tAddress \t-   %s", pr.address);
            printf("\n\tAge \t\t-   %d", pr.age);
            printf("\n\tContact no \t-   %s", pr.mob_no);

            gotoxy(1, 25);
            textcolor(13);
            printf("Press any key to continue.");
            getch();
            fclose(fp);
            return;
        }
    }
    gotoxy(1, 25);
    textcolor(4);
    printf("Error! Given ticket number is invalid press any key to continue.");
    fclose(fp);
    getch();
    return;
}

char* accept_mob_no()
{
    static char * mob_no[11];
    char *pos;
    system("cls");
    gotoxy(63, 1);
    textcolor(10);
    printf("Press 0 to exit");
    gotoxy(1, 2);
    textcolor(3);
    printf("Enter contact number for viewing all the tickets booked: ");
    fflush(stdin);
    num:
        fgets(mob_no,11,stdin);
        pos = strchr(mob_no, '\n');
        if(pos != NULL)
            *pos = '\0';
        if(strcmp(mob_no, "0") == 0)
            return NULL;
        if(check_mob_no(mob_no) == 0)
        {
            gotoxy(1, 25);
            textcolor(4);
            printf("Error! please enter valid number");
            gotoxy(58, 2);
            printf("                  ");
            gotoxy(58, 2);
            textcolor(3);
            goto num;
        }
        return mob_no;
}

int * get_ticket_no(char *mob_no)
{
    Passenger pr;
    FILE * fp = fopen("allbookings.dat", "rb");
    int count = 0,i=0;
    if(fp == NULL)
        return;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.mob_no, mob_no) == 0)
        {
            count++;
        }
    }
    if(count == 0)
        return NULL;
    rewind(fp);
    i=0;
    int *arr_mob_no = (int *)malloc((count+1) * sizeof(int));
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.mob_no, mob_no) == 0)
        {
            *(arr_mob_no + i) = pr.ticketno;
            i++;
        }
    }
    arr_mob_no[i] = -1;
    fclose(fp);
    return arr_mob_no;
}

void view_all_tickets(char * mob_no, int * arr_ticket_no)
{
    if(arr_ticket_no == NULL)
    {
        gotoxy(1, 24);
        textcolor(4);
        printf("Error! There is no ticket booked with contact no - %s", mob_no);
        textcolor(11);
        printf("\npress any key to go back to main menu");
        getch();
        return;
    }
    textcolor(14);
    printf("\n\n    The ticket(s) number booked via Contact no - %s", mob_no);
    textcolor(11);
    printf("\n");
    for(int i=0;*(arr_ticket_no + i) != -1;i++)
    {
        printf("\n\tTicket number - %d", *(arr_ticket_no + i));
    }
    gotoxy(1, 25);
    textcolor(13);
    printf("Press any key to go back to main menu.");
    getch();
}

void view_all_bookings()
{
    FILE * fp = fopen("allbookings.dat", "rb");
    Passenger pr;
    int found = 0;
    if(fp == NULL)
    {
        error:
            system("cls");
            textcolor(4);
            printf("\n\n\nThere are no bookings press any key to go back to main menu.");
            getch();
            fclose(fp);
            return;
    }
    system("cls");
    textcolor(3);
    printf("\n\n TICKET NO       NAME\t\tCLASS  TRAIN  GENDER\tAGE\tCONTACT NO");
    textcolor(14);
    printf("\n________________________________________________________________________________\n");
    textcolor(11);
    if(fp == NULL)
        return;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        printf("\n\n     %d\t\t%s\t",pr.ticketno, pr.p_name);
        if(strlen(pr.p_name) < 9)
            printf("\t");
        printf(" %c-AC\t%s\t%c\t%d\t%s", pr.p_class, pr.train_no, pr.gender, pr.age, pr.mob_no);
        found = 1;
    }
    if(found == 0)
        goto error;
    textcolor(14);
    printf("\n\n________________________________________________________________________________\n");
    gotoxy(50, 1);
    textcolor(10);
    printf("Press any key to continue");
    fclose(fp);
    getch();
}

char* accept_train_no()
{
    static char * train_no[11];
    char *pos;
    system("cls");
    gotoxy(63, 1);
    textcolor(10);
    printf("Press 0 to exit");
    gotoxy(1, 2);
    textcolor(3);
    printf("Enter train number: ");
    fflush(stdin);
    train:
        fgets(train_no,11,stdin);
        pos = strchr(train_no, '\n');
        if(pos != NULL)
            *pos = '\0';
        if(strcmp(train_no, "0") == 0)
            return NULL;
        if(check_train_no(train_no) == 0)
        {
            gotoxy(1, 25);
            textcolor(4);
            printf("Error! Given train no does not exists ");
            gotoxy(21, 2);
            printf("                  ");
            gotoxy(22, 2);
            textcolor(3);
            goto train;
        }
        return train_no;
}

void view_booking(char * train_no)
{
    FILE * fp = fopen("allbookings.dat", "rb");
    Passenger pr;
    int found = 0;
    if(fp == NULL)
    {
        error:
            system("cls");
            textcolor(4);
            printf("\n\n\nThere are no bookings press any key to go back to main menu.");
            getch();
            fclose(fp);
            return;
    }
    textcolor(13);
    system("cls");
    printf("\n\n\tBooking of Train No. %s", train_no);
    textcolor(3);
    printf("\n\n TICKET NO       NAME\t\tCLASS  TRAIN  GENDER\tAGE\tCONTACT NO");
    textcolor(14);
    printf("\n________________________________________________________________________________\n");
    textcolor(11);
    if(fp == NULL)
        return;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        if(strcmp(pr.train_no, train_no) == 0)
        {
            printf("\n\n     %d\t\t%s\t",pr.ticketno, pr.p_name);
            if(strlen(pr.p_name) < 9)
                printf("\t");
            printf(" %c-AC\t%s\t%c\t%d\t%s", pr.p_class, pr.train_no, pr.gender, pr.age, pr.mob_no);
            found = 1;
        }
    }
    if(found == 0)
        goto error;
    textcolor(14);
    printf("\n\n________________________________________________________________________________\n");
    gotoxy(50, 1);
    textcolor(10);
    printf("Press any key to continue");
    fclose(fp);
    getch();
}

int cancel_ticket(int ticket_no)
{
    FILE * fp1 = fopen("allbookings.dat", "rb");
    FILE * fp2 = fopen("temp.dat", "wb");
    Passenger pr;
    int found = 0;

    while(fread(&pr, sizeof(pr), 1, fp1) == 1)
    {
        if(pr.ticketno != ticket_no)
        {
            fwrite(&pr, sizeof(Passenger), 1, fp2);
        }
        else
            found = 1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found == 0)
    {
        remove("temp.dat");
    }
    else
    {
        remove("allbookings.dat");
        rename("temp.dat", "allbookings.dat");
    }
    return found;
}

/*  //This will delete the train from alltrains.dat
int cancel_train(char * train_no)
{
    FILE * fp1 = fopen("alltrains.dat", "rb");
    FILE * fp2 = fopen("temp.dat", "wb");
    Train tr;
    int found = 0;

    while(fread(&tr, sizeof(tr), 1, fp1) == 1)
    {
        if(strcmp(tr.train_no, train_no) != 0)
        {
            fwrite(&tr, sizeof(tr), 1, fp2);
        }
        else
            found = 1;
    }
    /*fclose(fp1);
    fclose(fp2);
    if(found == 0)
    {
        remove("temp.dat");
    }
    else
    {
        remove("alltrains.dat");
        rename("temp.dat", "alltrains.dat");
    }
    del_all_ticket(train_no);
    return found;
}*/

void del_all_ticket(char * train_no)
{
    FILE * fp = fopen("allbookings.dat", "rb");
    Passenger pr;
    int count=0;
    while(fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if(strcmp(pr.train_no, train_no) == 0)
            count++;
    }
    rewind(fp);
    int arr_ticket_no[count];
    count = 0;
    while(fread(&pr, sizeof(pr), 1, fp) == 1)
    {
        if(strcmp(pr.train_no, train_no) == 0)
        {
            arr_ticket_no[count] = pr.ticketno;
            count++;
        }
    }
    fclose(fp);
    for(int i=0; i<count;i++)
    {
        cancel_ticket(arr_ticket_no[i]);
    }
    return;
}

void bye_message()
{
    system("cls");
    gotoxy(20, 5);
    printf("Thank you Hope you liked our service\n\n\n\n");
    getch();
}
