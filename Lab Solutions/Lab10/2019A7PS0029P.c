/*************************************************************/
/*  Name: SANKHA DAS    ID NO. 2019A7PS0029P    Lab Sec. P6  */   
/*  DSA Lab 10 - AVL Tree Data Structure and Operations      */
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* Structure definition for a node of the AVL Tree */
typedef struct treenode{
    short val;  // key or value stored in the tree node
    struct treenode* left;
    struct treenode* right;
    short bf;   // height balance factor
} TreeNode;


/* a function to print the AVL tree in inorder traversal */
void printAVL(TreeNode* root){
    if(root==NULL){
        printf("NULL ");
        return;
    }
    printAVL(root->left);
    printf("%d ", root->val);
    printAVL(root->right);
}

/* function to calculate height of subtree rooted at a node */
int inclusiveHeight(TreeNode* node){
    if(node==NULL){
        return 0;
    }else{
        int maxSTHeight = inclusiveHeight(node->left);
        if (inclusiveHeight(node->right) > maxSTHeight)
            maxSTHeight = inclusiveHeight(node->right); 

        // height of the AVL tree is 1 + max(height of left subtree, height of right subtree)
        return 1 + maxSTHeight;
    }
}

/* function to calculate height balance factor of a node */
int calcBF(TreeNode* node){
    // height balance factor is height of left subtree - height of right subtree
    return inclusiveHeight(node->left) - inclusiveHeight(node->right);
}

/* function to update a node's height balance factor */
void updateBF(TreeNode* node){
    if(node != NULL){
        node->bf = calcBF(node);
    }
}

/* create and return a new node for the AVL tree */
TreeNode* newNode(int x){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->val = x;
    node->left = NULL;
    node->right = NULL;
    node->bf = calcBF(node);
    
    return node;
}

/* function to find the successor of a node in the AVL tree */
TreeNode* successor(TreeNode* node, int dir){
    TreeNode* curr = node;
    if(dir==0){     // fetch successor from left subtree
        while(curr->right != NULL)
            curr = curr->right;
    }else{          // fetch successor from right subtree
        while(curr->left != NULL)
            curr = curr->left;
    }
    return curr;
}

/* function to insert a new node in the tree without caring for the balancing of the tree after the insertion */
TreeNode* addPrimitive(TreeNode* root, short x){
    TreeNode* node = newNode(x);    // create a new node
    if(root == NULL)
        // leaf node reached, this is the appropriate position of insertion of the new node
        root = node;
    else if(root->val > x)
        // insert the new node in the left subtree
        root->left = addPrimitive(root->left, x);
    else
        // insert the new node in the right subtree
        root->right = addPrimitive(root->right, x);
    
    // calculate height balance factor of the nodes after insertion of the new element
    updateBF(root);
    return root;
}

/* function to find or search for a value in the AVL tree */
TreeNode* find(TreeNode* root, int src){
    if(root==NULL){
        printf("The value %d is not present in the tree...\n", src);
        return NULL;        // value not present in the tree
    }else if(src == root->val)
        return root;        // value found, return this node
    else if(src < root->val)
        return find(root->left, src);   // search for the value in the left subtree
    
    return find(root->right, src);  // search for the value in the right subtree
}

/* function to delete a node from the tree without caring for the balancing of the tree after the deletion */
TreeNode* deletePrimitive(TreeNode* root, int src){
    if(src == root->val){
        if(root->left == NULL && root->right == NULL)  // leaf node, simply nullify this node
            root = NULL;
        else{
            if(root->left == NULL){
                TreeNode* succ = successor(root->right, 1);              // finding the successor
                root->val = succ->val;
                root->right = deletePrimitive(root->right, succ->val);   // deleting the shifted node from the tree (otherwise duplicacy)
            }else{
                TreeNode* succ = successor(root->left, 0);               // finding the successor
                root->val = succ->val;
                root->left = deletePrimitive(root->left, succ->val);     // deleting the shifted node from the tree (otherwise duplicacy)
            }
        }        
    }else if(src < root->val){
        root->left = deletePrimitive(root->left, src);  // delete the node in the left subtree
    }else
        root->right = deletePrimitive(root->right, src); // delete the node in the right subtree

    // calculate height balance factor of the nodes after the deletion
    updateBF(root);
    return root;
}

/* function to rotate the sibtree according to the logic given in the lab sheet */
TreeNode* rotate(TreeNode* bt, TreeNode* X, TreeNode* Y, TreeNode* Z){
    TreeNode* a;
    TreeNode* b;
    TreeNode* c;

    short x = X->val;
    short y = Y->val;
    short z = Z->val;

    /* appropriately labelling a, b, c nodes according to order of values in nodes (a <= b <= c) */
    if(x <= y){
        if(y <= z){
            a = X;
            b = Y;
            c = Z;
        }else if(z <= x){
            a = Z;
            b = X;
            c = Y;
        }else{
            a = X;
            b = Z;
            c = Y;
        }
    }else{
        if(x <= z){
            a = Y;
            b = X;
            c = Z;
        }else if(z <= y){
            a = Z;
            b = Y;
            c = X;
        }else{
            a = Y;
            b = Z;
            c = X;
        }
    }

    TreeNode* T0;
    TreeNode* T1;
    TreeNode* T2;
    TreeNode* T3;

    /* appropriately labelling nodes as T0, T1, T2, T3 */
    T0 = a->left;
    if(a->right == b)
        T1 = b->left;
    else    
        T1 = a->right;

    if(b->right == c)
        T2 = c->left;
    else
        T2 = b->right;
    T3 = c->right;

    /* relinking children and subtrees */
    b->left = a;
    b->right = c;
    
    a->left = T0;
    a->right = T1;

    c->left = T2;
    c->right = T3;
    
    Z = b;      // replacing Z by b and returning this modified root of the subtree
    return Z;
}

/* function to find the parent node of a node, to be used in the rotation step */
TreeNode* parent(TreeNode* treeRoot, TreeNode* node){
    if(treeRoot->val == node->val)  // root has no parent, return NULL
        return NULL;
    else{
        TreeNode* curr = treeRoot;
        while(curr != NULL){
            if(curr->left == node || curr->right == node)   // parent found, return this node
                return curr;
            if(node->val < curr->val)                       // parent will be found in left subtree
                curr = curr->left;
            else                                            // parent will be found in right subtree
                curr = curr->right;                         
        }
    }
    return NULL;
}

/* function to insert new node in the AVL tree and resetting the AVL balance property at nearest point of imbalance */
TreeNode* add(TreeNode* treeRoot, TreeNode* root, short x){
   // simple primitive insertion procedure first
   TreeNode* node = newNode(x);
    if(root == NULL)
        root = node;
    else if(root->val > x)
        root->left = addPrimitive(root->left, x);
    else
        root->right = addPrimitive(root->right, x);
    
    updateBF(root);

    // now if the imbalance has been detected at this node, perform the steps for the rotation procedure
    if(root->bf == 2 || root->bf == -2){
        TreeNode* nodeX;
        TreeNode* nodeY;
        TreeNode* nodeZ;
        
        // appropriately labelling the nodes as X, Y, Z
        nodeZ = root;
        if(x < nodeZ->val)
            nodeY = nodeZ->left;
        else
            nodeY = nodeZ->right;

        if(x < nodeY->val)
            nodeX = nodeY->left;
        else
            nodeX = nodeY->right;

        // finding parent of the current subtree root
        TreeNode* parentOfRoot = parent(treeRoot, root);

        // linking the modified subtree to its parent
        if(parentOfRoot == NULL){
            // in case the subtree is the AVL root itself (no parent will exist in this case)
            root = rotate(treeRoot, nodeX, nodeY, nodeZ);
        }else{
            // linking the rotated subtree to its parent's left or right child pointer
            if(root->val < parentOfRoot->val)
                parentOfRoot->left = rotate(treeRoot, nodeX, nodeY, nodeZ);
            else
                parentOfRoot->right = rotate(treeRoot, nodeX, nodeY, nodeZ);
        }        
    }
    return root;
}

/* function to delete a node from the AVL tree and resetting the AVL balance property at nearest point of imbalance */
TreeNode* delete(TreeNode* treeRoot, TreeNode* root, int src){
    // perform primitive delete procedure first
    if(src == root->val){
        if(root->left == NULL && root->right == NULL)  // leaf node
            root = NULL;
        else{
            if(root->left == NULL){
                TreeNode* succ = successor(root->right, 1);
                root->val = succ->val;
                root->right = deletePrimitive(root->right, succ->val);   // deleting the shifted node from the tree (otherwise duplicacy)
            }else{
                TreeNode* succ = successor(root->left, 0);
                root->val = succ->val;
                root->left = deletePrimitive(root->left, succ->val);   // deleting the shifted node from the tree (otherwise duplicacy)
            }
        }        
    }else if(src < root->val){
        root->left = deletePrimitive(root->left, src);
    }else
        root->right = deletePrimitive(root->right, src);

    updateBF(root);

    // now if the imbalance has been detected at this node, perform the steps for the rotation procedure
    if(root->bf == 2 || root->bf == -2){
        TreeNode* nodeX;
        TreeNode* nodeY;
        TreeNode* nodeZ;
        
        // appropriately labelling the nodes as X, Y, Z
        nodeZ = root;
        if(src < nodeZ->val)
            nodeY = nodeZ->left;
        else
            nodeY = nodeZ->right;

        if(src < nodeY->val)
            nodeX = nodeY->left;
        else
            nodeX = nodeY->right;

        // finding parent of the current subtree root
        TreeNode* parentOfRoot = parent(treeRoot, root);

        // linking the modified subtree to its parent
        if(parentOfRoot == NULL){
            // in case the subtree is the AVL root itself (no parent will exist in this case)
            root = rotate(treeRoot, nodeX, nodeY, nodeZ);
        }else{
            // linking the rotated subtree to its parent's left or right child pointer
            if(root->val < parentOfRoot->val)
                parentOfRoot->left = rotate(treeRoot, nodeX, nodeY, nodeZ);
            else
                parentOfRoot->right = rotate(treeRoot, nodeX, nodeY, nodeZ);
        }        
    }
    return root;
}

// test suite for primitive operations
void testSuite1(){
    printf("\n\nTest Suite for Primitive Operations: \n\n");

    // building the AVL tree
    TreeNode* treeRoot = newNode(7);
    treeRoot = addPrimitive(treeRoot, 3);
    treeRoot = addPrimitive(treeRoot, 11);
    treeRoot = addPrimitive(treeRoot, 1);
    treeRoot = addPrimitive(treeRoot, 5);
    treeRoot = addPrimitive(treeRoot, 4);
    treeRoot = addPrimitive(treeRoot, 10);
    treeRoot = addPrimitive(treeRoot, 12);
    treeRoot = addPrimitive(treeRoot, 13);
    treeRoot = addPrimitive(treeRoot, 8);
    treeRoot = addPrimitive(treeRoot, 9);

    // printing the AVL tree in inorder fashion
    printf("AVL Tree: \n");
    printAVL(treeRoot);
    printf("\n\n");

    // finding the node with value 12 in the tree
    TreeNode* node = find(treeRoot, 12);
    printf("Node found: NODE = %d, BF = %d\n\n", node->val, node->bf);

    // finding the node with value 17 in the tree (non-existent)
    node = find(treeRoot, 17);
    printf("\n");

    // deleting the node with value 11 from the tree
    treeRoot = deletePrimitive(treeRoot, 11);

    // printing the modified AVL tree 
    printf("AVL Tree: \n");
    printAVL(treeRoot);
    printf("\n");
    
    printf("------------------------------------------------------------------------------------------------\n");
}

// test suite for modified operations
void testSuite2(){
    printf("\n\nTest Suite for Modified Operations: \n\n");

    // building the AVL tree
    TreeNode* treeRoot = newNode(7);
    treeRoot = add(treeRoot, treeRoot, 3);
    treeRoot = add(treeRoot, treeRoot, 11);
    treeRoot = add(treeRoot, treeRoot, 1);
    treeRoot = add(treeRoot, treeRoot, 5);
    treeRoot = add(treeRoot, treeRoot, 4);
    treeRoot = add(treeRoot, treeRoot, 10);
    treeRoot = add(treeRoot, treeRoot, 12);
    treeRoot = add(treeRoot, treeRoot, 13);
    treeRoot = add(treeRoot, treeRoot, 8);
    treeRoot = add(treeRoot, treeRoot, 9);

    // printing the AVL tree in inorder fashion
    printf("AVL Tree: \n");
    printAVL(treeRoot);
    printf("\n\n");
    
    // finding the node with value 12 in the tree
    TreeNode* node = find(treeRoot, 12);
    printf("Node found: NODE = %d, BF = %d\n\n", node->val, node->bf);

    // finding the node with value 17 in the tree (non-existent)
    node = find(treeRoot, 17);
    printf("\n");

    // deleting the node with value 11 from the tree
    treeRoot = delete(treeRoot, treeRoot, 11);

    // printing the modified AVL tree 
    printf("AVL Tree: \n");
    printAVL(treeRoot);
    printf("\n");

    printf("------------------------------------------------------------------------------------------------\n");
}

/* main function for testing and implementation of Q1  */
int main(){
    
    // executing and testing primitive operations
    testSuite1();

    // executing and testing modified AVL operations with balancing
    testSuite2();
    
    return 0;
}
