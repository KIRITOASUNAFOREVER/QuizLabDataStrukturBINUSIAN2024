#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define enterAfter getchar(); getchar()
#define clearCLI system("cls")

int ID = 0;

struct data{
    char charID[6], name[21], genre[10];
    float rating;
    int year;
    data *next;
}*table[100];

data *createNode(char charID[], char name[], char genre[], float rating, int year){
    data *newNode = (data*)malloc(sizeof(data));
    newNode->rating = rating;
    newNode->year = year;
    strcpy(newNode->name, name);
    strcpy(newNode->charID, charID);
    genre[0] = toupper(genre[0]);
    strcpy(newNode->genre, genre);
    newNode->next = NULL;

    return newNode;
}

void push(char charID[], char name[], char genre[], float rating, int year, int key){
    if(!table[key]){
        table[key] = createNode(charID, name, genre, rating, year); 
    } else {
        data *curr = table[key];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = createNode(charID, name, genre, rating, year); 
    }
}

void viewMovies(){
    clearCLI;
    printf(" LIST OF FILM\n ------------\n\n");
    bool dataAvailable = false;
    for(int i = 0; i < 100; i++){
        if(table[i]){
            dataAvailable = true;
        }
    }
    if(!dataAvailable) {
        printf(" No data !!!\n\n Press any key to continue..."); enterAfter;
        return;
    }
    for(int IDcounter = 0; IDcounter < ID; IDcounter++){
        int counter = 2;
        char charID[6];
        charID[counter++] =  (IDcounter/100) % 10 + '0';
        charID[counter++] =  (IDcounter/10) % 10 + '0';
        charID[counter++] =  IDcounter % 10 +'0';
        charID[counter++] = '\0';
        int key = (charID[4] + charID[2] - charID[3]) % 100;
        data* curr = table[key];
        if(!curr){
            continue;
        }
        while((curr->charID[2] != charID[2] || curr->charID[3] != charID[3] || curr->charID[4] != charID[4]) && curr->next){
            curr = curr->next;
        }
        if(curr->charID[2] == charID[2] && curr->charID[3] == charID[3] && curr->charID[4] == charID[4]){
            printf(" ID : [%s]\n TITLE : %s\n GENRE : %s\n RATING : %.1f\n YEAR : %d\n\n", curr->charID, curr->name, curr->genre, curr->rating, curr->year);
        }
    }
    printf(" Press enter to continue..."); enterAfter;
}



void addMovies(){
    clearCLI;
    char name[21];
    printf(" ADD NEW MOVIE\n -------------\n\n");
    while(true){
        printf(" Input Movie Title [LENGTH : 5 - 20]\n > ");
        scanf(" %[^\n]", name);
        if(strlen(name) >= 5 && strlen(name) <= 20){
            break;
        }
    }
    char genre[10];
    while(true){
        printf(" Input Movie Genre [Adventure | Romance | Comedies] (CASE INSENSITIVE)\n > ");
        scanf(" %[^\n]", genre);
        for(int i = 0; i < strlen(genre); i++){
            genre[i] = tolower(genre[i]);
        }
        if(strcmp(genre, "adventure") == 0 || strcmp(genre, "romance") == 0 || strcmp(genre, "comedies") == 0){
            break;
        }
    }
    float rating;
    while(true){
        printf(" Input Movie's Rating [RANGE : 0.0 - 5.0]\n > ");
        scanf(" %f", &rating);
        if(rating < 0.0 || rating  > 5.0){
            continue;
        } else {
            break;
        }
    }
    int year;
    while(true){
        printf(" Input Movie's published year [RANGE : 1900 - 2020]\n > ");
        scanf(" %d", &year);
        if(year < 1900 || year  > 2020){
            continue;
        } else {
            break;
        }
    }
    char charID[6];
    int counter = 0;
    charID[counter++] = genre[0] - 'a' + 'A';
    charID[counter++] = genre[strlen(genre) - 1] - 'a' + 'A';
    charID[counter++] =  (ID/100) % 10 + '0';
    charID[counter++] =  (ID/10) % 10 + '0';
    charID[counter++] =  ID % 10 +'0';
    charID[counter++] = '\0';
    printf("\n New Movie with ID [%s] has been added !", charID);
    enterAfter;
    int key = (charID[4] + charID[2] - charID[3]) % 100;
    push(charID, name, genre, rating, year, key);
    ID+=1;
}

bool viewMoviesDelete(){
    clearCLI;
    printf(" DELETE MOVIE\n ------------\n\n");
    bool dataAvailable = false;
    for(int i = 0; i < 100; i++){
        if(table[i]){
            dataAvailable = true;
        }
    }
    if(!dataAvailable) {
        printf(" No data !!!\n\n Press any key to continue..."); enterAfter;
        return false;
    }
    for(int IDcounter = 0; IDcounter < ID; IDcounter++){
        int counter = 2;
        char charID[6];
        charID[counter++] =  (IDcounter/100) % 10 + '0';
        charID[counter++] =  (IDcounter/10) % 10 + '0';
        charID[counter++] =  IDcounter % 10 +'0';
        charID[counter++] = '\0';
        int key = (charID[4] + charID[2] - charID[3]) % 100;
        data* curr = table[key];
        if(!curr){
            continue;
        }
        while((curr->charID[2] != charID[2] || curr->charID[3] != charID[3] || curr->charID[4] != charID[4]) && curr->next){
            curr = curr->next;
        }
        if(curr->charID[2] == charID[2] && curr->charID[3] == charID[3] && curr->charID[4] == charID[4]){
            printf(" ID : [%s]\n TITLE : %s\n GENRE : %s\n RATING : %.1f\n YEAR : %d\n\n", curr->charID, curr->name, curr->genre, curr->rating, curr->year);
        }
    }
    return true;
}


void deleteMovies(){
    clearCLI;
    if(viewMoviesDelete()){
        while(true){
            printf(" Choose the Movie's ID [AEXXX | REXXX |CSXXX]\n > ");
            char charID[6]; scanf(" %[^\n]", charID);
            if(strlen(charID) > 5){
                continue;
            }
            if(((charID[0] != 'A' || charID[1] != 'E') && (charID[0] != 'R' || charID[1] != 'E') && (charID[0] != 'C' || charID[1] != 'S')) || charID[2] - '0' < 0 || charID[2] - '0' > 9 || charID[3] - '0' < 0 || charID[3] - '0' > 9 || charID[4] - '0' < 0 || charID[4] - '0' > 9 ){
                continue;
            }
            int key = (charID[4] + charID[2] - charID[3]) % 100;
            if(!table[key]){
                printf(" Movie not found !!!"); enterAfter;
                return;
            } else if(strcmp(table[key]->charID, charID) == 0){
                data *deleteThis = table[key];
                printf("\n %s - %s deleted !!!", charID, deleteThis->name); enterAfter;
                table[key] = table[key]->next;
                free(deleteThis);
                deleteThis = NULL;
                return;
            } else {
                bool found = false;
                data* curr = table[key];
                while(curr->next){
                    if(!curr) break;
                    if(strcmp(curr->next->charID, charID) != 0){                    
                        curr = curr->next;
                    } else {
                        data *deleteThis = curr->next;
                        printf("\n %s - %s deleted !!!", charID, deleteThis->name); enterAfter;
                        curr->next = curr->next->next;
                        free(deleteThis); 
                        deleteThis = NULL;
                        found = true;
                        return;
                    }
                }
                if(!found){
                    printf(" Movie not found !!!"); enterAfter;
                    return;
                }
            }
        }
    }
}

int menu(){
    while(true){
        clearCLI;
        printf(" NEDFLIZ\n -------\n 1. Add New Movies\n 2. View Movies\n 3. Delete Movies\n 4. Exit\n Choose [1 - 4] > ");
        int choose; scanf(" %d", &choose);
        switch(choose){
            case 1:
                addMovies();
                break;
            case 2:
                viewMovies();
                break;
            case 3:
                deleteMovies();
                break;
            case 4:
                return 0;
                break;
        }
    }
}

int main(){
    for (int i  = 0; i < 100; i++){
        table[i] = NULL;
    }
    menu();
}
