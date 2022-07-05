#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void listAll();
void CreateNewTODO(char title[]);
void getLine(int n,char *st);
int main()
{
    
    int input;
    char ab[100],t[255];
    system("cls");
    FILE *TODOList = fopen("TODOList.txt","r");
    if(TODOList == NULL){
        printf("\t\tTodo List\n");
        printf("\tCreate your first TODO:\n");
        printf("\tEnter the title (eg., projekt,Morning Routine...)\n");
        scanf("%s",&t);
        CreateNewTODO(t);
        
    }
    char str[100];
    select:;
    
        system("cls");
        printf("\t\tTodo List\n");
        printf("\tEnter 1 to view all List\n");
        printf("\tEnter 2 to create new List\n\n");
        printf("\tEnter 0 to Exit\n");
        scanf("%d", &input);

        selectFromList:;
        switch (input)
        {
        case 1:
            while (true)
            {
                system("cls");
                int t;
                printf("\n\n\t List of all the TODOLists:\n\n");
                char s[100] = "TODOList";
                listAll(s,0);
                printf("\n\nEnter the number to Start the TODO\nEnter 0 to Exit\n");
                scanf("%d", &t);
                switch (t)
                {
                case 0:{
                    goto select;
                    break;
                }
                default:{                    
                    while(true){
                        system("cls");
                        getLine(t,str);
                        printf("%s:\n\n",str);
                        char string[100];
                        char path[100];
                        sprintf(path,"TODOs\\%s.txt", str);
                        FILE *TD = fopen(path,"r");
                        int i = 0;
                        while (fgets(string,100,TD))
                        {
                            if(string[0] == "\n")
                                continue;
                            i++;
                            printf("%d)%s", i, string);
                        }
                        fclose(TD);
                        printf("\n\nEnter 1 to add new task\nEnter 2 to delete task\nEnter 3 to exit\n");
                        int input;
                        scanf("%d", &input);
                        switch (input)
                        {
                        case 1:{
                            printf("\nEnter the task\n");
                            char task[255];
                            scanf("%s", &task);
                            char url[100];
                            sprintf(url, "TODOs\\%s.txt", str);
                            FILE *TODOList = fopen(url,"a");
                            fprintf(TODOList,"\n%s",task);
                            fclose(TODOList);
                            break;
                        }
                        case 2:{
                            printf("\nEnter the task index to delete\n");
                            int ind;
                            scanf("%d", &ind);
                            FILE *src;
                            FILE *temp;
                            char path[100];
                            sprintf(path, "TODOs\\%s.txt", str);
                            src = fopen(path, "r");
                            temp = fopen("TODOs\\delete.tmp", "w");
                            if (src == NULL || temp == NULL){
                                printf("Unable to open file.\n");
                                exit(EXIT_FAILURE);
                            }
                            rewind(src);
                            deleteLine(src, temp, ind);
                            fclose(src);
                            fclose(temp);
                            remove(path);
                            rename("TODOs\\delete.tmp", path);
                            fclose(src);
                            break;
                        }
                        case 3:{
                            goto selectFromList;
                            break;
                        }
                        default:{
                            printf("\nInvalid input\n");
                            break;
                        }
                        }
                    }
                    break;
                }
                }
            }
            break;
        case 2:
            printf("\t\tCreate New Todo List\n");
            printf("\tEnter the title (eg., projekt,Morning Routine...)\n");
            scanf("%s",&t);
            CreateNewTODO(t);
            goto select;
            break;

        default:
            break;
    }
    

}
void listAll(char n[],int isTodo){
    char string[100];
    if(!isTodo)
    sprintf(n, "%s.txt", n);
    else
    sprintf(n, "TODOs\\%s.txt", n);
    printf("\n%s\n",n);
    FILE *TODOList = fopen(n,"r");
    int i = 0;
    while (fgets(string,100,TODOList))
    {
        i++;
        printf("%d.%s", i, string);
    }
}
void CreateNewTODO(char title[]){
    system("cls");
    FILE *TODOList = fopen("TODOList.txt","a");
    if (TODOList == NULL)
        TODOList = fopen("TODOList.txt", "w");

    char tit[100];
    mkdir(".\\TODOs");
    sprintf(tit, "TODOs\\%s.txt", title);
    FILE *newTODO = fopen(tit, "w");
    fclose(newTODO);
    strcat(title, "\n");
    fputs(title,TODOList);
    fclose(TODOList);
}
void getLine(int n,char *st){
    FILE *TODOList = fopen("TODOList.txt", "r+");
    char a[100] = "";
    for (size_t i = 0; i < n; i++)
    {
        fgets(a,100,TODOList);
    };
    fclose(TODOList);
    a[strlen(a)-1] = '\0';
    strcpy(st,a);
}
// add item to TODO list
void addItem(char item[],char list[])
{
    char str[100];
    printf("\nEnter the task\n");
    scanf("%s", &str);
    FILE *TODO = fopen(strcat(list,".txt"),"a");
    fprintf(TODO,"\n%s",str);
    fclose(TODO);
}
void deleteLine(FILE *src, FILE *temp, const int line){
    char buffer[1000];
    int count = 1;
    while ((fgets(buffer, 1000, src)) != NULL){
        if (line != count)
        fputs(buffer, temp);
        count++;
    }
}