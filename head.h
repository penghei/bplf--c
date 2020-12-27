# ifndef HEAD_H
# define HEAD_H

# include <stdbool.h>


void gamebegin();
void gameinit();
void print(); 
void newnum();
int add(int *);
void slide(int *,int );
void keywatch(); 
int isLose(int);
void lost(int);
void gameloseui();
void welcome();
void ranks();
void gameuiprint();
void readline (char s[], int n);
void create_a_link();
bool search (char *s);
void Register ();
void log_in ();
void compire_grade ();
void print_grade ();
struct people  *find_last_node (struct people *p);
void clear_link ()  ;
void Delete (char *s);
void save ();
 
extern int score;


# endif
