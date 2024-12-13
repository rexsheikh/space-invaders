#include <unordered_map>
#include <memory> 
#include <string> 
using namespace std; 

class TrieNode{
    public:
    bool isLeaf; // Marks last character as the end of a string. 
    unordered_map<char, TrieNode*> children;  // Map of child nodes
    TrieNode(); 
    ~TrieNode(); 
};
class Trie{
    private:
    TrieNode* root; // Root used to check child TrieNodes sequentially.  
    public:
    Trie(); 
    ~Trie(); 
    void insert (const string &word); 
    bool search (const string &word) const; 
    bool startsWith(const string& prefix) const; 
};