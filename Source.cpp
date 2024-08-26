//============================================================================
// Name        : final project
// Author      : Tashi Anderson
// Version     : 1.0
// Copyright   : Copyright  2023 SNHU COCE
// Description : final project of cs 300! I used resources from past labs to create this.
//				Also decided to use binary tree to sort data, ended up being more simplistic than I thought
//				oopsies
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations, do i need this?
//double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string courseName;
    vector<string> preReq;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:

    // Internal structure for tree node
        struct Node {
        Course course;
        Node* left;
        Node* right;

        // default constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) :
            Node() {
            course = aCourse;
        }
    };


    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    //virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course aCourse);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    this->root = nullptr;
}



/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    preOrder(root);
}



/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course aCourse) {
    // if root equarl to null ptr
      // root is equal to new node course
    if (root == nullptr) {
        root = new Node(aCourse);
    }
    // else
      // add Node root and course
    else {
        addNode(root, aCourse);
    }
}

/**
 * Remove a course
 */
//void BinarySearchTree::Remove(string courseId) {
    // remove node root courseID
    //root = removeNode(root, courseId);
//

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* currentNode = root;
    Course aCourse;

    // keep looping downwards until bottom reached or matching courseId found
        // if match found, return current course
    while (currentNode != NULL) {
        if (currentNode->course.courseId == courseId) {
            return currentNode->course;
        }

        else if (courseId < currentNode->course.courseId) {// if course is smaller than current node then traverse left
            currentNode = currentNode->left;
        }

        else {// else larger so traverse right
            currentNode = currentNode->right;
        }
    }
    return aCourse;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param Course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course aCourse) {
    // if node is larger then add to left
    if (aCourse.courseId.compare(node->course.courseId) < 0) {
        if (node->left == NULL) { // if no left node
            node->left = new Node(aCourse);// this node becomes left
        }
        else {// else recurse down the left node
            addNode(node->left, aCourse);
        }
    }
    else {// else
        // if no right node
        if (node->right == NULL) {// this node becomes right
            node->right = new Node(aCourse);
        } //else
        else {
            addNode(node->right, aCourse); // recurse down the left node
        }
    }

}
void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != NULL) {
        inOrder(node->left);//InOrder not left
        inOrder(node->right);//InOder right
        cout << node->course.courseId << ", " << node->course.courseName << endl;
    }

}
void BinarySearchTree::postOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != NULL) {

        postOrder(node->left);//PostOrder not left
        cout << node->course.courseId << ", " << node->course.courseName <<  endl;
        postOrder(node->right);//postOrder right

    }

}

void BinarySearchTree::preOrder(Node* node) {
    if (node != NULL) {

        preOrder(node->left);//PreOrder not left

        preOrder(node->right);//preOrder right
        cout << node->course.courseId << ", " << node->course.courseName << endl;

    }
}

/**
 * Remove a course 
 */
void BinarySearchTree::Remove( string courseId) {
    // ??

    Node* par = NULL;
    Node* curr = root;

    while (curr != NULL) {
        if (curr->course.courseId == courseId) {
            if (curr->left == NULL && curr->right == NULL) {
                if (par == NULL) {
                    root = nullptr;
                }
                else if (par->left == curr) {
                    par->left = NULL;
                }
                else {
                    par->right = NULL;
                }
            }
            else if (curr->right == NULL) {
                if (par == NULL) {
                    root = curr->left;
                }
                else if (par->left == curr) {
                    par->left = curr->left;
                }
                else {
                    par->right = curr->left;
                }
            }
            else if (curr->left == NULL) {
                if (par == NULL) {
                    root = curr->right;
                }
                else if (par->left == curr) {
                    par->left = curr->right;
                }
                else {
                    par->right = curr->right;
                }
            }
            else {
                Node* suc = curr->right;

                while (suc->left != NULL) {
                    suc = suc->left;

                }

                Node successorData = Node(suc->course);
                Remove(suc->course.courseId);
                curr->course = successorData.course;
            }
            return;
        }
        else if (curr->course.courseId < courseId) {
            par = curr;
            curr = curr->right;
        }
        else {
            par = curr;
            curr = curr->left;
        }
    }
    return;
}
//how to read from commas! yay!
vector<string> Split(string lineFeed) {

    char delim = ',';

    lineFeed += delim;
    vector<string> lineTokens;
    string temp = "";
    for (int i = 0; i < lineFeed.length(); i++)
    {
        if (lineFeed[i] == delim)
        {
            lineTokens.push_back(temp);
            temp = "";
            i++;
        }
        temp += lineFeed[i];
    }
    return lineTokens;
}
//now to load the courses...
void loadCourses(string csvPath, BinarySearchTree* courseList) {
    // Create a data structure and add to the collection of courses 
    //fixed error stating exception at kernel.dll

    ifstream inFS; 
    string line;  
    vector<string> stringTokens;

    inFS.open(csvPath); 

    if (!inFS.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }
    while (!inFS.eof()) {

        Course aCourse;
        getline(inFS, line);
        stringTokens = Split(line);

        if (stringTokens.size() < 2) { 
            cout << "\nError. Skipping line." << endl;
        }

        else {

            aCourse.courseId = stringTokens.at(0);
            aCourse.courseName = stringTokens.at(1);

            for (unsigned int i = 2; i < stringTokens.size(); i++) {

                aCourse.preReq.push_back(stringTokens.at(i));
            }
            courseList->Insert(aCourse);
        }
    }

    inFS.close(); 
}




/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course aCourse) {
    cout << aCourse.courseId << ", " << aCourse.courseName << endl;
    cout << "Prereqs: ";

    if (aCourse.preReq.empty()) {
        cout << "N/A" << endl;
    }

    else {
        for (unsigned int i = 0; i < aCourse.preReq.size(); i++) {

            cout << aCourse.preReq.at(i);
            if (aCourse.preReq.size() > 1 && i < aCourse.preReq.size() - 1) {
                cout << ", ";
            }
        }
    }
    return;
}

/**
*The one and only main() method
*/
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, aCourseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        aCourseKey = argv[2];
        break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";//input file name here to run the file you need
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  4. Remove Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Complete the method call to load the courses
            loadCourses(csvPath, bst);

           // cout <<"courses read" << endl;

         break;

        case 2:
            bst->InOrder();
            break;

        case 3:

            course = bst->Search(aCourseKey);

            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Id " << aCourseKey << " not found." << endl;
            }

            break;

        case 4:
            bst->Remove(aCourseKey);
            break;

        case 9:
            exit;
            break;
        
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
