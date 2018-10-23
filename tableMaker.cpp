#include <stdlib.h>
#include <time.h>
#include "utils.h"

string generatePassword();
string hashStr(string toHash);
void sortTable(fstream *unsortedTable);
void resadFileContent();

int main(void)
{
    srand(time(NULL));

    fstream table(FILE_NAME, ios::trunc | ios_base::in | ios_base::out);
    if (!table.is_open())
    {
        cout << "problem when oppening the file";
        exit(-1);
    }

    const clock_t begin_time = clock();
    string password;
    string hashed;
    string reduced;
    for (int i = 0; i < NBR_OF_ENTRIES; i++)
    {
        password = generatePassword();
        reduced = password;
        cout << reduced << endl;
        for (int i = 0; i < NBR_OF_REDUCTION; i++)
        {
            hashed = hashStr(reduced);
             cout << hashed << endl;
            //cout << hashed << endl;
            reduced = reduce(i, hashed);
            cout << reduced << endl;
           
        }
        table << password + reduced + "\n";
        cout << "\n" << endl;
        //cout << "line count "<< i <<endl; // [Wang Yiwei]
    }
    sortTable(&table);
    table.close();
    //Calcul du temps que la creation de la table prend
    std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
    return 0;
}

void sortTable(fstream *unsortedTable)
{
    int i, y, cmp, emp = 0;
    string smallestReduce, reduceToCompare, temp;
    unsortedTable->seekg(0, unsortedTable->end);
    streamsize tableSize = unsortedTable->tellg();
    if (tableSize == -1)
    {
        cout << "une erreur est survenue dans tellg" << endl;
        exit(-1);
    }
    //cout << "tablesize = " << tableSize << endl;
    unsortedTable->seekg(0, unsortedTable->beg);

    for (i = 0; i < tableSize; i += LINE_SIZE)
    {
        //cout << "table sorting line count: " << i << endl; //[Wang Yiwei]
        unsortedTable->seekg(i, ios::beg);
        getline(*unsortedTable, smallestReduce);
        temp = smallestReduce;
        emp = i;
        for (y = i + LINE_SIZE; y < tableSize; y += LINE_SIZE)
        {
            //cout << "y = " << y << endl;
            unsortedTable->seekg(y, ios::beg);
            getline(*unsortedTable, reduceToCompare);
            cmp = smallestReduce.substr(PASSWORD_SIZE, LAST_REDUCE_SIZE).compare(reduceToCompare.substr(PASSWORD_SIZE, LAST_REDUCE_SIZE));
            if (cmp == 0)
            {
                cout << "/!\\ 2x le même hash" << endl;
            }
            else if (cmp > 0)
            {
                smallestReduce = reduceToCompare;
                emp = y;
            }
        }

        unsortedTable->seekp(i, ios::beg);
        *unsortedTable << smallestReduce;
        unsortedTable->seekp(emp, ios::beg);
        *unsortedTable << temp;
    }
}

string generatePassword()
{
    string const alphaNumericLowerCase = "abcdefghijklmnopqrstuvwxyz0123456789";
    string randomPassword;
    for (int i = 0; i < PASSWORD_SIZE; i++)
    {
        randomPassword += alphaNumericLowerCase[rand() % alphaNumericLowerCase.length()];
    }
    return randomPassword;
}

//each line is LINE_SIZE bites
void readFileContent()
{
    string line;
    ifstream table("rainbowTable.txt");
    table.seekg(0, table.end);
    streamsize tableSize = table.tellg();
    int i = 0;
    for (i = 0; i < tableSize; i += LINE_SIZE)
    {

        table.seekg(i + PASSWORD_SIZE, ios::beg);

        getline(table, line);
        cout << line << endl;
    }

    table.close();
}
