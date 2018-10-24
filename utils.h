#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <functional>
#include <math.h>
#include "sha256.h"

using namespace std;

static const int PASSWORD_SIZE = 8;
static const int LAST_REDUCE_SIZE = 8;
static const int END_OF_LINE_N_STUFF = 1;
static const int LINE_SIZE = PASSWORD_SIZE + LAST_REDUCE_SIZE + END_OF_LINE_N_STUFF;
static const int NBR_OF_REDUCTION = 50000; //50000
static const int NBR_OF_ENTRIES = 1000;
static const string FILE_NAME = "rainbowTable.txt";
static const string alphanum = "0123456789abcdefghijklmnopqrstuvwxyz";
static const int HASH_LENGTH = 64;
static const int ALPHANUM_SIZE = 36;

string reduce(int i, string hash);
string hashStr(string toHash);
