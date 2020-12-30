#include<stdio.h>
#include<conio.h>   
#include<time.h> 
#include <stdlib.h>
# include "head.h" 
int num[4][4];
int lose = 0,isAdd = 0;
int score = 0; 

int main(){//������ ��Ϸ���к��� 
	gamebegin(1);
	while(1){//��Ϸ��Ҫ������һ��ѭ���н��� 
		keywatch();
		system("cls");
		gameuiprint();
		print();
		save();		
		isLose(isAdd);
	} 
}

void welcome2(){
	printf("\t\t**************welcome to 2048************\t\t\n");            //�����Ϸ�˵���ͼ��
    printf("\t\t*              a  ranking                 *\n");
    printf("\t\t*              b  delete your account     *\n");
    printf("\t\t*              c  modify code             *\n");
    printf("\t\t*              d  play now                *\n");
    printf("\t\t*******************************************\n");
    printf("Plz enter here:[ ]\b\b");
    
}
void welcome1(){
	printf("\t\t**************welcome to 2048************\t\t\n");            //�����Ϸ�˵���ͼ��
    printf("\t\t*              1  regesiter               *\n");
    printf("\t\t*              2  log in                  *\n"); 
    printf("\t\t*              3  ranking                 *\n");
    printf("\t\t*******************************************\n");
    printf("Plz enter here:[ ]\b\b");
}

int cmp(const int*a,const int*b){//�������õıȽ��� 
	return (int*)b - (int*)a;
}
void ranks(){//�������� 
	printf("\t\t* * * * * * * * * * * * * * * *\t\t\n");
	printf("\t\t*      ranking in 2048:       *\t\t\n");
	print_grade (); 
	printf("\t\t* * * * * * * * * * * * * * * *\t\t\n");
}
void gameuiprint(){//��Ϸ���� 
	printf("\t\t\t* * * * * * * * * * * * * * * *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t*           2048              *\t\t\t\n");
	printf("\t\t\t*                             *\t\t\t\n");
	printf("\t\t\t* * * * * * * * * * * * * * * *\t\t\t\n");
}
void gameloseui(){//����� 
	printf("\t\t��***********��\t\t\n");
    printf("\t\t*> YOU  LOSE!<*\t\t\n");
    printf("\t\t��***********��\t\t\n");
    printf("\t\tpush any button to return  menu\t\t\n"); 
    getch();
    system("cls");
    gamebegin(2);
}
void gamebegin(int i){//�˵�  
	if(i == 1)
		welcome1();
	else if(i == 2)
		welcome2();//��ʼ���� 
	char set;
	set = getchar();
	if(set == '1'){
		Register();
		system("cls");
		gamebegin(1);
	}else if(set == '2'){
		system("cls");
		log_in();
		system("cls");
		gamebegin(2);
		
	}else if(set == '3' ){
		system("cls");
		ranks();
		printf("push any button to return");
		getch();
		system("cls");
		gamebegin(1);
	}else if(set == 'a' && i == 2){
		system("cls");
		ranks();
		getch();
		system("cls");
		gamebegin(2);
	
	}else if(set == 'b' && i == 2){
		system("cls");
		delete_account ();
		printf("delete successfully! push any button to return");
		getch();
		system("cls");
		gamebegin(1);
	}else if(set == 'c' && i == 2){
		system("cls");
		modify_code ();
		printf("modify successfully! push any button to return");
		getch();
		system("cls");
		gamebegin(1);  
	}else if(set == 'd' && i == 2){
		system("cls");
		gameinit();//��ʼ��Ϸ 
	}else{
		printf("\nplease enter correctly");
		getch();
		system("cls");
		if(i == 1)
			gamebegin(1);
		else if(i == 2)
			gamebegin(2);
	}
}
void gameinit(){//��ʼ�� 
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			num[i][j] = 0;
			
	newnum();
	newnum();
	gameuiprint();//��������Ϸui 
	print();
}
void print(){//��Ϸ��Ĳ��� 
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

void newnum(){//����������� 
	int k = 0,b[16],s[16] = {0},n = 0,q;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
				b[k] = num[i][j];
				k++;
		}
	}
	for(k = 0, q = 0;k < 16;k++){
		if(b[k] == 0){
			s[q] = k;
			n++;
			q++;
		}else{
			continue;
		}
	}
	int rannum = rand() % n;
	int rnum = s[rannum];
	b[rnum] = 2; 
	k = 0;
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			num[i][j] = b[k];
			k++;
		}
	}
}


int add(int *arr)//�Ӻͺ����������л����н���һλ����ļӺ� 
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
            if (next != -1) {//�ӵ�һ������0��λ������ң��ҵ���һ������0��λ�� 
                 if(arr[i] == arr[next]){
                    arr[i] *= 2;//��������ӱ� 
                    score += arr[i]*10; //�����仯 
                    arr[next] = 0;
                    isAdd = 1;
                }
            }
        }
        return isAdd;
}

void slide(int *arr,int x){//�����������Ӻ���ɺ��ƶ� 
	int t = 0,k = 0;
	if(x == 0){
		do{
			for(int i = 3;i > 0;i--){
				if(arr[i] == 0){
					t = arr[i];
					arr[i] = arr[i-1];
					arr[i-1] = t; 			
				}
			}//�ѵ�ǰλ������һλ���� 
			k++;
		}while(k < 4);//����ظ��Ĵ� 
	}
	if(x == 1){
		do{
			for(int i = 0;i < 3;i++){//����һλ���� 
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

void keywatch(){//���ƺ��� 
	int i,j,k,t,isAdd,b[4] = {0};
	char key;
	key = _getch();
	switch(key){
		case 'w':
		case 'W':
			for(j = 0;j < 4;j++){
				for(i = 0;i < 4;i++){
					b[i] = num[i][j];//���ϲ�� 
				}
				isAdd = add(b);
				slide(b,1);
				for(i = 0;i < 4;i++){
					num[i][j] = b[i];
				}
			}
			newnum();
			
			lose = isLose(isAdd);//���ж� 
			break;
		case 's':
		case 'S'://���Ҳ��  ����ͬ�� 
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
int isLose(int isAdd){//��Ϸʧ���ж� 
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


