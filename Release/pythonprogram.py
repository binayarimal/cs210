import re
import string

#Reads the item file, and creates a dictionary of items in the file with its frequency.
#This funcction is called in all other function in this page.
def itemDictionary():   
    dictItems = {}
    f = open("items.txt", "r")  
    for x in f:
        x = x.strip()       
        if(x in dictItems):  
            dictItems[x] += 1
        else:
            dictItems[x] = 1
    f.close()
    return dictItems
 
#Prints all items in the file.
def printallItems():
    items = itemDictionary()
    for item in items:
        print(item, ": ", items[item])


 #Compares user specified items with items in dictionary and prints item and frequency if it matches.
def getSpecificItem(item):
    itemLowerCase = item.lower()
    itemAmount = 0
    items = itemDictionary()
    if (itemLowerCase.capitalize() in items ):
        itemAmount = items[itemLowerCase.capitalize() ]
    return itemAmount;

#Creates a freqency.dat file.
def createDataFile():   
    items = itemDictionary() 
    f = open("frequency.dat", "w")
    f.write("")
    f.close()

    appendFile = open("frequency.dat", "a")
    for item in items:      
        appendFile.write(item+ ": " + str(items[item]) + "\n")       
    appendFile.close()

 
    



    
