#include <iostream>
#include "utils.h"
#include "sha256.h"
#include <sstream>
#include <string>
#include <functional>
#include <math.h>
/*
string reduce(int i, string hash)
{

    stringstream ss;
    ss << hash;
    int x;
    ss >> hex >> x;
    cout << "i : " << i << endl;
    cout << "x : " << x << endl;
    cout << "x + i % (36 ^ 8) : " << (x + i) % static_cast<int>(pow(36, 8)) << endl;

    cout << "hash : " << hash << endl;
    /*
    unsigned long long x = std::stoull("b5eec042bffb6e37", nullptr, 16);
    cout << "x : " << x << endl;
    
    int j;
    static const char alphanum[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (ALPHANUM_SIZE - 1);
    string reply;
    hash<std::string> hasher;

    unsigned int x = hasher(hash);
    x = x + i % static_cast<int>(pow(36, PASSWORD_LENGTH));
    for (j = 0; j < PASSWORD_LENGTH; j++)
    {

        reply += alphanum[(x % 100) % max_index];
        x /= 10;
    }
    return reply;

    //cout << pow(3, 2) << endl;
    return hash.substr(0, 8);
}
*/
string reduce(int counter, string hashinput)
{
    string hexpwd = "", alfpwd = "";

    int start_pos = counter % 64; //the counter modulo the length of sha256 digest length (64)
    string pwd;
    const string alphanum = "0123456789abcdefghijklmnopqrstuvwxyz";
    const int ALPHANUM_SIZE = 36;

    if (start_pos > 48)
    { //push the start position to 16 position to the left to avoid overflow
        string spart1 = hashinput.substr(start_pos, 64 - start_pos);
        string spart2 = hashinput.substr(0, (16 - 64 + start_pos));
        hexpwd = (spart1 + spart2);
    }
    else
    {
        hexpwd = (hashinput.substr(start_pos, 16));
    };

    alfpwd = ""; //reset the alphanumeric password
    const int HEXPWD_SIZE = 16;

    for (int j = 1; j < (HEXPWD_SIZE / 2 + 1); j++)
    {
        string stemp = hexpwd.substr((j - 1) * 2, 2); // two hex value at a time
        std::istringstream converter(stemp);
        unsigned int value;
        converter >> std::hex >> value;  // convert double digits hex to unassigned int
        int k = (value % ALPHANUM_SIZE); // get an index k in string alphanum
        alfpwd = alfpwd + alphanum[k];
        //cout <<hexpwd<<endl;
    };

    return alfpwd; //return alphanumeric pwd;
}

string hashStr(string toHash)
{
    return sha256(toHash);
}