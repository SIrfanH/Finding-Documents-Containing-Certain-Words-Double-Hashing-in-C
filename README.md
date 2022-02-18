# Finding-Documents-Containing-Certain-Words-Double-Hashing-in-C
A program that finds and lists the documents that contain user given words. First the program reads the given document then creates a dictionary of words that were in the document and when the creation of the dictionary is done it asks the user for words to look for in the dictionary. It is also possible to add multiple documents to the dictionary. The conversion of words to a hash is done by using Horner Method. The dictionary keeps track of the documents and words. When the word is found in the dictionary the documents that contained the word is listed.
## Program Features
The program has four main features:
### Adding a new document to the dictionary
When a new document is given by the user, every word inside the document is passed through Horner hashing algorithm and a hash value is created for the word. Then if the word was already in the dictionary only the document name is added to the hash index of the dictionary. if it wasn't in the dictionary both word and the document is added.<br/>
### Searching for the given word
When the word to search is given by the user, it is passed through the same Horner hashing function and the hashed index is searched for the word. If the word is found then documents containing the word is fetched from the dictionary and printed on screen. If it is not found then a message is written on screen. The number of steps taken to search the word is also calculated.<br/>
### Creating the Hash Table
The hash table is created using the following rules:
- Open Addressing for the table and Double Hashing for solving the collision problem is used. The double hashing formula:
```
h(key, i) = [ h1(key) + i * h2(key) ] mod M
h1(key) = key mod M
h2(key) = 1 + ( key mod MM )
```
- The program does not differentiate between lowercase and uppercase letter and Horner Method is userd for converting the words to number.<br/>
-  The size of the hash table represented by M is selected as the nearest prime number to 1000. MM is M-1.
### Storing the Table in a File
The program stores the hashtable in a file in order not repeatedly create the table for the documents. It also calculate the loadfactor value for the table which represents the usage percentage of the table and stores it in the same file as the dictionary.
