#include <iostream>
#include "trie.h"
using namespace std; 

int main(){
    Trie trie; 
    trie.insert("hello"); 
    trie.insert("world"); 
    cout << "Search 'hello': " << (trie.search("hello") ? "Found" : "Not Found") << endl;
    cout << "Search 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Search 'cats': " << (trie.search("hell") ? "Found" : "Not Found") << endl;
    return 0; 
}