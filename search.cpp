#include <iostream>
#include <direct.h>
#include <vector>
#include <list>
#include <io.h>
#include <thread>

using namespace std;



vector<string> get_folders(const string& folder)
{
    vector<string> folders;

    string current_folder = folder;

            if (*(current_folder.end() - 1) != '\\')
            {
                current_folder.append("\\*");
            }
            else
            {
                current_folder.append("*");
            }

        struct _finddata_t file_info;
        auto file_handler = _findfirst(current_folder.c_str(), &file_info);

            while (file_handler != -1)
            {
                if (file_info.attrib & _A_SUBDIR)
                {
                    string folder(current_folder);
                    folder.pop_back();
                    folder.append(file_info.name);
                    folders.push_back(folder.c_str());
                }

                if (_findnext(file_handler, &file_info) != 0)
                    break;
            }
    return folders;
}

string search_in_folder(const string &folder, bool recurcive, const string& search_name) {

    string file;
    list<string> subfolders;

    subfolders.push_back(folder);
    while (!subfolders.empty())
    {

        string current_folder(subfolders.back());

        if (*(current_folder.end() - 1) != '\\')
        {
            current_folder.append("\\*");
        }
        else
        {
            current_folder.append("*");
        }

            subfolders.pop_back();
            struct _finddata_t file_info;
            auto file_handler = _findfirst(current_folder.c_str(), &file_info);

            while (file_handler != -1)
            {

                if (recurcive && (!strcmp(file_info.name, ".") || !strcmp(file_info.name, "..")))
                {
                    if (_findnext(file_handler, &file_info) != 0) break;
                    continue;
                }


                if (file_info.attrib & _A_SUBDIR)
                {
                    if (recurcive) {
                        // will search sub folder
                        string folder(current_folder);
                        folder.pop_back();
                        folder.append(file_info.name);

                        subfolders.push_back(folder.c_str());
                    }
                }
                else
                {
                    if (file_info.name == search_name)
                    {
                        // it's a file
                        string file_path;
                        // current_folder.pop_back();
                        file_path.assign(current_folder.c_str()).pop_back();
                        file_path.append(file_info.name);

                        file = file_path;
                        return file;
                    }
                }

                if (_findnext(file_handler, &file_info) != 0)
                    break;
            }  // while
            _findclose(file_handler);

       
    }

    return file;
}

int start_search(string directory, string str_to_find)
{
        string end_file = search_in_folder(directory, false, str_to_find);
        if (!end_file.empty())
        {
            return 0;
        }
            vector<string> folders;
            folders = get_folders(directory);

     thread t1([&]() {
         for (string i : folders){
                    
             end_file = search_in_folder(i, true, str_to_find);
             if (!end_file.empty())
                 {
                     cout << "file path: " << end_file << endl;
                            return 0;
                 }
         }
     });
t1.join();

    return 0;
}