#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<io.h>

#define MAXINODE 50

#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

typedef struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
}SUPERBLOCK, *PSUPERBLOCK;

typedef struct Inode
{
    char FileName[40];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    int ReferenceCount;
    int Permission;   // 1  2  3
    struct Inode *next;
}INODE, *PINODE, **PPINODE;

typedef struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Count;
    int Mode;   // 1  2  3
    PINODE PtrInode;
}FILETABLE, *PFILETABLE;

typedef struct ufdt
{
    PFILETABLE PtrFiletable;
}UFDT;

UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKobj;
PINODE Head = NULL;         

void man(char *name)
{
    if(name == NULL) return;

    if(strcmp(name, "create") == 0)
    {
        printf("Description : Used to create new regular file\n");
        printf("Usage : create File_name permission\n");
    }
    else if(strcmp(name, "read") == 0)
    {
        printf("Description : Used to read data from regular file\n");
        printf("Usage : read File_name No_Of_Bytes_To_Read\n");
    }
    else if(strcmp(name, "write") == 0)
    {
        printf("Description : Used to write into regular file\n");
        printf("Usage : write File_name \n After that enter the data that you want to write into the file\n");
    }
    else if(strcmp(name, "ls") == 0)
    {
        printf("Description : Used to list all information of files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp(name, "stat") == 0)
    {
        printf("Description : Used to display statistical information about files\n");
        printf("Usage : stat File_name\n");
    }
    else if(strcmp(name, "fstat") == 0)
    {
        printf("Description : Used to display statistical information about file\n");
        printf("Usage : fstat File_Descriptor\n");
    }
    else if(strcmp(name, "truncate") == 0)
    {
        printf("Description : Used to remove data from file\n");
        printf("Usage : truncate File_name\n");
    }
    else if(strcmp(name, "open") == 0)
    {
        printf("Description : Used to open existing file\n");
        printf("Usage : open File_name\n");
    }
    else if(strcmp(name, "close") == 0)
    {
        printf("Description : Used to close opened file\n");
        printf("Usage : close File_name\n");
    }
    else if(strcmp(name, "closeall") == 0)
    {
        printf("Description : Used to closecall the opened files\n");
        printf("Usage : closeall\n");
    }
    else if(strcmp(name, "lseek") == 0)
    {
        printf("Description : Used to change the file offset\n");
        printf("Usage : lseek File_name ChangeInOffset StartPoint\n");
    }
    else if(strcmp(name, "rm") == 0)
    {
        printf("Description : Used to delete the file\n");
        printf("Usage : rm File_name\n");
    }
    else
    {
        printf("ERROR : No manual entry available\n");
    }
}

void DisplayHelp()
{
    printf("Is To List out all files\n");
    printf("clear: To clear console\n");
    printf("open: To open the file\n");
    printf("close: To close the file\n");
    printf("closeall: To close all opened files\n");
    printf("read: To Read the contents from file\n");
    printf("write To Write contents into file\n");
    printf("exit: To Terminate file system\n");
    printf("stat: To Display information of file using name\n");
    printf("fstat:To Display information of file using file descriptor\n");
    printf("truncate: To Remove all data from file\n");
    printf("rm: To Delet the file\n");
}

int GetFdFromName(char *name)
{
    int i = 0;

    while(i < 50)
    {
        if(UFDTArr[i].PtrFiletable != NULL)
            if(strcmp((UFDTArr[i].PtrFiletable-> PtrInode-> FileName), name) == 0)
            break;
        i++;
    }

    if(i == 50) return -1;
    else    return i;
}

PINODE Get_Inode(char *name)
{
    PINODE Temp = Head;
    int i = 0;

    if(name == NULL)
        return NULL;
    
    while(Temp != NULL)
    {
        if(strcmp(name, Temp->FileName) == 0)
            break;
        Temp=Temp->next;
    }
    return Temp;
}

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE Temp = Head;

    while( i <= MAXINODE)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        newn->LinkCount = 0;
        newn->ReferenceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;

        newn->Buffer = NULL;
        newn->next  = NULL;

        newn->InodeNumber = i;

        if(Temp == NULL)
        {
            Head = newn;
            Temp = Head;
        }
        else
        {
            Temp->next = newn;
            Temp = Temp->next;
        }
        i++;
    }
    printf("DILB created successfully\n");
}

void InitialiseSuperBlock()
{
    int i = 0;
    while(i < MAXINODE)
    {
        UFDTArr[i].PtrFiletable = NULL;
        i++;
    }

    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInodes = MAXINODE;
}

int CreateFile(char *name, int Permission)
{
    int i = 0;
    PINODE Temp = Head;

    if((name == NULL) || (Permission == 0) || (Permission > 3))
        return -1;
    
    if(SUPERBLOCKobj.FreeInodes == 0)
        return -2;

    (SUPERBLOCKobj.FreeInodes)--;

    if(Get_Inode(name) != NULL)
        return -3;
    
    while(Temp != NULL)
    {
        if(Temp->FileType == 0)
            break;
        Temp = Temp->next;
    }

    while(i < 50)
    {
        if(UFDTArr[i].PtrFiletable == NULL)
            break;
        i++;
    }

    UFDTArr[i].PtrFiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    UFDTArr[i].PtrFiletable->Count = 1;
    UFDTArr[i].PtrFiletable->Mode = Permission;
    UFDTArr[i].PtrFiletable->ReadOffset = 0;
    UFDTArr[i].PtrFiletable->WriteOffset = 0;

    UFDTArr[i].PtrFiletable->PtrInode = Temp;

    strcpy(UFDTArr[i].PtrFiletable->PtrInode->FileName, name);
    UFDTArr[i].PtrFiletable->PtrInode->FileType = REGULAR;
    UFDTArr[i].PtrFiletable->PtrInode->ReferenceCount = 1;
    UFDTArr[i].PtrFiletable->PtrInode->LinkCount = 1;
    UFDTArr[i].PtrFiletable->PtrInode->FileSize = MAXFILESIZE;
    UFDTArr[i].PtrFiletable->PtrInode->FileActualSize = 0;
    UFDTArr[i].PtrFiletable->PtrInode->Permission = Permission;
    UFDTArr[i].PtrFiletable->PtrInode->Buffer = (char *)malloc(MAXFILESIZE);

    return i;
}

// rm_File("Demo.txt")
int rm_File(char *name)
{
    int fd = 0;

    fd = GetFdFromName(name);
    if(fd == -1)
        return -1;
    
    (UFDTArr[fd].PtrFiletable->PtrInode->LinkCount)--;

    if(UFDTArr[fd].PtrFiletable->PtrInode->LinkCount == 0)
    {
        UFDTArr[fd].PtrFiletable->PtrInode->FileType = 0;
        // free(UFDTArr[i].PtrFiletable->PtrInode->Buffer);
        free(UFDTArr[fd].PtrFiletable);
    }

    UFDTArr[fd].PtrFiletable = NULL;
    (SUPERBLOCKobj.FreeInodes)++;
}

int ReadFile(int fd, char *Arr, int iSize)
{
    int read_size = 0;

    if(UFDTArr[fd].PtrFiletable == NULL)    return -1;

    if(UFDTArr[fd].PtrFiletable->Mode != READ && UFDTArr[fd].PtrFiletable->Mode != READ+WRITE)  return -2;

    if(UFDTArr[fd].PtrFiletable->PtrInode->Permission != READ && UFDTArr[fd].PtrFiletable->PtrInode->Permission != READ+WRITE)  return -2;

    if(UFDTArr[fd].PtrFiletable->ReadOffset == UFDTArr[fd].PtrFiletable->PtrInode->FileActualSize)  return -3;

    if(UFDTArr[fd].PtrFiletable->PtrInode->FileType != REGULAR)     return -4;

    read_size = (UFDTArr[fd].PtrFiletable->PtrInode->FileActualSize) - (UFDTArr[fd].PtrFiletable->ReadOffset);
    if(read_size < iSize)
    {
        strncpy(Arr,(UFDTArr[fd].PtrFiletable->PtrInode->Buffer) + (UFDTArr[fd].PtrFiletable->ReadOffset), read_size);

        UFDTArr[fd].PtrFiletable->ReadOffset = UFDTArr[fd].PtrFiletable->ReadOffset + read_size;
    }
    else
    {
        strncpy(Arr, (UFDTArr[fd].PtrFiletable->PtrInode->Buffer) + (UFDTArr[fd].PtrFiletable->ReadOffset), iSize);

        (UFDTArr[fd].PtrFiletable->ReadOffset) = (UFDTArr[fd].PtrFiletable->ReadOffset) + iSize;
    }

    return iSize;
}

int WriteFile(int fd, char *Arr, int iSize)
{
    if(((UFDTArr[fd].PtrFiletable->Mode) != WRITE) && ((UFDTArr[fd].PtrFiletable->Mode) != READ + WRITE))   return -1;

    if(((UFDTArr[fd].PtrFiletable->PtrInode->Permission) != WRITE) && ((UFDTArr[fd].PtrFiletable->PtrInode->Permission) != READ + WRITE))   return -1;

    if((UFDTArr[fd].PtrFiletable->WriteOffset) == MAXFILESIZE)  return -2;

    if((UFDTArr[fd].PtrFiletable->PtrInode->FileType) != REGULAR)   return -3;

    strncpy((UFDTArr[fd].PtrFiletable->PtrInode->Buffer) + (UFDTArr[fd].PtrFiletable->WriteOffset), Arr, iSize);

    (UFDTArr[fd].PtrFiletable->WriteOffset) = (UFDTArr[fd].PtrFiletable->WriteOffset) + iSize;

    (UFDTArr[fd].PtrFiletable->PtrInode->FileActualSize) = (UFDTArr[fd].PtrFiletable->PtrInode->FileActualSize) + iSize;

    return iSize;
}

int OpenFile(char *name, int mode)
{
    int i = 0;
    PINODE temp = NULL;

    if(name == NULL || mode <+ 0)   return -1;


    temp = Get_Inode(name);
    if(temp == NULL)    return -2;


    if(temp->Permission < mode) return -3;
    

    while(i<50)
    {
        if(UFDTArr[i].PtrFiletable == NULL) 
            break;
        i++;
    }

    UFDTArr[i].PtrFiletable = (PFILETABLE)malloc(sizeof(PFILETABLE));
    if(UFDTArr[i].PtrFiletable == NULL) return -1;
    UFDTArr[i].PtrFiletable->Count = 1;
    UFDTArr[i].PtrFiletable->Mode = mode;
    if(mode == READ + WRITE)
    {
        UFDTArr[i].PtrFiletable->ReadOffset = 0;
        UFDTArr[i].PtrFiletable->WriteOffset = 0;
    }
    else if(mode == READ)
    {
        UFDTArr[i].PtrFiletable->ReadOffset = 0;
    }
    else if(mode == WRITE)
    {
        UFDTArr[i].PtrFiletable->WriteOffset = 0;
    }
    UFDTArr[i].PtrFiletable->PtrInode = temp;
    (UFDTArr[i].PtrFiletable->PtrInode->ReferenceCount)++;

    return i;
}

void CloseFileByName(int fd)
{
    UFDTArr[fd].PtrFiletable->ReadOffset = 0;
    UFDTArr[fd].PtrFiletable->WriteOffset = 0;
    (UFDTArr[fd].PtrFiletable->PtrInode->ReferenceCount)--;
}


int main()
{
    char *ptr = NULL;
    int iRet = 0, fd = 0, Count = 0;
    char Command[4][80], Str[80], Arr[1024];


    return 0;
}