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
    myfile <<"\n" + txt ;
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

int main()
{
    int option;
    int id;
    string FName;
    string LName;
    float GPA;
    string record = "";
    string line;

    cout<<"Select query type: \n 1-Insert \n 2-Delete \n 3-Update \n";
    cin >> option;

    //create file
    /*ofstream myfile;
    myfile.open("data.txt",ios::out | ios::app);*/
    
    
    while (option != 4) {

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
            cout << record<<endl;
            record = "";
            break;
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
                if (id != d_id && tempno == (getNoLines()-2)) {
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
            break;
        }
        else if (option == 3) {
            string line, update_id;
            ifstream data;
            data.open("data.txt");
            ofstream temp;
            temp.open("temp.txt", ios::out | ios::app);

            cout << "Enter ID you want to Update: ";
            cin >> update_id;
            string newFname, newLname,newGPA;
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
                    temp << record ;
                }else if (id == update_id) {
                    record += update_id + "  " + newFname + "  " + newLname + "  " + newGPA;
                    temp << record << endl;
                    tempno++;
                }
            }
            data.close();
            temp.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            break;
        }
    }
}

