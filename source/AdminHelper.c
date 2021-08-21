//
// Created by asmaa160195 on 8/20/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/STD_Types.h"
#include "../headers/AdminHelper.h"

extern record head;
extern u8 n[20];
extern u16 a;
extern u8 g;
extern u16 iD;

u32 ListLength = 0;
bool sameid= false;
bool lastf = false;
bool available = false;
u16 slots [slotsNo] = {0};        //each slot equals 0 is not reserved and equals the patient iD if reserved.
                                  //  2   2:30   3   4   4:30

void AddRecord(u8 n[], u16 a, u8 g, u16 iD) {
    int i;
    /* First Node to Create */
    if (ListLength ==0) {
        for(i=0; i<strlen(n); i++) {
            head.name[i] = n[i];
        }
        head.age = a;
        head.gender = g;
        head.id = iD;
        head.next = NULL;
    }
    else {
        record *last;

        /* Allocate the node */
        record *new = (record*) malloc(sizeof(record));
        /* Assign the received value to the new node */
        for(i=0; i<strlen(n); i++) {
            new ->name[i] = n[i];   // *new.name
        }
        new -> age = a;
        new -> gender = g;

        /* Loop through the entire list to search for nodes with same ID */
        last = &head;
        while (!sameid && !lastf) {
            if (last -> id == iD) {
                sameid = true;
            }
            if (last -> next == NULL)  {
                lastf = true;
            }
            last = (last->next);
        }

        if (sameid == false) {
            new -> id = iD;
            lastf = false;
        }
        else {
            printf("\nSorry! This ID already exists. Please Try again\n");
            sameid = false;
            lastf = false;
            return;
        }

        /* Make the new node next pointer to Null,
        as it will be added to the end of the list */
        new -> next = NULL;

        /* Search for the last node to make it point to the new last node */
        last = &head;
        while (last->next != NULL){
            last = (last->next);
        }

        last->next = new;
    }

    /* Increase the list length by one node */
    ListLength++;

    return;

}


void EditRecord(u16 iD) {
    int i;
    record *last;
    last = &head;

    while (!sameid && !lastf) {
        printf("\nSearching if the ID exists....\n");

        //searching for the node with that id
        if (last -> id == iD) {
            sameid = true;
            printf("Found the ID!\n");
            printf("Here's the old record info..\n");

            //print the old record info
            printf("Name is: ");
            puts(last -> name);
            printf("Age is: %d\n", last -> age);
            printf("gender is %c\n",last -> gender);
            printf("ID is %d\n",last -> id);
            printf("You can edit the record now.. Please enter the following info..\n");

            //scanf the new record info
            printf("\nPatient Name (use '-' instead of space): ");
            scanf("%s" , &n);
            for(i=0; i<strlen(n); i++) {
                last ->name[i] = n[i];   // *new.name
            }
            printf("\nPatient age: ");
            scanf("%d" , &a);
            last -> age = a;
            printf("\nPatient Gender (m:0,f:1): ");
            scanf("%c" , &g);
            scanf("%c" , &g);       //repeated to fix the scanf with character issue!
            last -> gender = g;
        }

        if (last -> next == NULL)  {
            lastf = true;
        }
        last = (last->next);
    }

    if (lastf == true) {
        printf("\nSorry! This ID doesn't exists.\n");
        lastf = false;
        return;
    }

    if (sameid == true) {
        sameid = false;
    }

    return;
}


void ReserveSlot(void) {
    u16 i;
    u16 s;

    printf("\nOnly the following slots are available..\n");
    for (i=1; i<=slotsNo; i++) {
        if (slots[i-1] == 0) {
            switch(i) {
                case 1:
                    printf("Slot %d: 2PM - 2:30PM\n" , i);
                    break;
                case 2:
                    printf("Slot %d: 2:30PM - 3PM\n", i);
                    break;
                case 3:
                    printf("Slot %d: 3PM - 3:30PM\n", i);
                    break;
                case 4:
                    printf("Slot %d: 4PM - 4:30PM\n", i);
                    break;
                case 5:
                    printf("Slot %d: 4:30PM - 5PM\n", i);
                    break;
            }
        }
    }

    printf("Please enter the desired slot number: ");
    scanf("%d", &s);

    //check if the slot is valid
    while(!available) {
        for (i=1; i<=slotsNo; i++) {
            if (slots[i - 1] == 0) {
                if (s == i) {
                    available = true;
                    break;
                }
            }
        }
        if (i> 5) {
            break;
        }
    }

    if ( (!available) || (1> s) || (s>5) ) {
        printf("Sorry! Reservation failed. Invalid slot choice.\n");
        return;
    }
    else if (available) {
        available = false;
        printf("\nPlease enter the patient ID: ");
        scanf("%d", &iD);
    }

    //check if the id is vaild
    record *last;
    last = &head;
    while (!sameid && !lastf) {
        printf("\nSearching if the ID exists....\n");

        //searching for the node with that id
        if (last -> id == iD) {
            sameid = true;
            slots[s-1] = iD;
        }

        if (last -> next == NULL)  {
            lastf = true;
        }

        last = (last->next);
    }

    if (sameid == true) {
        slots[s-1] = iD;
        printf("\nDone! Slot is successfully reserved!\n");
        sameid = false;
        lastf = false;
        return;
    }
    else {
        printf("\nSorry! Reservation failed. This ID doesn't exists.\n");
        lastf = false;
        return;
    }
}



void CancelReservation(u16 iD) {
    u16 i;
    for (i=1; i<=slotsNo; i++){
        if (slots[i-1] == iD) {
            slots[i-1] = 0;
            printf("\nThe reservation for patient with ID %d is cancelled\n", iD);
            return;
        }
    }

    printf("\nSorry! This ID doesn't have a reservation!\n");
    return;
}


void PrintRecordList(void)
{
    int i;
    printf("\n\n----------------------\n");
    /* at lease 1 node is created */
    if (ListLength > 0)
    {
        record *last = &head;
        u32 i = 1;

        /* Print the list head */
        printf("Patient Number %d : \n", i);
        printf("Name is: ");
        puts(last -> name);
        printf("Age is: %d\n", last -> age);
        printf("gender is %c\n",last -> gender);
        printf("ID is %d\n",last -> id);
        /* Print all nodes util you find the last node
        which has the next pointer equals to NULL  */
        while ((last -> next) != NULL)
        {
            i++;
            last = last -> next;
            printf("Patient Number %d : \n", i);
            printf("Name is: ");
            puts(last -> name);
            printf("Age is: %d\n", last -> age);
            printf("gender is %c\n",last -> gender);
            printf("ID is %d\n",last -> id);
        }
    }

    else
    {
        printf("List is Empty\n");
    }

    printf("----------------------\n\n\n");
}

