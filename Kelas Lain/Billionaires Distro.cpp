#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct cloth{
    int cid;
    char name[50];
    char size;
    int price;
    int quantity;
    struct cloth* next;
}cloth;

cloth* chain[99];
int cid_no;
int count;

void init()
{
    int i;
    for(i=0;i<99;++i)
        chain[i]=NULL;
}

int findkey(int cid_no)
{
    char str[3];
    if(cid_no/10 == 0)
    {
        str[0]='0';
        str[1]='0';
        str[2]=cid_no+'0';
    }

    else if(cid_no/100==0)
    {
        str[0]='0';
        str[1]='0'+cid_no/10;
        str[2]='0'+cid_no%10;
    }
    else if(cid_no/1000==0)
    {
        str[0]='0'+cid_no/100;
        int tens=cid_no%100;
        str[1]='0'+tens/10;
        str[2]='0'+tens%10;
    }

    int key='C'+'H'+str[0]+str[1]+str[2];
    return key%99;
}

void insert_hash(char* name, char size, int price, int quantity)
{
    cloth* node=(cloth*)malloc(sizeof(cloth));
    if(node==NULL)
    {
        printf("Unable to allocate memory\n");
        exit(1);
    }
    node->cid=cid_no;
    strncpy(node->name,name,49);
    node->size=size;
    node->price=price;
    node->quantity=quantity;
    node->next=NULL;
    int key=findkey(cid_no);
    if(chain[key]==NULL)
        chain[key]=node;
    else
    {
        cloth* temp=chain[key];
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=node;
    }
}

cloth* previous(int cid)
{
    int key=findkey(cid);
    cloth* temp=chain[key];
    if(!temp)
        return NULL;
    while(temp->next)
    {
        if(temp->next->cid==cid)
            return temp;
        temp=temp->next;
    }
    return temp;
}

cloth* retrieve_value(int cid)
{
    int key=findkey(cid);
    cloth* temp=chain[key];
    if(!temp)
        return NULL;
    while(temp)
    {
        if(temp->cid==cid)
            return temp;
        temp=temp->next;
    }
    return temp;

}

void printlines(char c,int times)
{
    int i;
    for(i=0;i<times;++i)
        putchar(c);
    printf("\n");
}

void print_hash()
{
    if(count<=0)
    {
        printf("\nNo Cloth Yet\n");
    }
    else
    {
        printf("=================================================================\n");
        printf("| Id\t| %-21s| Size\t| %-10s| %-10s|\n","Name","Price","Quantity");
        printf("=================================================================\n");
        for(int i=1;i<=cid_no;++i)
        {
            cloth* node=retrieve_value(i);
            if(node)
            printf("| CH%03d\t| %-21s| %c\t| %-10d| %-10d|\n",node->cid,node->name,node->size,node->price,node->quantity);
        }
        printf("=================================================================\n");
    }
}

void remove_value(char *cid)
{
    cid=cid+2;
    int key=atoi(cid);
    if(key==0){
    	if(count > 0)
        {
    		char buf[6];
            char* cid;
            printf("Search Cloth Id (Case insensitive): ");
            char c;
            scanf("%c",&c);
            cid=fgets(buf,sizeof(buf),stdin);
            remove_value(cid);
        }
        return;
	}
        
    int key_in_hash=findkey(key);
    cloth* node=retrieve_value(key);
    cloth* prev=previous(key);
    if(node)
    {
        printf("Deleted Item\n");
        printf("Id\t: CH%03d\n",node->cid);
        printf("Name\t: %s\n",node->name);
        printf("Size\t: %c\n",node->size);
        printf("Price\t: %d\n",node->price);
        printf("Quantity: %d\n",node->quantity);
        if(!node->next)
        {
            chain[key_in_hash]=NULL;
        }
        else
            prev->next=node->next;
        count--;
        return;
    }else{
    	if(count > 0)
        {
    		char buf[6];
            char* cid;
            printf("Search Cloth Id (Case insensitive): ");
            char c;
            scanf("%c",&c);
            cid=fgets(buf,sizeof(buf),stdin);
            remove_value(cid);
        }
        return;
	}
}

void bawah(){
	for(int i = 0 ; i < 26 ; i++){
		printf("\n");
	}
}

int main()
{
    cid_no=0;
    init();
    count=0;
    while(1)
    {
    	system("cls");
    	bawah();
        int choice=-1;
        print_hash();
        printf("\n\n");
        int b=printf("Billionaires Distro\n");
        printlines('=',b);
        printf("1. Add New Cloth\n");
        printf("2. Delete Cloth\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf(" %d",&choice);
        getchar();
        if(choice==1)
        {
        	system("cls");
            cid_no++;
            count++;
            printf("\tCH%03d\n",cid_no);

            char str[49];
            char* name=NULL;
            char c;
            int price;
            int quant;
            do
            {
                char c;
                printf("Insert Cloth Name [6..20]: ");
                name=fgets(str,sizeof(str),stdin);
                int len=strlen(str);
                if(str[len-1]=='\n')
                    str[len-1]='\0';
            }while(strlen(name) < 6 || strlen(name) > 20);
            
			do{
                printf("Insert cloth size[S | M | L] (case insensitive) : ");
                char x;
                scanf("%[\n]c",&x);
                scanf("%c",&c);
                if(c=='S' || c=='s' || c=='M' || c=='m' || c=='L' || c=='l')
                {
                    c=toupper(c);
                    break;
                }
            }while(c!='S' || c!='M' || c!='L');

            do{
                printf("Insert Cloth Price[100000 - 500000] : ");
                scanf("%d",&price);
            }while(price < 100000 || price > 500000);

            do{
                printf("Insert Cloth Quantity[quantity > 0] : ");
                scanf("%d",&quant);
            }while(quant < 0);

            insert_hash(name,c,price,quant);
        }
        else if(choice==2)
        {
        	system("cls");
            print_hash();
            if(count > 0)
            {
        		char buf[6];
                char* cid;
                printf("Search Cloth Id (Case insensitive): ");
                char c;
                scanf("%c",&c);
                cid=fgets(buf,sizeof(buf),stdin);
                remove_value(cid);
            }
            getchar();
        }
        else if(choice==3)
            exit(0);
        printf("\n");
    }
    return 0;
}
