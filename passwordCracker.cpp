#include "utils.h"

string searchInTable(string pwdToFind, ifstream *table);
string binarySearchRecursiveStyle(string pwdToFind, ifstream *table, streamsize low, streamsize high);
void findPassword(string password, string hashToBreak, int counter);

int main(void)
{
    string hashToBreak;
    cout << "hash à cracker :" << endl;
    cin >> hashToBreak;
    if (hashToBreak.length() != HASH_LENGTH)
    {
        cout << "votre hash dois faire " << HASH_LENGTH <<" carractères ! " << endl
             << "avez vous bien écrit le hash en hexadecimal ?" << endl;
        exit(-1);
    }

    const clock_t begin_time = clock();
    string result;
    int i, j;
    string tmpHash, tmpPassword;

    ifstream table(FILE_NAME);
    if (!table.is_open())
    {
        cout << "problem when oppening the file";
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
        }
    }
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
    table.close();
}


void findPassword(string password, string hashToBreak, int counter)
{
    int i;
    string hash;
    for (i = 0; i < counter; i++)
    {
        hash = hashStr(password);
        if (hashToBreak.compare(hash) == 0)
        {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Le mot de passe du hash " << hashToBreak << " est " << password << endl;
            exit(0);
        }
        password = reduce(i, hash);
    }
    cout << "-----------------------------------------------------------" << endl;
    cout << "Le mot de passe n'a pas été trouvé, il y a une collision." << endl;
    exit(-1);
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
        cout << "une erreur est survenue dans tellg" << endl;
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
        cout << "Le password est : " << result << endl;
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
