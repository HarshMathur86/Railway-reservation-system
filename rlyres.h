#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED


struct Train
{
    char train_no[10];
    char from[10];
    char to[10];
    int fac_fare;
    int sac_fare;
};

struct Passenger
{
    char p_name[20];
    char gender;
    char train_no[10];
    char p_class;
    char address[30];
    int age;
    int ticketno;
    char mob_no[12];
};

typedef struct Train Train;
typedef struct Passenger Passenger;

int enterchoice();       //For displaying available options to user & returning choice entered by him/her to main( ) function
void add_trains();     //For adding some train details to a file
void view_trains();    //For displaying details of all the trains from the file
int book_ticket(Passenger *);   //For accepting a PASSENGER variable as argument and booking his ticket . If booking is successful it will return the ticket no , otherwise -1. It also saves the booked ticket to a FILE.
int * get_ticket_no(char *);    //For accepting a passenger's mobile number as argument and returning all his ticket nos. If record is not present it returns NULL.
void view_ticket(int);             //For accepting a ticket number as argument and displaying the ticket details.
void view_all_bookings();     //For displaying all the booked tickets.
void view_booking(char *);  //For accepting a train number as argument and displaying the ticket booked for that train.
int cancel_ticket(int);            //For accepting a ticket number as argument and canceling the ticket and  if the ticket is cancelled successfully it returns 1 otherwise it returns 0
//int cancel_train(char *);       //For accepting a train number and deleting all the tickets of that train. If the cancellation is done  successfully it returns 1 otherwise it returns 0

//book_ticket() supporting functions
Passenger * get_passenger_details(); //main() will call this and if input is success then book_ticket() is called.
int check_train_no(char *);         //Check whether th train no exist or not. return 1 if exits otherwise 0.
int get_booked_ticket_count(char *, char);  //accept train_no and class F/S & return no of tickets booked in the given train in given class.
int last_ticket_no();           //Return the ticket no of last booked ticket and if no ticket is booked it will return 0.
int check_mob_no(char *);
//void err_handler(int x, int y)    //in this the x is the input x co-ordinate and y is the rank of error which is also work as a y co-ordinate for the gotoxy() Function
//Line 45 err_handler() will help to reduce "70" line of code of get_passenger_details()
int accept_ticket_no();//accept ticket number and perform all the validations and return the ticket no

char* accept_mob_no();//Takes the mobile no for viewing all tickets book by a mob no
void view_all_tickets(char *, int *);//accepts mob_no and array of ticket_no and print the tickets booked
char* accept_train_no();//This will accept train no with all validations and return train no
void del_all_ticket(char *);//Delete all the ticket of the canceled train no.
void bye_message(); //a short message at the end
#endif // RLYRES_H_INCLUDED
