# rainbowtable
Rainbow Table Attack Assignment

# System configuration:  
Debian 9.2, g++ (8.2.1), sha256.h, sha256.cpp


# Project configuration:  
0. password definition: fixed 8 digits alphanumeric fron the character set: "0123456789abcdefghijklmnopqrstuvwxyz"
1. utils.h contains every parameter of the program, you can for instance change the NBR_OF_REDUCTION and the NBR_OF_ENTRIES before executing the makefile.
2. 'make all' to compile with the Makefile.
3. "./tableMaker" to generate the rainbowTable.txt
4. "./passwordCracker" to enter a known sha256 hash in order to get a possible alphanumeric password

# Project members: 
Patience Mbatchou Sandjon  
Cadnel Zomahoun  
Yiwei Wang  
Jolan Whatelet  
Benjamin Bergé   

# Added features:  
0. the table is sorted in tableMaker and is searched by a binary search in passwordCracker in order to gain time
1. the table creation use thread to be faster  

Note: the thread library used to create the table is not compatible with MacOS




