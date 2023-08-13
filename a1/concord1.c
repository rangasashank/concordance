#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFLEN 1000

//finding the smallest(ascii) word excluding the words in exclusions and returning the line in which it exits after caapitalising it.
char* smallest(char indexing[200][BUFLEN], char exclude[100][BUFLEN], int len_indexing, int len_exclude) {
    char line[BUFLEN];
    char final_line[BUFLEN]={};
    char *final_line_ptr = final_line;
    char smallest_word[BUFLEN] = "zzz";
    int index = 0;
    int i;
    
    // looping through lines_for_indexing
    for(i = 0; i< len_indexing; i++) {
        strcpy(line,indexing[i]);
        char *token = strtok(line," "); //tokenizing
        char word[BUFLEN];
        // looping through the tokens
        while(token != NULL) {
            //if exclusions is empty
            if (len_exclude==0)
            {
                strcpy(word,token);
            }

            else{
                //looping through exclusions and comparing the token
                for(int j = 0; j< len_exclude; j++) {
                if (strcmp(token,exclude[j])==0)
                {
                    strcpy(word,"");
                    break;//as it is an exclusion
                } else
                {
                    if (strcmp(word,token)!=0)                                                  
                    {
                        strcpy(word,token);
                    }
                    
                }
                

                
            }
            }
            
            token = strtok(NULL, " ");

            if ((strcmp(word,"")!=0) && (strcmp(word,smallest_word)<0))
            {
                index = i;//storing the index of the line containing the smallest word
                strcpy(smallest_word, word);
            }

        }
    }
    
    //for the final iteration when all the concatinations are done, the smallest word would not be updated 
    //as every word would be in exceptions
    if (strcmp(smallest_word,"zzz")==0)
    {
        return final_line_ptr;
    }


    else
    {

    strcpy(line,indexing[index]);
    char *token = strtok(line, " ");
    //loop through the line containing the smallest word and capitalize the smallest word
    while (token!= NULL)
    {
        if (strcmp(token,smallest_word)==0)
        {
            for (int k = 0; token[k]!='\0'; k++) {
                if(token[k] >= 'a' && token[k] <= 'z') {
                    token[k] = token[k] - 32;
                }
            }
            strcat(final_line,token);
            
            strcat(final_line," ");
            

        }
        else
        {
                strcat(final_line,token);
                strcat(final_line," ");
        }
        
        token = strtok(NULL, " ");
    }
    

    final_line[strlen(final_line)-1] ='\0';//removing the white space at the end
    }
    
    return final_line_ptr;
}

//de capitalising the smallest word to add it in the exclusions
char* excl_word(char line_ex[BUFLEN]) {
    char exclusion_word[BUFLEN]={};
    char *exclusion_word_ptr = exclusion_word;
    char *tok = strtok(line_ex," ");

    //looping through the tokens of the final line
    while (tok!=NULL)
    {
        //finding the token with capital letters and decapitalising it
        for (int i = 0; i < strlen(tok); i++)
        {
            if (tok[i]>='A' && tok[i]<='Z')
            {
                tok[i] += 32;
            }
            else
            {
                break;
            }
        
            strcpy(exclusion_word, tok);
            
        }
        tok = strtok(NULL, " ");
        

    }
    return exclusion_word_ptr;

}



int main(int argc, char *argv[])
{
    //making a array of strings and copying each line to it
    char buffer[BUFLEN];
    int num_lines = 0;
    char array[500][1000];
    while (fgets(buffer, sizeof(char) * BUFLEN, stdin)) {
        buffer[strcspn(buffer, "\r\n")] = 0;//making sure the string will be exactly equal to the line copied
       strncpy(array[num_lines], buffer, 1000);
       num_lines++;
    }


    //getting the index of the start of the exclusion words and end of the exclusion words by looping through the array of strings
    //and comparing it with single quotes and double quotes
    char single_quote[] = "''''";
    char double_quote[] = "\"\"\"\"";
    int start_index =0;
    int end_index=0;

    for (int j = 0; j< num_lines; j++) {
        if(strcmp(array[j],single_quote)==0){
            start_index = j+1;
        }
        if(strcmp(array[j],double_quote)==0) {
            end_index = j-1;
        }
        
    }


    //copying all the strings in the array between the quotes to a new array of strings
    char exclusion[100][BUFLEN];
    int l=start_index;
    for (int k = 0; k<= 100; k++) {
         if (l<=end_index){
             strcpy(exclusion[k],array[l]);
             l++;
         }  
     }

    //getting the lines_for_indexing, as we have index before the double quote, the next index till the end of array will
    //be the lines to be indexed

    int words_start = end_index+2;
    char lines_for_indexing[200][BUFLEN];
    int y = 0;
    for(int z = words_start; z<num_lines; z++) {
       strcpy(lines_for_indexing[y],array[z]);
       y++; 

    }
    int len_lines_for_indexing = y+1;
    int len_exclusions = end_index - (start_index-1);

    //find the word that is smallest(ascii) in the lines_for_indexing and print the line that contains it by capitalising it
    
    char final[BUFLEN];
    char exclusion_word[BUFLEN];

    strcpy(final, smallest(lines_for_indexing,exclusion,len_lines_for_indexing,len_exclusions));
    printf("%s",final);


    while(strlen(final)!=0) {
        printf("\n");
        strcpy(exclusion_word,excl_word(final));
        strcpy(exclusion[len_exclusions], exclusion_word);//copying the smallest word to exceptions
        len_exclusions += 1;
        strcpy(final, smallest(lines_for_indexing,exclusion,len_lines_for_indexing,len_exclusions));
        printf("%s",final);
    }

}
