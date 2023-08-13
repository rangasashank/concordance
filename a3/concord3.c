/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"

void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}

//Input through stdin
void get_input(char** array, int *num_lines) {
    char *buffer = emalloc(sizeof(char)*101);
    while (fgets(buffer, (sizeof(char)*101), stdin)!=NULL) {

        buffer[strcspn(buffer, "\r\n")] = 0;//making sure the string will be exactly equal to the line copied
        if (strlen(buffer)!=0)
        {
            strcpy(array[*num_lines], buffer);
            *num_lines += 1;
        }
    }
    free(buffer);
    //return array;
    
}

//convert string to lowercase
void lower_case(char* lower, char* normal){
    for (int i = 0; normal[i] != '\0'; i++)
        {
            lower[i] = tolower(normal[i]);
        }

}

// find the word that is smallest in lexographic order
void smallest_word(char* smallestWord, node_t *exclusion, node_t *indexing){
    strcpy(smallestWord,"zzz");
    smallestWord[strcspn(smallestWord, "\r\n")] = 0;
    
    
    char* line = emalloc(sizeof(char)*150);

    node_t *curr = NULL;

    for (curr = indexing; curr!= NULL; curr = curr -> next)
    {
        char* word = calloc(41,sizeof(char));
        char* lower_word = calloc(41,sizeof(char));
        strcpy(line,curr->text);
        line[strcspn(line, "\r\n")] = 0;
        char *token = strtok(line," ");
         // looping through the tokens
        while(token != NULL) {
            char* o_token = calloc(41,sizeof(char));

            // making the token lowercase
            lower_case(o_token,token);
        
            //if exclusions is empty
            if (exclusion==NULL)
            {
                strcpy(word,token);
                word[strcspn(word, "\r\n")] = 0;
                strcpy(lower_word, o_token);
                lower_word[strcspn(lower_word, "\r\n")] = 0;
            }

            else{
                //looping through exclusions and comparing the token

                node_t *curr2 = NULL;
                for(curr2 = exclusion; curr2 != NULL; curr2 = curr2 -> next) {
                        
                        if (strcmp(o_token,curr2->text)!=0)
                        {
                                strcpy(word,token);
                                word[strcspn(word, "\r\n")] = 0;
                                strcpy(lower_word, o_token);
                                lower_word[strcspn(lower_word, "\r\n")] = 0;
                        } 
                        else
                        {
                            strcpy(word," ");
                            word[strcspn(word, "\r\n")] = 0;

                            break;//as it is an exclusion
                        }
                
            }
            }
            // making smallestWord to lowercase
            char* small_small = calloc(41,sizeof(char));
            lower_case(small_small,smallestWord);
            // check again if word in exclusion
            node_t *cur = NULL;
            int count = 0;
            for (cur = exclusion; cur!=NULL; cur = cur->next)
            {
                if (strcmp(word,cur->text)==0)
                {
                    count += 1;
                    break;
                }
                else{
                    count = 0;
                }
                
            }
            

            if ((strcmp(word," ")!=0) && (strcmp(lower_word,small_small)<0) && (count==0))
            {
                strcpy(smallestWord, word);
                smallestWord[strcspn(smallestWord, "\r\n")] = 0;
            }
        // freeing up
        free(o_token); 
        free(small_small);
        token = strtok(NULL, " ");
        }
        // freeing up
        free(word);
        free(lower_word);
    }
    //freeing up
    free(line);
    if (strcmp(smallestWord, "zzz") == 0)
    {
        strcpy(smallestWord," ");
        smallestWord[strcspn(smallestWord, "\r\n")] = 0;

    }
    
    
    
}

// capitalize the word and return the sentence to be printed
void capitalize(char* sentence, char*word) {
    char* duplicate = emalloc(strlen(sentence)+1);
    strcpy(duplicate,sentence);
    char* token = strtok(duplicate," ");
    char* final = emalloc(sizeof(char)*150);
    strcpy(final,"");
    final[strcspn(final, "\r\n")] = 0;
    //finding the smalles word in the sentence and capitalizing it
    while (token!= NULL)
    {
        if (strcmp(token,word)==0)
        {
            for (int k = 0; token[k]!='\0'; k++) {
                if(token[k] >= 'a' && token[k] <= 'z') {
                    token[k] = token[k] - 32;
                }
            }
        }
            strcat(final,token);
            strcat(final," ");     
            token = strtok(NULL, " ");
    }
    final[strlen(final)-1] ='\0';//removing the white space at the end
    strcpy(sentence,final);
    free(final);
    free(duplicate);
    
}


//return line after appropriate formatting

void final(char* final_sentence, int num_spaces) {
    char* arr1 = emalloc(sizeof(char)*(strlen(final_sentence))+2);
    char* arr2 = calloc(71,sizeof(char));
    int count = 0;
    int length_of_words = 0;
    strcpy(arr2,"");
    arr2[strcspn(arr2, "\r\n")] = 0;
    strcpy(arr1,final_sentence);
    arr1[strcspn(arr1, "\r\n")] = 0;

    
    

    //adding each letter to arr1 and counting the legth of each word before smallest word to add with number of spaces later
    
    for(int i=0; arr1[i]!=0; i++){
        char c = arr1[i];
        if((c == ' ') && (count<num_spaces)){
            count += 1;
        }
        else if(c!=' ' && count<num_spaces){
            length_of_words += 1;

        }
        else{
            count += 0;
            length_of_words += 0;
        }
    }

    for (int i = 0; i < 70; i++)
    {
        arr2[i] = ' ';
    }
    arr2[69]='\0';

    size_t a = 29; // 30th column
    size_t upper = length_of_words + num_spaces; // index of first letter of smallest word

    size_t k = upper;
    //adding letters to the left of index 29(column 30)
    while (k>0 && a>0){
        arr2[a-1] = arr1[k-1];
        k = k-1;
        a = a-1;
    }
       
    
    a = 29;
    k = upper;

    //adding letters to the right of index 29(column 30)
    while (k<strlen(arr1) && a<strlen(arr2)){
        arr2[a] = arr1[k];
        a = a+1;
        k = k+1;
    }

    //removing any words before column 10
    int m = 0;
    while (m<9){
        if (arr2[m] != ' '){
            int n = m;
            while (arr2[n] != ' '){
                arr2[n] = ' ';
                n = n+1;
            }
        }
        m = m+1;
    }
    
    //removing any words after column 60
    int l = 69;
    while(l > 59){
        if(arr2[l]!= ' '){
            int n = l;
            while (arr2[n] != ' '){
                arr2[n] = ' ';
                n = n-1;
            }
        }
        l = l-1; 
    }
    // finding spaces at front
    int n = 0;
    int start_space = 0;
    while (arr2[n] == ' '){
        start_space += 1;
        n = n+1;
    }

    int end_spaces = 0;
    int z = 69;
    while(arr2[z] == ' '){
        end_spaces += 1;
        z = z-1;
    }


    // concatinating to new string without spaces and printing with required format
    size_t length = strlen(arr2);
    int line_length = length- end_spaces;
    char* final_arr = calloc((line_length - start_space)+1,sizeof(char));
    
    for(size_t i = start_space; i<line_length; i++){
        strncat(final_arr,&arr2[i],1);
    }
    
    printf("%*s", line_length,final_arr);
    free(final_arr); //freeing final_arr
    free(arr2); //freeing arr2
    free(arr1); // freeing arr1

    

}

int main(int argc, char *argv[])
{
    char **array = calloc(1000,sizeof(char*));
    int num_lines = 0;

    for(int i =0; i<1000;i++){
        array[i] = calloc(150,sizeof(char));

    }
    get_input(array,&num_lines);//storing stdin in an array

    //version check
    if (strcmp(array[0],"1")==0)
    {
        printf("Input is version 1, concord3 expected version 2\n");
        exit(0);

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

    //getting all exclusion words as a linked list
    node_t *temp_node = NULL;
    node_t *head_excl = NULL;
        end_index += 1;
            for (int i = start_index; i < end_index; i++) {
            temp_node = new_node(array[i]);
            head_excl = add_end(head_excl, temp_node);
            }
        

    
    //getting all indexing lines as a linked list
    node_t *temp_node_1 = NULL;
    node_t *head_index = NULL;
        for (int i = end_index+1; i < num_lines; i++) {
        temp_node_1 = new_node(array[i]);
        head_index = add_end(head_index, temp_node_1);
        }

    //freeing each element of array
    for (int i = 0; i < 1000; i++)
    {
        free(array[i]);
    }
    
    //freeing array
    free(array);

    char* smallestWord = emalloc(sizeof(char)*40);
    smallest_word(smallestWord,head_excl,head_index); //getting the smallestWord
    node_t *word_n = new_node(smallestWord);
    char* final_sentence = emalloc(sizeof(char)*101);

    //looping till smallestWord is not " "
    while(strcmp(smallestWord," ")!=0){
        node_t *curr;
        // looping through each line
        for (curr = head_index; curr!=NULL; curr = curr->next)
        {   
            char* sentence = emalloc(sizeof(char)*101);
            strcpy(sentence,curr->text);
            sentence[strcspn(sentence, "\r\n")] = 0;
            strcpy(final_sentence,curr->text);
            final_sentence[strcspn(final_sentence, "\r\n")] = 0;
            char *token = strtok(sentence," ");
            int index = 0;
            // finding if smallestWord is in the line
            while (token!=NULL)
             {       
                 if(strcmp(token,smallestWord) == 0){ 
                   capitalize(final_sentence,smallestWord); //capitalize
                   final(final_sentence,index); // indexing
                   printf("\n");
                   break;
                }
                else
                {
                    index += 1;
                }
                token = strtok(NULL, " ");
            }  
            free(sentence);
        }
        //updating exclusion words, smallestWord and smallestWord node
        head_excl = add_end(head_excl,word_n);
        smallest_word(smallestWord,head_excl,head_index);
        word_n = new_node(smallestWord);
    }

    //freeing up all the char arrays and linked lists used
    free(final_sentence);
    free(smallestWord);
    free(word_n);

    temp_node = head_excl;
    while(temp_node != NULL){
        assert(temp_node != NULL);
        head_excl = remove_front(head_excl);
        free(temp_node);
        temp_node = head_excl;
    }
    assert(head_excl == NULL);

    temp_node_1 = head_index;
    while(temp_node_1 != NULL){
        assert(temp_node_1 != NULL);
        head_index = remove_front(head_index);
        free(temp_node_1);
        temp_node_1 = head_index;
    }
    assert(head_index == NULL);

}
