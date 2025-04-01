#include <iostream>
#include <stdexcept>
#include "MinHeap.hpp"

int MinHeap::parent(int i)
{
    return (i - 1)/2;
}

int MinHeap::left_child(int i)
{
    return 2 * i + 1;
}


int MinHeap::right_child(int i)
{
    return 2 * i + 2;
}

void MinHeap::bubbleUp(int index)
{
    while (heap_arr[parent(index)] > heap_arr[index] && index > 0)
    {
        std::swap(heap_arr[parent(index)], heap_arr[index]);
        index = parent(index);

    }
}

void MinHeap::bubbleDown(int index)
{
    int smallest = index;
    int left_index = left_child(index);
    int right_index = right_child(index);

    if (left_index < size && heap_arr[left_index] < heap_arr[smallest])
    {
        smallest = left_index;
    }

    if (right_index < size && heap_arr[right_index] < heap_arr[smallest])
    {
        smallest = right_index;
    }

    if (smallest != index)
    {
        std::swap(heap_arr[index], heap_arr[smallest]);
        bubbleDown(smallest);
    }
    
}

void MinHeap::expandHeap()
{
    int newCapacity = capacity * 2;
    int* newArray = nullptr;

    try
    {
        newArray = new int[newCapacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Allocation failed : " << e.what() << std::endl;
        return; // Early exit preventing using an unitialized array. 
    }

    for (int i = 0; i < size; i++)
    {
        newArray[i] = heap_arr[i];
    }
    
    delete[] heap_arr;
    heap_arr = newArray;
    capacity = newCapacity;
    
}

MinHeap::MinHeap(int cap) : capacity(cap), size(0) {
    try
    {
        heap_arr = new int[capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << "Heap allocation failed : " << e.what() << std::endl;
        throw;
    }
    
}

/**
 * @brief Destructor that cleans up the allocated memory.
 */

MinHeap::~MinHeap()
{
    delete[] heap_arr;
}


void MinHeap::insert_new(int key)
{
    if (size == capacity)
    {
        expandHeap();
    }
    heap_arr[size] = key;
    bubbleUp(size);
    size = size + 1;
}

int MinHeap::extractMin()
{
    if (size == 0)
    {
        throw std::length_error("The heap is empty. ");
    }
    
    int root = heap_arr[0];
    heap_arr[0] = heap_arr[size - 1];
    size = size - 1;
    bubbleDown(0);
    return root;

}

int MinHeap::getMin() const {
    if (size == 0)
    {
        throw std::length_error("The heap is empty. ");
    }

    return heap_arr[0];
    
}

int MinHeap::getSize() const {
    return size;
}