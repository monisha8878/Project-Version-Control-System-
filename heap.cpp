# include <iostream>
#include <vector> 
#include "filestructure.cpp"
# pragma once
class File; //forward declaration 
using namespace std;
class heapManager_time{
 
    public:
    vector <File*> allfiles;

    void addFile(File* file){
        allfiles.push_back(file);
        int i=allfiles.size()-1;
        int parent = (i-1)/2 ;
        while(i>0){
        time_t time1 =allfiles[parent]->edited_time; 
        time_t time2 =allfiles[i]->edited_time; 
        if(time2>time1){
            swap(allfiles[parent],allfiles[i]);
            i=(i-1)/2;
        }
        else{
            break;
        }
        }
        return;


    }
    File* deleteTop_time(vector<File*> &allfiles_copy){
        File* recentfile=allfiles_copy[0];
        File* lastfile=allfiles_copy[allfiles_copy.size()-1];
        swap(allfiles_copy[0], allfiles_copy.back());  
            allfiles_copy.pop_back();  // removes the last element (which was the max)
            heapify_time_down(allfiles_copy,0);
        return recentfile;
    }


        


    void recentFiles(int num){
        int i = 0 ;
        vector <File*> allfiles_copy=allfiles;
        cout<<"RECENT FILES : "<<endl;

        if(!allfiles_copy.empty()){
        while(num>0 &&!allfiles_copy.empty()){
            File* recentfile=allfiles_copy[0];
            cout<<"---------------------"<<endl;
            time_t snap_time = recentfile->edited_time;

            cout<<recentfile->getname()<<endl;
            cout<<"Edited Time: " <<ctime(&snap_time)<<endl;
           swap(allfiles_copy[0], allfiles_copy.back());  
            allfiles_copy.pop_back();  // removes the last element (which was the max)
            heapify_time_down(allfiles_copy,0);
            num-=1;
            cout<<"---------------------"<<endl;
            

        }
    }
        else{
            cout<<"No recent Files"<<endl;
        }
        }
      void heapify_time_down(vector <File*>& heap,int i ){
        int n = heap.size();
        int largest=i;
        int left=2*i+1;
        int right=2*i+2;
        if(left<n&& heap[left]->edited_time>heap[largest]->edited_time){
            largest=left;
        }
        if(right<n&& heap[right]->edited_time>heap[largest]->edited_time){
            largest=right;
        }
        if(largest!=i){
            swap(heap[largest],heap[i]);
            heapify_time_down(heap,largest);
        }

    }
      void heapify_time_up(vector <File*>& heap,int i ){
        
        int parent = (i-1)/2 ;
        while(i>0){
        time_t time1 =heap[parent]->edited_time; 
        time_t time2 =heap[i]->edited_time; 
        if(time2>time1){
            swap(heap[parent],heap[i]);
            i=(i-1)/2;
        }
        else{
            break;
        }
        }
        return;
    }
    void updateFile_time(File* file){
        for (int i = 0 ; i < allfiles.size(); i ++){
            if (allfiles[i]==file){
                allfiles.erase(allfiles.begin()+i);
                break;
            }
            

        }
        allfiles.push_back(file);
            heapify_time_up(allfiles,allfiles.size()-1);
    }
    

};
class heapManager_versions{
   
    public:
    vector <File*> allfiles;

    void addFile(File* file){
        allfiles.push_back(file);
        int i=allfiles.size()-1;
        int parent = (i-1)/2 ;
        while(i>0){
        int versions1 =allfiles[parent]->version_map.get_size(); 
        int versions2=allfiles[i]->version_map.get_size(); 
        if(versions2>versions1){
            swap(allfiles[parent],allfiles[i]);
            i=(i-1)/2;
            
        }
        else{
            break;
        }
        }
        return;


    }

        void biggestTrees(int num){
            int i = 0 ;
            vector <File*> allfiles_copy=allfiles;
            if(!allfiles_copy.empty()){
            cout<<"Files arranged in  decreasing order of number of versions : "<<endl;
            
            while(num>0){
            File* recentfile=allfiles_copy[0];
                cout<<"---------------------"<<endl;
                cout<<recentfile->getname()<<endl;
                //cout<<recentfile->version_map.get_size()<<endl;
                cout<<recentfile->total_versions<<endl;
            swap(allfiles_copy[0], allfiles_copy.back());  
                allfiles_copy.pop_back();  // removes the last element (which was the max)
                heapify_version_down(allfiles_copy,0);
                num-=1;
            cout<<"---------------------"<<endl;
            
          




            }
        }
        else{
            cout<<"No files exist"<<endl;
        }
        }
        void heapify_version_down(vector <File*>& heap,int i ){
            int n = heap.size();
            int largest=i;
            int left=2*i+1;
            int right=2*i+2;
            if(left<n&& heap[left]->total_versions>heap[largest]->total_versions){
                largest=left;
            }
            if(right<n&& heap[right]->total_versions>heap[largest]->total_versions){
                largest=right;
            }
            if(largest!=i){
                swap(heap[largest],heap[i]);
                heapify_version_down(heap,largest);
            }

        }
        void heapify_version_up(vector <File*>& heap,int i ){
            
            
            int parent = (i-1)/2 ;
            while(i>0){
            int versions1 =heap[parent]->total_versions; 
            int versions2=heap[i]->total_versions; 
            if(versions2>versions1){
                swap(heap[parent],heap[i]);
                i=(i-1)/2;
            
            }
            else{
                break;
            }
            }
            return;


        }
        
        File* deleteTop_version(vector<File*> &allfiles_copy){
            File* recentfile=allfiles_copy[0];
            File* lastfile=allfiles_copy[allfiles_copy.size()-1];
            swap(allfiles_copy[0], allfiles_copy.back());  
                allfiles_copy.pop_back();  // removes the last element (which was the max)
                heapify_version_down(allfiles_copy,0);
            return recentfile;
        }
        void updateFile_version(File* file){
            for (int i = 0 ; i < allfiles.size(); i ++){
                if (allfiles[i]==file){
                    allfiles.erase(allfiles.begin()+i);
                    break;
                }
                
            }
            allfiles.push_back(file);
            heapify_version_up(allfiles,allfiles.size()-1);

        }

};

