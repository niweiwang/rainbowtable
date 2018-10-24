#include <ostream>
#include <thread>
#include <ctime>
#include <vector>
#include <time.h>
#include <chrono>
#include "utils.h"

void rainbowtable(int seed, string filename, int tablesize);
string generatePassword();
bool copyfile(string sourcefile, fstream &dest_file);
void sortTable(fstream *unsortedTable);

int main() {
    srand(time(NULL));

    const clock_t begin_time = clock();
    unsigned num_cpus = std::thread::hardware_concurrency();
    string filename[num_cpus];
    int entries_by_cpu= NBR_OF_ENTRIES/num_cpus;

    cout << "Launching " << num_cpus << " threads to create rainbow table.\n";
    //cout << "Estimate to finish in "<< int(NBR_OF_ENTRIES/(1.5*num_cpus)*1.1) << " seconds..."<< endl;

    std::vector<std::thread> threads;

    //First thread takes the rest of nbr entries modulo nbr threads + his share of the work
    filename[0]= "rainbow" + to_string(1);
    threads.push_back(std::thread(rainbowtable,rand()+0*1000,filename[0], entries_by_cpu + NBR_OF_ENTRIES%num_cpus));
    //Each other thread process a same number of entries
    for(unsigned int i = 1; i < num_cpus; ++i){
        filename[i]= "rainbow" + to_string(i+1);
        threads.push_back(std::thread(rainbowtable,rand()+i*1000,filename[i], entries_by_cpu));
    }
    for(auto& thread : threads){thread.join();}



    // merge rainbow1, rainbow2, rainbow3....
    //string filetosort ="./"+FILE_NAME;
    fstream combined_file(FILE_NAME, ios::trunc | ios_base::in | ios_base::out|std::ios_base::binary);

    if (!combined_file.is_open())
    {
        cout << "1. problem when oppening rainbow.txt file.";
        exit(-1);
    }
    for(unsigned int j = 0; j < num_cpus; ++j)
    {
        if (copyfile(filename[j],combined_file)){
            cout << filename[j]<<" appended to "<<FILE_NAME<<endl;
        }
        else {
                cout << "2. problem when oppening the files.";
                exit(-1);
                }
    }
    combined_file.close();
    // end merge rainbow

    fstream table(FILE_NAME, ios_base::in | ios_base::out);
    if (!table.is_open())
    {
        cout << "3.problem when oppening r.txt file.";
        exit(-1);
    }
    cout<< "Sorting the Rainbow Table..."  <<endl;
    sortTable(&table);
    table.close();


    cout << "The table creation took " << float(clock() - begin_time) / CLOCKS_PER_SEC/num_cpus << " seconds." << endl;
    return 0;

}


void rainbowtable(int seed, string filename, int tablesize){
    string password;
    string hashed;
    string reduced;

    srand(seed);
    fstream table(filename, ios::trunc | ios_base::in | ios_base::out);
    if (!table.is_open()){
            cout << "problem when oppening the file";
            exit(-1);
    }

    for (int i = 0; i < tablesize; i++)
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

    table.close();

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

bool copyfile(string sourcefile, fstream &dest_file)
{

    string filetopen ="./"+sourcefile;
    std::ifstream srce_file(filetopen,std::ios_base::binary);

    if (!srce_file.is_open())
    {
        cout << "problem when oppening the file";
        exit(-1);
    }

     if (!dest_file.is_open())
    {
        cout << "problem when oppening the file";
        exit(-1);
    }

    if(srce_file)
    {
        dest_file.seekp(0, std::ios_base::end);
        dest_file << srce_file.rdbuf();
        srce_file.close();
        return true ;
    }
    else
    {
        std::cerr << "error: could not open " << sourcefile << '\n' ;
        return false ;
    }



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

