### Rex Sheikh 
### Data Structures Final Project 


# Overview - Trie Data Structure and Game Implementation 
The Trie data structure can efficiently store and retrieve words even in with large search spaces like dictionaries making it a suitable choice for tools like autocomplete and spellchecking. Although pronounced "try", the Trie data structure still has the form of a tree. The first character of each word comprise the children of a root node. These nodes are linked with each successive character in the word until reaching a leaf node creating the basic structure below.

![Figure 1.](assets/trie.png)

This implementation uses two classes, TrieNode and Trie. The Node class uses an unordered map to store other TrieNode's as children and a boolean, isLeaf to signal the termination of each word. The Trie class holds the root which is simply a pointer to the root node and key methods to build and search the Trie. Later sections describe the Trie in detail, but it's worth emphasizing that searching the Trie is _O(L)_ time complexity where _L_ is the length of the word making it comparitively fast. 

This game leverages that speed to quickly check user input against a set of words. 
***add more detail about game input***

# Getting Started


# The Trie in Detail

# Space Invaders Game Design 

# Conclusion

# Notes 
Compiling with: g++ -o typing_test main.cpp -std=c++11 -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system