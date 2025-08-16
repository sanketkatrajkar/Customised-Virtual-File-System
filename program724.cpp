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
# define ERR_PERMISSION_DENIED -5
# define ERR_INSUFFICIENT_SPACE -6
# define ERR_INSUFFICIENT_DATA -7
 
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
    printf("ls : it is use to list out all file from the direcotory \n");
    printf("stat : it is use to display statistidcal information about file\n");
    printf("write : it is use to write the data into the file\n");
    printf("read : it is use to the data from the file\n");

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

    }
     else if(strcmp(name, "stat") == 0)
    {
         printf("Discription : This command is use to Dsiplay stastical information aobut the file\n");
         printf("Usage : stat file_name \n");
         printf("File_name : the name of file that you want to Display \n");

    }
     else if(strcmp(name, "ls") == 0)
    {
         printf("Discription : This command is use to all infomation about the files from the directory\n");

         printf("Usage : ls \n");

    }
    else if(strcmp(name, "write") == 0)
    {
         printf("Discription : This command is use  write the data into the file\n");

         printf("Usage : Write file_discription \n");

    }
    else if(strcmp(name, "read") == 0)
    {
         printf("Discription : This command is use  read the data from file\n");

         printf("Usage : read file_discription_ size\n");
         printf("File_Discripter : its a value raturned byy crate system call\n");
         printf("Size : Number of bytes that you want to read \n");

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

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : ls_file
//   Discription : It is used to a all file in directory 
//   Input : nothing
//   Ouput : nothing 
//   Author : Sanket Ashok Katrajkar.
//   Date :  15/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

// Marvelous CVSF >> ls 

void ls_file()
{
    PINODE temp = head;

    while(temp != NULL)
    {
        if(temp -> FileType != 0)
        {
            printf("%s\n", temp -> FileName);
        }

        temp = temp -> next;
    }
}


///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : stat_file
//   Discription : It is used to a show about the given file 
//   Input : file name
//   Ouput : nothing 
//   Author : Sanket Ashok Katrajkar.
//   Date :  15/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

// Marvelous CVSF >> stat Demo.txt

int stat_file(char *name)
{
    PINODE temp = head;

    if(name == NULL)
        return ERR_INVALID_PARAMETER;

    if(IsFileExists(name) == false)
        return ERR_FILE_NOT_EXISTS;

    while(temp != NULL)
    {
        if((strcmp(name, temp->FileName) == 0) && (temp->FileType != 0))
        {
            printf("--------------- Statistical Information of file ---------------------\n");
            printf("File name : %s\n", temp->FileName);
            printf("File Size on Disk : %d\n", temp->FileSize);
            printf("Actual file size : %d\n", temp->ActualFileSize);
            printf("Link Count : %d\n", temp->LinkCount);
            printf("File permission : ");
            if(temp->Permission == READ)
            {
                  printf("Read\n");
            } 
            else if(temp->Permission == WRITE)
            {
                  printf("Write\n");
            }
            else if(temp->Permission == READ + WRITE)
            {
                 printf("Read + Write\n");
            } 

            printf("File type : ");
            if(temp->FileType == REGULAFILE)
            {
                 printf("Regular file\n");
            } 
            else if(temp->FileType == SPECIALFILE)
            {
                 printf("Special file\n");
            } 

            break;
        }
        temp = temp->next;
    }

    return EXICUTE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : Write_file
//   Discription : It is used to wirte the contain the file 
//   Input : file Discripter ,
//           Adress of buffer which contains the data 
//           size of data that we want ot write
//   Ouput : Number of bytes succesfully written into the fle
//   Author : Sanket Ashok Katrajkar.
//   Date :  15/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

// Marvelous CVSF >>  write

int write_file( 
                 int fd,           // file discripter of file 
                 char *data ,      // data that we want to wirte 
                 int size          // size of data that we want to write
            )
{
    unsigned long int offset = 0;

    printf("File Discirpter is : %d\n", fd);
    printf("Data that we want to write : %s\n", data);
    printf("Number of bytes that we want to write : %d\n", size);

    //Invalid value of fd 
    if(fd < 0 || fd > MAXOPNEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    //file is not opned or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXISTS;
    }
      // if there is no permission to write the data into the file
    if(uareaobj.UFDT[fd] -> ptrinode -> Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }
    // Unable to write as ther is no sufficiendt space
    if((MAXFILESIZE - uareaobj.UFDT[fd] -> WriteOffSet) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }
    //Calculate the actual offset
    // offset = uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd] -> WriteOffSet;

    // Write the actual data
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd] -> WriteOffSet, data, size);
    
    //updat the write offset
    uareaobj.UFDT[fd]-> WriteOffSet = uareaobj.UFDT[fd] -> WriteOffSet + size;

    // write the actual size of ufleafter writeing the new data
    uareaobj.UFDT[fd]-> ptrinode ->ActualFileSize = uareaobj.UFDT[fd] ->ptrinode ->ActualFileSize + size;

    return size;
} 

///////////////////////////////////////////////////////////////////////////////////
//
//   Funtion Name : read_file
//   Discription : It is used to read the cotain the file 
//   Input : file Discripter ,
//           Adress empty buffer
//           size of data that we want ot read
//   Ouput : Number of bytes succesfully read into the fle
//   Author : Sanket Ashok Katrajkar.
//   Date :  15/08/2025
//
/////////////////////////////////////////////////////////////////////////////////////

// Marvelous CVSF >>  read 3 10

int read_file(
                int fd,            //file discripter 
                char * data,       // address of emty buffer
                int size           // Nubmer of file bytes that we want to read
)
{
     //Invalid value of fd 
    if(fd < 0 || fd > MAXOPNEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(data == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }
    //file is not opned or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXISTS;
    }
      // if there is no permission to read the data into the file
    if(uareaobj.UFDT[fd] -> ptrinode -> Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }
     // Unable to read as ther is no sufficiendt space
    if((MAXFILESIZE - uareaobj.UFDT[fd] -> ReadOffSet) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    strncpy(data , uareaobj.UFDT[fd] -> ptrinode -> Buffer + uareaobj.UFDT[fd] -> ReadOffSet , size);

    uareaobj.UFDT[fd] -> ReadOffSet = uareaobj.UFDT[fd] -> ReadOffSet + size;
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
    char InputBuffer[MAXFILESIZE] = {"\0"};
    char *EmptyBuffer = NULL;

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
               //Marvellout CVFS > ls 
            else if(strcmp(Command[0], "ls") == 0)
            {
                ls_file();
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
                   printf("Invalid paramerter \n");
                   printf(("please check the man page \n"));
                }
            }
            else if(strcmp(Command[0], "stat") == 0)
            {
                 iRet = stat_file(Command[1]);
                 if(iRet == ERR_FILE_NOT_EXISTS)
                 {
                     printf("Error : ");
                 }
                 if (iRet == ERR_INVALID_PARAMETER)
                 {
                    printf("Invalid paramerter \n");
                    printf(("please check the man page \n"));
                 }
            }
                
             else if(strcmp(Command[0], "write") == 0)
             {
                 printf("List Enter the data that you want to write : \n");
     
                 scanf("%[^'\n]s", InputBuffer);
                 fflush(stdin);

                 iRet = write_file(atoi(Command[1]), InputBuffer, strlen(InputBuffer));

                 if(iRet == ERR_INSUFFICIENT_SPACE)
                 {
                    printf("Error : Insufficient space in the data block for the file \n");
                 }
                 else if(iRet == ERR_PERMISSION_DENIED)
                 {
                    printf("Error : unable to write the as there is no write permissioon \n");
                 }
                 else if(iRet == ERR_INVALID_PARAMETER)
                 {
                    printf("Error : Invalide paramerter for th function \n");
                    printf("please check the man page for mroe details\n");
                 }
                 else if(iRet == ERR_FILE_NOT_EXISTS)
                 {
                    printf("Error : fd in invalide \n");
                 }
                 else
                 {
                    printf("%d butes get succesfully written into the file \n", iRet);
                    printf("Data from file is : %s\n", uareaobj.UFDT[0] -> ptrinode -> Buffer);
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
            //Marvellout CVFS > read 3 10
            else if(strcmp(Command[0], "read") == 0)
            {
               EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));


               iRet = read_file(atoi(Command[1]), EmptyBuffer , atoi(Command[2]));

               
                 if(iRet == ERR_INSUFFICIENT_DATA)
                 {
                    printf("Error : Insufficient space in the data block for the file \n");
                 }
                 else if(iRet == ERR_PERMISSION_DENIED)
                 {
                    printf("Error : unable to READ the as there is no read permissioon \n");
                 }
                 else if(iRet == ERR_INVALID_PARAMETER)
                 {
                    printf("Error : Invalide paramerter for th function \n");
                    printf("please check the man page for mroe details\n");
                 }
                 else if(iRet == ERR_FILE_NOT_EXISTS)
                 {
                    printf("Error : fd in invalide \n");
                 }
                 else
                 {
                    printf("Read operation is succesfull\n");
                    printf("data from file is : %s\n ", EmptyBuffer);

                    free(EmptyBuffer);
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

} /// End of main