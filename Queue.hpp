#pragma once

/**
 * @brief A fixed-size circular queue implementation using an array.
 * 
 * Supports enqueue, dequeue, peek, and utility methods to check state.
 * Used primarily in BFS traversal.
 */

class Queue {

    private:

    int* array; // Pointer to the array storing queue elements. 
    int capacity; // Maximum number of elements the queue can hold.
    int front; // Index of the front (head) of the queue. 
    int rear; // Index of the rear (tail) of the queue. 
    int count; // Current number of elements in the queue.

    public:

    /**
     * @brief Constructs a queue with the given capacity.
     * @param size The maximum number of elements the queue can hold.
     */

    Queue(int size);

    /**
     * @brief Destructor. Frees the allocated array memory.
     */

    ~Queue();

    /**
     * @brief Adds an item to the rear of the queue.
     * @param item The item to add.
     * @throws std::overflow_error if the queue is full.
     */

    void enqueue(int item);

    /**
     * @brief Removes and returns the item at the front of the queue.
     * @return The item at the front.
     * @throws std::underflow_error if the queue is empty.
     */

    int dequeue();

    /**
     * @brief Returns the item at the front without removing it.
     * @return The front item.
     * @throws std::underflow_error if the queue is empty.
     */

    int peek() const;

    /**
     * @brief Checks if the queue is full.
     * @return true if the queue is full, false otherwise.
     */

    bool isFull() const;

    /**
     * @brief Checks if the queue is empty.
     * @return true if the queue is empty, false otherwise.
     */

    bool isEmpty() const;

    /**
     * @brief Returns the capacity of the queue.
     * @return The maximum number of elements the queue can hold.
     */
    
    int cap() const;    

};
