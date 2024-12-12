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
1 - Compiling with: g++ -o typing_test main.cpp -std=c++11 -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system


2 - how to draw a triangle in SFML
Point 0: The bottom-middle point of the triangle.
Set to (size.x / 2.f, size.y) to position it at the middle of the bottom edge.
Point 1: The top-left corner.
Set to (0.f, 0.f) to position it at the top-left of the bounding box.
Point 2: The top-right corner.
Set to (size.x, 0.f) to position it at the top-right of the bounding box.


# to do
SPRITES 
[x] sprite motion 
    - straight down, sine wave (left to right, right to left), diagonal 
[x] multiple sprite render
[] on correct, spin out, fade away


GAME
[] game over when sprite reaches certain point or 50 words have been typed 
[] iterate score
[] spawn - max 50 words
[] track accuracy, wpm  
[] environment - background (starry night)
[] typing area - show user input, clear on enter. 


 



# references 
- starry night background https://www.pexels.com/search/starry%20night/
- general SFML setup and usage https://www.sfml-dev.org/tutorials/2.6/
- enumeration: https://en.cppreference.com/w/cpp/language/enum
- emplace_back vs push_back (needed to create invaders inside a loop)
    - https://cplusplus.com/reference/vector/vector/emplace_back/
    - https://cplusplus.com/reference/vector/vector/push_back/
    - https://andreasfertig.blog/2023/04/push_back-vs-emplace_back-when-to-use-what/
    
