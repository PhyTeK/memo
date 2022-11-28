#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memo.h"

int append_data(char *file, char *date,char *data){
  FILE *db;
  char str[MAXL];
  char dat[100];
  char mes[100];
  int id=0;
  
  // Read the last line and set id
  db=fopen(file,"r");
  while(fgets(str, sizeof(str), db) != NULL);
  sscanf(str,"%d,%s,%s",&id,&dat,&mes);
  fclose(db);

  // Append to the end of database
  db=fopen(file,"a");
  fprintf(db,"%d,%s,\"%s\"\n",++id,date,data);
  fclose(db);

  return 0;
}

int search_data (char *db,char *word){
  // Search word in file db and print each id/line number
  int num=0;
  char str[MAXL];
  FILE *file;
  file=fopen(db,"r");

  while(fgets(str,1000,file)){
    
    if(strstr(str,word)){
	num++;
	printf("%s",str);
    }
  }
  fclose(file);
  return 0;
}
void show_help(){
  char help[]="   -h Show this help.\n"
    "   -i Init a new empty database. For example:\n"
    "      memo -i memo.csv\n"
    "      Create a new empty database with the name memo.csv\n"
    "   -a Append at the end of the database the following message.\n"
    "      memo -a This message will be included at the end of the database\n"
    "   -s Search and find specific entries in the database.\n"
    "      memo -s 09-11-2022 will show all entries at a this given date.\n"
    "      memo -s programming will show all entries containing the word\n"
    "              programming.\n"
    "   -d Delete an entry in the database.\n"
    "      memo -d 123 will delete entry number 123.\n";
  
  printf("%s\n",help);
}

int delete_data(char *file,long id){
  // Copy database without the lines starting with id
  // to a tempory file, rename it and delete.
  char str[MAXL],date[50],message[MAXL];
  FILE *fpt,*ftmp;
  long idf;
  fpt=fopen(file,"r");
  ftmp=fopen("tmp.txt","w");
  while(fgets(str,MAXL,fpt)){
    sscanf(str,"%d,%s,%s",&idf,&date,&message);
    if(idf != id)
      fprintf(ftmp,"%s",str);

  }
  fclose(ftmp);
  fclose(fpt);

  remove(DEFAULT);
  rename("tmp.txt",DEFAULT);

  return 0;
}
int init(char *file){
  FILE *fin,*frc;
  char ans;
  // Check if file exist
  if((fin=fopen(file,"r")) != NULL){
    fclose(fin);
    printf("Are you sure you want to overwrite file %s enter [y or n]?",file);
    scanf("%c",&ans);
    if(ans == 'n'){
      return 1;
    }  
  }
  // file does not exist
  fin=fopen(file,"w");
  fprintf(fin,"%s\n","Memo DataBase");
  fclose(fin);
  // Update default database
  frc=fopen(".memorc","w");
  fprintf(frc,"#ifndef __DEFAULT__\n",file);
  fprintf(frc,"#define __DEFAULT__  1\n",file);
  fprintf(frc,"#define DEFAULT \"%s\"\n",file);
  fprintf(frc,"#endif\n",file);
  fclose(frc);

  return 0;
}
