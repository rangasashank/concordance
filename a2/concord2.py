#!/usr/bin/env python3
import sys

# get the smallest word
def smallest_word(exclusion_list, indexing_list):

    smallest_word = "zzz"
    word = ""
    for i in indexing_list:
        word_list = i.split(" ")
        k = 0
        while k < len(word_list):
            if len(exclusion_list)== 0:
                word = word_list[k]
            else:
                for j in exclusion_list:
                    if j != word_list[k].lower():
                        word = word_list[k]
                    else:
                        word = ""
                        break
            if word!="" and ((word.lower())<(smallest_word.lower())) and (word not in exclusion_list):
                smallest_word = word
            k+=1

    if smallest_word == "zzz":
        smallest_word = ""
        return smallest_word
    else:
        return smallest_word

# return the sentence after capitalising the required word
def capitalize(sentence, smallest_word):
    new_sentence =""
    list_sentence = sentence.split(" ")
    for i in list_sentence:
        if i == smallest_word:
            new_sentence += (i.upper() + " ")
        else:
            new_sentence += (i + " ")
    return new_sentence.strip()

# return the line after appropriate formatting
def final(sentence,num_spaces):
    arr1 = []
    arr2 = []
    count = 0
    length_of_words = 0
    
    # adding each letter to arr1 and counting the legth of each word before smallest word to add with number of spaces later
    for c in sentence:
        if c == " " and count < num_spaces:
            count += 1
            arr1.append(c)
        elif c != " " and count < num_spaces:
            length_of_words +=1 
            arr1.append(c)
        else:
            arr1.append(c)
        
        

    for i in range(70):
        arr2.append(" ")

    a = 29 # 30th column
    upper = length_of_words+num_spaces # index of first letter of smallest word

    k = upper

    # adding letters to the left of index 29(column 30)
    while k>0 and a>0:
        arr2[a-1] = arr1[k-1]
        k = k-1
        a = a-1
    
    a = 29
    k = upper

    # adding letters to the right of index 29(column 30)
    while k<len(arr1) and a<len(arr2):
        arr2[a] = arr1[k]
        a = a+1
        k = k+1



    # removing any words before column 10
    m = 0
    while m<9:
        if arr2[m] != " ":
            n = m
            while arr2[n] != " ":
                arr2[n] = " "
                n = n+1
        m = m+1
    
    # removing any words after column 60
    m = 69
    while m > 59:
        if arr2[m]!= " ":
            n = m
            while arr2[n] != " ":
                arr2[n] = " "
                n = n-1
        m = m-1
 
    # getting the number of spaces at beginning and end
    n = 0
    start_space = 0
    end_space = 0
    while arr2[n] == " ":
        start_space += 1
        n = n+1
    
    m = 69
    while arr2[m] == " ":
        end_space += 1
        m = m-1
        
    
    # adding the required letter to a sentence 
    final_sentence = ""
    z = start_space
    arr2_no_end = len(arr2) - end_space
    while z < (arr2_no_end):
        final_sentence += arr2[z]
        z = z+1
    
    # formatting the sentence with requires space at front
    final_sentence_1 = "{:>{}}".format(final_sentence,arr2_no_end)

    
    return final_sentence_1



def main():
    
    list_lines =[]
    exclusion_start = 0
    exclusion_end = 0
    for line in sys.stdin:
        lines = line.splitlines()
        list_lines += lines

    i = 0
    for x in list_lines:
        if x == "\'\'\'\'":
            exclusion_start = i+1
            i+=1
        if x == '\"\"\"\"':
            exclusion_end = i-1
            i+=1
        else:
            i+=1
    # checking for version
    for x in list_lines:
        if x == "1":
            s =  "Input is version 1, concord2.py expected version 2"
            return print(s)
            
        elif x =="2":
            break

    exclusion_list = []
    j = exclusion_start
    while j < exclusion_end:
        exclusion_list.append(list_lines[j])
        j+=1

    indexing_list = []
    indexing_start = exclusion_end+1
    k = indexing_start
    while k < len(list_lines):
        indexing_list.append(list_lines[k])
        k += 1
    

    smallestword = smallest_word(exclusion_list, indexing_list) # getting the smallest word
    while(smallestword!=""):
        for l in indexing_list:
            sentence_list = l.split(" ")
            if smallestword in sentence_list:
                index_small = sentence_list.index(smallestword)
                sentence = capitalize(l,smallestword)
                sentence = final(sentence,index_small)
                print(sentence)
            
                
                


        exclusion_list.append(smallestword)
        smallestword = smallest_word(exclusion_list,indexing_list)



        





if __name__ == "__main__":
    main()
