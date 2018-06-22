#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: load_date <date time>.\n");
        return 0;
    }

    cout << argv[1] << endl;
    char buf1[128];
    char buf2[128];
    char buf3[128];
    char buf4[128];
    char buf5[128];
    sscanf(argv[1], "%[0-9] %[0-9]:%[0-9]:%[0-9].%[0-9]",
           buf1, buf2, buf3, buf4, buf5);
    cout << buf1 << endl;
    cout << buf2 << endl;
    cout << buf3 << endl;
    cout << buf4 << endl;
    cout << buf5 << endl;
}

#if 0
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: load_date <date time>.\n");
        return 0;
    }

    cout << argv[1] << endl;
    string in = argv[1];
    istringstream iss(in);
    int num;
    iss >> num;
    cout << num << endl;
    return 0;
}
#endif
