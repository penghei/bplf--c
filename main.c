#include<stdio.h>
#include<conio.h>   
#include<time.h> 
#include <stdlib.h>
# include "head.h" 
int num[4][4];
int lose = 0,isAdd = 0;
int score = 0; 

int main(){
	gamebegin();
	while(1){
		keywatch();
		system("cls");
		gameuiprint();
		print();
		save();		
		isLose(isAdd);
	} 
}

void welcome(){
	printf("\t\t**************welcome to 2048************\t\t\n");            //�����Ϸ�˵���ͼ��
    printf("\t\t*              1  regesiter               *\n");
    printf("\t\t*              2  log in                  *\n");
    printf("\t\t*              3  Play Now                *\n");
    printf("\t\t*              4  ranking                 *\n");
    printf("\t\t*******************************************\n");
    printf("Plz enter here:[ ]\b\b");
    
}

int cmp(const int*a,const int*b){
	return (int*)b - (int*)a;
}
void ranks(){
	
	printf("\t\t* * * * * * * * * * * * * * * *\t\t\n");
	printf("\t\t*      ranking in 2048:       *\t\t\n");
	print_grade (); 
	printf("\t\t* * * * * * * * * * * * * * * *\t\t\n");
}
void gameuiprint(){
	printf("\t\t\t* * * * * * * * * * * * * * * *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t*           2048              *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t* * * * * * * * * * * * * * * *\t\t\t\n");
	
	
}
void gameloseui(){
	printf("\t\t��***********��\t\t\n");
    printf("\t\t*> YOU  LOSE!<*\t\t\n");
    printf("\t\t��***********��\t\t\n");
    printf("\t\tpush any button to return  menu\t\t\n"); 
    getch();
    system("cls");
    gamebegin();
}
void gamebegin(){
	welcome();//��ʼ���� 
	char set;
	set = getchar();
	if(set == '1'){
		Register();
		gamebegin();
	}else if(set == '2'){
		log_in();
	}else if(set == '3'){
		system("cls");
		gameinit();
	}else if(set == '4'){
		ranks();
		getch();
		system("cls");
		gamebegin();
	}
	else{
		printf("\nplease enter correctly");
		getch();
		system("cls");
		gamebegin();
	}
}
void gameinit(){
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			num[i][j] = 0;
			
	newnum();
	newnum();
	gameuiprint();//��������Ϸui 
	print();
}
void print(){
	int i,j;
	printf("\t\t\t Score : %d \t\t\t\n",score);	
	printf("\t\t\t---------------------\n\t\t\t");
	for (j = 0; j<4; j++)                 //���4*4�ı��
    {
        for (i = 0; i<4; i++)
            if (num[j][i] == 0)
                printf("|    ");
            else
                printf("|%4d", num[j][i]);
        printf("|\n");
        printf("\t\t\t---------------------\n\t\t\t");
    }
}

void newnum(){
	int k = 0,b[16],single[16] = {1},n = 0;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			k++;
			b[k] = num[i][j];
		}
	}
	for(k = 0;k < 16;k++){
		if(b[k] == 0){
			n++;
		}else
			continue;
	}
	int rannum = rand() % n;
	b[rannum] = 2;
	k = 0;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			k++;
			num[i][j] = b[k];
		}
	}
}


int add(int *arr)
{
 		int i ,next,len,m,isAdd = 0;
        for (i = 0; i < 4; i++) {
            next = -1;
            for (m = i+1; m < 4; m++){
                if(arr[m] != 0) {
                    next = m;
                    break;
                }
            }
            if (next != -1) {
                 if(arr[i] == arr[next]){
                    arr[i] *= 2;
                    score += arr[i]*10; 
                    arr[next] = 0;
                    isAdd = 1;
                }
            }
        }
        return isAdd;
}

void slide(int *arr,int x){
	int t = 0,k = 0;
	if(x == 0){
		do{
			for(int i = 3;i > 0;i--){
				if(arr[i] == 0){
					t = arr[i];
					arr[i] = arr[i-1];
					arr[i-1] = t; 			
				}
			}
			k++;
		}while(k < 4);
	}
	if(x == 1){
		do{
			for(int i = 0;i < 3;i++){
				if(arr[i] == 0){
					t = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = t; 			
				}
			}
			k++;
		}while(k < 4);
	}
}

void keywatch(){
	int i,j,k,t,isAdd,b[4] = {0};
	char key;
	key = _getch();
	switch(key){
		case 'w':
		case 'W':
			for(j = 0;j < 4;j++){
				for(i = 0;i < 4;i++){
					b[i] = num[i][j];
				}
				isAdd = add(b);
				slide(b,1);
				for(i = 0;i < 4;i++){
					num[i][j] = b[i];
				}
			}
			newnum();
			
			lose = isLose(isAdd);
			break;
		case 's':
		case 'S':
			for(j = 0;j < 4;j++){
				for(i = 0;i < 4;i++){
					b[i] = num[i][j];
				}
				isAdd = add(b);
				slide(b,0);
				for(i = 0;i < 4;i++){
					num[i][j] = b[i];
				}
			}
			newnum();
			
			lose = isLose(isAdd);
			break;
		case 'a':
		case 'A':
			for(i = 0;i < 4;i++){
				for(j = 0;j < 4;j++){
					b[j] = num[i][j];
				}
				isAdd = add(b);
				slide(b,1);
				for(j = 0;j < 4;j++){
					num[i][j] = b[j];
				}
			}
			newnum();
			
			lose = isLose(isAdd);
			break;
		case 'd':
		case 'D':
			for(i = 0;i < 4;i++){
				for(j = 0;j < 4;j++){
					b[j] = num[i][j];
				}
				isAdd = add(b);
				slide(b,0);
				for(j = 0;j < 4;j++){
					num[i][j] = b[j];
				}
			}
			newnum();
			
			lose = isLose(isAdd);
			break;		
	}
}
int isLose(int isAdd){
	int isFull = 1;
	for(int i = 0;i < 4;i++){
		for(int j = 0; j < 4;j++){
			if(num[i][j] == 0){
				isFull = 0;
			}
		}
	}
	if(isFull == 1 && isAdd == 0){
		gameloseui();		
	}
}


