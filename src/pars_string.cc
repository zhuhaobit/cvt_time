#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> splitString(string str)
{
    istringstream ss(str);
    string s;
    vector<string> res;
    while (ss >> s)
        res.push_back(s);
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: parse_string file" << endl;
        return -1;
    }
    const char* filename = argv[1];
    ifstream str_file(filename);
    string line;
    if (str_file.is_open())
    {
        while (str_file.good())
        {
            getline(str_file, line);
            if (line.length() > 0)
            {
                vector<string> ret = splitString(line);
                cout << ret[0] << endl;
            }
        }
    }

    return 0;
}
