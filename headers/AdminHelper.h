//
// Created by asmaa160195 on 8/20/2021.
//

#ifndef MAIN_C_ADMINHELPER_H
#define MAIN_C_ADMINHELPER_H

#define slotsNo         5       //default number of doctor slots

typedef struct node_type record;

struct node_type{
    u8 name[20];
    u16 age;
    u8 gender;
    u16 id;
    record *next;
};

void LoginMode(void);
void AddRecord(u8 n[], u16 a, u8 g, u16 iD);
void EditRecord(u16 iD);
void ReserveSlot(void);
void CancelReservation(u16 iD);
void PrintRecordList(void);

#endif //MAIN_C_ADMINHELPER_H
