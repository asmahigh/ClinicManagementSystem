//
// Created by asmaa160195 on 8/20/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/STD_Types.h"
#include "../headers/Login.h"


bool correctmode = false;
bool AdminToUser = false;
bool UserToAdmin = false;

extern u8 n[20];
extern u16 a;
extern u8 g;
extern u16 iD;
extern u8 mode;


void ChooseMode () {

    printf("Welcome to the system!\nPlease Choose the login mode.\nEnter a/A for ADMIN and u/U for USER.\n");

    do {
        printf("Mode: ");
        scanf("%c" , &mode);
        if ((mode =='a') || (mode =='A') || (mode =='u') || (mode =='U')) {
            correctmode = true;
        }
        else {
            scanf("%c" , &mode);        //repeated to fix the scanf with char issue
        }
        if ((mode =='a') || (mode =='A') || (mode =='u') || (mode =='U')) {
            correctmode = true;
        }
        else {
            printf("\nSorry! Login failed. Invalid mode choice.\n");
        }
    } while(correctmode != true) ;

    return;

}

void AdminUser() {
    u16 password=0;
    u16 trial = 2;
    u8 task;
    AdminToUser = false;
    UserToAdmin = false;

    //Admin Mode
    if( (mode == 'a')|| (mode == 'A') ){
        printf("\nAdmin mode.. Please Enter the password.\nPassword:");
        scanf("%d" , &password);
        if (password==1234) {
            printf("\nPassword is Correct.\nYou are now in the ADMIN mode.\n");
        }
        else {
            while((trial != 0) && (password != 1234)){
                printf("Password is Incorrect. Please try again.\nPassword:");
                scanf("%d" , &password);
                trial--;
            }
            if (password == 1234) {
                printf("\nPassword is Correct.\nYou are now in the ADMIN mode.\n");
            }
            else {
                printf("Sorry! Incorrect password for 3 consecutive times.\nThe system shall close now.\n");
                return 0;
            }
        }


        while (AdminToUser == false){
            printf("\nTo add new patient record, press 1.\n"
                   "To edit patient record, press 2.\n"
                   "To reserve a slot with the doctor, press 3.\n"
                   "To cancel reservation, press 4.\n"
                   "To switch the mode, press 5.\n"
                   "To end the program, press 0\n"
                   "TASK: ");

            scanf("%d" , &task);


            switch(task) {
                case 0:
                    return;
                case 1:
                    printf("\nPatient Name (use '-' instead of space): ");
                    scanf("%s" , &n);
                    printf("\nPatient age: ");
                    scanf("%d" , &a);
                    printf("\nPatient Gender (m:0,f:1): ");
                    scanf("%c" , &g);
                    scanf("%c" , &g);
                    printf("\nPatient ID: ");
                    scanf("%d" , &iD);
                    AddRecord(n,a,g,iD);
                    break;
                case 2:
                    printf("\nPlease enter the patient ID: ");
                    scanf("%d" , &iD);
                    EditRecord(iD);
                    PrintRecordList();
                    break;
                case 3:
                    ReserveSlot();
                    break;
                case 4:
                    printf("\nPlease enter the ID to cancel the reservation: ");
                    scanf("%d" , &iD);
                    CancelReservation(iD);
                    break;
                case 5:
                    printf("\nYou chose to exit admin mode!\n");
                    AdminToUser = true;
                    break;
                default:
                    printf("\nSorry! Invalid Choice! Please try again.\n");
                    getchar();
                    break;
            }
        }
        ChooseMode();
        AdminUser();
    }

    //User Mode
    else if((mode == 'u') || (mode == 'U')){
        printf("\nYou are now in the USER mode.\n");

        while (UserToAdmin == false){
            printf("\nTo view patient record, press 1.\n"
                   "To view todays reservations., press 2.\n"
                   "To switch the mode, press 3.\n"
                   "To end the program, press 0\n"
                   "TASK: ");

            scanf("%d" , &task);

            switch(task) {
                case 0:
                    return;
                case 1:
                    printf("\nPlease enter the patient iD: ");
                    scanf("%d" , &iD);
                    ViewRecord(iD);
                    break;
                case 2:
                    printf("\nPlease enter the patient ID: ");
                    scanf("%d" , &iD);
                    ViewReservation(iD);
                    break;
                case 3:
                    printf("\nYou chose to exit user mode!\n");
                    UserToAdmin = true;
                    break;
                default:
                    printf("\nSorry! Invalid Choice! Please try again.\n");
            }
        }
        ChooseMode();
        AdminUser();
    }

}



