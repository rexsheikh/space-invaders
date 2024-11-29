#include <iostream>
#include <fstream>
#include <string>
#include "trie.h"
using namespace std; 

int main(){
    Trie trie; 
    ifstream inputFile("words1.txt"); 
    if(!inputFile.is_open()){
        cout << "Failed to open file." << endl; 
        return 1; 
    }
    string word; 
    while(inputFile >> word){
        trie.insert(word); 
    }
    inputFile.close(); 
    cout << "Search 'hello': " << (trie.search("hello") ? "Found" : "Not Found") << endl;
    cout << "Search 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Search 'cats': " << (trie.search("hell") ? "Found" : "Not Found") << endl;
    return 0; 
}