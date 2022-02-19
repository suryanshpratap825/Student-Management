#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
void InsertRecord();
void DisplayRecord();
void SearchRecord();
void DeleteRecord();
void UpdateRecord();
void SortRecord();

struct Student
{
    int roll;
    char sec[10];
    char name[40];
    int marks;
    float grade;
}s;

int main()
{
    char ch,pass[30],i=0;
    char userEnterPass[30];

    printf("*************************************************************************\n");
    printf("*******************         Welocome         ****************************\n");
    printf("*************************************************************************\n");
    sleep(5);
    system("CLS");
    FILE *fp;
    fp=fopen("password.txt","r");
    if(fp==NULL)
    {
        printf("Can't open the file");
    }
    while(1)
    {
        ch=fgetc(fp);
        if(ch==EOF)
            break;
        pass[i++]=ch;
    }
    pass[i]='\0';
    // printf("%s\n",pass);
    fclose(fp);


/*------------------------------------------------------------------------------------------*/ 

    //user entered password is here
    i=0;
    printf("Enter Your Password:");
    while(1) //Here we use loop for hide the password from the client screen and print * in the place of the password
    {
        ch=getch(); //using getch the value is not show on the screen
        if(ch==13)  //Check if user Enter the Enter then exit the loop because 13 is ASCII of Enter
        {
            userEnterPass[i]='\0';
            break;
        }
    userEnterPass[i++]=ch;
    printf("*");
    }
    // printf("%s",userEnterPass);

/*-------------------------------------------------------------------------------------*/
    sleep(3);
    system("CLS");
    if(strcmp(userEnterPass,pass)==0)
    {
        printf("\nLog in succesfull");
        system("CLS");
        int choice;
        while(1)
        {
            printf("Enter 1 for Enter Student Details:\n");
            printf("Enter 2 for Display Student Details:\n");
            printf("Enter 3 for Search Student Details:\n");
            printf("Enter 4 for Delete Student Details:\n");
            printf("Enter 5 for Update Studnet Details:\n");
            printf("Enter 6 for Sort the Student Detials:\n");
            printf("Enter 7 for Exit:");

            printf("\nEnter Your choice: ");
            scanf("%d",&choice);
            switch (choice)
            {
            case 1: 
                system("CLS");
                InsertRecord();
                break;
            case 2:
                system("CLS");
                DisplayRecord();
                break;
            case 3:
                system("CLS");
                SearchRecord();
                break;
            case 4: 
                system("CLS");
                DeleteRecord();
                break;
            case 5:
                system("CLS");
                UpdateRecord();
                break;
            case 6:
                system("CLS");
                SortRecord();
                break;
            case 7:
                exit(1);
            default:
                printf("Please Enter the right key");
                break;
            }
        }
    }
    else{
        printf("\nYou Enter a wrong Password! Please Try again Later!");
    }

    return 0;
}

void InsertRecord(){
    FILE *fp;
    fp=fopen("stu.txt","ab+");
    if(fp==NULL)
    {
        printf("Error: Can't open the file!!");
        return;
    }
    printf("\n\t\nYour Previously Stored Data are:");
    DisplayRecord();
    printf("\n\t\nEnter new Student data:");
    printf("\n\t\nEnter Roll No:");
    scanf("%d",&s.roll);
    fflush(stdin);
    printf("\n\t\nEnter Student Name:");
    gets(s.name);
    printf("\n\t\nEnter Student Section:");
    gets(s.sec);
    printf("\n\t\nEnter Student Total Marks:");
    scanf("%d",&s.marks);
    printf("\n\t\nEnter Student Grade:");
    scanf("%f",&s.grade);

    fwrite(&s,sizeof(s),1,fp);
    {
        printf("\n\t\n Inseted Successfully\n");
    }
    fclose(fp);
    printf("Now Updated Record are:");
    DisplayRecord();
}

void DisplayRecord(){
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("Error: Can't open the file!!");
        return;
    }   
    printf("Students Record are::");
    printf("Roll No\nStudent Name\nSection\nMarks\nGrade:\n\n");
    while(fread(&s,sizeof(s),1,fp)!=NULL)
    {
        printf("%d\t%s\t%s \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);
    }
    fclose(fp);
}

void SearchRecord(){
    int ro,flag=0;
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\nError: Can't open the file!!");
        return;
    }
    printf("\n\t\nEnter Student Roll Number which you want to search:");
    scanf("%d",&ro);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.roll==ro)
        {
            flag=1;
            printf("\n\t\nFound- Search Succesfully");
            printf("\nRoll No.\t Name of Student \t Section \t Marks \t Grade\n");
            printf("%d\t%s\t%s \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);
        }
    }
    if(flag==0)
    {
        printf("\n\t\nRecord Not Found");
    }
    fclose(fp);
}

void DeleteRecord()
{
    char name[40];
    unsigned flag=0;
    FILE *fp,*ft;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\nError: Can't open the file!!");
        return;
    }
    printf("\n\t***** Previous Stored Data ****");
    DisplayRecord();
    printf("\n\n\tEnter the Student Name Which You want to Delete:");
    scanf("%s",name);
    ft=fopen("stu1.txt","ab+");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(strcmp(name,s.name)!=0)
        {
            printf("\n\t\tRecord Deleted Succesfully\n");
            fwrite(&s,sizeof(s),1,ft);
        }
        else 
            flag=1;
    }
    if(flag==0)
    {
        printf("\n\n\tNo Such Record Found!!");
    }
    fclose(fp);
    fclose(ft);
    remove("stu.txt");
    rename("stu1.txt","stu.txt");
    printf("\n\t\t Updated Record!!\n");
    DisplayRecord();
}

void UpdateRecord(){
    int ro,flag=0;
    FILE *fp;
    fp=fopen("stu.txt","rb+");
    if(fp==NULL)
    {
        printf("\n\t\nError: Can't open the file!!");
        return;
    }
    printf("\n\t\nEnter Student Roll Number which you want to search:");
    scanf("%d",&ro);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {
        if(s.roll==ro)
        {
            flag=1;
            printf("\nRoll No\t Name of Student\tsection\tMarks\tGrade\n");
            printf("%d\t%s\t%s \t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);
            printf("\n\t\t*** Now Enter The new Record***\n\n");

            printf("\n\t\tUpdated Student Roll Number: ");
            scanf("%d",&s.roll);
            fflush(stdin);
            printf("\n\t\tUpdated Student Name: ");
            gets(s.name);
            printf("\n\t\tUpdate Student Section: ");
            gets(s.sec);
            printf("\n\t\n Update Student Marks: ");
            scanf("%d",&s.marks);
            printf("\n\t\nUpdated Student Grade:");
            scanf("%f",&s.grade);
            fseek(fp,-(long)sizeof(s),1);
            fwrite(&s,sizeof(s),1,fp);
            printf("\n\n\t Record Updted Successfully Cehck The Display");
        }
    }
    if(flag==0)
        {
            printf("\n\t\tError: Something Not Write!!!\n");
        }
    fclose(fp);
}

void SortRecord()
{
    struct Student temp;
    struct Student arr[50];
    int i,j,k=0;
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\nError: Can't open the file!!");
        return;
    }
    i=0;
    while(fread(&arr[i],sizeof(arr[i]),1,fp)==1)
    {
        i++;k++;
    }
    for(i=0;i<k;i++)
    {
        for(j=0;i<k-i-1;j++)
        {
            if(arr[j].roll>arr[j+1].roll)
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    printf("\n\t\tAfter Sorting Student Details!!\n\n");
    for(i=0;i<k;i++)
    {
        printf("\n\t\t%s\t\t%s\t\t%d\t\t%f\n",arr[i].roll,arr[i].name,arr[i].sec,arr[i].marks,arr[i].grade);\
    }
    fclose(fp);
}