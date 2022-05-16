#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class Vector {
public:
  Vector();                      // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index) const;      // accesses the specified element without bounds checking
  T& at(int index) const;              // accesses the specified element, throws an exception of
                                 // type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;              // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty 
  void print() const;            // print all elements, is used to debug
private:
  void inflate();                // expand the storage of the container to a new capacity,
                                 // e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the number of elements that can be held in currently
                                 // allocated storage
};
template <class T>
Vector<T>::Vector(): m_nSize(0), m_nCapacity(0), m_pElements(NULL) {};
template <class T>
Vector<T>::Vector(int size): m_nSize(0), m_nCapacity(size) {
    m_pElements = new T[size];
}
template <class T>
Vector<T>::Vector(const Vector& r) {
    m_nSize = r.size();
    m_nCapacity = m_nSize;
    m_pElements = new T[m_nSize];
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r[i];
}
template <class T>
Vector<T>::~Vector() {
    delete[] m_pElements;
}
template <class T>
T& Vector<T>::operator[](int index) const{
    return m_pElements[index];
}
template <class T>
T& Vector<T>::at(int index) const{
    if (index >= m_nSize || index < 0) {
        // format exception message
        stringstream ss;
        if (m_nCapacity == 0)
            ss << "Error: the vector is empty!";
        else
            ss << "Error: the valid range is from 0 to " << m_nSize - 1 << "!";
        throw out_of_range(ss.str());
    }
    else
        return m_pElements[index];
}
template <class T>
int Vector<T>::size() const{ return m_nSize; }
template <class T>
void Vector<T>::push_back(const T& x) {
    if (m_nSize >= m_nCapacity)
        inflate();
    m_pElements[m_nSize] = x;
    m_nSize++;
    return;
}
template <class T>
void Vector<T>::clear() { m_nSize = 0; }
template <class T>
bool Vector<T>::empty() const{ return m_nSize == 0; }
template <class T>
void Vector<T>::inflate() {
    if (m_nCapacity == 0) {
        // capacity is zero, init to 2
        m_nCapacity = 2;
        m_pElements = new T[m_nCapacity];
    }
    else {
        // not zero, enlarge to twice
        m_nCapacity = 2 * m_nCapacity;
        T* new_pElements = new T[m_nCapacity];
        // copy element to new memory
        for (int i = 0; i < m_nSize; i++)
            new_pElements[i] = m_pElements[i];
        delete[] m_pElements;
        m_pElements = new_pElements;
        return;
    }
}
template <class T>
void Vector<T>::print() const {
    cout << "Size: " << m_nSize << " Capacity: " << m_nCapacity << endl;
    if (empty()) 
        cout << "This vector is empty!";
    for (int i = 0; i < m_nSize; i++)
        cout << m_pElements[i] << ' ';
    cout << endl;
}

int main() {
    // blank init
    Vector<int> v1;
    v1.print();

    // specify size
    Vector<int> v2(10);
    v2.print();
    // copy
    Vector<int> v3(v2);
    v3.print();
    v2.push_back(1);
    for (int i = 0; i < 10; i++) 
        v3.push_back(i);
    // push and inflate
    v2.print();
    v3.print();

    // clear
    v3.clear();
    v3.print();

    // size(), emtpy() and operator[]
    cout << "size: " << v2.size() << " empty: " << v2.empty() << endl
        << "This first element:" << ' ' << v2[0] << endl;

    // throw exception
    try {
        v2.at(2);
    }
    catch(const out_of_range& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}