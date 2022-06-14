#include <iostream>
#include <stdlib.h>
#define BASEPOOLCOUNT 16ULL

/* Implementation of Memory Pool
 * Maintain a internal linked list to store a series of memory blocks inscresing 
 * in capacity providing available memory. Each block contains a linked list which
 * trace the memory already allocated, a node pointer to free memory.
 * When an allocation required, the pool traverse the free node list to check
 * whether there are enough memory in certain block, return the node pointer if 
 * found or use malloc() two times as large as the max size of maintained blocks, 
 * then check the capacity again. If required memory is larger than 64kb, just use
 * malloc() to allocate the memory and package it into a node.
 */

template<typename value_type>
class Allocator {
public:
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    
    // these types works for memory pool
    struct node {
        node *next;
        pointer lump;
        size_t size;
        // TODO
    };
    typedef node *node_pointer;
    struct block {
        block *next;
        node_pointer node_head;
        node_pointer free_node;
    };
    typedef block *block_pointer;

    // core function
    pointer allocate(size_t count);
    void deallocate(pointer ptr, size_t count);

    // construct/destruct object with arguments
    template<typename Objty, typename ...Types>
    void construct(Objty *ptr, Types&& ...args);
    template<typename Uty> void destroy(Uty *ptr);

    Allocator();
    ~Allocator();
    pointer address(reference val) const;
    const_pointer address(const_reference val) const;

protected:
    block_pointer m_block_head;
    int m_block_number;
    size_t m_block_capacity;
    size_t m_base_size;

    // this function is used to add a block to list when memory not enough
    block_pointer add_block(void);
    pointer push_node(block_pointer block, size_t count);
};