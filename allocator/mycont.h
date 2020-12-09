#pragma once

#include <memory>

template<typename T, typename Allocator = std::allocator<T>>
class MyCont {
    struct node {
        node* next;
        T* valPtr;
    };
    node* head, * tail;
    static inline std::allocator_traits<Allocator> dataAllocTraits;
    static inline Allocator dataAlloc;
    static inline typename std::allocator_traits<Allocator>:: template rebind_traits< node > nodeAllocTraits;
    static inline typename std::allocator_traits<Allocator>:: template rebind_alloc< node > nodeAlloc;   

public:
    MyCont();
    ~MyCont();

    class Iterator {
        node nd;
    public:
        Iterator();
        Iterator(const node& _nd);
        T& operator*() const;
        Iterator& operator++();
        bool operator==(const Iterator& rhv) const;
        bool operator!=(const Iterator& rhv) const;
    };

    Iterator begin() const;
    Iterator end() const;
    void push(T val);
};


template<typename T, typename Allocator>
MyCont<T, Allocator>::MyCont() :head(nullptr), tail(nullptr) {}


template<typename T, typename Allocator>
MyCont<T, Allocator>::~MyCont() {
    node* p = head;
    while (p) {
        node* next = p->next;
        dataAllocTraits.destroy(dataAlloc, p->valPtr);
        dataAllocTraits.deallocate(dataAlloc, p->valPtr, 1);
        nodeAllocTraits.deallocate(nodeAlloc, p, 1);
        p = next;
    }
}

template<typename T, typename Allocator>
void MyCont<T, Allocator>::push(T val) {
    node* new_nd = nodeAllocTraits.allocate(nodeAlloc, 1);
    new_nd->next = nullptr;
    new_nd->valPtr = dataAllocTraits.allocate(dataAlloc, 1);
    dataAllocTraits.construct(dataAlloc, new_nd->valPtr, std::forward<T>(val));
    if (tail != nullptr) {
        tail->next = new_nd;
        tail = new_nd;
    }
    else {
        tail = head = new_nd;
    }
}


template<typename T, typename Allocator>
typename MyCont<T, Allocator>::Iterator MyCont<T, Allocator>::begin() const {
    return (head == nullptr) ? Iterator(node{}) : Iterator(*head);
}


template<typename T, typename Allocator>
typename MyCont<T, Allocator>::Iterator MyCont<T, Allocator>::end() const {
    return Iterator(node{});
}

// MyCont::Iteraror

template<typename T, typename Allocator>
MyCont<T, Allocator>::Iterator::Iterator() :nd(nullptr) {}


template<typename T, typename Allocator>
MyCont<T, Allocator>::Iterator::Iterator(const node& _nd) : nd(_nd) {}


template<typename T, typename Allocator>
bool MyCont<T, Allocator>::Iterator::operator==(const Iterator& rhv) const {
    return this->nd.valPtr == rhv.valPtr;
}


template<typename T, typename Allocator>
bool MyCont<T, Allocator>::Iterator::operator!=(const Iterator& rhv) const {
    return this->nd.valPtr != rhv.nd.valPtr;
}


template<typename T, typename Allocator>
T& MyCont<T, Allocator>::Iterator::operator*() const {
    return *nd.valPtr;
}

template<typename T, typename Allocator>
typename MyCont<T, Allocator>::Iterator& MyCont<T, Allocator>::Iterator::operator++() {
    if (nd.next != nullptr) {
        nd = *nd.next;
    }
    else {
        nd = node{};
    }
    return *this;
}
