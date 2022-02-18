#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Size 997
#define wSize 20

void toupperCase(char string[]); // converts words to uppercase
struct node* createNode(char word[], char docName[]); // creates a new node for new word if necessary
void nullify_table(struct node* hashTable[]); // makes the hash table null at the start
void nullify_docnames(struct node* head);   // makes all elements inside hash table null;
int horner(char word[]);    // string to key using horner method
void createHashtable(struct node* hashTable[],char word[], char docName[]); // creates hash table using word and document name given as argument
void printValue(struct node* hashTable[], char word[]); // searches and prints all the documents that the word exists in
void writeToFile(struct node* hashTable[]); // saves the hash table to a text file
void createExistingTable(struct node* hashTable[]); // recreates the saved hash table from saved text file
void readFile(char filename[], struct node* hashTable[]); // reads new document and creates a hashtable


int numElements = 0; // for storing number of elements inside hash table

struct node // saves word and it's documents
{
    char word[wSize];
    struct documents* docName[wSize];
};
struct documents
{
    char name[wSize];
};
void nullify_table(struct node* hashTable[]) //makes the hash table null at the start
{
    for(int i = 0; i<Size; i++)
    {
        hashTable[i] = NULL;
    }
}

void nullify_docnames(struct node* head) // makes all elements inside hash table null;
{
    for(int i = 0; i<wSize; i++)
    {
        head->docName[i] = NULL;
    }
}

int horner(char word[]) // string to key using horner method
{
    int length = strlen(word);
    toupperCase(word);
    long long int hash = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        hash = (31 * hash) + (word[i]-'A'+1);
    }
    hash = hash%Size;
    return hash;
}

void toupperCase(char string[]) // converts words to uppercase
{
    int i;
    for (i = 0; string[i]!='\0'; i++) {
        if(string[i] >= 'a' && string[i] <= 'z') {
            string[i] = string[i]-32;
        }
    }
}

void createHashtable(struct node* hashTable[],char word[], char docName[]) // creates hash table using word and document name given as argument
{
    int key = horner(word); // get the key using horner method
    double loadFactor;      // for saving loadfactor
    int doubleIndex;        // index for double hash
    int index1 = key%Size;  // first index
    int index2 = 1+(key%(Size-1)); // used for double hashing
    if( hashTable[index1] != NULL ) // if element is not null, do double hashing, if element is null add the element, commands are in else branch
    {
        if(strcmp(word, hashTable[index1]->word))// if element is not null, see if the elements are same strcmp returns 0 if same
        { // elements are not same get new index
            int i=1;
            doubleIndex = (index1+(i*index2))%Size; // new index using double hash
            while((hashTable[doubleIndex] != NULL) && (i<Size))
            {
                if(!strcmp(word, hashTable[doubleIndex]->word)) // if new index element is not null, break if they are the same
                {
                    break;
                }
                i++;
                doubleIndex = (index1+(i*index2))%Size;
            }
            if(hashTable[doubleIndex] == NULL)  // if new index is null add the element
            {
                loadFactor = (float)numElements/Size;

                printf("Load Factor is %lf\n",loadFactor);
                if(loadFactor<0.8)
                {
                    numElements++;
                    hashTable[index1] = createNode(word, docName);
                }
                else if(loadFactor>0.8 && loadFactor <1)
                {
                    printf("WARNING : Hash Table is NEARLY FULL\n");
                    numElements++;
                    hashTable[index1] = createNode(word, docName);
                }
                else
                {
                    printf("Hash Table is Full\n");
                    printf("Element not added :\n");
                    printf("%s\n", word);
                }
                return;
            }
            else if(i>= Size)   // cound't produce new index
            {
                printf("Program Could not find a Suitable place for the Word '%s'\n", word);
                return;
            }
            else    // if the elements are same add the document name to the list
            {
                int i=0;
                while(hashTable[index1]->docName[i] != NULL ) // find an empty space for the new document
                {
                    if(!strcmp(hashTable[index1]->docName[i]->name, docName))
                    {
                        return;
                    }
                    i++;
                }
                hashTable[index1]->docName[i] = (struct documents*)malloc(sizeof(struct documents));
                strcpy(hashTable[index1]->docName[i]->name, docName);
                return;
            }
        }
        else // if elements are same add new document to the list
        {
            int i=0;
            while(hashTable[index1]->docName[i] != NULL )
            {
                if(!strcmp(hashTable[index1]->docName[i]->name, docName))
                {
                    return;
                }
                i++;
            }
            hashTable[index1]->docName[i] = (struct documents*)malloc(sizeof(struct documents));
            strcpy(hashTable[index1]->docName[i]->name, docName);
        }
    }
    else // if first index is null add the element
    {
        loadFactor = (float)numElements/Size;
        printf("Load Factor is %lf\n",loadFactor);
        if(loadFactor<0.8)
        {
            numElements++;
            hashTable[index1] = createNode(word, docName);
            return;
        }
        else if(loadFactor>0.8 && loadFactor <1)
        {
            printf("WARNING : Hash Table IS NEARLY FULL\n");
            hashTable[index1] = createNode(word, docName);
            return;
        }
        else
        {
            printf("Hash Table is Full\n");
            printf("Element not added :\n");
            printf("%s\n", word);
            return;
        }

    }
    return;
}

void createHashtable2(struct node* hashTable[],char word[], char docName[]) // creates hash table using word and document name given as argument
{
    int key = horner(word); // get the key using horner method
    float loadFactor;      // for saving loadfactor
    int doubleIndex;        // index for double hash
    int index1 = key%Size;  // first index
    int index2 = 1+(key%(Size-1)); // used for double hashing
    if( hashTable[index1] != NULL ) // if element is not null, do double hashing, if element is null add the element, commands are in else branch
    {
        if(strcmp(word, hashTable[index1]->word))// if element is not null, see if the elements are same strcmp returns 0 if same
        { // elements are not same get new index
            int i=1;
            doubleIndex = (index1+(i*index2))%Size; // new index using double hash
            while((hashTable[doubleIndex] != NULL) && (i<Size))
            {
                if(!strcmp(word, hashTable[doubleIndex]->word)) // if new index element is not null, break if they are the same
                {
                    break;
                }
                i++;
                doubleIndex = (index1+(i*index2))%Size;
            }
            if(hashTable[doubleIndex] == NULL)  // if new index is null add the element
            {
                loadFactor = (float)numElements/Size;

                //printf("Load Factor is %lf\n",loadFactor);
                if(loadFactor<0.8)
                {
                    numElements++;
                    hashTable[index1] = createNode(word, docName);
                }
                else if(loadFactor>0.8 && loadFactor <1)
                {
                    //printf("WARNING : Hash Table is NEARLY FULL\n");
                    numElements++;
                    hashTable[index1] = createNode(word, docName);
                }
                else
                {
                    //printf("Hash Table is Full\n");
                    //printf("Element not added :\n");
                    printf("%s\n", word);
                }
                return;
            }
            else if(i>= Size)   // cound't produce new index
            {
                printf("Program Could not find a Suitable place for the Word '%s'\n", word);
                return;
            }
            else    // if the elements are same add the document name to the list
            {
                int i=0;
                while(hashTable[index1]->docName[i] != NULL ) // find an empty space for the new document
                {
                    if(!strcmp(hashTable[index1]->docName[i]->name, docName))
                    {
                        return;
                    }
                    i++;
                }
                hashTable[index1]->docName[i] = (struct documents*)malloc(sizeof(struct documents));
                strcpy(hashTable[index1]->docName[i]->name, docName);
                return;
            }
        }
        else // if elements are same add new document to the list
        {
            int i=0;
            while(hashTable[index1]->docName[i] != NULL )
            {
                if(!strcmp(hashTable[index1]->docName[i]->name, docName))
                {
                    return;
                }
                i++;
            }
            hashTable[index1]->docName[i] = (struct documents*)malloc(sizeof(struct documents));
            strcpy(hashTable[index1]->docName[i]->name, docName);
        }
    }
    else // if first index is null add the element
    {
        loadFactor = (float)numElements/Size;
        //printf("Load Factor is %lf\n",loadFactor);
        if(loadFactor<0.8)
        {
            numElements++;
            hashTable[index1] = createNode(word, docName);
            return;
        }
        else if(loadFactor>0.8 && loadFactor <1)
        {
            numElements++;
            //printf("WARNING : Hash Table IS NEARLY FULL\n");
            hashTable[index1] = createNode(word, docName);
            return;
        }
        else
        {
           // printf("Hash Table is Full\n");
           // printf("Element not added :\n");
           // printf("%s\n", word);
            return;
        }

    }
    //printf("Load Factor is %f\n", loadFactor);
    return;
}

void printValue(struct node* hashTable[], char word[]) // searches and prints all the documents that the word exists in
{
    int steps = 1;  // save the number of steps used for searching the word
    int key = horner(word); // find the horner key and make the element uppercase
    int doubleIndex;
    int index1 = key%Size;
    int index2 = 1+(key%(Size-1));
    if( hashTable[index1] != NULL ) // if first index is null it means the element does not exist
    {
        if(!strcmp(word, hashTable[index1]->word)) // if the first index is not null check if they words are same
        {
            steps++;        // increment number of steps and write documents
            int j=0;
            printf("Word is %s\n", hashTable[index1]->word);
            printf("Documents that the word exists are :\n");
            while(hashTable[index1]->docName[j] != NULL)
            {
                printf("%s\n", hashTable[index1]->docName[j]->name);
                j++;
            }
            printf("Number of steps taken : %d\n", steps);
            return;
        }
        else    // if they are not the same, find new index and increment the steps every time new index is generated
        {
            steps++;
            int i=1;
            doubleIndex = (index1+(i*index2))%Size;
            while(hashTable[doubleIndex] != NULL && i<Size)
            {
                if(!strcmp(word, hashTable[doubleIndex]->word))
                {
                    int j=0;
                    printf("Word is %s\n", hashTable[doubleIndex]->word);
                    printf("Documents that the word exists are :\n");
                    while(hashTable[doubleIndex]->docName[j] != NULL)
                    {
                        printf("%s\n", hashTable[doubleIndex]->docName[j]->name);
                        j++;
                    }
                    printf("Number of Steps taken : %d\n",steps);
                    return;
                }
                i++;
                doubleIndex = (index1+(i*index2))%Size;
                steps++;
            }
            printf("Word Does Not Exist\n");
            printf("Number of Steps Taken : %d\n",steps);
            return;

        }
    }
    else
    {
        printf("Word Does Not Exist\n");
        printf("Number of Steps Taken : %d\n",steps);
        return;
    }
}

struct node* createNode(char word[], char docName[]) // creates a new node for new word if necessary
{
    int i;
    struct node* pointer = NULL;
    pointer = (struct node*)malloc(sizeof(struct node));
    strcpy(pointer->word, word);
    nullify_docnames(pointer);
    while(pointer->docName[i] != NULL)
    {
        i++;
    }
    pointer->docName[i] = (struct documents*)malloc(sizeof(struct documents));
    strcpy(pointer->docName[i]->name, docName);
    return pointer;
};

void writeToFile(struct node* hashTable[]) // saves the hash table to a text file
{
    FILE *file = fopen("18011904.txt", "w");
    if ( file == NULL)
    {
        printf("Could not write to the file\n");
        return;
    }
    int i;
    for(i=0; i<Size; i++)
    {
        if(hashTable[i] != NULL)
        {
            int j=0;
            fprintf(file, "%s ", hashTable[i]->word);
            while(hashTable[i]->docName[j] != NULL)
            {
                fprintf(file, "%s ", hashTable[i]->docName[j]->name);
                j++;
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    return;

}

void createExistingTable(struct node* hashTable[]) // recreates the saved hash table from saved text file
{
    char line[Size];
    char word[wSize];
    char docName[wSize];
    FILE *file = fopen("18011904.txt", "r");
    if ( file == NULL)
    {
        //printf("Could not read the file\n");
        return;
    }

    while(!feof(file))
    {
        fgets(line, Size, file); // get one line at a time from the text
        int i=0;
        int len = strlen(line);
        int k;

        for(k = 0; k< wSize; k++)  // making sure the array elements are null
        {
            word[k] = 0;
        }

        while(i<len-1)
        {
            for(k=0;k<wSize;k++)
            {
                docName[k]=0;
            }

            if( i==0 )
            {
                int j=0;
                while( line[i] != ' ' && line[i] != ',' && line[i] != NULL && line[i] != '\n' /*&& line[i] != '.'*/ && line[i]!='?')
                {
                    word[j] = line[i];  // get character by character
                    i++;
                    j++;
                }
            }
            else
            {
                int j=0;
                while( line[i] != ' ' && line[i] != ',' && line[i] != NULL && line[i] != '\n' && line[i]!='?')
                {
                    docName[j] = line[i];  // get character by character
                    i++;
                    j++;
                }
                createHashtable2(hashTable, word, docName);
            }
            i++;

        }
    }
}

void readFile(char filename[], struct node* hashTable[]) // reads new document and creates a hashtable
{
    FILE *file;
    char line[10000];
    char word[wSize];

    file = fopen(filename, "r");
    if ( file == NULL)
    {
        printf("Could no read the file\n");
        return;
    }

    while(!feof(file))
    {
        fgets(line,Size,file); // get one line first from the text
        int i=0;
        int len = strlen(line);
        while(i<len)
        {
            int k;
            for(k = 0; k< wSize; k++)  // making sure the array elements are null
            {
                word[k] = 0;
            }

            int j =0; // used for reading line character by character
            while( line[i] != ' ' && line[i] != ',' && line[i] != NULL && line[i] != '\n' && line[i] != '.' && line[i]!='?')
            {
                word[j] = line[i];  // get character by character
                i++;
                j++;
            }
            if(word[0] != 0)
            {
                createHashtable(hashTable,word,filename);
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    fclose(file);
    writeToFile(hashTable);
    printf("File Added Successfully\n");
    return;
}

int main()
{
    int select;
    char docName[20];
    char word[20];
    int value=1;
    struct node* hashTable[Size];
    nullify_table(hashTable);
    createExistingTable(hashTable);



    while(value)
    {
        printf("Enter 1 : To ADD Documents, Enter 2 : To SEARCH From Documents, Enter Any other number: To EXIT\n");
        scanf("%d", &select);
        switch(select)
        {
            case 1:
            {
                printf("Enter the name of the file:\n");
                scanf("%s",docName);
                readFile(docName, hashTable);
                break;
            }

            case 2:
            {
                printf("Enter the WORD you are looking for:\n");
                scanf("%s",word);
                printValue(hashTable, word);
                break;

            }
            default:
                printf("Program Exited\n");
                value = 0;
                break;
        }
    }

    return 0;
}
