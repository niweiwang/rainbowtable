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
        cout << "A problem was encountered when oppening the file "<<FILE_NAME;
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

        for (int i = 0; i < NBR_OF_REDUCTION; i++)
        {
            hashed = hashStr(reduced);
            reduced = reduce(i, hashed);
        }
        table << password + reduced + "\n";
    }
    sortTable(&table);
    table.close();
    cout << "The table creation took " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." << endl;
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
        cout << "An error was encountered using tellg" << endl;
        exit(-1);
    }
    unsortedTable->seekg(0, unsortedTable->beg);

    for (i = 0; i < tableSize; i += LINE_SIZE)
    {
        unsortedTable->seekg(i, ios::beg);
        getline(*unsortedTable, smallestReduce);
        temp = smallestReduce;
        emp = i;
        for (y = i + LINE_SIZE; y < tableSize; y += LINE_SIZE)
        {
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
    string randomPassword;
    for (int i = 0; i < PASSWORD_SIZE; i++)
    {
        randomPassword += alphanum[rand() % alphanum.length()];
    }
    return randomPassword;
}

//each line is LINE_SIZE bites
void readFileContent()
{
    string line;
    ifstream table(FILE_NAME);
    table.seekg(0, table.end);
    streamsize tableSize = table.tellg();
    int i = 0;
    for (i = 0; i < tableSize; i += LINE_SIZE)
    {

        table.seekg(i + PASSWORD_SIZE, ios::beg);

        getline(table, line);
    }

    table.close();
}
