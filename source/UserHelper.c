//
// Created by asmaa160195 on 8/20/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/STD_Types.h"
#include "../headers/UserHelper.h"
#include "../headers/AdminHelper.h"


extern record head;
extern bool sameid;
extern bool lastf;
extern u16 slots [slotsNo];

void ViewRecord(u16 iD) {

    /* Loop through the entire list to search for nodes with same ID */
    record *last;
    last = &head;

    while (!sameid && !lastf) {

        if (last -> id == iD) {
            sameid = true;
            break;
        }
        if (last -> next == NULL)  {
            lastf = true;
        }
        last = (last->next);
    }


    if (sameid == false) {
        printf("\nSorry! This ID doesn't exist. Please Try again\n");
        lastf = false;
        return;
    }

    else {
        printf("Here's the record info..\n");

        //print the record info
        printf("Name is: ");
        puts(last -> name);
        printf("Age is: %d\n", last -> age);
        printf("gender is %c\n",last -> gender);
        printf("ID is %d\n",last -> id);
        sameid = false;
        lastf = false;
        return;
    }

}


void ViewReservation(u16 iD) {
    u16 i;
    bool temp[slotsNo] = {false};
    for (i=1; i<=5; i++) {
        if (slots[i - 1] == iD) {
            temp[i - 1] = true;
        }
    }
    printf("\nThe following slots are reserved..\n");
    for (i=1; i<=slotsNo; i++) {
        if (temp[i-1] == true) {
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
}

