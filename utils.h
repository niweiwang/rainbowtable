#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include "sha256.h"


using namespace std;

static const int PASSWORD_SIZE = 8;
static const int LAST_REDUCE_SIZE = 8;
static const int END_OF_LINE_N_STUFF = 1;
static const int LINE_SIZE = PASSWORD_SIZE + LAST_REDUCE_SIZE + END_OF_LINE_N_STUFF;

static const int NBR_OF_REDUCTION = 3;

static const int NBR_OF_ENTRIES = 2;

static const string FILE_NAME = "rainbowTable.txt";

using namespace std;

string reduce(int i, string hash);
string hashStr(string toHash);
