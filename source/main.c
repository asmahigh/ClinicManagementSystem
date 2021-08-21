#include <stdio.h>
#include <stdbool.h>
#include "../headers/STD_Types.h"
#include "../headers/AdminHelper.h"
#include "../headers/UserHelper.h"
#include "../headers/Login.h"

u8 n[20];
u16 a;
u8 g;
u16 iD;
u8 mode;
record head;

int main() {

    ChooseMode();
    AdminUser();

    return 0;
}
