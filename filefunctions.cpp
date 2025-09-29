 # include <iostream>
 #include <vector>
 #include<string>
 #include<map>
 #include <ctime>
 #include "filestructure.cpp"
  #include "heap.cpp"
  #include <algorithm>
using namespace std;

        fileMap file_map;
        heapManager_time allfiles_time;
        heapManager_versions allfiles_version;
        

        void snapshot(string name, string message){
            File* active_file=file_map.find(name);
            if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}
            active_file->active_version->commitsnapshot();
            active_file-> edited_time=active_file->active_version->get_snapshot_time();
            allfiles_time.updateFile_time(active_file);

           
            active_file->active_version->message=message;
            allfiles_version.updateFile_version(active_file);
            cout<<"Snapshot Made."<<endl;
            return;
        }

        void createFile(string name="New file" , string initial_content=""){
            if (file_map.find(name)!=nullptr){
                cout<<"File already exists. Please choose new name for your file."<<endl;
                return;
            }
            else{
                File* newFile=new File(name,initial_content); 
                file_map.insert(name,newFile);
                File fileobject=*newFile;
                cout<<name<<" has been created"<<endl;
                snapshot(name,"initial commit");
                allfiles_time.updateFile_time(newFile);
                allfiles_version.updateFile_version(newFile);


            

                
            }
            
            return;
        }
        void read(string name){
            File* active_file=file_map.find(name);
            if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}
            string content= (file_map.find(name))->active_version->get_content();
           cout<<content<<endl;
        }
        void insert(string name,string insertcontent){
            File* active_file=file_map.find(name);
            if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}
           
            if(active_file->active_version->status()==true){
                int new_ver= active_file->version_map.get_size();
                string new_content=active_file->active_version->get_content()+insertcontent;
                TreeNode* new_insertion=  new TreeNode(new_ver,new_content,false,active_file->active_version);
                active_file->total_versions+=1;

                active_file->active_version=new_insertion;
                active_file->edited_time=time(nullptr);
                allfiles_time.updateFile_time(active_file);
                active_file->version_map.insert(new_ver,active_file->active_version);
                allfiles_version.updateFile_version(active_file);

                

            }
            else{
                string final_content=active_file->active_version->get_content()+insertcontent;
                active_file->active_version->change_content(final_content);
                active_file->edited_time=time(nullptr);
                allfiles_time.updateFile_time(active_file);
                
                


            }
            cout<<"Content Inserted"<<endl;
        }
        void update(string name,string updatecontent){
            File* active_file=file_map.find(name);
            if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}
      

            if(active_file->active_version->status()==true){
                int new_ver= active_file->version_map.get_size();
            
                string new_content=updatecontent;
                TreeNode* new_updation= new TreeNode(new_ver,new_content,false,active_file->active_version);
                active_file->active_version=new_updation;
               

                active_file->edited_time=time(nullptr);
                allfiles_time.updateFile_time(active_file);
                active_file->version_map.insert(new_ver, active_file->active_version);
                active_file->total_versions+=1;
                allfiles_version.updateFile_version(active_file);



                
            }
            else{
                string final_content=updatecontent;
                active_file->active_version->change_content(final_content);
                active_file->edited_time=time(nullptr);
                allfiles_time.updateFile_time(active_file);
               

                
            }
            cout<<"Content Updated"<<endl;
           

        }
        void rollback(string name,int versionid=0){
            File* active_file=file_map.find(name);
            if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}

            if (versionid < 0 || versionid >= active_file->version_map.get_size()) {
            cout << "No such version exists." << endl;
            return;
            }

            active_file->active_version=active_file->version_map.mapvector[versionid];
            // if(active_file->active_version==nullptr){
            //     cout<<"No such version Exists."<<endl;
            //     return;
            // }

            cout<<"Rolled back to version"<<versionid<<endl;
            return;
            

        } 
         void history(string name) {
                cout << "Files in Chronological Order of Timestamp on the active branch:" << endl;
                File* active_file=file_map.find(name);
                if (active_file==nullptr){ cout<<"No such file exists."<<endl; return;}
                vector<TreeNode*> branch_snapshots;
                TreeNode* node = file_map.find(name)->active_version;
                while (node != nullptr) {
                    if (node->status()==true) { // Only snapshots
                        branch_snapshots.push_back(node);
                    }
                    node = node->parent;
                }
                reverse(branch_snapshots.begin(), branch_snapshots.end());
                for (auto snap : branch_snapshots) {
                    cout << "-------------------------------" << endl;
                    cout << "Version: " << snap->get_version_id() << endl;
                    cout << "Content: " << snap->get_content() << endl;
                    cout << "Snapshot Message: " << snap->message << endl;
                    time_t snap_time = snap->get_snapshot_time();
                    cout << "Time when Snapshotted: " << ctime(&snap_time) << endl;
                    cout << "-------------------------------" << endl;
    }
}

        
            

        
        
       




