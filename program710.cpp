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

int main ()
{
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[4][80];

    cout << "----------------------------------------------------------------------------------\n";
    cout << "------------------- Marvellous CVFS started Successfully -------------------------\n";
    cout << "----------------------------------------------------------------------------------\n";

    printf("\nMarvellous CVFS > ");
    fgets(str,sizeof(str),stdin);
        
    iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);

    printf("Number of tokens are : %d",iCount);

        
     // End of While (CUSTOME SHELL)
    

    return 0;

} /// End of Main