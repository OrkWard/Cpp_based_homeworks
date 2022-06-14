#include "Allocator.h"

template<typename value_type>
Allocator<value_type>::Allocator(): m_block_number(1) {
    // initialize the pool with base size defined 
    m_base_size = BASEPOOLCOUNT * sizeof(value_type);
    m_block_capacity = BASEPOOLCOUNT;
    m_block_head = new block(
        NULL, NULL, new node(NULL, malloc(m_base_size), BASEPOOLCOUNT));
}

template<typename value_type>
Allocator<value_type>::~Allocator() {

}

template<typename value_type>
Allocator<value_type>::pointer Allocator<value_type>::allocate(size_t count) {
    block_pointer head = m_block_head;
    // scan the free node list, pick a piece of memory if found a block with 
    // enough space
    while(head != NULL) {
        if (count <= head->free_node->size) 
            return push_node(head, count);
        else
            head = head->next;
    }

    // add block till the capacity large enough to cover the required size
    do {
        head = add_block();
    } while(count > m_block_capacity);
    return push_node(head, count);
}

template<typename value_type>
template<typename Objty, typename ...Types>
void Allocator<value_type>::construct(Objty *ptr, Types&& ...args) {

}

template<typename value_type>
template<typename Uty>
void Allocator<value_type>::destroy(Uty *ptr) {

}

template<typename value_type>
void Allocator<value_type>::deallocate(pointer ptr, size_t count) {
    // don't do anything
    return;
}

template<typename value_type>
Allocator<value_type>::pointer Allocator<value_type>::address(reference value) const {

}

template<typename value_type>
Allocator<value_type>::const_pointer Allocator<value_type>::address(const_reference value) const {

}

template<typename value_type>
Allocator<value_type>::block_pointer Allocator<value_type>::add_block(void) {
    // update the information
    m_block_capacity *= 2;
    ++m_block_number;

    block_pointer head = m_block_head;
    while(head->next != NULL)
        head = head->next;
    head->next = new block(
        NULL, NULL, new node(NULL, malloc(m_block_capacity * sizeof(value_type)), m_block_capacity));
    return head->next;
}

template<typename value_type>
Allocator<value_type>::pointer Allocator<value_type>::push_node(block_pointer block, size_t count) {
    node_pointer head = block->node_head;
    // case that no space allocated in this block
    if (head == NULL) {
        block->node_head = new node(NULL, block->free_node->lump, count);
        head = block->node_head;
    }
    else {
        // insert new node at the tail
        while(head->next != NULL)
            head = head->next;
        head->next = new node(NULL, block->free_node->lump, count);
        head = head->next;
    }
    // decrease the size of free node
    block->free_node->lump = head->lump + head->size;
    block->free_node->size -= count;
    return head->lump;
}