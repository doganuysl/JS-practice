#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a binary tree node
typedef struct node {
    char* word;
    int count;
    struct node* left;
    struct node* right;
} node;

// Create a new node with the given word and count
node* create_node(char* word, int count) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->word = (char*) malloc(strlen(word) + 1);
    strcpy(new_node->word, word);
    new_node->count = count;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert a new node into the tree in alphabetical order
void insert_node(node** root, char* word) {
    // If the tree is empty, create a new node as the root
    if (*root == NULL) {
        *root = create_node(word, 1);
        return;
    }

    // Start at the root of the tree
    node* curr = *root;

    // Compare the word to be inserted with the word in the current node
    int cmp = strcmp(word, curr->word);

    // If the word to be inserted comes before the word in the current node,
    // go to the left subtree
    if (cmp < 0) {
        insert_node(&(curr->left), word);
    }
    // If the word to be inserted comes after the word in the current node,
    // go to the right subtree
    else if (cmp > 0) {
        insert_node(&(curr->right), word);
    }
    // If the word to be inserted is the same as the word in the current node,
    // increment the count for that word
    else {
        curr->count++;
    }
}

// Print the words in the tree in no particular order, along with the number of times each word appears
void print_words_non(node* root) {
    if (root == NULL) {
        return;
    }
    printf("%s %d Time%s\n", root->word, root->count, root->count == 1 ? "" : "s");
    print_words_non(root->left);
    print_words_non(root->right);
}

// Print the words in the tree in alphabetical order, along with the number of times each word appears
void print_words_with_counts(node* root) {
    if (root == NULL) {
        return;
    }
    print_words_with_counts(root->left);
    printf("%s %d Time%s\n", root->word, root->count, root->count == 1 ? "" : "s");
    print_words_with_counts(root->right);
}

void search_word(node* root, char* word, int depth) {
    // Start at the root of the tree
    node* curr = root;

    // If the current node is NULL, print an error message and return
    // (this means that the word was not found in the tree)
    if (curr == NULL) {
        printf("Error: Word not found in the tree.\n");
        return;
    }

    // Compare the word to be searched with the word in the current node
    int cmp = strcmp(word, curr->word);

    // If the word to be searched is the same as the word in the current node,
    // print the depth of the tree and the count for that word
    if (cmp == 0) {
        printf("%s: Depth %d, %d Time(s)\n", word, depth, curr->count);
        return;
    }
    // If the word to be searched comes before the word in the current node,
    // go to the left subtree
    else if (cmp < 0) {
        search_word(curr->left, word, depth + 1);
    }
    // If the word to be searched comes after the word in the current node,
    // go to the right subtree
    else {
        search_word(curr->right, word, depth + 1);
    }
}


// Read the words from the given file and add them to the binary search tree
void read_words(node** root, const char* filename) {
    // Open the file for reading
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Read the words from the file, one at a time
    char word[128];
    while (fscanf(fp, "%s", word) == 1) {
        // Convert the word to lowercase
        for (int i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        // Add the word to the binary search tree
        insert_node(root, word);
    }

    // Close the file
    fclose(fp);
}

//nodes of tree
int count_nodes(node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

//depth of tree
int get_depth(node* root) {

    int max(int a, int b) {
    return (a > b) ? a : b;
}
    if (root == NULL) {
        return 0;
    }
    return 1 + max(get_depth(root->left), get_depth(root->right));
}

//for beginnig informations
void print_begin(node* root) {
    printf("\nIn total %d words were read from the file and saved in the binary search tree.\n", count_nodes(root));
    printf("Number of nodes of the binary search tree: %d\n", count_nodes(root));
    printf("The depth of binary search tree: %d\n", get_depth(root));

    if (root == NULL) {
        return;
    }
}

int main(int argc, char** argv) {

    // Create an empty binary search tree
    node* root = NULL;

    // Read the words from the input file
    read_words(&root, "Words.txt");

    //for beginnig informations
    print_begin(root);

    // Loop until the user wants to exit
    int option = 0;
    while (option != 4) {
        printf("\nChoose an option:\n");
        printf("1. Print different words\n");
        printf("2. Print different words in alphabetical order\n");
        printf("3. Search word\n");
        printf("4. Exit\n\n");
        printf("Your choice is: ");

        scanf("%d", &option);

        switch (option) {
            case 1:
                // Print the different words in the tree
                print_words_non(root);
                break;
            case 2:
                // Print the different words in alphabetical order
                print_words_with_counts(root);
                break;
            case 3:
                // Search for a word in the tree
                printf("\n");
                char word[128];
                printf("Enter a word to search: ");
                scanf("%s", word);
                // Call search_word with the root of the tree, the word to search for, and the initial depth (0)
                search_word(root, word, 0);
                break;
            case 4:
                // Exit the program
                break;
            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    }

    return 0;
}