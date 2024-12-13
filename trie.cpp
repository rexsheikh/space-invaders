#include "trie.h"

//initial state -> no leaves. 
TrieNode::TrieNode() : isLeaf(false) {}
TrieNode::~TrieNode(){
    for(auto& pair : children){
        delete pair.second; 
    }
}
// Root node instantiation, has no character assigned but unordered map of children. 
Trie::Trie(){
    root = new TrieNode(); 
}
// Destructor
Trie::~Trie(){
    delete root; 
}
// Insert method for building the Trie. If the current character is not in the Trie, 
// it is assigned as a key with value of a new Trie Node. That node is set to current 
// and the loop progresses until the last character is reached which has isLeaf assigned marking 
// the end of a complete word. 
void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->isLeaf = true;
}

// Similar to the insert method but checks the input string sequentially by character. 
// If the end of the string is reached and there is a matching sequence of TrieNodes and 
// the last character is marked as a leaf in the Trie, return true. Otherwise, no match and return false. 
bool Trie::search(const std::string& word) const {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return current->isLeaf;
}
