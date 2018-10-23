# rainbowtable
Rainbow Table Attack Assignment

# System configuration:
Debian 9.2, g++ (8.2.1), sha256.h, sha256.cpp


# Project configuration:

0. password definition: fixed 8 digits alphanumeric fron the character set: "0123456789abcdefghijklmnopqrstuvwxyz"
1. utils.h: change NBR_OF_REDUCTION, NBR_OF_PASSWORD before executing.
2. ./ Make all
3. ./tableMaker to generate the rainbowTable.txt (average speed 300 line per minute)
4. ./ passwordCracker to enter a known sha256 hash in order to get a possible alphanumeric password

# TO-DO:

0. Add threading to increase the table creation performance
1. Update 'System Configuration' list




