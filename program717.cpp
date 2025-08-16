////////////////////////////////////////////////////////////////////////////////////
//
//   Header file Inclusion
//
//////////////////////////////////////////////////////////////////////////////////////
#include<iostream>

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
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
//   User define  Marcros for error handling
//
/////////////////////////////////////////////////////////////////////////////////////
 
# define ERR_INVALID_PARAMETER -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXITS -3

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

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : DiplayHelp
//   Discription : It is used to Display the informatio aobut commands 
//   Author : Sanket Ashok Katrajkar.
//   Date :  11/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

void DsiplayHelp()
{
    printf("------------------------------------------------------------------------------------\n");
    printf("----------------------Commad Manual of Marvellous CVFS -----------------------------\n");
    printf("------------------------------------------------------------------------------------\n");

    printf("it is use of clear the console of Marvellous CVFS \n");
    printf("It is use to termminate the shell of Marvellous CVFS \n");

    // add more options here

    printf("------------------------------------------------------------------------------------\n");

}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : ManPage 
//   Discription : It is used to Display the Manual page of the command 
//   Input : It accept the command name
//   Ouput : Display the Manual Detail the Commands 
//   Author : Sanket Ashok Katrajkar.
//   Date :  11/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

void ManPage(
              char *name       // Name of command
            )
{
    if(strcmp(name, "creat") == 0)
    {
         printf("Discription : This command is use to create to new regual file our file systems\n");
         printf("Usage : Create  File_name Permission \n");
         printf("File_name : the name of file that you want to create \n");
         printf("Permission : \n1 : read , \n2 : write , \n3 : read and write");
    }
    else if(strcmp(name, "man exit") == 0)
    {
         printf("Discription : This command is use to exit\n");
         printf("Usage : exit \n");

    } // add more options here

    printf("no manual entry for %s\n",name);
}
///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : isFileExitests 
//   Discription : It is used to  a new regular file 
//   Input : It accept the file name
//   Ouput : it returns boolean value (if present false : it not present)
//   Author : Sanket Ashok Katrajkar.
//   Date :  11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////

bool IsFileExists(
                    char *name  // Name of file that you want to check
                 )
{
    PINODE temp = head;
    bool bFlag = false;
        
    while(temp != NULL)
    {
        if((strcmp (name , temp -> FileName) == 0) && (temp -> FileType == REGULAFILE))
        {
           bFlag = true;
           break;
        }

        temp = temp -> next;
    }

    return bFlag;
}



///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : CreteFile 
//   Discription : It is used to  a new regular file 
//   Input : It accept the file name and permission 
//   Ouput : It return file discipter f 
//   Author : Sanket Ashok Katrajkar.
//   Date :  11/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                char *name,       // Name of file
                int permission   // Permission of create file
              )
{ 
    // if file name is missing 
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    
    // if enter permission is invalid 
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    //check whether empty inode is there or not 
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    //check whether file is already exits or not
    if(IsFileExists(name) == true)
    {
         return ERR_FILE_ALREADY_EXITS;
    }

    

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
    int iRet = 0;
    char Command[5][80];

    StartAuxilaryDataInitialiser();

    cout << "----------------------------------------------------------------------------------\n";
    cout << "------------------- Marvellous CVFS started Successfully -------------------------\n";
    cout << "----------------------------------------------------------------------------------\n";

    while (1)
    {
        fflush(stdin);

        printf("\nMarvellous CVFS > ");
        fgets(str,sizeof(str),stdin);
        
        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);

        if(iCount == 1)
        {
            if(strcmp(Command[0], "exit") == 0)
            {
              printf("Thank you for using Marvellous CVFS \n");
              printf("Deallocated all resources...\n");
  
              break;
            }

                 //Marvellout CVFS > HELP 
            else if(strcmp(Command[0], "Help") == 0)
            {
                DsiplayHelp();
            } 
                       //Marvellout CVFS > cls 
            else if(strcmp(Command[0], "clear") == 0)
            {
                  system("clear");
            }

        }    // End of IF ICount == 1
        else if(iCount == 2)
        {
                  //Marvellout CVFS > creat

            if(strcmp(Command[0], "man") == 0)
            {
               ManPage(Command[1]);
            }

        }    // End of IF ICount == 2
        else if(iCount == 3)
        {
            //Marvellout CVFS > creat Ganesh.txt 3
            if(strcmp(Command[0] , "creat") == 0)
            {
               iRet = CreateFile(Command[1], atoi(Command[2]));
               
               if(iRet == ERR_INVALID_PARAMETER)
               {
                 printf("Error : Invalid paramerter for function\n");
                 printf("Please check Man page for more details\n");
               }
               else if(iRet == ERR_NO_INODES)
               {
                 printf("Error : Unable to create file as there is no INodes ");
               }
               else if(iRet == ERR_FILE_ALREADY_EXITS)
               {
                 printf("Error : Unable to create file as file already exitsts\n");
               }
            }

        }   // End of IF ICount == 3
        else if(iCount == 4)
        {

        }  // End of IF ICount == 4
        else
        {
            printf("Command not fount \n");
            printf("Please refer Help option or use man command\n");

        }  //End of Invalid Command part 

    } // End of While (CUSTOME SHELL)
    

    return 0;

} /// End of Main