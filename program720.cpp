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
//   User defined Marcros;
//
/////////////////////////////////////////////////////////////////////////////////////

# define MAXFILESIZE 100

// Maximum number of files htat we can opned
# define MAXOPNEDFILES 20  
// maximum number of file that we can create
# define MAXINODE 5          

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULAFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

# define EXICUTE_SUCCESS 0

////////////////////////////////////////////////////////////////////////////////////
//
//   User define  Marcros for error handling
//
/////////////////////////////////////////////////////////////////////////////////////
 
# define ERR_INVALID_PARAMETER -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXITS -3

# define ERR_FILE_NOT_EXISTS -4



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
//   Discription : Hold the infomation about the Process. 
//
/////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPNEDFILES];

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

    while( i <  MAXOPNEDFILES)
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
        newn -> FileType = 0;
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
    printf("---------------------- Commad Manual of Marvellous CVFS -----------------------------\n");
    printf("------------------------------------------------------------------------------------\n");

    printf("it is use to display the specific manual page for command\n");
    printf("exit : It is used to terminate the shell of Marvellous CVFS\n");
    printf("clear : It is used to clear the console of Marvellous CVFS\n");
    printf("Creat :It is use to create new regular file \n");
    printf("Unlink : it is use to delete the exitsting file \n");

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
         printf("Permission : \n1 : read \n2 : write  \n3 : read and write");
    }
    else if(strcmp(name, "man exit") == 0)
    {
         printf("Discription : This command is use to exit\n");
         printf("Usage : exit \n");

    } 
    else if(strcmp(name, "unlink") == 0)
    {
         printf("Discription : This command is use to delete to new regual file our file systems\n");
         printf("Usage : Create  File_name Permission \n");
         printf("File_name : the name of file that you want to delete \n");
         printf("Permission : \n1 : read \n2 : write  \n3 : read and write");

    }// add more options here
    else 
    {
       printf("no manual entry for %s\n",name);
    }

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
/////////////////////////////////////////////////////////////////////////////////////

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
//   Ouput : It return file discripter  
//   Author : Sanket Ashok Katrajkar.
//   Date :  11/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                char *name,       // Name of file
                int permission   // Permission of create file
              )
{ 
    PINODE temp = head;
    int i = 0;

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
 
    // Loop to search free Inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp -> next;
    }
   
    //iNode not found
    if(temp == NULL)
    {
        printf("Inode not found\n");
        return -1;
    }

   // search first not null value for UFD
   for(i = 0 ; i < MAXINODE; i++)
   {
     if(uareaobj.UFDT[1] == NULL)
     {
        break;
     }
   }

   //check the maximum inode is for creating file
   if(i == MAXINODE)
   {
     printf("Unbale to create file as max opened file limit reaches\n");
     return -1;
   }

   // Allocate ememory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

   //Initialise elemenets of file table 
   uareaobj.UFDT[i] ->  ReadOffSet = 0;
   uareaobj.UFDT[i] ->  WriteOffSet = 0;
   uareaobj.UFDT[i] ->  Count = 1;
   uareaobj.UFDT[i] ->  Mode = permission;

   // Connect file table with IIT 
   uareaobj.UFDT[i] ->  ptrinode = temp;

   strcpy(uareaobj.UFDT[i] ->  ptrinode -> FileName ,name);
   uareaobj.UFDT[i] ->  ptrinode -> FileSize = MAXFILESIZE;
   uareaobj.UFDT[i] ->  ptrinode -> ActualFileSize = 0;
   uareaobj.UFDT[i] ->  ptrinode -> FileType = REGULAFILE;
   uareaobj.UFDT[i] ->  ptrinode -> ReferenceCount = 1;
   uareaobj.UFDT[i] ->  ptrinode -> LinkCount = i;
   uareaobj.UFDT[i] ->  ptrinode -> Permission = permission;

   // Allocate memory for Buffer

   uareaobj.UFDT[i]->ptrinode->Buffer = (char * )malloc(MAXFILESIZE);

   return i;
}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : Unlink file
//   Discription : It is used to delete a new regular file 
//   Input : It accept the file name 
//   Ouput : nothing 
//   Author : Sanket Ashok Katrajkar.
//   Date :  15/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////


int UnlinkFile(
                 char *name // name of file 
               )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_EXISTS;
    }

    for(i = 0; i< MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {

            if(strcmp(uareaobj.UFDT[i] -> ptrinode ->FileName, name) == 0)
            {
                 //Deallocate the memory of buffer
                 free(uareaobj.UFDT[i] -> ptrinode -> Buffer);

                 // Reset of all values of Inode
                    uareaobj.UFDT[i] -> ptrinode -> FileSize = 0;
                    uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
                    uareaobj.UFDT[i] -> ptrinode -> LinkCount = 0;
                    uareaobj.UFDT[i] -> ptrinode -> Permission = 0 ;
                    uareaobj.UFDT[i] -> ptrinode -> FileType = 0;
                   
                    //Dealocate mermory of file table
                    free(uareaobj.UFDT[i]);

                    // Set NULL to UFDT Member
                    uareaobj.UFDT[i] = NULL;

                    //Increament the value of free iNode counts
                    superobj.FreeInodes++;

                    break;

            } // End of IF 
        }  // End of IF 
    }  // End of for 

    return EXICUTE_SUCCESS;

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

                 //Marvellout CVFS > help 
            else if(strcmp(Command[0], "help") == 0)
            {
                DsiplayHelp();
            } 
                       //Marvellout CVFS > cls 
            else if(strcmp(Command[0], "clear") == 0)
            {
                  system("cls");
            }

        }    // End of IF ICount == 1
        else if(iCount == 2)
        {
                  //Marvellout CVFS > creat

            if(strcmp(Command[0], "man") == 0)
            {
               ManPage(Command[1]);
            }
               //Marvellout CVFS > unlimk
            else if(strcmp(Command[0], "unlink") == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == EXICUTE_SUCCESS)
                {
                    printf("unlink operation is successfully performs\n");
                }
                else if(iRet == ERR_FILE_NOT_EXISTS)
                {
                    printf("Error : unable to do unlink activity as file is not presenet\n");
                }
                else if (iRet == ERR_INVALID_PARAMETER)
                {
                   printf("unvalid paramerter \n");
                   printf(("please check the man page \n"));
                }
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
                 printf("Error : Unable to create file as file already exits\n");
               }
               else
               {
                 printf("file is succesfuly created with FD : %d\n",iRet);
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

    } // End of While (CUSTOMiZE SHELL)
    

    return 0;

} /// End of MAIN