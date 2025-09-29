 # include <iostream>
 #include <vector>
 #include<string>
 #include<map>
 #include <ctime>
 # pragma once
 #include "map.cpp"
 
using namespace std;




class TreeNode{
    private:
    int version_id; 
    string content; 
    bool snapshot;

    time_t created_timestamp; 
    time_t snapshot_timestamp ;// null if not a snapshot 
    vector <TreeNode* > children; 

    public: 
    string message; 
    TreeNode* parent; 

    TreeNode(int version_id=0,string content=" ",bool snapshot=false,TreeNode* parent=nullptr){
        //cout<<"New version created"<<endl;
        this->version_id=version_id; 
        this->content=content; 
        this->snapshot=snapshot; 
        this->parent=parent;
        this->created_timestamp=time(nullptr);
        this->snapshot_timestamp=-1; 
        } ; 
   
    
    void commitsnapshot(){
        this->snapshot=true;
        this->snapshot_timestamp=time(nullptr);
         TreeNode*par=this->parent; 
         if (par!=nullptr){par->children.push_back(this);}
    }
    bool status(){
        return snapshot;
    }
    int get_version_id(){
        return version_id;
    }
    string get_content(){
        return content;
    }
    void change_content(string newcontent){
            if (snapshot) {
            cout << "Error: cannot modify a snapshot version" << endl;
            return;
            }
            this->content = newcontent;
        
    }
    vector <TreeNode*> getchildren(){
        return this->children;
    }
    time_t get_snapshot_time(){
        return snapshot_timestamp;
    }
    time_t get_created_time(){
        return created_timestamp;
    }


};

class File{
    friend class TreeNode;
    private: 
        string  file_name; 
        TreeNode* root;
        
    public: 
        int total_versions ;

        time_t edited_time;

        TreeNode* active_version ;
        versionMap version_map ;

        File(string file_name="New File",string content=" "){
        
            this->root= new TreeNode(0,content,false,nullptr);
            this->active_version=root; 
            edited_time=root->get_snapshot_time();
            version_map.insert(0,root); 
            total_versions=1;
            this->file_name=file_name; 
            this->active_version->change_content(content);

        }
        TreeNode* getroot(){
            return this->root;
        }
        string getname(){
            return file_name;
        }

    };