from Record import Record

class doubleHashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table : "))
        
        self.table = list(None for i in range(self.size))
        self.elementCount = 0
        self.comparisons = 0
   
   
    def isFull(self):
        if self.elementCount == self.size:
            return True
        else:
            return False
      
    def h1(self, element):
        return element % self.size
       
    def h2(self, element):
        return 5-(element % 5)
           
   
    def doubleHashing(self, record):
        posFound = False
        limit = self.size
        i = 1
        while i <= limit:
       
            newPosition = (self.h1(record.get_number()) + i*self.h2(record.get_number())) % self.size
          
            if self.table[newPosition] == None:
                posFound = True
                break
            else:
                # as the position is not empty increase i
                i += 1
        return posFound, newPosition
 
       
    # method that inserts element inside the hash table
    def insert(self, record):
        # checking if the table is full
        if self.isFull():
            print("Hash Table Full")
            return False
           
        posFound = False
       
        position = self.h1(record.get_number())
           
        # checking if the position is empty
        if self.table[position] == None:
            # empty position found , store the element and print the message
            self.table[position] = record
            print("Phone number of " + record.get_name() + " is at position " + str(position))
            isStored = True
            self.elementCount += 1
       
        # If collision occured 
        else:
            print("Collision has occured for " + record.get_name() + "'s phone number at position " + str(position) + " finding new Position.")
            while not posFound:
                posFound, position = self.doubleHashing(record)
                if posFound:
                    self.table[position] = record
                    #print(self.table[position])
                    self.elementCount += 1
                    #print(position)
                    #print(posFound)
                    print("Phone number of " + record.get_name() + " is at position " + str(position))
 
        return posFound
       
 
    # searches for an element in the table and returns position of element if found else returns False
    def search(self, record):
        found = False
        position = self.h1(record.get_number())
        self.comparisons += 1

        if(self.table[position] != None):
            if(self.table[position].get_name() == record.get_name()):
                print("Phone number found at position {}".format(position) + " and total comparisons are " + str(1))
                return position
           
            # if element is not found at position returned hash function
            # then we search element using double hashing
            else:
                limit = self.size
                i = 1
        
                newPosition = position
                # start a loop to find the position
                while i <= limit:
                    # calculate new position by double Hashing
                    position = (self.h1(record.get_number()) + i*self.h2(record.get_number())) % self.size
                    self.comparisons += 1
                    # if element at newPosition is equal to the required element
                   
                    if(self.table[position] != None):
                        if self.table[position].get_name() == record.get_name():
              
                            found = True
                            break
                       
                        elif self.table[position].get_name() == None:
                            found = False
                            break
                           
                        else:
                            # as the position is not empty increase i
                            i += 1
              
              
            if found:
                print("Phone number found at position {}".format(position) + " and total comparisons are " + str(i+1))
        #return position
            else:
                print("Record not Found")
                return found           
   
   
    # method to display the hash table
    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: "+str(i) + "\t\t" + str(self.table[i]))
        print("The number of phonebook records in the Table are : " + str(self.elementCount))