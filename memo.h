#ifndef __MEMO_HEADER__
#define __MEMO_HEADER__

int init(char *);
void show_help(void);
int search_data(char*,char*);
int append_data(char*,char*,char*);
int delete_data(char*,long);

typedef struct Data{
  int id;
  int date;
  char data[100];
} Data;

#define DEFAULT "memo.csv"
#define MAXL 200  // Max length of an entry in database

#endif
