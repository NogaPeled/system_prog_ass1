#pragma once
#include <iostream>
#include <stdexcept>

/**
 * @class MinHeap
 * @brief Implements a minimum heap for integers.
 *
 * A MinHeap maintains elements in such a way that the smallest element is always the root.
 * This implementation dynamically expands as more elements are added.
 */

class MinHeap {

    private:
    
    int* heap_arr; // Array to store the heap elements
    int capacity; // The capacity of heap_arr
    int size; // Current amount of elements in the heap

    /**
     * @brief Calculates the parent index of a given index.
     * @param i The index of which to find the parent.
     * @return The index of the parent.
     */

    int parent(int i);

    /**
     * @brief Calculates the left child index of a given index.
     * @param i The index of which to find the left child.
     * @return The index of the left child.
     */

    int left_child(int i);
    
    /**
     * @brief Calculates the right child index of a given index.
     * @param i The index of which to find the right child.
     * @return The index of the right child.
     */

    int right_child(int i);

    /**
     * @brief Moves the element at the given index up to its correct position in the heap.
     * @param index The starting index.
     * @note Complexity: O(log n)
     */

    void bubbleUp(int index);

    /**
     * @brief Moves the element at the given index down to its correct position in the heap.
     * @param index The starting index.
     * @note Complexity: O(log n)
     */

    void bubbleDown(int index);

    /**
     * @brief Doubles the capacity of the heap when it is full.
     * @throws std::bad_alloc if memory allocation fails.
     * @note Ensures strong exception safety.
     */

    void expandHeap();

    public:

    /**
     * @brief Constructs a new MinHeap with a given initial capacity.
     * @param cap The initial capacity of the heap.
     * @throws std::bad_alloc if memory allocation fails.
     */

    MinHeap(int cap);

    /**
     * @brief Destructor that cleans up the allocated memory.
     */

    ~MinHeap();

    /**
     * @brief Inserts a new integer into the heap.
     * @param key The integer to insert.
     */

    void insert_new(int key);

    /**
     * @brief Extracts and returns the smallest element from the heap.
     * @return The smallest element in the heap.
     * @throws std::length_error If the heap is empty.
     */

    int extractMin();

    /**
     * @brief Gets the smallest element without removing it.
     * @return The smallest element in the heap.
     * @throws std::length_error If the heap is empty.
     */

    int getMin() const;

    /**
     * @brief Returns the number of elements in the heap.
     * @return The size of the heap.
     */

    int getSize() const;

};