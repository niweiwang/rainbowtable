#include "utils.h"

string searchInTable(string pwdToFind, ifstream *table);
string binarySearchRecursiveStyle(string pwdToFind, ifstream *table, streamsize low, streamsize high);
void findPassword(string password, string hashToBreak, int counter);

int main(void)
{
    string hashToBreak;
    cout << "Hash to crack :" << endl;
    cin >> hashToBreak;
    if (hashToBreak.length() != HASH_LENGTH)
    {
        cout << "Your hash must be of " << HASH_LENGTH <<" characters ! " << endl
             << "Did you correctly wrote the hash in hexadecimal ?" << endl;
        exit(-1);
    }

    const clock_t begin_time = clock();
    string result;
    int i, j;
    string tmpHash, tmpPassword;

    ifstream table(FILE_NAME);
    if (!table.is_open())
    {
        cout << "A problem was encountered when oppening the file "<<FILE_NAME;
        exit(-1);
    }

    /*** 
    *We look for the entry that describe the chain the password is stored in
    *Call findPassword once found.
    **/
    for (i = NBR_OF_REDUCTION - 1; i >= 0; i--)
    {
        tmpHash = hashToBreak;
        for (j = i; j < NBR_OF_REDUCTION; j++)
        {
            tmpPassword = reduce(j, tmpHash);
            tmpHash = hashStr(tmpPassword);
        }

        result = searchInTable(tmpPassword, &table);
        if (result.compare("        ") != 0)
        {
            findPassword(result, hashToBreak,i);
            break;
        }
    }
    if (result.compare("        ") == 0){
        cout << "Password not found" << endl;
    }
    cout << "The research took " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." << endl;
    table.close();
    return 0;
}


void findPassword(string password, string hashToBreak, int counter)
{
    int i;
    string hash, lastPassword;
    for (i = 0; i < counter+1; i++)
    {
        hash = hashStr(password);
        lastPassword = password;
        password = reduce(i, hash);
    }
    if (hashToBreak.compare(hash) == 0)
    {
        cout << "-----------------------------------------------------------" << endl;
        cout << "The corresponding password of hash " << hashToBreak << " is " << lastPassword << endl;
    }else{
        cout << "-----------------------------------------------------------" << endl;
        cout << "The password could not be found, it means there is a collision." << endl;
        exit(-1);
    }
}

/**
*Search a password in the file using binarysearch
**/
string searchInTable(string pwdToFind, ifstream *table)
{
    streamsize low = 0, high = 0;
    table->seekg(0, ios::end);
    streamsize tableSize = table->tellg();
    if (tableSize == -1)
    {
        cout << "An error was encountered using tellg" << endl;
        exit(-1);
    }
    high = tableSize / LINE_SIZE;
    string result = binarySearchRecursiveStyle(pwdToFind, table, low, high - 1);
    if (result.compare("        ") == 0)
    {
        return result;
    }
    else
    {
        return result;
    }
}

string binarySearchRecursiveStyle(string pwdToFind, ifstream *table, streamsize low, streamsize high)
{
    if ((high >= low) && (high <= NBR_OF_ENTRIES) && (low <= NBR_OF_ENTRIES))
    {
        string line, temppwd;
        int cmp;
        streamsize middle = low + (high - low) / 2;
        table->seekg(middle * LINE_SIZE, ios::beg);
        getline(*table, line);

        cmp = pwdToFind.compare(line.substr(PASSWORD_SIZE, LAST_REDUCE_SIZE)); 

        if (cmp == 0)
        {
            return line.substr(0, PASSWORD_SIZE);
        }
        else if (cmp > 0)
        {
            return binarySearchRecursiveStyle(pwdToFind, table, middle + 1, high);
        }
        else if (cmp < 0)
        {
            return binarySearchRecursiveStyle(pwdToFind, table, low, middle - 1);
        }
    }

    return "        ";
}
