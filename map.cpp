 # include <iostream>
 #include <vector>
 class TreeNode;
 class File;
using namespace std;
class versionMap{
 public: 
 vector<TreeNode*> mapvector;

 TreeNode* find(int version_id){
    if(version_id<0||version_id>mapvector.size()-1){ return nullptr;}
    return mapvector[version_id];

 }
 int get_size(){
    //cout<<mapvector.size();

    return mapvector.size();
 }
 void insert(int i ,TreeNode* activeversion){
    if (i >= mapvector.size()) {
        mapvector.resize(i + 1, nullptr); // grow exactly to size i+1
    }
    mapvector[i] = activeversion;

 }
 
};



class fileMap {
private:
    vector<vector<pair<string, File*>>> table;
    int numBuckets; // number of buckets
    int size;       // number of key-value pairs
    const double loadFactorThreshold = 0.7; // rehash when load factor exceeds

    int hashFunction(const string& key) {
        int hashnum = 0;
        for (auto c : key) hashnum += c;
        return hashnum % numBuckets;
    }

    void rehash() {
        int oldNumBuckets = numBuckets;
        numBuckets *= 2; // double the bucket count
        vector<vector<pair<string, File*>>> newTable(numBuckets);

        for (int i = 0; i < oldNumBuckets; i++) {
            for (auto &p : table[i]) {
                int newIndex = hashFunction(p.first);
                newTable[newIndex].push_back(p);
            }
        }

        table = move(newTable);
        // cout << "Rehashing done. New bucket count: " << numBuckets << endl;
    }

public:
    fileMap(int buckets = 200) {
        numBuckets = buckets;
        table.resize(numBuckets);
        size = 0;
    }

    void insert(string key, File* file) {
        int value = hashFunction(key);

        for (int i = 0; i < table[value].size(); i++) {
            if (table[value][i].first == key) {
                cout << "File already exists." << endl;
                return;
            }
        }

        table[value].push_back({key, file});
        size++;

        // Rehash if load factor exceeded
        if ((double)size / numBuckets > loadFactorThreshold) {
            rehash();
        }
    }

    File* find(string key) {
        int value = hashFunction(key);
        for (int i = 0; i < table[value].size(); i++) {
            if (table[value][i].first == key) {
                return table[value][i].second;
            }
        }
        //cout << "No file exists" << endl;
        return nullptr;
    }
       void clear() {
        table.clear();
        table.resize(numBuckets); // reset table with empty buckets
        size = 0;
    }
};


