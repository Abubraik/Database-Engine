// Database Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#define TEXT_FILE_PATH "data/data.txt"
using namespace std;

void Insert(string txt, string filepath) {
    ofstream myfile;
    myfile.open(filepath, ios::out | ios::app);
    myfile << "\n" + txt;
    myfile.close();
}
int getNoLines() {
    int number_of_lines = 0;
    string line;
    ifstream myfile("data.txt");

    while (getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}


class Hash
{
    int BUCKET;    // No. of buckets

    // Pointer to an array containing buckets
    list<int>* table;
public:
    Hash(int V);  // Constructor

    // inserts a key into hash table
    void insertItem(int x);

    // deletes a key from hash table
    void deleteItem(int key);

    // hash function to map values to key
    int hashFunction(int x) {
        return (x % BUCKET);
    }

    void displayHash();
};

Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<int>[BUCKET];
}

void Hash::insertItem(int key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

void Hash::deleteItem(int key)
{
    // get the hash index of key
    int index = hashFunction(key);

    // find the key in (index)th list
    list <int> ::iterator i;
    for (i = table[index].begin();
        i != table[index].end(); i++) {
        if (*i == key)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

// function to display hash table
void Hash::displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}

void ShowRecords() {
    string line;
    ifstream data;
    data.open("data.txt");
    system("CLS");
    cout << endl;
    while (getline(data, line)) {
        cout << line << endl;
    }
    cout << endl;
    data.close();
}



int main()
{
    int option;
    int id;
    string FName;
    string LName;
    float GPA;
    string record = "";
    string line;

    ifstream data;
    data.open("data.txt");
    Hash HashTable(getNoLines() - 1);
    int i = 0;
    while (getline(data, line)) {
        if (i == 0) {
            i++; continue;
        }
        string id(line.begin(), line.begin() + line.find(" "));
        HashTable.insertItem(stoi(id));
    }
    data.close();

    do
    {
        cout << "Select operation to do: \n 1-Show records \n 2-Show HashTable \n 3-Make a query \n 4-EXIT \n Option: ";
        cin >> option;
        if (option == 1) {
            ShowRecords();
            cin.get();
        }
        else if (option == 2) {
            cout << "---------- HashTable ---------- \n";
            HashTable.displayHash();
            cout << "------------------------------- \n";
            cin.get();
        }
        else if (option == 3) {
            system("CLS");
            ShowRecords();
            cout << endl;
            cout << "Select query type: \n 1-Insert \n 2-Delete \n 3-Update \n Option: ";
            cin >> option;

            

            if (option == 1) {
                //Insert
                ifstream data;
                data.open("data.txt");
                id = getNoLines();
                string str_id;

                cout << "Enter First Name: ";
                cin >> FName;
                cout << "Enter Last Name: ";
                cin >> LName;
                cout << "Enter GPA: ";
                cin >> GPA;

                string lastID;
                while (getline(data, line)) {
                    string id(line.begin(), line.begin() + line.find(" "));
                    lastID = id;
                }
                int nlastID = stoi(lastID) + 1;
                str_id = to_string(nlastID);
                record += str_id + "  " + FName + "  " + LName + "  " + to_string(GPA);
                Insert(record, "data.txt");
                cout << record << endl;
                record = "";
                cin.get();
            }
            else if (option == 2) {
                string d_id;
                cout << "Enter ID you want to DELETE: ";
                cin >> d_id;
                //check if id is available or not ;


                ifstream data;
                data.open("data.txt");
                ofstream temp;
                temp.open("temp.txt", ios::out | ios::app);

                int tempno = 0;
                while (getline(data, line)) {
                    string id(line.begin(), line.begin() + line.find(" "));
                    if (id != d_id && tempno == (getNoLines() - 2)) {
                        temp << line;
                    }
                    else if (id != d_id) {
                        temp << line << endl;
                        tempno++;
                    }
                }
                data.close();
                temp.close();
                remove("data.txt");
                rename("temp.txt", "data.txt");
            }
            else if (option == 3) {
                string line, update_id;
                ifstream data;
                data.open("data.txt");
                ofstream temp;
                temp.open("temp.txt", ios::out | ios::app);

                cout << "Enter ID you want to Update: ";
                cin >> update_id;
                string newFname, newLname, newGPA;
                cout << "Enter new First Name: ";
                cin >> newFname;
                cout << "Enter new Last Name: ";
                cin >> newLname;
                cout << "Enter new GPA: ";
                cin >> newGPA;

                int tempno = 0;
                record = "";
                while (getline(data, line)) {
                    string id(line.begin(), line.begin() + line.find(" "));
                    if (id != update_id && tempno == (getNoLines() - 2) && data.eof()) {
                        temp << line;
                    }
                    else if (id != update_id) {
                        temp << line << endl;
                        tempno++;
                    }
                    else if (id == update_id && tempno == (getNoLines() - 2) && data.eof()) {
                        record += update_id + "  " + newFname + "  " + newLname + "  " + newGPA;
                        temp << record;
                    }
                    else if (id == update_id) {
                        record += update_id + "  " + newFname + "  " + newLname + "  " + newGPA;
                        temp << record << endl;
                        tempno++;
                    }
                }
                data.close();
                temp.close();
                remove("data.txt");
                rename("temp.txt", "data.txt");
            }
            cin.get();
            system("CLS");
        }
        cin.get();
        system("CLS");

    }//end of do
    while (option != 4);
}