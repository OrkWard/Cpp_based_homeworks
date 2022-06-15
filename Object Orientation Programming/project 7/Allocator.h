#include <stdlib.h>
#include <iostream>

namespace myAllocator {

constexpr auto BASEPOOLCOUNT = 16ULL;

/* Implementation of Memory Pool
 * Maintain a list of free nodes in a continuous memory block. Nodes won't
 * always have the same size. When asked to allocate a object, the allocator
 * pick a memory block from the first node of the list. If the size of the 
 * node larger than 1, just reduce the size of it. If the pool capacity is 
 * not enough, use malloc() to add another block with the same size of the
 * capacity now. If not, remove the node from the list. When asked to 
 * deallocate a object, the allocator package the given pointer to a node 
 * and insert it into the list.
 */

template<typename _Ty>
class Allocator {
public:
    // types required
    typedef _Ty value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template <typename _other>
    struct rebind { typedef Allocator<_other> other; };
    
    // functions
    Allocator();
    Allocator(const Allocator& allocator);
    Allocator(Allocator&& allocator);
    template <typename _other>
    Allocator(const Allocator<_other>& allocator);

    ~Allocator();

    pointer allocate(size_type count);
    void deallocate(pointer ptr, size_type count);

    size_type max_size() const;

    pointer address(reference _Val) const;
    const_pointer address(const_reference _Val) const;

    void construct(pointer _Ptr, const_reference _Val);
    void destory(pointer _Ptr);

protected:
    // this struct store a block of memory
    struct node {
        node(node* next, pointer block, size_type size) {
            this->next = next;
            this->block = block;
            this->size = size;
        };
        node *next;
        pointer block;
        size_type size;
    };

    typedef node *node_pointer;
    size_type m_capacity;  // store the pool capacity
    node_pointer m_free_list_head;
    node_pointer m_free_list_tail;
    node_pointer m_block_list;  // store the head of every blocks allocated by malloc(), use for free()
    node_pointer add_block();   // add a node to free node list
};

template<typename _Ty>
Allocator<_Ty>::~Allocator() {
    node_pointer p = m_block_list;
    while (p != NULL) {
        free(p->block);
        p = p->next;
    }
}

template<typename _Ty>
Allocator<_Ty>::Allocator() {
    // initialize the pool with base size defined 
	this->m_capacity = 0;
	this->m_free_list_head = NULL;
	this->m_free_list_tail = NULL;
    this->m_block_list = NULL;
}

template<typename _Ty>
Allocator<_Ty>::Allocator(const Allocator& allocator) {
	this->m_capacity = 0;
	this->m_free_list_head = NULL;
	this->m_free_list_tail = NULL;
    this->m_block_list = NULL;
}

template<typename _Ty>
Allocator<_Ty>::Allocator(Allocator&& allocator) {
	this->m_capacity = 0;
	this->m_free_list_head = NULL;
	this->m_free_list_tail = NULL;
    this->m_block_list = NULL;
}

template<typename _Ty>
template<typename _other>
Allocator<_Ty>::Allocator(const Allocator<_other>& allocator) {
	this->m_capacity = 0;
	this->m_free_list_head = NULL;
	this->m_free_list_tail = NULL;
    this->m_block_list = NULL;
}


template<typename _Ty> 
typename Allocator<_Ty>::pointer Allocator<_Ty>::allocate(size_type count)
{
	// find a node with enough capacity
    node_pointer pNode = m_free_list_head; 
	while (pNode != NULL && pNode->size < count) {
		pNode = pNode->next;
	}
	if (pNode == NULL) 
		do {
			pNode = add_block();
		} while (pNode->size < count);

	// if larger, reduce the node
	if (pNode->size > count) {
		pNode->size -= count;
		return pNode->block + pNode->size;
	}
	// if equal, delete the node
	else if (pNode->size == count) {
		if (pNode->next == NULL) {
            pointer pObj = pNode->block;
			m_free_list_head = NULL;
			m_free_list_tail = NULL;
            return pObj;
		}
		else {
			m_free_list_head = pNode->next;
			pointer pObj = pNode->block;
			delete pNode;
			return pObj;
		}
	}
	else {
		std::cout << "what fuck?" << std::endl;
		return NULL;
	}
}

template<typename _Ty>
void Allocator<_Ty>::deallocate(pointer ptr, size_type count) {
	// insert the pointer to the list
	if (m_free_list_tail == NULL) {
		m_free_list_head = new node(NULL, ptr, count);
		m_free_list_tail = m_free_list_head;
	}
	else {
		m_free_list_tail->next = new node(NULL, ptr, count);
		m_free_list_tail = m_free_list_tail->next;
	}
}

template<typename _Ty>
typename Allocator<_Ty>::size_type Allocator<_Ty>::max_size() const
{
	// sizeof(size_type)
	return INT64_MAX;
}

template<typename _Ty>
typename Allocator<_Ty>::pointer myAllocator::Allocator<_Ty>::address(reference _Val) const {
	return &_Val;
}

template<typename _Ty>
typename Allocator<_Ty>::const_pointer myAllocator::Allocator<_Ty>::address(const_reference _Val) const {
	return &_Val;
}

template<typename _Ty>
void myAllocator::Allocator<_Ty>::construct(pointer _Ptr, const_reference _Val) {
	new(_Ptr) value_type(_Val);
}

template<typename _Ty>
void myAllocator::Allocator<_Ty>::destory(pointer _Ptr) {
	_Ptr->~value_type();
}

template<typename _Ty>
typename Allocator<_Ty>::node_pointer Allocator<_Ty>::add_block() {
	// get a new block
	if (m_free_list_head == NULL) {
		if (m_capacity == 0) {
			m_capacity = BASEPOOLCOUNT;
		}
		m_free_list_head = new node(NULL, (pointer)malloc(m_capacity * sizeof(value_type)), m_capacity);
		m_free_list_tail = m_free_list_head;
	}
	else {
		m_free_list_tail->next = new node(NULL, (pointer)malloc(m_capacity * sizeof(value_type)), m_capacity);
		m_free_list_tail = m_free_list_tail->next;
	}

	// insert it to the block list for destruction
	if (m_block_list == NULL) {
		m_block_list = new node(NULL, m_free_list_tail->block, m_capacity);
	}
	else {
		m_block_list->next = new node(NULL, m_free_list_tail->block, m_capacity);
		m_block_list = m_block_list->next;
		m_capacity *= 2;
	}
	return m_free_list_tail;
}

}
