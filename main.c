//
//  main.c
//  amazing-hack
//
//  Created by thiagesh s. senguttuvan on 19/09/15.
//  Copyright © 2015 zoho. All rights reserved.
//

#include <stdio.h>
#include <string.h>
void readFile();
int isItemFound(char *line,char *itemNo);
void displayItemDetails(char *toBeParsed);

enum attributes {
    ITEMID = 0,
    AUTHORS = 1,
    RELEASEDATE = 2,
    LISTPRICE = 3,
    PUBLISHER = 4
};

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    readFile();
    displayItemDetails("");
    return 0;
}

void readFile()
{
    FILE *file;
    file=fopen("/Volumes/Macintosh HD/Volumes/Official/amazin-hack/main_folder/112836.csv", "r");
    
    if(file == NULL)
    {
        printf("file not found");
        return;
    }
    
    char *line = NULL;
    size_t len = 0;
    char read;
    while ((read = getline(&line, &len, file)) != -1)
        {
            
            char *stringToFindCorrectItem;
            strcpy(stringToFindCorrectItem, line);
            if(isItemFound(stringToFindCorrectItem,"1001"))
            {
                printf("line %s", line);
                displayItemDetails(line);
                break;
            }
        }
    
    
}

void displayItemDetails(char *toBeParsed)
{
    char *itemDetailsArray[10];
    char *ch;
    int i=0;
    ch = strtok(toBeParsed, ",");
    
    while (ch != NULL) {
        itemDetailsArray[i]=ch;
        i++;
        ch = strtok(NULL, ",");
    }
    
    for(int k=0;k<i;k++)
    {
        switch (k) {
            case ITEMID:
                printf("Item ID : %s\n",itemDetailsArray[ITEMID]);
                break;
            case AUTHORS:
                printf("Author : %s\n",itemDetailsArray[AUTHORS]);
                break;
            case RELEASEDATE:
                printf("Release Date : %s\n",itemDetailsArray[RELEASEDATE]);
                break;
            case LISTPRICE:
                printf("List Price : %s\n",itemDetailsArray[LISTPRICE]);
                break;
            case PUBLISHER:
                printf("Publisher : %s\n",itemDetailsArray[PUBLISHER]);
                break;
                
            default:
                break;
        }
//        printf("%s",itemDetailsArray[k]);
    }
    
}

int isItemFound(char *line,char *itemNo)
{
//    char tokenstring[] = line;
    char seps[] = ",";
    char* token;

    
    token = strtok (line, seps);
    
    if(strcmp(token, itemNo) == 0)
    {
        printf("item found \n");
        return 1;
    }
    else
    {
        printf("item not found\n");
        return 0;
    }

    
//    printf("token %s \n",token);
    
//    return 0;
    
}