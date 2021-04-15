#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Nake
{
    char id[15];
    char name[55];
    char category[15];
    char brand[15];
    int stock;
    int price;
    Nake *prev;
    Nake *next;
};

Nake *head[55];
Nake *tail[55];
Nake *temp;

int index;
int track;
int i, ch;

Nake *assignNake(char *id, char *name, char *category, char *brand, int stock, int price)
{
    Nake *nake = (Nake *)malloc(sizeof(Nake));
    strcpy(nake->id, id);
    strcpy(nake->name, name);
    strcpy(nake->category, category);
    strcpy(nake->brand, brand);
    nake->stock = stock;
    nake->price = price;
    nake->prev = NULL;
    nake->next = NULL;

    return nake;
}

int doHash(char *id)
{
    int key = id[3] + id[4] - '0' - '0';
    key -= 1;

    return key % 55;
}

void insertNake(char *id, char *name, char *category, char *brand, int stock, int price)
{
    Nake *nake = assignNake(id, name, category, brand, stock, price);
    int idx = doHash(id);

    if (head[idx] != NULL)
    {
        tail[idx]->next = nake;
        nake->prev = tail[idx];
        tail[idx] = nake;
    }
    else
    {
        head[idx] = nake;
        tail[idx] = nake;
    }
    index++;
    track++;
}

void deleteNake(char *id)
{
    if (index > 0)
    {
        ch = 1;
        for (i = 0; i < 55; i++)
        {
            temp = head[i];
            if (temp)
            {
                while (temp)
                {
                    if (strcmp(temp->id, id) == 0)
                    {
                        if (temp == head[i])
                        {
                            if (head[i] != tail[i])
                            {
                                head[i] = head[i]->next;
                                head[i]->prev = NULL;
                                free(temp);
                            }
                            else
                            {
                                free(head[i]);
                                head[i] = NULL;
                                tail[i] = NULL;
                            }
                        }
                        else if (temp == tail[i])
                        {
                            if (head[i] != tail[i])
                            {
                                tail[i] = tail[i]->prev;
                                tail[i]->next = NULL;
                                free(temp);
                            }
                            else
                            {
                                free(tail[i]);
                                head[i] = NULL;
                                tail[i] = NULL;
                            }
                        }
                        else
                        {
                            temp->prev->next = temp->next;
                            temp->next->prev = temp->prev;
                            free(temp);
                            temp = NULL;
                        }
                        index--;
                        ch = 0;
                    }
                    temp = temp->next;
                }
            }
            if (ch == 0)
            {
                break;
            }
        }
    }
}

void viewNake()
{
    int j = 1;
    if (index > 0)
    {
        printf("======================================================================================\n");
        printf("| No |  ID   |        Product Name        |   Category   |  Brand  | Stock |  Price  |\n");
        printf("======================================================================================\n");
        for (i = 0; i < 55; i++)
        {
            temp = head[i];
            if (temp)
            {
                while (temp)
                {
                    printf("| %-2d | %-5s | %-26s | %-12s | %-7s | %-5d | %-7d |\n", j, temp->id, temp->name, temp->category, temp->brand, temp->stock, temp->price);
                    j++;
                    temp = temp->next;
                }
            }
        }
        printf("======================================================================================\n");
    }
    else
    {
        printf("There is No Data !\n\n\n");
    }
}

int main()
{
    int pil, ok, pul, sat, naga;
    char id[11] = "";
    char sg[11] = "";
    char name[31], category[11], brand[11];
    int stock, price;
    index = 0;
    track = 1;
    do
    {
        system("cls");
        viewNake();
        printf("NAKEWAREHOUSE\n");
        printf("=============\n");
        printf("1. Insert New Product\n");
        printf("2. Delete Product\n");
        printf("3. Exit\n");
        printf(">> ");
        scanf("%d", &pil);
        getchar();
        switch (pil)
        {
        case 1:
            system("cls");
            do
            {
                naga = 0;
                strcpy(name, "");
                printf("Input Product Name [5 - 24 character]: ");
                scanf("%[^\n]", name);
                getchar();
                naga = strlen(name);
            } while (naga < 5 || naga > 24);
            do
            {
                ok = 1;
                strcpy(category, "");
                printf("Choose Category [Shoes | Bag] (case sensitive): ");
                scanf("%[^\n]", category);
                getchar();
                if (strcmp(category, "Shoes") == 0 || strcmp(category, "Bag") == 0)
                {
                    ok = 0;
                }
            } while (ok);
            do
            {
                ok = 1;
                strcpy(brand, "");
                printf("Choose Brand [Nike | Adidas] (case sensitive) : ");
                scanf("%[^\n]", brand);
                getchar();
                if (strcmp(brand, "Nike") == 0 || strcmp(brand, "Adidas") == 0)
                {
                    ok = 0;
                }
            } while (ok);
            do
            {
                stock = 0;
                printf("Input Stock [ 50 - 150 ] : ");
                scanf("%d", &stock);
                getchar();
            } while (stock < 50 || stock > 150);
            do
            {
                price = 0;
                printf("Input Price [ 200000 - 1000000 ] : ");
                scanf("%d", &price);
                getchar();
            } while (price < 200000 || price > 1000000);
            id[0] = 'N';
            id[1] = 'K';
            id[2] = 'W';
            if (track == 0)
            {
                id[3] = '0';
                id[4] = '0';
            }
            else if (track < 10)
            {
                id[3] = '0';
                id[4] = track + '0';
            }
            else if (track == 10)
            {
                id[3] = '1';
                id[4] = '0';
            }
            else if (track < 100 && track > 10)
            {
                pul = track / 10;
                sat = track % 10;
                id[3] = pul + '0';
                id[4] = sat + '0';
            }
            insertNake(id, name, category, brand, stock, price);
            break;

        case 2:
            system("cls");
            viewNake();
            if (index == 0)
            {
                printf("Press Enter to Continue..");
                getchar();
            }
            else
            {
                ch = 1;
                do
                {
                    printf("Input ItemID to delete (case insensitive) : ");
                    scanf("%[^\n]", sg);
                    getchar();
                    if (strlen(sg) == 5)
                    {
                        if (sg[0] == 'n')
                        {
                            sg[0] = 'N';
                        }
                        if (sg[1] == 'k')
                        {
                            sg[1] = 'K';
                        }
                        if (sg[2] == 'w')
                        {
                            sg[2] = 'W';
                        }
                        deleteNake(sg);
                    }
                } while (ch);
            }
            break;
        }
    } while (pil != 3);

    return 0;
}
