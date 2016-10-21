#include <iostream>
#include <sstream>
#include <map>

using namespace std;

enum BstTraversalType {IN_ORDER, PRE_ORDER, POST_ORDER};

template <typename T>
struct BstNode
{
    T data;
    BstNode<T>* left;
    BstNode<T>* right;
};

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() : m_root(NULL) {}
    virtual ~BinarySearchTree()
    {
        clearTree();
    }

    BinarySearchTree(const BinarySearchTree<T>& rhs)
    {
        m_root = copyTree(rhs.m_root);
    }

    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& rhs)
    {
        if(this != &rhs)
        {
            // Clean up existing data
            clearTree();

            // Copy data from other tree
            m_root = copyTree(rhs.m_root);
        }

        return *this;
    }

    void add(T t)
    {
        if(!m_root)
        {
            // Tree is empty. Insert element at root of tree
            m_root = new BstNode<T>;
            m_root->data = t;
            m_root->left = NULL;
            m_root->right = NULL;
        }
        else
        {
            add(m_root, t);
        }
    }

    void remove(T t)
    {
        if(m_root)
        {
            m_root = remove(m_root, t);
        }
    }
    
    string toString(const BstTraversalType traversalType) const
    {
        stringstream ss;
        toString(m_root, traversalType, ss);
        
        return ss.str();
    }
    
    string toVisualString() const
    {
        map<int, string> treeDepthMap;
        
        buildDepthMap(m_root, treeDepthMap, 1);

        // Parse map of strings to draw tree
        stringstream treeStr;
        for(map<int, string>::iterator iter = treeDepthMap.begin(); iter != treeDepthMap.end(); ++iter)
        {
            treeStr << "Depth " << iter->first << ": " << iter->second << endl;
        }

        return treeStr.str();
    }

    void clearTree()
    {
        if(m_root)
        {
            // Clear nodes from root node
            clearTree(m_root);
            m_root = NULL;
        }
    }

private:
    void add(BstNode<T>* node, T t)
    {
        if(node)
        {
            if(t < node->data)
            {
                if(node->left)
                {
                    // Insert into left subtree
                    add(node->left, t);
                }
                else
                {
                    // Create new node as left subtree
                    node->left = new BstNode<T>;
                    node->left->data = t;
                    node->left->left = NULL;
                    node->left->right = NULL;
                }
            }
            else
            {
                if(node->right)
                {
                    // Insert into right subtree
                    add(node->right, t);
                }
                else
                {
                    // Create new node as right subtree
                    node->right = new BstNode<T>;
                    node->right->data = t;
                    node->right->left = NULL;
                    node->right->right = NULL;
                }
            }
        }
    }

    BstNode<T>* remove(BstNode<T>* node, T t)
    {
        if(node)
        {
            if(t == node->data)
            {
                if(node->right)
                {
                    // Find min value in right subtree to replace this node's data
                    node->data = findMin(node->right);
                    node->right = remove(node->right, node->data);
                }
                else if(node->left)
                {
                    // Find max value in left subtree to replace this node's data
                    node->data = findMax(node->left);
                    node->left = remove(node->left, node->data);
                }
                else
                {
                    // Node is a leaf node. Delete node
                    delete node;
                    node = NULL;
                }
            }
            else if(t < node->data)
            {
                node->left = remove(node->left, t);
            }
            else
            {
                node->right = remove(node->right, t);
            }
        }

        return node;
    }

    T findMin(BstNode<T>* node) {
        if(node->left)
            return findMin(node->left);
        else
            return node->data;
    }

    T findMax(BstNode<T>* node) {
        if(node->right)
            return findMax(node->right);
        else
            return node->data;
    }

    void toString(const BstNode<T>* node,
        const BstTraversalType traversalType, stringstream& ss) const
    {
        if(node)
        {
            if(traversalType == IN_ORDER)
            {
                if(node->left) toString(node->left, traversalType, ss);
                ss << node->data << " ";
                if(node->right) toString(node->right, traversalType, ss);
            }
            else if(traversalType == PRE_ORDER)
            {
                ss << node->data << " ";
                if(node->left) toString(node->left, traversalType, ss);
                if(node->right) toString(node->right, traversalType, ss);
            }
            else if(traversalType == POST_ORDER)
            {
                if(node->left) toString(node->left, traversalType, ss);
                if(node->right) toString(node->right, traversalType,ss);
                ss << node->data << " ";
            }
        }
    }

    void buildDepthMap(const BstNode<T>* node, map<int, string>& treeDepthMap, const int depth) const
    {
        if(node)
        {
            if(node->left) buildDepthMap(node->left, treeDepthMap, depth+1);
            visitNode(node, treeDepthMap, depth);
            if(node->right) buildDepthMap(node->right, treeDepthMap, depth+1);
        }
    }
    
    void visitNode(const BstNode<T>* node, map<int, string>& treeDepthMap, const int depth) const
    {
        stringstream nodeStr;
        map<int, string>::iterator depthIter = treeDepthMap.find(depth);

        if(depthIter != treeDepthMap.end())
        {
            // Entry for this depth already exists. Append to string
            nodeStr << " " << node->data;
            depthIter->second.append(nodeStr.str());
        }
        else
        {
            // Create entry for this depth
            nodeStr << node->data;
            treeDepthMap[depth] = nodeStr.str();
        }
    }

    void clearTree(BstNode<T>* node)
    {
        if(node)
        {
            if(node->left) clearTree(node->left);
            if(node->right) clearTree(node->right);

            delete node;
        }
    }

    BstNode<T>* copyTree(const BstNode<T>* otherTree)
    {
        if(otherTree)
        {
            BstNode<T>* copyNode = new BstNode<T>;
            copyNode->data = otherTree->data;
            copyNode->left = copyTree(otherTree->left);
            copyNode->right = copyTree(otherTree->right);

            return copyNode;
        }
        else
        {
            return NULL;
        }
    }

private:
    BstNode<T>* m_root;
};

template <typename T>
void printTree(const BinarySearchTree<T>& tree);

void testBst();
void testBstRemove();

int main()
{
    // testBst();
    testBstRemove();

    return 0;
}

template <typename T>
void printTree(const BinarySearchTree<T>& tree)
{
    cout << "In-order traversal     : " << tree.toString(IN_ORDER) << endl;
    cout << "Pre-order traversal    : " << tree.toString(PRE_ORDER) << endl;
    cout << "Post-order traversal   : " << tree.toString(POST_ORDER) << endl;
    cout << endl << tree.toVisualString() << endl;
}

void testBst()
{
    BinarySearchTree<int> bst;
    bst.add(2);
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(0);

    printTree(bst);

    BinarySearchTree<char> charTree;
    charTree.add('F');
    charTree.add('B');
    charTree.add('G');
    charTree.add('A');
    charTree.add('D');
    charTree.add('I');
    charTree.add('H');
    charTree.add('C');
    charTree.add('E');

    printTree(charTree);
    
    BinarySearchTree<char> charTreeCopy = charTree;
    printTree(charTreeCopy);
    
    charTreeCopy.add('Z');
    printTree(charTreeCopy);
    
    // Test clearing copied tree to make sure original tree is not affected
    charTreeCopy.clearTree();
    printTree(charTreeCopy);
    printTree(charTree);

    // Test assignment operator
    charTreeCopy = charTree;
    printTree(charTreeCopy);
}

void testBstRemove()
{
    BinarySearchTree<int> bst;
    bst.add(2);
    bst.add(1);
    bst.add(3);
    bst.add(5);
    bst.add(4);
    bst.add(0);
    printTree(bst);

    cout << "Remove 3" << endl;
    bst.remove(3);
    printTree(bst);
    
    cout << "Remove 0" << endl;
    bst.remove(0);
    printTree(bst);
    
    cout << "Remove 2 (root)" << endl;
    bst.remove(2);
    printTree(bst);
    
    cout << "Remove 99 (does not exist)" << endl;
    bst.remove(99);
    printTree(bst);
}
