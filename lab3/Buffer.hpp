#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <mutex>
#include <condition_variable>
#include <stack>

#define BUFFER_CAPACITY 10 
#define CONSUMER_MAX_WAIT_TIME 300

template <class T>
class Buffer {
    // Buffer fields
    T buffer [BUFFER_CAPACITY];
    int buffer_size;
    int left; // index where variables are put inside of buffer (produced)
    int right; // index where variables are removed from buffer (consumed)
    
    // Fields for concurrency
    std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;
   
    
public:

    int getSize() const{
        return buffer_size;
    }
    // Place integer inside of buffer
    void produce(int thread_id, T num) {
        // Acquire a unique lock on the mutex
        std::unique_lock<std::mutex> unique_lock(mtx);
        
        //std::cout << "thread " << thread_id << " produced " << num << "\n";
        
        // Wait if the buffer is full
        not_full.wait(unique_lock, [this]() {
            return buffer_size != BUFFER_CAPACITY;
        });
        
        // Add input to buffer
        buffer[right] = num;
        //std::cout<<num.getPathToImage()<<std::endl;
        // Update appropriate fields
        right = (right + 1) % BUFFER_CAPACITY;
        buffer_size++;
        
        // Unlock unique lock
        unique_lock.unlock();
        
        // Notify a single thread that buffer isn't empty
        not_empty.notify_one();
    }
        
        // Remove integer from buffer
    T consume(int thread_id) {
        // Acquire a unique lock on the mutex
        std::unique_lock<std::mutex> unique_lock(mtx);
        
        // Wait if buffer is empty
         if(not_empty.wait_for(unique_lock, std::chrono::milliseconds(CONSUMER_MAX_WAIT_TIME), [this]() {
            return buffer_size != 0;
        }));
        
        // Get value from position to remove in buffer
        T result = buffer[left];
        
        //std::cout << "thread " << thread_id << " consumed " << result << "\n";
        
        // Update appropriate fields
        left = (left + 1) % BUFFER_CAPACITY;
        buffer_size--;
        
        // Unlock unique lock
        unique_lock.unlock();
        
        // Notify a single thread that the buffer isn't full
        not_full.notify_one();
        
        // Return result
        return result;
    }
    
    Buffer(): left(), right(), buffer_size(){}
};

#endif