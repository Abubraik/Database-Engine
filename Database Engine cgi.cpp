// Database Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_FILE_PATH "data/data.txt"
#include <vector>

using namespace std;

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

    void ClearTable();
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
        cout << "</br>";
    }
}

//insert into file
void Insert(string txt, string filepath) {
    ofstream myfile;
    myfile.open(filepath, ios::out | ios::app);
    myfile << "\n" + txt;
    myfile.close();
}

//get number of lines in file
int getNoLines() {
    int number_of_lines = 0;
    string line;
    ifstream myfile("data.txt");

    while (getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}

//display records in file
void ShowRecords() {
    string line;
    ifstream data;
    data.open("data.txt");
    system("CLS");
    cout << "******** Records ********\n";
    while (getline(data, line)) {
        cout << line << endl;
    }
    cout << "*************************\n";
    data.close();
}

//check Record availability
bool ChechReocrd(string d_id) {
    bool found = false;
    string line;
    ifstream data;
    data.open("data.txt");
    while (getline(data, line)) {
        string id(line.begin(), line.begin() + line.find(" "));
        if (id == d_id) {
            found = true;
            break;
        }
    }
    data.close();
    return found;
}
bool valid(int option) {
    bool valid = false;
    if (option > 0 && option < 5) {
        valid = true;
    }
    else {
        valid = false;
    }
    return valid;
}
void Webhead() {
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title> Database Engine </title>\n";
    cout << "</head>\n";
    string line;
    ifstream data;
    data.open("data.txt");

    cout << "<body>\n";
    cout << "<div style=\"text-align: center; \">\n";
    cout << "******** Records ********\n </br>";
    while (getline(data, line)) {
        cout << line << "</br>" << endl;
    }
    cout << "*************************\n";
    cout << "</div>";

    data.close();
}
void searchString(vector<string>&l, string s, string delim) {
    size_t pos = 0;
    string token1;
    while ((pos = s.find(delim)) != std::string::npos)
    {
        token1 = s.substr(0, pos); // store the substring   
        l.push_back(token1);
        s.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
    }
    l.push_back(s);

}

void InsertfromForm(string Fname, string Lname, string GPA, Hash HashTable) {
    //Insert
    string line;
    string record;
    ifstream data;
    data.open("data.txt");
    string str_id;

    string lastID;//store the last id in record for no collision
    while (getline(data, line)) {
        string id(line.begin(), line.begin() + line.find(" "));
        lastID = id;
    }
    int nlastID = stoi(lastID) + 1;
    str_id = to_string(nlastID);
    record += str_id + "  " + Fname + "  " + Lname + "  " + GPA;
    Insert(record, "data.txt");
    HashTable.insertItem(nlastID);//insert in hashtable
    //cout << record << endl;
    record = "";
}

void DeletefromForm(string ID, Hash HashTable) {
    string line;
    string record;
    if (ChechReocrd(ID) == true) {
        ifstream data;
        data.open("data.txt");
        ofstream temp;
        temp.open("temp.txt", ios::out | ios::app);

        int tempno = 0;
        while (getline(data, line)) {
            string id(line.begin(), line.begin() + line.find(" "));
            if (id != ID && tempno == (getNoLines() - 2)) {
                temp << line;
            }
            else if (id != ID) {
                temp << line << endl;
                tempno++;
            }

        }
        HashTable.deleteItem(stoi(ID));
        data.close();
        temp.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");
    }
}

void UpdatefromForm(string ID, string Fname, string Lname, string GPA) {
    string line;
    string record;
    if (ChechReocrd(ID) == true) {//check availability of record
        ifstream data;
        data.open("data.txt");
        ofstream temp;
        temp.open("temp.txt", ios::out | ios::app);


        int tempno = 0;
        record = "";
        while (getline(data, line)) {
            string id(line.begin(), line.begin() + line.find(" "));
            if (id != ID && tempno == (getNoLines() - 2) && data.eof()) {
                temp << line;
            }
            else if (id != ID) {
                temp << line << endl;
                tempno++;
            }
            else if (id == ID && tempno == (getNoLines() - 2) && data.eof()) {
                record += ID + "  " + Fname + "  " + Lname + "  " + GPA;
                temp << record;
            }
            else if (id == ID) {
                record += ID + "  " + Fname + "  " + Lname + "  " + GPA;
                temp << record << endl;
                tempno++;
            }
        }
        data.close();
        temp.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");
    }
}
void ShowHashTable(Hash HashTable) {
    cout << "<div style=\"text-align: center; \">\n";
    cout << "******** HashTable ********\n </br>";
    HashTable.displayHash();
    cout << "***************************\n";
    cout << "</div>";
}
int main()
{

    string line;

    //open file and create HashTable
    Hash HashTable(10);
    ifstream data;
    data.open("data.txt");
    int i = 0;
    while (getline(data, line)) {
        if (i == 0) {
            i++; continue;
        }
        string id(line.begin(), line.begin() + line.find(" "));
        HashTable.insertItem(stoi(id));
    }
    data.close();



    Webhead();
    //insert
    cout << "<div style=\"text-align: center; \">\n";
    cout << "<form action = \"DatabaseEngine.cgi\" method = \"get\">";
    cout << "<h1>Select Query Type</h1>";
    cout << "</div>";
    cout << "<input type=\"radio\" name=\"option\" value=\"Insert\" />Insert </br>\n";
    cout << "Enter First Name: <input type = \"text\" name=\"Fname\" /> \n";
    cout << "Enter Last Name: <input type = \"text\" name=\"LName\" /> \n";
    cout << "Enter GPA: :<input type = \"text\" name=\"GPA\" /> </br>\n ";
    cout << "<input type=\"submit\" value=\"Query\" style=\"margin: 4px; \"> </br></br> \n";
    cout << "</form>";
    //delete
    cout << "<form action = \"DatabaseEngine.cgi?\" method = \"get\" \n>";
    cout << "<input type=\"radio\" name=\"option\" value=\"Delete\" />Delete </br>";
    cout << "Enter ID <input type=\"text\" name=\"ID\"/> </br> \n";
    cout << "<input type=\"submit\" value=\"Query\" style=\"margin: 4px; \"> </br></br> \n";
    cout << "</form>";
    //upadate
    cout << "<form action = \"DatabaseEngine.cgi?\" method = \"get\">";
    cout << "<input type=\"radio\" name=\"option\" value=\"Update\" />Update </br>";
    cout << "Enter ID <input type=\"text\" name=\"ID\"/> \n";
    cout << "Enter First Name: <input type = \"text\" name=\"Fname\" /> \n";
    cout << "Enter Last Name: <input type = \"text\" name=\"Lname\" /> </br> </br> \n";
    cout << "Enter GPA: :<input type = \"text\" name=\"GPA\" /> </br>\n";
    cout << "<input type=\"submit\" value=\"Query\" style=\"margin: 4px; \"> </br></br> \n";
    cout << "</form>";
    //
    cout << "<form action = \"DatabaseEngine.cgi\" method = \"get\">";
    cout << "<input type=\"radio\" name=\"option\" value=\"HashTable\" />HashTable </br>";
    cout << "<input type=\"submit\" value=\"Show\" style=\"margin: 4px; \"></br></br> \n ";
    cout << "</form>";

    cout << "<div style=\"text-align: center; \">\n";
    cout << "<form action=\"DatabaseEngine.cgi\">  <input type = \"submit\" value=\"Refresh\" /> </form>";


    vector <string> list1;
    vector <string> list2;

    string given_str = getenv("QUERY_STRING");
    // option=Delete ID=9
    searchString(list1, given_str, "&");
    for (int i = 0; i < list1.size(); i++) {
        // option Delete ID 9
        searchString(list2, list1[i], "=");
    }
    bool cdash = false;
        for (int i = 0; i < list2.size(); i++) {
            if (list2[i] == "" && list2.size()>2) {
                cdash = true;
            }
        }
        if (cdash == true) {
            for (int i = 0; i < list2.size(); i++) {
                if (list2[i] == "") {
                    list2.erase(list2.begin() + i);
                }
            }
        }
    
    if (list2[0] == "option" && list2[1] == "Insert" && list2.size() == 8) {

        InsertfromForm(list2[3], list2[5], list2[7], HashTable);

    }
    else if (list2[0] == "option" && list2[1] == "Delete" && list2.size() == 4) {
        DeletefromForm(list2[3], HashTable);

    }
    else if (list2[0] == "option" && list2[1] == "Update" && list2.size() == 10) {
        UpdatefromForm(list2[3], list2[5], list2[7], list2[9]);
    }
    else if (list2[0] == "option" && list2[1] == "HashTable") {
        ShowHashTable(HashTable);
    }
  /*  cout << list2.size() << endl;
    
    cout << list2.size() << endl;
    for (int i = 0; i < list2.size(); i++) {
        cout << list2[i] << endl;
    }
  */
            cout << "</body>\n";
            cout << "</html>\n";
}