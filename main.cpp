#include <iostream>
#include "search.h"
#include <string>


using namespace std;

int main()
{
    string directory = "C:\\";
    string str_to_find;
    cout << "enter a file name with expancion ";
    getline(cin,str_to_find);
    cout << "wait..........loading" << endl;
    start_search(directory, str_to_find);

     system("pause");
    return 0;
}