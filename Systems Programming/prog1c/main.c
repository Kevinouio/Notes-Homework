#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*

Name: Kevin Ho
NetID: Kth258
Date: 8/27/2024
Description: So this is simply just code that will create a BST in C. Now the description
of the program in the canvas assignment said to just do what the functionallity asks for which is the
insert function and to take the string inputs. Now the other functions such as search, remove and the copy constructor
functions aer there because i asked Mr Knight whether we need to have them as they don't contribute to the functionallity of the code
but stated "Yes .. that would be nice …"


*
*/


// Class equivalent for creating a node.
struct BSTnode {
    char *word;
    struct BSTnode *left, *right;

};

//Function to create a node
struct BSTnode* createNode(const char* word) {

    //Allocates the memory for the node
    struct BSTnode* temp = (struct BSTnode*)malloc(sizeof(struct BSTnode));

    //Declared the varibles and pointers for the node.
    temp->word = strdup(word);
    temp->left = NULL;
    temp->right = NULL;

    //Returns the created node
    return temp;
}

//Function to insert the node into a BST
struct BSTnode* insertNode(struct BSTnode* node, char* word) {
    // Base case in the recusion in which it will create a leaf node for the node above
    if (node == NULL) {
        return createNode(word);
    }

    //Traverses to teh left node of the value of the string is leff than the root node that it is currently on.
    else if (strcmp(node->word, word) > 0) {
        node->left = insertNode(node->left, word);
    }

    //Traverses to teh left node of the value of the string is leff than the root node that it is currently on.
    else if (strcmp(node->word, word) < 0) {
        node->right = insertNode(node->right, word);
    }

    //Returns the previous node in order to come back to the actual root of the tree.
    return node;
}

// Fucntion that will print the post order o the BST
void postOrder(struct BSTnode* root) {
    //Base case where it will move onto the next node or print out the right node.
    if (root == NULL) return;

    //Traverses the BST the furthest left first then right if the left tree ends up being empty
    postOrder(root->left);
    postOrder(root->right);

    //Prints out the node word
    printf("%s",root->word);
    printf(", ");

}

// Search traversal to find if the word is within the tree
bool search(struct BSTnode* root, char* word) {

    // Returns false if it ends up at a leaf node is not the correct word that is being searched for.
    if (root==NULL) return false;

    // Returns true if the current node is the word that is found
    else if(strcmp(root->word, word) == 0) return true;

    // Traverses to the left node of the root
    else if(strcmp(word, root->word)  > 1)  return search(root->left,word);

     // Traverses to the right node of the root
    else return search(root->right, word);

}

// Copy constructor of the tree.
struct BSTnode* copy(struct BSTnode* root) {

    //Stops traversing thorugh a direction of the node.
    if (root == NULL) return NULL;

    //Creates a new node for the tree
    struct BSTnode* newNode = createNode(root->word);

    // Recursively copy the left and right subtrees
    newNode->left = copy(root->left);
    newNode->right = copy(root->right);

    // Returns node of the tree and will return to the tree once done running
    return newNode;
}

// This function i have no clue what it is supposed to do other than return true because within the original cpp file
// The function also only returns true within the funciton.
bool Remove(struct BSTNode* node, const char* word) {
    return true;
}

// Deallocates the Tree by deallocating the node then
void dealloc(struct BSTnode* root) {
    if(root == NULL) return;

    //Recusively deallocates each node with it's children.
    dealloc(root->left);
    dealloc(root->right);

    // Deallocates the node and turns thenode to be a null node
    free(root);
    root = NULL;
}

int main()
{
    // Initalizes the user inputted string
    char userInput[100];

    // Outputs for user to understand how the code works.
    printf("Please enter a series of words to store in a BST \n");
    printf("Type 'STOP' to end the series and output the BST \n");
    struct BSTnode* root = NULL;

    // Iterates the user input
    while (1) {
        printf("Enter: ");
        scanf("%s", userInput);

        // Breaks the loop if STOP is inputted
        if (!(strcmp(userInput, "STOP"))) break;

        // Inserts the node otherwise
        else {
            root = insertNode(root, userInput);
        }
    }

    // Prints out the tree in postOrder
    printf("In postorder \n");
    postOrder(root);
    printf("\n");

    /*
    //Demonstation o fthe copy constructor
    struct BSTnode* copyroot = copy(root);
    postOrder(copyroot);
    printf("\n");
    dealloc(copyroot);
    */


    /*
    // Example runnning of the search function
    printf("What word/string would you like to search for? \n");
    printf("Type 'STOP' to end the series and output the BST \n");
    while (1) {
        printf("Enter: ");
        scanf("%s", userInput);
        if (!(strcmp(userInput, "STOP"))) break;
        else {
            bool result = search(root,userInput);
            if (result == 1) {
                printf("FOUND\n");
            }
            else {
                printf("NOT FOUND\n");
            }
        }
    }
    */

    // Deallocates the tree
    dealloc(root);

    return 0;

}
