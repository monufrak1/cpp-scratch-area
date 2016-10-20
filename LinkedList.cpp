#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* next;
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : m_head(NULL) {}
    ~LinkedList()
    {
        clear();
    }
    
    LinkedList(const LinkedList<T>& rhs) 
    {
        // Copy list
        copyList(rhs);
    }
    
    LinkedList<T>& operator=(const LinkedList<T>& rhs)
    {
        if(this != &rhs)
        {
            // Clear current list
            clear();
            
            // Copy rhs list
            copyList(rhs);
        }
        
        return *this;
    }
    
    virtual void add(T t)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = t;
        newNode->next = NULL;
        
        if(!m_head)
        {
            // List is empty. Add new node at head of list
            m_head = newNode;
        }
        else
        {
            // Add new node to the end of the list
            Node<T>* curr = m_head;
            while(curr->next)
            {
                curr = curr->next;
            }
            
            curr->next = newNode;
        }
    }
    
    void remove(T t)
    {
        Node<T>* curr = m_head;
        Node<T>* prev = NULL;
        
        // Find element to delete
        while(curr)
        {
            if(curr->data == t)
            {
                break;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        
        if(curr)
        {
            if(curr == m_head)
                m_head = m_head->next;
            else
                prev->next = curr->next;
            
            delete curr;
        }
    }
    
    bool search(T t) const
    {
        Node<T>* curr = m_head;
        while(curr)
        {
            if(curr->data == t)
                return true;
            else 
                curr = curr->next;
        }
        
        return false;
    }
    
    string toString() const
    {
        stringstream ss;
        
        Node<T>* curr = m_head;
        while(curr)
        {
            ss << curr->data << " ";
            curr = curr->next;
        }
        
        return ss.str();
    }
    
    void clear()
    {
        // Delete all nodes
        Node<T>* curr = m_head;
        while(curr)
        {
            Node<T>* temp = curr;
            curr = curr->next;
            
            delete temp;
        }
        
        m_head = NULL;      
    }
    
protected:
    void copyList(const LinkedList<T>& rhs)
    {
        m_head = NULL;
        Node<T>* curr = rhs.m_head;
        while(curr)
        {
            // Add each element from rhs list
            add(curr->data);
            curr = curr->next;
        }
    }
    
protected:
    Node<T>* m_head;
};

template <typename T>
class SortedLinkedList : public LinkedList<T>
{
    public:
        SortedLinkedList() : LinkedList<T>() {}
        SortedLinkedList(const LinkedList<T>& rhs)
        {
            this->copyList(rhs);
        }
    
        virtual void add(T t)
        {
            Node<T>* newNode = new Node<T>;
            newNode->data = t;
            newNode->next = NULL;
            
            if(!this->m_head)
            {
                // List is empty. Add new node at head of list
                this->m_head = newNode;
            }
            else
            {
                Node<T>* prev = NULL;
                Node<T>* curr = this->m_head;
                while(curr)
                {
                    if(curr->data >= t)
                    {
                        if(curr == this->m_head)
                        {
                            newNode->next = this->m_head;
                            this->m_head = newNode;
                        }
                        else
                        {
                            prev->next = newNode;
                            newNode->next = curr;
                        }
                        
                        break;
                    }
                    
                    prev = curr;
                    curr = curr->next;
                }
                
                if(!curr)
                {
                    // Add element at the end of the list
                    prev->next = newNode;
                }
            }
        }
};

template <typename T>
void searchList(const LinkedList<T>& list, T value);

template <typename T>
void searchList(const LinkedList<T>& list, T value);

void testLinkedList();
void testSortedLinkedList();
void testCopyList();

int main()
{
    testLinkedList();
    testSortedLinkedList();
    testCopyList();
    
    return 0;
}

template <typename T>
void printList(const LinkedList<T>& list)
{
    cout << "List contains: " << list.toString() << endl;
}

template <typename T>
void searchList(const LinkedList<T>& list, T value)
{
    cout << value
         << (list.search(value) ? " found in list." : " not found in list.")
         << endl;
}

void testLinkedList()
{
    cout << "====== TESTING LINKED LIST ======" << endl;
    
    LinkedList<int> list;
    
    // Add elements
    list.add(1);
    list.add(2);
    list.add(3);
    printList(list);
    
    // Search
    searchList(list, 1);
    searchList(list, 2);
    searchList(list, 3);
    searchList(list, 99);
    
    // Test removing a non existing element
    list.remove(99);
    printList(list);
    
    // Add new element
    list.add(99);
    printList(list);
    
    // Search
    searchList(list, 99);
    
    // Remove original elements
    list.remove(1);
    list.remove(2);
    list.remove(3);
    printList(list);
    
    // Search
    searchList(list, 1);
    searchList(list, 2);
    searchList(list, 3);
    searchList(list, 99);
    
    // Remove last element
    list.remove(99);
    printList(list);
    
    // Search empty list
    searchList(list, 99);
}

void testSortedLinkedList()
{
    cout << "====== TESTING SORTED LINKED LIST ======" << endl;
    
    SortedLinkedList<int> list;
    
    // Add elements
    list.add(3);
    list.add(2);
    list.add(1);
    printList(list);
    
    // Search
    searchList(list, 1);
    searchList(list, 2);
    searchList(list, 3);
    searchList(list, 99);
    
    // Test removing a non existing element
    list.remove(99);
    printList(list);
    
    // Add new element
    list.add(99);
    printList(list);
    
    // Search
    searchList(list, 99);
    
    // Remove original elements
    list.remove(1);
    list.remove(2);
    list.remove(3);
    printList(list);
    
    // Search
    searchList(list, 1);
    searchList(list, 2);
    searchList(list, 3);
    searchList(list, 99);
    
    // Remove last element
    list.remove(99);
    printList(list);
    
    // Search empty list
    searchList(list, 99);
}

void testCopyList()
{
    cout << "====== TESTING COPY LINKED LIST ======" << endl;
    
    LinkedList<int> list1;
    list1.add(3);
    list1.add(1);
    list1.add(2);
    
    LinkedList<int> list2(list1); // Test copy constructor
    
    printList(list1);
    printList(list2);
    
    LinkedList<int> list3 = list1; // Test copy constructor
    
    printList(list3);
    
    LinkedList<int> list4;
    list4.add(4);
    list4.add(5);
    
    list3 = list4; // Test assignment operator
    
    printList(list3);

    cout << "====== TESTING COPY SORTED LINKED LIST ======" << endl;
    
    SortedLinkedList<int> sList1;
    sList1.add(3);
    sList1.add(1);
    sList1.add(2);
    
    SortedLinkedList<int> sList2(sList1); // Test copy constructor
    
    printList(sList1);
    printList(sList2);
    
    SortedLinkedList<int> sList3 = list1; // Test copy constructor
    
    printList(sList3);
    
    LinkedList<int> list5;
    list5.add(20);
    list5.add(10);
    
    sList1 = sList3 = list5; // Test assignment operator
    
    printList(list5);
    printList(sList1);
    printList(sList3);
}