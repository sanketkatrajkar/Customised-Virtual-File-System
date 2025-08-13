////////////////////////////////////////////////////////////////////////////////////
//
//   Header file Inclusion
//
//////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////
//
//   User fefined Marcros;
//
/////////////////////////////////////////////////////////////////////////////////////

# define MAXFILESIZE 100

# define MAXINODE 5

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULAFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

////////////////////////////////////////////////////////////////////////////////////
//
//   Structure Name : BootBlock
//   Discription :    Holds Infomation to botot the operatin system
//
/////////////////////////////////////////////////////////////////////////////////////

struct BoolBlock
{
    char Information[100];

};

////////////////////////////////////////////////////////////////////////////////////
//
//   Structure Name : SuperBlock
//   Discription :    Hold the infomation about the file System
//
/////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;

};


////////////////////////////////////////////////////////////////////////////////////
//
//   Structure Name : Inode
//   Discription :    Hold the infomation about the file 
//
/////////////////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int LinkCount;
    char *Buffer;
    int Permission;

    struct Inode *next;
    
}INODE , *PINODE , ** PPINODE;

////////////////////////////////////////////////////////////////////////////////////
//
//   Structure Name : FileTable
//   Discription :    Hold the infomation about the opend file 
//
/////////////////////////////////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffSet;
    int WriteOffSet;
    int Count;
    int Mode;

    PINODE ptrinode;
}FILETABLE , *PFILETABLE;

////////////////////////////////////////////////////////////////////////////////////
//
//   Structure Name : UREA
//   Discription :    Hold the infomation about the Process. 
//
/////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXINODE];

};

////////////////////////////////////////////////////////////////////////////////////
//
//     Golble varible for object  used in project
//
/////////////////////////////////////////////////////////////////////////////////////

 BoolBlock bootobj;
 SuperBlock superobj;
 PINODE head = NULL;
 UAREA uareaobj;

 ///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : InitialiaseUAREA
//   Discription : It is used to InitialiaseUAREA 
//   Author : Sanket Ashok Katrajkar.
//   Date :  10/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

void InitialisseUREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    while( i < MAXINODE)
    {
       uareaobj.UFDT[i] = NULL;
       i++;
    }

    cout << "Marvellous CVFS : UAREA Initialiseion Succesfuully\n";

}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : Initialize SuperBlock
//   Discription : It is used to initiablize the ontents of super block
//   Author : Sanket Ashok Katrajkar.
//   Date :   10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;
    
    cout << "Marvellous CVFS : SuperBlcok Initialiseion Succesfuully\n";

}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : DILB 
//   Discription : It is used to create Linked List of Inodes
//   Author : Sanket Ashok Katrajkar.
//   Date :   10/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 0;
    PINODE newn = NULL;
    PINODE temp = head;

    while (i <= MAXINODE)
    {
        newn = new INODE;
        
        newn -> InodeNumber = i;
        newn -> FileSize = 0;
        newn -> ActualFileSize = 0;
        newn -> LinkCount = 0;
        newn -> Permission = 0 ;
        newn -> Buffer = NULL; 
        newn -> next = NULL;

        if(temp == NULL)
        {
           head = newn;
           temp = head;
        }
        else
        {
           temp -> next = newn;
           temp = temp -> next;
        }

        i++;
    }

    cout << "Marvellous CVFS : DILB created Succesfuully\n";   
}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : Start Auxilary data Initialiser
//   Discription : It is used to initiablize Start Auxilary data Initialiser
//   Author : Sanket Ashok Katrajkar.
//   Date :  10/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

void StartAuxilaryDataInitialiser()
{
    
    strcpy(bootobj.Information,"Boot process of operatin system");

    cout << bootobj.Information << "\n";

    InitialiseSuperBlock();

    CreateDILB();

    InitialisseUREA();

    cout << "Marvellous CVFS : Auxilary data Initialiser Succesfuully\n";
}


////////////////////////////////////////////////////////////////////////////////////
//
//   Entry point function of project (main)
//
/////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[4][80];

    StartAuxilaryDataInitialiser();

    cout << "----------------------------------------------------------------------------------\n";
    cout << "------------------- Marvellous CVFS started Successfully -------------------------\n";
    cout << "----------------------------------------------------------------------------------\n";

    while (1)
    {
        printf("\nMarvellous CVFS > ");
        fgets(str,sizeof(str),stdin);
        
        iCount = sscanf(str,"%s %s %s %s");

        
    } // End of While (CUSTOME SHELL)
    

    return 0;

} /// End of Main