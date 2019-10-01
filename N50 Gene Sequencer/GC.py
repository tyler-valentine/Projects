#answer = ["AAAATCTCCAGTGCCCAAGACCACGGGCGCTCGGCGCCTTGGCTAATCCCCGTACATGTTGTTATAAATAATCAGTAGAAA"]

# in order to run with input file:
# comment out initial declaration of sequences below and uncomment sequences and sequences = FASTQparse below
# File = 'xxx' in FASTQparse() is the input parse file
# parse file must be in gene sequencing format (typically .fq)

#----------GLOBAL VARIABLES----------#
sequences = ["GTTATAAATAATCAGTAGAAA", "AAAATCTCCAGTGCCCAAGA", "AATCCCCGTACATGTTGTTA", "TGCCCAAGACCACGGGCGCT", "GCGCCTTGGCTAATCCCCGT", "CACGGGCGCTCGGCGCCTTG"]
#sequences = []
sequences2 = []
scraps = []
match = False
combined = True
ident = 0

"""
Parser for genome sequencer.
File set as included rand.500.1.fq
"""
def FASTQparse():
    File = open('rand.500.1.fq','r')
    gInput = []
    splitter = ['@','I','\n',"random_",'_',':','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','/']
    rawTxt = File.read()
    count = 0
    for i in range(len(splitter)):
        rawTxt = rawTxt.replace(splitter[i],"")

    gInput = rawTxt.split('+')

    del(gInput[10000])
    
    for k in range(len(gInput)):
        if(len(gInput[k]) == 0 ):
            count+= 1

    return gInput


#sequences = FASTQparse()



# Function to perform the actual combinations of 'matching' strings
def combine(seq1,seq2,ident,y,z):
    combined = False # variable to determine if a combination has actually been made
    
    # Nested for loop to increment through all possible combinations of the characters of the two sequences
    for i in range (len(seq1)):
        for j in range (len(seq2)):
            
            # If two characters match then we start checking for a series of matches
            if (seq1[i] == seq2[j]):
                
                # Checks to see if the match is at the beginning of one of the sequences.
                # If it's not at the beginning of one of the sequences then there is no point trying to merge the two sequences
                if((i == 0) or (j == 0)):  
                    n = 0 # counter that keeps track of how many character matches in a row there have been
                    
                    # loop that iterates as long as characters in both strings at same relative position match
                    for k in range (j,len(seq2)): 
                        if (i+n > len(seq1)-1):
                            break # need a break statement in case i goes outside of the bounds of seq1
                        
                        # if there is a match in the next position
                        if (seq1[i+n] == seq2[j+n]):
                            match = True
                            n += 1
                        
                        # if there isn't a match than stop iterating through the two sequences
                        else:
                            match = False
                            break
                        
                        # Checks to make sure that the segment that was matched was the end of one of the sequences.
                        # We already know from the if statement above that one of the sequences was at its beginning when the match started
                        # so now we know that we have a match at the beginning of one sequence and the end of another.
                        # Additionally checks to make sure that the match was long enough to avoid false positives 
                        if (((i+n == len(seq1)) or (j+n == len(seq2))) and (n > 3)):
                            combined = True # keeps track of if a combination was made
                            
                            # if we are dealing with sequence list
                            if (ident == 0):

                                # if j == 0 then all of seq1 needs to be used for the combo. if i == 0 all of seq2 needs to be used
                                # The new combined sequence goes into the empty sequence2 list
                                # Once a sequence has been used in a combination it is deleted. The new combined sequence will have all of
                                # its characters and it is no longer needed 
                                if (j == 0):
                                    sequences2.append(seq1+str(seq2[n:]))
                                    sequences[y] = ""
                                    sequences[z] = ""
                                if (i == 0):
                                    sequences2.append(seq2+str(seq1[n:]))
                                    sequences[z] = ""
                                    sequences[y] = ""
                            
                            # Same as above but dealing with sequences2 to sequences.
                            elif (ident == 1):
                                if (j == 0):
                                    sequences.append(seq1+str(seq2[n:]))
                                    sequences2[y] = ""
                                    sequences2[z] = ""
                                if (i == 0):
                                    sequences.append(seq2+str(seq1[n:]))
                                    sequences2[z] = ""
                                    sequences2[y] = ""
    
    return combined # return value indicating if a combination was performed



# Function responsible for calling the combine function while there are still sequences eligible to be combined
def sequencing(sequences, sequences2, ident):
    combined = False # variable to keep track of if a combination was performed

    # While loop that will keep trying to combine sequences until there is one large sequence or all
    # sequences have been moved to the scrap list
    while (((len(sequences) != 1) and (len(sequences2) != 1)) and ((len(sequences)) + (len(sequences2)) != 0)):
        
        # if we are dealing with the sequences list
        if (ident == 0):
            
            # nested for loop that will compare all elements in the sequences list with each other
            for i in range (0,len(sequences)-1):
                for j in range(i+1,len(sequences)):

                    # if a combination is sucessfully performed than we update our combined variable
                    if(combine(sequences[i],sequences[j],0,i,j)):
                        combined = True
            
            # Every element in our list that was not combined with anything will get added to a scrap array and later reintroduced
            # to the final array of segments. This allows pieces of the genome that were never combined to still be used in the
            # N50 statistical evaluation
            for x in sequences:
                if (x != ""):
                    scraps.append(x) 
            
            # Once all of the elements in the list have been dealt with the list is deleted and the identifying value is set
            # to the other list (0 for sequences and 1 for sequences2). Now this list can act as the holder for the other list
            del sequences[:]
            ident = 1
        
        # Identical process as above but using sequences2 as the active list and sequences as the holding list
        elif (ident == 1):
            for i in range (0,len(sequences2)-1):
                for j in range(i+1,len(sequences2)):
                    if(combine(sequences2[i],sequences2[j],1,i,j)):
                        combined = True
            for x in sequences2:
                if (x != ""):
                    scraps.append(x)
            del sequences2[:]
            ident = 0

    # if the length of sequences is not 0 it was our holding list and is next up to become active
    if (len(sequences) != 0):
        
        # move all elements from scraps into sequences, our next active list
        for x in scraps:
            sequences.append(x)
        del scraps[:]

    # if the length of sequences2 is not 0 it was our holding list and is next up to become active
    elif (len(sequences2) != 0):

        # move all elements from scraps into sequences2, our next active list
        for x in scraps:
            sequences2.append(x)
        del scraps[:]

    # if both sequences and sequences2 have been emptied, all of our segments are in scraps. We move them to
    # sequences in preperation for the final N50 statistical evaluation.
    elif (len(scraps) != 0):
        for x in scraps:
            sequences.append(x)
        del scraps[:]
    
    return combined # indicates if a combine was performed



# Function that determines the length of the last segment that is added before crossing the
# N50 threshold. Returns length of segment.
def N50(sequences):
    totLen = 0 # total length of sequence
    halfLen = 0 # half the length of sequence
    runTot = 0 # running total to compare to halfLen

    # Loop to get the length of all the sequences in sequences
    for i in range (len(sequences)):
        totLen = totLen + len(sequences[i])

    halfLen = totLen/2
    
    # Loop to find the point/sequence where we have reached half the length of all of the sequences
    for i in range (len(sequences)):
        runTot = runTot + len(sequences[i])
        
        # If we have reached that point/sequence, return the length of said sequence
        if (runTot > halfLen):
            return len(sequences[i])



#----------MAIN FUNCTION-----------#

# If there are elements in the sequences list it is our active list
if (len(sequences) != 0):
    combined = True
    
    # While calling sequencing is resulting in combinations the loop will continue 
    while (combined == True):
        combined = sequencing(sequences, sequences2, 0)

# --SUSPECTED TO BE USELESS--
# sequencing2 is the active list       
#elif (len(sequences2) != 0):
    #combined = True
    #while (combined == True):
        #combined = sequencing(sequences, sequences2, 1)

# Housekeeping...
# If, after all combinations have been performed, the genome segments are in the segments2 list they are moved to the segments list 
if (len(sequences2) != 0):
    for x in sequences2:
        sequences.append(x)
    del sequences2[:]

# Sort the finalized sequences list from shortest to longest
sequences.sort(key=len, reverse=False)

# Print the finalized list for testing
print(sequences)

# Print other lists to ensure empty for testing
print(sequences2, scraps)


print(N50(sequences))
