#include "utils.h"

string searchInTable(string pwdToFind, ifstream *table);
string binarySearchRecursiveStyle(string pwdToFind, ifstream *table, streamsize low, streamsize high);
void findPassword(string password, string hashToBreak);

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

    string result;
    int i, j;
    string tmpHash, tmpPassword;

    ifstream table(FILE_NAME);
    if (!table.is_open())
    {
        cout << "problem when oppening the file";
        exit(-1);
    }

    //On cherche dans quelle "chaine" de hash/reduce le password est
    //une fois qu'on a trouver le password de début de chaine, on appelle findPassword avec.
    //for (i = NBR_OF_REDUCTION - 1; i >= 0; i--)
    for (i = NBR_OF_REDUCTION - 1; i >= 0; i--)
    {
        cout << "\n\n"
             << endl;
        tmpHash = hashToBreak;
        for (j = i; j < NBR_OF_REDUCTION; j++)
        {
            cout << j << " - " << reduce(j, tmpHash) << endl;
            tmpPassword = reduce(j, tmpHash);
            tmpHash = hashStr(tmpPassword);
        }

        result = searchInTable(tmpPassword, &table);
        if (result.compare("        ") != 0)
        {
            findPassword(result, hashToBreak);
        }
        //tmpPassword = reduce(i, tmpHash);
        //tmpHash = hashStr(tmpPassword);
    }
}

//on donne le mdp de début de chaine, et on applique hash/reduce jusqu'a ce qu'on le trouve.
//no need of redoing all of that, just hash to break to which we apply counter reductions (we know counter in the main)
void findPassword(string password, string hashToBreak)
{
    int i;
    string hash;
    for (i = 0; i < NBR_OF_REDUCTION; i++)
    {
        hash = hashStr(password);
        if (hashToBreak.compare(hash) == 0)
        {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Le mot de passe du hash " << hashToBreak << " est " << password << endl;
            exit(0);
        }
        password = reduce(i, hash);
        cout << password << " counter : " << i << " hash: " << hash << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
    cout << "Le mot de passe n'a pas été trouvé, il y a une collision." << endl;
    exit(-1);
}

//using binarysearch
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
        cout << "Ce hash : " << pwdToFind << " n'est pas dans la table =/ " << endl;
        return result;
    }
    else
    {
        cout << "Le password est : " << result << endl;
        return result;
    }
}

//obvious name is obvious
string binarySearchRecursiveStyle(string pwdToFind, ifstream *table, streamsize low, streamsize high)
{
    if ((high >= low) && (high <= NBR_OF_ENTRIES) && (low <= NBR_OF_ENTRIES))
    {
        streamsize middle = low + (high - low) / 2;
        cout << "high : " << high << endl;
        cout << "middle : " << middle << endl;
        cout << "low : " << low << endl;
        string line, temppwd;
        int cmp;
        table->seekg(middle * LINE_SIZE, ios::beg);
        getline(*table, line);
        cout << "line = " << line << endl;

        cmp = pwdToFind.compare(line.substr(PASSWORD_SIZE, LAST_REDUCE_SIZE)); // Wang Yiwei

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
