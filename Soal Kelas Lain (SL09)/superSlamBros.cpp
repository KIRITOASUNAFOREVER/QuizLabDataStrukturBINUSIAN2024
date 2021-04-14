#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define enterAfter getchar(); getchar()
#define clearCLI system("cls"); printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

int ID = 0;

struct data{
    char charID[6], name[26];
    int power, defend, speed;

    data *next;
}*table[10];

data *createNode(char charID[], char name[], int power, int defend, int speed){
    data *newNode = (data*)malloc(sizeof(data));
    newNode->power = power;
    newNode->defend = defend;
    newNode->speed = speed;
    strcpy(newNode->name, name);
    strcpy(newNode->charID, charID);
    newNode->next = NULL;

    return newNode;
}

void push(char charID[], char name[], int power, int defend, int speed, int key){
    if(!table[key]){
        table[key] = createNode(charID, name, power, defend, speed); 
    } else {
        data *curr = table[key];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = createNode(charID, name, power, defend, speed); 
    }
}

void viewChallanger(){
    clearCLI;
    bool dataAvailable = false;
    for(int i = 0; i < 10; i++){
        if(table[i]){
            dataAvailable = true;
        }
    }
    if(!dataAvailable) {
        printf("        No Data Found!\n        Press enter to continue..."); enterAfter;
        return;
    }
    printf("        ==================\n         Challenger List\n        ==================\n         _____________________________________________________\n        |    ID |                      Name | PWR | DEF | SPD |\n        |_______|___________________________|_____|_____|_____|\n");
    for(int IDcounter = 1; IDcounter <= ID; IDcounter++){
        int counter = 0;
        char charID[6];
        charID[counter++] = 'C';
        charID[counter++] = 'H';
        charID[counter++] =  (IDcounter/100) % 10 + '0';
        charID[counter++] =  (IDcounter/10) % 10 + '0';
        charID[counter++] =  IDcounter % 10 +'0';
        charID[counter++] = '\0';
        int key = IDcounter/10 % 10;
        data* curr = table[key];
        while(strcmp(curr->charID, charID)!=0 && curr->next){
            curr = curr->next;
        }
        if(strcmp(curr->charID, charID)==0){
            printf("        | %s |                       %s | %d | %d | %d |\n", curr->charID, curr->name, curr->power, curr->defend, curr->speed);
        }
    }
    printf("        |_______|___________________________|_____|_____|_____|\n        Press enter to continue..."); enterAfter;
}



void addChallenger(){
    clearCLI;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    ID+=1;
    char name[26];
    while(true){
        printf("        Input Challenger name [3-25 characters]: ");
        scanf(" %[^\n]", name);
        if(strlen(name) >= 3 && strlen(name) <= 25){
            break;
        }
    }
    int power, defend, speed;
    while(true){
        printf("        Input Power, Defend and Speed [Total = 350]:\n        Power [100-200]: ");
        scanf(" %d", &power);
        printf("        Defend [50-100]: ");
        scanf(" %d", &defend);
        printf("        Speed [100-150]: ");
        scanf(" %d", &speed);
        if(power < 100 || power > 200 || defend < 50 || defend > 100 || speed  < 100 || speed > 150 || power + speed + defend < 350 || power + speed + defend > 350){
            continue;
        } else {
            break;
        }
    }
    char charID[6];
    int counter = 0;
    charID[counter++] = 'C';
    charID[counter++] = 'H';
    charID[counter++] =  (ID/100) % 10 + '0';
    charID[counter++] =  (ID/10) % 10 + '0';
    charID[counter++] =  ID % 10 +'0';
    charID[counter++] = '\0';
    system("cls");
    clearCLI;
    printf("\n\n\n\n");
    printf("        ===================\n         Challenger Detail\n        ===================\n        ID      : %s\n        Name    : %s\n        Power   : %d\n        Defend  : %d\n        Speed   : %d\n\n        %s Joins the Battle!\n        Press enter to continue...", charID, name, power, defend, speed, name);
    enterAfter;
    int key = ID/10 % 10;
    push(charID ,name, power, defend, speed, key);
}

bool viewChallangerDelete(){
    clearCLI;
    bool dataAvailable = false;
    for(int i = 0; i < 10; i++){
        if(table[i]){
            dataAvailable = true;
        }
    }
    if(!dataAvailable) {
        printf("        No Data Found!\n        Press enter to continue..."); enterAfter;
        return false;
    }
    printf("        ==================\n         Challenger List\n        ==================\n         _____________________________________________________\n        |    ID |                      Name | PWR | DEF | SPD |\n        |_______|___________________________|_____|_____|_____|\n");
    for(int IDcounter = 1; IDcounter <= ID; IDcounter++){
        int counter = 0;
        char charID[6];
        charID[counter++] = 'C';
        charID[counter++] = 'H';
        charID[counter++] =  (IDcounter/100) % 10 + '0';
        charID[counter++] =  (IDcounter/10) % 10 + '0';
        charID[counter++] =  IDcounter % 10 +'0';
        charID[counter++] = '\0';
        int key = IDcounter/10 % 10;
        data* curr = table[key];
        while(strcmp(curr->charID, charID)!=0 && curr->next){
            curr = curr->next;
        }
        if(strcmp(curr->charID, charID)==0){
            printf("        | %s | %25s | %3d | %3d | %3d |\n", curr->charID, curr->name, curr->power, curr->defend, curr->speed);
        }
    }
    printf("        |_______|___________________________|_____|_____|_____|\n");
    return true;
}


void deleteChallenger(){
    clearCLI;
    if(viewChallangerDelete()){
        while(true){
            printf("        Enter Challenger ID [CHXXX (X is 0-9)]: ");
            char charID[6]; scanf(" %[^\n]", charID);
            if(strlen(charID) > 5){
                continue;
            }
            if(charID[0] != 'C' || charID[1] != 'H' || charID[2] - '0' < 0 || charID[2] - '0' > 9 || charID[3] - '0' < 0 || charID[3] - '0' > 9 || charID[4] - '0' < 0 || charID[4] - '0' > 9 ){
                continue;
            }
            int IDfetch = ((charID[2] - '0') * 100) + ((charID[3] - '0') * 10) + ((charID[4] - '0')); 
            int key = IDfetch/10 % 10;
            if(strcmp(table[key]->charID, charID) == 0){
                data *deleteThis = table[key];
                printf("        ===================\n         Challenger Detail\n        ===================\n        ID      : %s\n        Name    : %s\n        Power   : %d\n        Defend  : %d\n        Speed   : %d\n        Press enter to continue...", deleteThis->charID, deleteThis->name, deleteThis->power, deleteThis->defend, deleteThis->speed); enterAfter;
                table[key] = table[key]->next;
                free(deleteThis);
                deleteThis = NULL;
                return;
            } else {
                bool found = false;
                data* curr = table[key];
                while(curr->next){
                    if(strcmp(curr->next->charID, charID) != 0){                    
                        curr = curr->next;
                    } else {
                        data *deleteThis = curr->next;
                        printf("        ===================\n         Challenger Detail\n        ===================\n        ID      : %s\n        Name    : %s\n        Power   : %d\n        Defend  : %d\n        Speed   : %d\n        Press enter to continue...", deleteThis->charID, deleteThis->name, deleteThis->power,deleteThis->defend, deleteThis->speed); enterAfter;
                        curr->next = curr->next->next;
                        free(deleteThis); 
                        deleteThis = NULL;
                        found = true;
                        return;
                    }
                }
                if(!found){
                    printf("        Challenger ID not Found!\n        Press enter to continue..."); enterAfter;
                    return;
                }
            }
        }
    }
}

int menu(){
    while(true){
        clearCLI;
        printf("                     ____  _  _  ____  ____  ____\n                    / ___)/ )( \\(  _ \\(  __)(  _ \\\n                    \\___ \\) \\/ ( ) __/ ) _)  )   /\n                    (____/\\____/(__)  (____)(__\\_)\n           ____  __     __   _  _    ____  ____   __   ____\n          / ___)(  )   / _\\ ( \\/ )  (  _ \\(  _ \\ /  \\ / ___)\n          \\___ \\/ (_/\\/    \\/ \\/ \\   ) _ ( )   /(  O )\\___ \\\n          (____/\\____/\\_/\\_/\\_)(_/  (____/(__\\_) \\__/ (____/\n        ======================================================\n        1. Add Challenger\n        2. View Challenger\n        3. Delete Challenger\n        4. Exit\n        >> ");
        int choose; scanf(" %d", &choose);
        switch(choose){
            case 1:
                addChallenger();
                break;
            case 2:
                viewChallanger();
                break;
            case 3:
                deleteChallenger();
                break;
            case 4:
                return 0;
                break;
        }
    }
}

int main(){
    for (int i  = 0; i < 10; i++){
        table[i] = NULL;
    }
    menu();
}
