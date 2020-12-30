# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <windows.h>
# include <conio.h>
# include <stdbool.h>
# include <ctype.h>

# define NAME_LEN 30
# define NUM_LEN 20

struct people
{
    char name[NAME_LEN + 1];
    int score;
    char account[NUM_LEN + 1];
    char code[NUM_LEN + 1];
    struct people *next;
};

int score;
struct people *first = NULL;
struct people *the_account = NULL;              //�����ҵ�ָ���˻���������������

void readline (char s[], int n)
{
    char ch;
    int i = 0; 
    while (isspace(ch = getchar()))
    ;
    while (ch != '\n' && ch != EOF)
    {
        if (i < n)
        s[i++] = ch;
        ch = getchar();
    }
    s[i] = '\0';
}

void create_a_link()            //���ļ��е���Ϣ��ȡ������������
{
    FILE *fp;
    if ((fp = fopen("account.txt", "r")) == NULL)
    {
        printf("The file can't be opened");
        exit(EXIT_FAILURE);
    }

    while (!feof(fp))
    {
        struct people *new_node;
        new_node = (struct people *)malloc(sizeof(struct people));
        fscanf(fp, "%s%s%s%d", new_node -> account, new_node -> code, new_node -> name, &new_node -> score);
        new_node -> next = first;
        first = new_node;
    }
    fclose(fp);
}

struct people  *find_last_node (struct people *p)                     //�ҵ���һ���ڵ�
{
    struct people *cur, *pre = NULL;
    for (cur = first; cur != p; pre = cur, cur = cur -> next)
        ;
    return pre;
}

void clear_link ()                              //�������
{
    struct people *p, *pre = NULL;
    for (p = first; p != NULL; pre = p, p = p -> next)
        ;
    for (struct people *p ; first != NULL; )
    {
    	if ((p = find_last_node(pre)) == NULL)
		{
			free(pre);
			first = NULL;
			break;	
		}		 
        p -> next = NULL;
        free(pre);
        pre = p;
    }
}

bool search (char *s)          //���������Ƿ����˺Ŵ���
{
    struct people *p;
    for (p = first; p != NULL; p = p -> next)
    {
        if (!strcmp(s, p -> account))
        {
            the_account = p;
            return true;
        }    
    }
    return false;
}

void Register ()        //ע��
{
    system("cls");                     //�Ѿ�д������������
    clear_link();
    create_a_link();                
    char check[NUM_LEN + 1];
    struct people *new_account;
    new_account = (struct people *)malloc(sizeof(struct people));

    if (new_account == NULL)
    {
        printf("No more space");
        return;
    }

    for (;;)
    {
        printf("Please enter your account: ");
        readline(new_account -> account, NUM_LEN);
        if (search(new_account -> account))
            printf("The account has existed, please enter again\n");
        else
            break;
    }

    printf("Please enter your name: ");
    readline(new_account -> name, NAME_LEN);
    printf("Please enter your code: ");
    readline(new_account -> code, NUM_LEN);
    printf("Please enter your code again: ");      
    readline(check, NUM_LEN);                    //�������������Ƿ�һ��

    for (;;)
        if (!strcmp(new_account -> code, check))
            {
                FILE *fp;
                if ((fp = fopen("account.txt", "a")) == NULL)     //�˺Ŵ���λ�ã����Ա��˼ǵø���
                {    
                    printf("The file can't be opened");
                    exit(EXIT_FAILURE);
                }
                fprintf(fp, " %s %s %s 0", new_account -> account, new_account -> code, new_account -> name);
                fclose(fp);
                printf("Congratulations!Registerd successfully!");
                break;
            }
        else
        {
            printf("Your code is wrong, please enter your code again: \n");
            readline(check, NUM_LEN);
        }

    free(new_account);
    printf("Press any key to return");
    getch();
    
                                    //�ǵ�д���ز˵�
}

void log_in ()
{
    clear_link();
    create_a_link();
    char account[NUM_LEN + 1];
    char code[NUM_LEN + 1];

    for (;;)
    {
        printf("Please enter your account: ");
        readline(account, NUM_LEN);
        if (search(account))
            break;
        else
            printf("Can't find your account, please enter again\n");
    }
    for (;;)
    {
        printf("Please enter your code: ");
        readline(code, NUM_LEN);
        if (!strcmp(code, the_account -> code))
        {
            printf("Log in successfully!Enjoy your game!");
            break;
        }
        else
            printf("Your code is wrong, please enter again\n");
    }
                                   //�ǵüӽ�����Ϸ�ĺ���
}

void compire_grade ()                //�����˻��е�������
{
    if (score > the_account -> score)
        the_account -> score = score;
}

void Delete (char *s)                   //ɾ������Ľڵ�
{
    struct people *cur;
    struct people *pre;
    for (cur = first, pre = NULL; cur != NULL; pre = cur, cur = cur -> next)
        if (!strcmp(s, cur -> account))
            break;
    if (pre == NULL)
        first = first -> next;
    else
        pre -> next = cur -> next;
    free(cur);
}

void print_grade ()                           //��Ϸ������ӡ�ɼ���
{
    clear_link();
    create_a_link();
    struct people *p;                   //���������ָ��
    struct people *max;                 //�ҳ�������score���Ľڵ��ָ��
    for ( ; first != NULL; )
    {
        for (p = first, max = p; p != NULL; p = p -> next)
            if (p -> score > max -> score)
                max = p;
        printf("\t\t*      %s        %5d       *\t\t\n", max -> name, max -> score);
        Delete(max -> account);
    }
}

void save (void)
{
    FILE *fp;

    if ((fp = fopen("account.txt", "w")) == NULL)
    {    
        printf("The file can't be opened");
        exit(EXIT_FAILURE);
    }

    compire_grade();

    struct people *p;
    for (p = first; p != NULL; p = p -> next)
        fprintf(fp, " %s %s %s %d", p -> account, p -> code, p -> name, p -> score);    
    fclose(fp);
}

void modify_code ()                         //�޸�����
{
    char account[NUM_LEN];
    clear_link();
    create_a_link();
    for (;;)
    {
        printf("Enter the account you want to modify: ");
        readline(account, NUM_LEN);
        if (search(account))
        {
            printf("Please enter your new code: ");
            readline(the_account -> code, NUM_LEN);
            save();
            return;
        }
        else
            printf("Can't find your account, please enter again\n");
    }
}

void delete_account ()                   //ɾ���˺�
{
    char account[NUM_LEN];
    clear_link();
    create_a_link();
    for (;;)
    {
        printf("Enter the account you want to delete: ");
        readline(account, NUM_LEN);
        if (search(account))
        {
            Delete(account);
            save();
            return;
        }
        else
            printf("Can't find your account, please enter again\n");
    }
}


