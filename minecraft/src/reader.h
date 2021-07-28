#ifndef READER_H
#define READER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Reader {
private:
    ifstream file;
    stringstream ss;
public:
    Reader() {}
    Reader(const char* filepath) : ss()
    {
        this->read(filepath);
    }
    ~Reader(){}

    void read(const char* filepath)
    {
        try
        {
            file.open(filepath);
            ss.str("");
            ss.clear();
            string line;
            while (getline(file, line))
            {
                ss << line << "\n";
            }
            file.close();
        }
        catch (const ifstream::failure& e)
        {
            cout << "Exception while opening/reading a file: " << filepath << endl;
        }
    }

    string getContent()
    {
        return ss.str();
    }
    stringstream& getContent(int)
    {
        return ss;
    }

    void displayContent(ostream& out = cout)
    {
        string line;
        while(getline(ss, line))
        {
            out << line.c_str() << "\n";
        }
    }
};

#endif