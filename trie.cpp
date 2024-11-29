#include "trie.h"

//initial state -> no leaves. 
TrieNode::TrieNode() : isLeaf(false) {}
TrieNode::~TrieNode(){
    for(auto& pair : children){
        delete pair.second; 
    }
}
Trie::Trie(){
    root = new TrieNode(); 
}
Trie::~Trie(){
    delete root; 
}
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

bool Trie::startsWith(const std::string& prefix) const {
    TrieNode* current = root;
    for (char c : prefix) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return true;
}