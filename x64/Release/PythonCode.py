"""
PythonCode.py

    Author: James Furman
    Date: 2022-12-11

Various functions for use with the Corner Grocer purchase tracking and analysis app. 
See GrocerMenuFuncs.cpp for documentation of practical functionality.
"""

import re
import string

"""
Opens a file that must have the name of one item on each line. Counts the number of times each 
item occurs and prints to console a list displaying each item and the number of times it occurs. 

Returns 0 - useless in this implementation but could serve as an exit code.
"""
def CountItems(filenameStr):
    f = open(filenameStr, 'r')
    purchasedList = f.readlines()
    f.close()

    itemsList = []

    for i in range(len(purchasedList)):
        purchasedList[i] = purchasedList[i].strip()

    for item in purchasedList:
        if item not in itemsList:
            itemsList.append(item)

    totalWidth = 30
    for item in itemsList:
        numStr = str(purchasedList.count(item))
        spaceWidth = totalWidth - (len(item) + len(numStr))
        print(item + " " + ("." * spaceWidth) + numStr)

    return 0

"""
Reads items from a file (as CountItems), counts the number of times each occurs, prints
a histogram displaying an asterisk for each occurence, and writes (or overwrites) a file
to contain precisely the same histogram.

Returns 0 - useless in this implementation but could serve as an exit code.

E.g.:
Item1 .....| ***
F .........| *******
ThisItem ..| *****
ItemLength | **
ItemsLength| ***
"""
def ChartItems(readFileStr, writeFileStr):
    f = open(readFileStr, 'r')
    purchasedList = f.readlines()
    f.close()

    itemsList = []

    for i in range(len(purchasedList)):
        purchasedList[i] = purchasedList[i].strip()

    for item in purchasedList:
        if item not in itemsList:
            itemsList.append(item)

    itemLength = len(max(itemsList, key = len))

    f = open(writeFileStr, 'w')
    for item in itemsList:
        spaceWidth = itemLength - len(item)
        itemCt = purchasedList.count(item)
        
        if spaceWidth > 1:
            print(item + ("." * spaceWidth) + "| " + ("*" * itemCt))
            f.write(item + ("." * spaceWidth) + "| " + ("*" * itemCt) + "\n")
        else:
            print(item + (" " * spaceWidth) + "| " + ("*" * itemCt))
            f.write(item + (" " * spaceWidth) + "| " + ("*" * itemCt) + "\n")
        
    f.close()

    return 0


"""
Takes the name of a file to read (as other functions) and a string of an item to search for. Counts 
the number of times the item named in the string occurs in the list of items and returns that
number as an int.
"""
def CountOneItem(filenameStr, itemSearch):
    f = open(filenameStr, 'r')
    purchasedList = f.readlines()
    f.close()

    itemSearch = itemSearch.strip()

    for i in range (len(purchasedList)):
        purchasedList[i] = purchasedList[i].strip()
    
    totalWidth = 30
    searchNum = purchasedList.count(itemSearch)

    return searchNum

"""
Reads items from a file (as other functions) and returns a list of strings representing each item
precisely once, no matter how many times the item occurs in the file. 
"""
def GetItems(filenameStr):
    f = open(filenameStr, 'r')
    purchasedList = f.readlines()
    f.close()

    itemsList = []

    for i in range(len(purchasedList)):
        purchasedList[i] = purchasedList[i].strip()

    for item in purchasedList:
        if item not in itemsList:
            itemsList.append(item)
    
    return itemsList
