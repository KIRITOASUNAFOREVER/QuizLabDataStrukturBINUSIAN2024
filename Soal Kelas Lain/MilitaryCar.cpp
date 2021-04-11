#include<stdio.h>
#include <string.h>
#include<stdlib.h>

int size = 100;
int jumlah_data = 0;
int jumlah_id = 0;

typedef struct Node{
    char kode[6];
    char vehicle_name[100];
    int armor_strength;
	char weapon[15];
	int price;
	char tire_type[100];
    struct Node *next;
}Node;

Node *insert(Node *node, int hash_index, char kode[6], char a[100], int as, char b[15], int c, char d[100]);
Node *del(Node *node,int table_range, char val[6]);
void display(Node *node, int table_range, int menu);

int main(){
    Node *node;
    int n, i, j, choice;
    int hash_num, val;	
	char search[6];	

    node = (Node*) malloc(size*sizeof(Node));

    for(i = 0; i < size; i++){
    	node[i].next = NULL;
    }
    
    int loop = 1;
    while(loop == 1){
    	char vehicle_name[100];
    	char weapon[15];
    	int price;
    	char tire_type[100];
    	
    	system("cls");
    	
    	display(node, size, 1);
    	
    	printf(" 1. Create new vehicle\n");
    	printf(" 2. Sell vehicle\n");
		printf(" 3. Exit\n");
		printf(" >> ");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:
				{
					system("cls");
					char new_kode[6];
					if(jumlah_id < 9){
						int number = jumlah_id+1;
						sprintf(new_kode, "VE00%d", number);
					}else if(jumlah_id < 99){
						int number = jumlah_id+1;
						sprintf(new_kode, "VE0%d", number);
					}else{
						int number = jumlah_id+1;
						sprintf(new_kode, "VE%d", number);
					}
					
					printf(" =======\n");
					printf("  %s \n", new_kode);
					printf(" =======\n\n");
					
					int loop2 = 1;
					while(loop2 == 1){
						printf(" Vehicle name [must more than 5 charcters]: ");
						scanf(" %[^\n]s", &vehicle_name);
						if(strlen(vehicle_name) >= 5){
							break;
						}
					}
					
					while(loop2 == 1){
						printf(" Weapon [Cannon|Machine Gun] (case sensitive): ");
						scanf(" %[^\n]s", &weapon);
						if(strcmp(weapon, "Cannon") == 0){
							break;
						}else if(strcmp(weapon, "Machine Gun") == 0){
							break;
						}
					}
					
					while(loop2 == 1){
						printf(" Price [100000 - 1000000]: ");
						scanf(" %d", &price);
						if(price >= 100000){
							if(price <= 1000000){
								break;
							}
						}
					}
					
					char value_tire[100];
					while(loop2 == 1){
						printf(" Tire type [must endWith ' tires']: ");
						scanf(" %[^\n]s", &tire_type);
						strcpy(value_tire, tire_type);
						char *token = strtok(tire_type, " ");
						char check[5];
						while(token != NULL){
							strcpy(check, token);
							token = strtok(NULL, " ");
						}
						
						if(strcmp(check, "tires") == 0){
							break;
						}
					}
					
					printf("\n");
					int hash = jumlah_id + 1 % size;
					printf(" Vehicle ID     : %s\n",new_kode);
					printf(" Name           : %s\n",vehicle_name);
					int armor_strength = (rand() % (100 - 60 + 1)) + 60;
					printf(" Armor Strength : %d%%\n",armor_strength);
					printf(" Weapon         : %s\n",weapon);
					printf(" Price          : $%d\n",price);
					printf(" Tire type      : %s\n",value_tire);
					
					while(loop2 == 1){
						printf(" \n Cofirm Insert [Y/N] (case sensitive): ");
						char yesno[1];
						scanf(" %s", &yesno);
						if(strcmp(yesno, "Y") == 0){
							node = insert(node, hash, new_kode, vehicle_name, armor_strength, weapon, price, value_tire);	
							printf(" Insert Success!");
							jumlah_data++;
							jumlah_id++;
							break;
						}else if(strcmp(yesno, "N") == 0){
							printf(" Insert Cancelled!");
							break;
						}	
					}
				break;
			}
		case 2:
			{
				system("cls");
				if(jumlah_data==0){
					display(node, size, 2);
				}else{
					display(node, size, 2);
					printf(" Input Vehicle Id (case sensitive): ");
					scanf(" %[^\n]s", &search);
					node = del(node, size, search);
					printf("\n--------\n");
				}
				system("pause");
				
				break;
			}
		case 3:
			exit(1);
			break;
		default:
			break;	

	    }

	}	

	return 0;

}

void display(Node *node, int table_range, int menu){
    int i;
    Node* cur;
    if(jumlah_data == 0){
    	if(menu == 1){
    		printf(" =============\n");
			printf(" List is Empty\n");
			printf(" =============\n\n");
		}else{
			printf(" ======================\n");
			printf(" No vehicle in the list\n");
			printf(" ======================\n\n");
		}
	}else{
		for(i = 0; i < table_range; i++){
			if(node[i].next == NULL){
		        continue;
			}
		
			cur = node[i].next;
			while(cur!=NULL){
				printf(" Vehicle ID     : %s\n",cur->kode);
				printf(" Name           : %s\n",cur->vehicle_name);
				printf(" Armor Strength : %d%%\n",cur->armor_strength);
				printf(" Weapon         : %s\n",cur->weapon);
				printf(" Price          : $%d\n",cur->price);
				printf(" Tire type      : %s\n\n",cur->tire_type);
				cur=cur->next;
			}
			printf("\n");	
	    }
	}
}


Node *insert(Node *node, int hash_index, char kode[6], char a[100], int as, char b[15], int c, char d[100]){
    Node *nn, *cur;
    nn = (Node*)malloc(sizeof(Node));
    strcpy(nn->kode, kode);
    strcpy(nn->vehicle_name, a);
    nn->armor_strength = as;
	strcpy(nn->weapon, b);
    nn->price = c;
    strcpy(nn->tire_type, d);
    nn->next=NULL;
    if(node[hash_index].next == NULL){
		node[hash_index].next = nn;
		return node;
    }

    cur = node[hash_index].next;
    while(cur->next != NULL){
		cur=cur->next;
    }
    cur->next = nn;
    return node;
}

Node *del(Node *node, int table_range, char search[6]){
	char aa[6];
	strcpy(aa, search);
	char *token = strtok(search, "VE");
	int val;
	char value[4];
	while(token != NULL){
		strcpy(value, token);
		val = atoi(value);
		token = strtok(NULL, " ");
	}
	
    int index = val % table_range;
	Node *prev;

    if(node[index].next == NULL){
    	printf(" %s not found !\n",aa);
		return node;
    }

    if(strcmp(node[index].next->kode, aa) == 0){
    	printf(" %s is on sale !\n",aa);
		jumlah_data--;
		node[index].next = node[index].next->next;
		return node;
    }

    prev = node[index].next;
    while(prev->next!=NULL){
		if(strcmp(prev->next->kode, aa) == 0){
			prev->next = prev->next->next;
			printf(" %s is on sale !\n",aa);
			jumlah_data--;
			return node;
		}
		prev = prev->next;
    }

	printf(" %s not found !\n",aa);

    return node;

}
