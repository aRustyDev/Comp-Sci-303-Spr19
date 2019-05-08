#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iterator>

using namespace std;

struct Node{
    char alpha; //Data
    string morse; //Key
    Node* left;
    Node* right;
};

Node* newNode(Node& temp, string morse, char alpha){

    temp.alpha = alpha;
    temp.morse = morse; //Key Value
    temp.left =  NULL;  //Standard Children are NULL
    temp.right = NULL;

    return &temp;
}
Node* insertNode(Node* tempNode, Node* root, int i = 0){
    vector<char> morseArr = {};
    int n = 0;
    for(char & c : tempNode->morse){
        morseArr[n] = c;
        n++;
    }
    char c = morseArr[i];

    if(root == NULL){
        return tempNode;
    }
    else if(c == '.'){//Go Left
        if(root->left != NULL){
            i++;
            insertNode(tempNode, root->left, i);
        }
        else
            root->left = tempNode;//Set New Child
    }
    else if(c == '_'){//Go Right
        if(root->right != NULL){
            i++;
            insertNode(tempNode, root->right, i);
        }
        else
            root->right = tempNode;//Set New Child
    }
    // else {
    //   cout << "input error \n" << endl;
    // }
}
Node* findChar(char c, vector<Node> bst){
    Node leaf = bst[0];
    while(c != leaf.alpha){
        if(c > leaf.alpha){
            Node * leaf = leaf->right;
        }
        else if(c < leaf.alpha){
            Node * leaf = leaf->left;
        }
    }
    return &leaf;
}
Node* findMorse(char c, vector<Node> bst){
    Node leaf = bst.front();
    string word; //str read by char
    for (char & c : word){//search morseKey for the equivalent value and append stream
        if(&c == "."){
            Node * leaf = leaf->left;
        }
        else if(&c == "_"){
            Node * leaf = leaf->right;
        }
    }
    return &leaf;
}
string encode(const string& clearTextStr, vector<Node> morseKey){ //Encode a given message as Morse
    string morseStr;
    istringstream message(clearTextStr);//str divisible by " "
    string word; //str read by char
    while(message >> word){//
        for (char & c : word){//search morseKey for the equivalent value and append stream
            Node * temp = findMorse(c, morseKey);
            morseStr.append(temp->morse + " ");
        }
    }
}
string decode(const string& morseCode, vector<Node> morseKey){ //Decode a given morse message
    string clearTextStr;
    istringstream message(morseCode);//str divisible by " "
    string word; //str read by char
    while(message >> word){//
        for (char & c : word){//search morseKey for the equivalent value and append stream
            Node * temp = findChar(c, morseKey);
            clearTextStr.append(temp->alpha + " ");
        }
    }
}
vector<Node> BST_Builder(string InFile, Node * root){// Builds the BST for Morse Encoding/Decoding

    ifstream inputFile(InFile);
    vector<Node> peopleVector = {};
    string morse;
    char alpha;                                     //Value of Node "a,b,c.. etc"

    while(inputFile >> alpha >> morse){             //Build the peopleVector, that feeds the BST
        Node thisNode;
        thisNode = *newNode(thisNode, morse, alpha);//Unordered Create Node
        peopleVector.push_back(thisNode);           //Push new Node onto peopleVector
    }

    for(int x = 0; x < peopleVector.size(); x++){ //Build the BST
        insertNode(&peopleVector[x], root);
    }
}

int main() {

    Node* root = NULL;
    vector<Node> morseBST = BST_Builder("morse key file location", root);
    encode("a plain text message", morseBST);
    decode("a morse code message", morseBST);

    return 0;
}
