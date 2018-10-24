#include "utils.h"

string reduce(int counter, string hashinput)
{
    string hexpwd = "", alfpwd = "", pwd;
    int start_pos = counter % HASH_LENGTH; //the counter modulo the length of sha256 digest length (64)
    

    if (start_pos > 48)
    { //push the start position to 16 position to the left to avoid overflow
        string spart1 = hashinput.substr(start_pos, HASH_LENGTH - start_pos);
        string spart2 = hashinput.substr(0, (16 - HASH_LENGTH + start_pos));
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