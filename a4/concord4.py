import sys
import re

class concord:

    # constructor
    def __init__(self, input=None, output=None):
        self.input = input
        self.output = output
        self.__output_file()

    # output to file
    def __output_file(self):
        if self.output != None:
            file2 = open(self.output, 'w')
            lines = self.full_concordance()
            for line in lines:
                file2.write("%s\n"%line)

    # taking input from stdin or file
    def __input_lines(self):
        list_lines = []
        lines = []
        if self.input == None:
            for line in sys.stdin:
                lines = line.splitlines()
                list_lines += lines
        else:
            file1 = open(self.input, 'r')
            list_lines = file1.readlines()
            list_lines = [element.strip() for element in list_lines]
            file1.close()
        return list_lines

    # getting start and end index of exclusion words
    def __get_exclusion_start_end(self):
        i = 0
        self.exclusion_start = 0
        self.exclusion_end = 0
        for x in self.inputs:
            if x == "\'\'\'\'":
                self.exclusion_start = i+1
                i+=1
            if x == '\"\"\"\"':
                self.exclusion_end = i-1
                i+=1
            else:
                i+=1
    
    # getting list of exclusion words
    def __get_exclusion_list(self):
        self.exclusion_list = []
        j = self.exclusion_start
        while j < self.exclusion_end:
            self.exclusion_list.append(self.inputs[j])
            j+=1

    #  getting list of indexing words
    def __get_indexing_list(self):
        self.indexing_list = []
        indexing_start = self.exclusion_end+1
        k = indexing_start
        while k < len(self.inputs):
            self.indexing_list.append(self.inputs[k])
            k += 1

    # checking for version
    def __version_check(self):
        if self.inputs[0] == "1":
            s =  "Input is version 1, concord4.py expected version 2"
            return print(s)

    # making indexing list to a string
    def __make_string(self):
        self.indexing_string = ""
        for line in self.indexing_list:
            self.indexing_string += line + " "
        self.indexing_string.strip()

    # removing exclusion words from the string of all the indexing lines
    def __remove_exclusions(self):
        self.new_string = self.indexing_string
        for self.word in self.exclusion_list:
            self.new_string1 = ""
            self.new_string1 = re.sub(rf"\b{self.word}\b", '', self.new_string, flags=re.IGNORECASE)
            self.new_string = self.new_string1

    # adding all the indexing words excluding exclusions to a list and sorting it
    def __add_words_to_list(self):
        self.indexing_list_without_exclusions = self.new_string.split(" ")
        self.indexing_list_without_exclusions = self.indexing_list_without_exclusions[:-1]
        self.sorted_list = sorted(self.indexing_list_without_exclusions, key=str.casefold)

    # get the sorted list of the of indexing words
    def __smallest_word(self):
        self.__make_string()
        self.__remove_exclusions()
        self.__add_words_to_list()
    
    # making correct spaces in the front
    def __correct_spaces_start(self):
        if len(self.first_half) > 20:
            self.first_half = self.first_half[len(self.first_half)-21:len(self.first_half)]
            if self.first_half[0] != ' ':
                self.first_half = self.first_half.split(' ',1)[1]

    # making correct spaces in the end
    def __correct_spaces_end(self):
        if len(self.second_half) > 31:
            self.second_half = self.second_half[0:32]
            if self.second_half[len(self.second_half)-1] != ' ':
                self.second_half = self.second_half.rsplit(' ',1)[0]
    
    # indexing the line accordingly by having the capitalised word at column 30
    def __final_indexing(self):
        res = re.search(rf"\b{self.required_word.upper()}\b",self.line1)
        upper = res.start()

        self.first_half = self.line1[0:upper]
        self.second_half = self.line1[upper:len(self.line1)]
        
        self.first_half_length = 30
        self.second_half_length = 40
            
        self.__correct_spaces_start()
        self.__correct_spaces_end()

        starting_spaces = self.first_half_length - len(self.first_half) - 1 
        ending_spaces = self.second_half_length - len(self.second_half)

        self.indexed_string = (" "*starting_spaces) + self.first_half + self.second_half + (" "*ending_spaces)


        return self.indexed_string.rstrip()


    def full_concordance(self):
        self.inputs = self.__input_lines()
        self.__get_exclusion_start_end()
        self.__version_check
        self.__get_exclusion_list()
        self.__get_indexing_list()
        self.__smallest_word()

        self.required_word = self.sorted_list.pop(0) #getting the first element of the sorted array of indexing words
        self.final = []

        while len(self.sorted_list) >= 0:
            for line in self.indexing_list:
                line_split = line.split(" ")
                if (self.required_word != "") and (self.required_word in line_split):
                    self.line1 = re.sub(rf"\b{self.required_word}\b",self.required_word.upper(),line) #capitalizing the word
                    self.line1 = self.__final_indexing()
                    # to avoid repetetions
                    if(self.line1 not in self.final):
                        self.final.append(self.line1) #appending the final line to a list
            
            if(len(self.sorted_list)!=0):
                self.required_word = self.sorted_list.pop(0)
            else:
                break
            
        return self.final #returning the final list


        