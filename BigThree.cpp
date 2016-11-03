#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 10

using namespace std;

class RandArray
{
public:
    RandArray(const int arrayLength)
        : m_length(arrayLength)
    {
        // Allocate array
        m_array = new int[m_length];

        // Randomize array
        for(int i = 0; i < m_length; i++)
        {
            m_array[i] = rand() % MAX_VALUE + 1;
        }
    }

    ~RandArray()
    {
        if(m_array)
        {
            delete [] m_array;
            m_array = NULL;
        }
    }

    RandArray(const RandArray* rhs)
    {
        copy(rhs);
    }

    RandArray& operator=(const RandArray& rhs)
    {
        if(this != &rhs)
        {
            if(m_array)
            {
                delete [] m_array;
                m_array = NULL;
            }

            copy(rhs);
        }

        return *this;
    }

    friend ostream& operator<<(ostream& os, const RandArray& rhs);

private:
    void copy(const RandArray& toCopy)
    {
        if(toCopy.m_length > 0 && toCopy.m_array) {
            m_length = toCopy.m_length;
            m_array = new int[m_length];
            memcpy(m_array, toCopy.m_array, m_length * sizeof(int));
        }
    }

private:
    int  m_length;
    int* m_array;
};

ostream& operator<<(ostream& os, const RandArray& rhs)
{
    stringstream arrayStr;
    for(int i = 0; i < rhs.m_length; i++)
    {
        arrayStr << rhs.m_array[i];
        if(i < rhs.m_length - 1)
            arrayStr << ", ";
    }

    os << endl
       << "Array length: " << rhs.m_length << endl
       << "[" << arrayStr.str() << "]" << endl
       << endl;

    return os;
}

int main()
{
    RandArray rand1(5);
    RandArray rand2(10);

    cout << "rand1: " << rand1 << "rand2: " << rand2 << endl; 

    // Test Copy Constructor
    RandArray copy1 = rand1;
    RandArray copy2(rand2);

    cout << "copy1: " << copy1 << "copy2: " << copy2 << endl; 

    // Test Assignment operator
    copy1 = copy2;
    
    cout << "copy1: " << copy1 << "copy2: " << copy2 << endl;
}