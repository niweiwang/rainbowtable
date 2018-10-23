#include <iostream>
#include <string.h>

static const int PASSWORD_SIZE = 8;
static const int LAST_REDUCE_SIZE = 8;
static const int END_OF_LINE_N_STUFF = 1;
static const int LINE_SIZE = PASSWORD_SIZE + LAST_REDUCE_SIZE + END_OF_LINE_N_STUFF;

static const int NBR_OF_REDUCTION = 50000;

static const int NBR_OF_PASSWORD = 50000;

using namespace std;

string reduce(int i, string hash);
string hashStr(string toHash);
