#include <iostream>
#include <sstream>
#include <string>


#include "filefunctions.cpp"
using namespace std;

int main() {
    cout << "Enter commands (type END to finish):\n";


    string line;
    while (getline(cin, line)) {
        //if (line == "END") break;

        stringstream ss(line);
        string command;
        ss >> command;
        
        if (command == "CREATE") {
            string filename;
            ss >> filename;
            string content;
            getline(ss, content);          // read the rest of the line
            if (!content.empty() && content[0] == ' ') content.erase(0, 1); // remove leading space
                
            createFile(filename,content );
        }
        else if (command=="READ"){
            string filename;
            ss>>filename;
            read(filename);
        }
        else if (command == "INSERT") {
                string filename;
                ss >> filename;
                string content;
                getline(ss, content);          // read the rest of the line
                if (!content.empty() && content[0] == ' ') content.erase(0, 1); // remove leading space
                insert(filename, content);
        }
        else if (command == "UPDATE") {
                string filename;
                ss >> filename;
                string content;
                getline(ss, content);          
                if (!content.empty() && content[0] == ' ') content.erase(0, 1); 
                update(filename, content);
        }
        else if (command == "SNAPSHOT") {
            string filename;
            ss >> filename;
            string message;
                getline(ss, message);          
                if (!message.empty() && message[0] == ' ') message.erase(0, 1); 
               
                snapshot(filename, message);
        }
        else if (command == "ROLLBACK") {
            string filename;
            int version;
            ss >> filename >> version;
            rollback(filename, version);
        }
        else if (command == "HISTORY") {
            string filename;
            ss >> filename;
            history(filename);
        }
        else if (command == "RECENT_FILES") {
            int n;
            ss >> n;
            allfiles_time.recentFiles(n);
        }
        else if (command == "BIGGEST_TREES") {
            int n;
            ss >> n;
            allfiles_version.biggestTrees(n); 
        }
        else if (command=="END"){
            //ENDS THE PROGRAM 
            break;
        }
        else {
            cout << "Unknown command: " << command << endl;
        }

    }

    // Reset all global structures automatically

    file_map.clear();    
    allfiles_time = heapManager_time();
    allfiles_version = heapManager_versions();

    cout << "All data has been reset.\n";
    return 0;
}
