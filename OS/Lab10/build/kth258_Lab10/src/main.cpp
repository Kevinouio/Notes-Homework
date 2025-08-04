#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <atomic>
#include <mutex>
#include <utility>
#include <condition_variable>
#include <gmpxx.h>

std::queue<std::pair<int, int>> sharedQueue;
std::mutex mutex;
std::condition_variable cv;
std::atomic<bool> shouldContinue(true);

long long int_power(int base, int exp)
{
    long long result = 1;
    long long max_value = std::numeric_limits<long long>::max();

    while (exp)
    {
        if (exp % 2 == 1)
        {
            if (result > max_value / base)
            { // Check for overflow
                std::cerr << "Overflow detected in power calculation\n";
                return -1; // Indicate overflow
            }
            result *= base;
        }
        if (exp != 1 && base > max_value / base)
        { // Check for overflow on base squaring
            std::cerr << "Overflow detected in power calculation\n";
            return -1; // Indicate overflow
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

/*
 * Function: thread1_task
 * ----------------------
 * Producer function that generates pairs of integers (base, exponent),
 * adds them to a shared queue, and notifies consumers of available data.
 *
 * Pseudocode:
 * 1. For each element in the provided `value` and `power` arrays:
 *    a. Create a delay to simulate processing time.
 *    b. Form a pair (base, exponent) from the current values.
 *    c. Acquire a lock on the shared mutex to ensure exclusive access to the queue.
 *    d. Push the pair into the shared queue.
 *    e. Print a message indicating the produced item.
 *    f. Notify one consumer that a new item is available.
 *    g. The lock is automatically released after this block (RAII).
 *
 * 2. After all items are produced:
 *    a. Set `shouldContinue` to false to signal end of production.
 *    b. Use `cv.notify_all()` to wake up any remaining consumers waiting for items.
 */


void thread1_task()
{
    int value[10] = {32, 45, 78, 90, 123, 150, 175, 200, 210, 212};
    int power[10] = {2, 3, 4, 5, 6, 7, 3, 6, 5, 4};

    // TODO: Implement the pseudocode above.
    for (int i = 0; i < 10; i++)
    {
        // Create a delay to simulate processing time.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Form a pair (base, exponent)
        std::pair<int, int> item(value[i], power[i]);

        // Acquire a lock on the shared mutex to ensure exclusive access to the queue.
        {
            std::lock_guard<std::mutex> lock(mutex);
            sharedQueue.push(item);
            std::cout << "Produced: " << item.first << "^" << item.second << std::endl;
        }
        // Notify one consumer that a new item is available.
        cv.notify_one();
    }

    // After all items are produced, signal end of production.
    shouldContinue = false;
    cv.notify_all();
    
}

bool hasWork()
{
    return !sharedQueue.empty() || !shouldContinue;
}


/*
 * Function: thread2_task
 * @param id: The identifier of the consumer thread.
 * ----------------------
 * Consumer function that retrieves pairs (base, exponent) from a shared queue,
 * computes the power, and displays the result. The function runs until all items
 * are processed and the producer signals completion.
 *
 * Pseudocode:
 * 1. Enter a loop to continually check for available work:
 *    a. Acquire a lock on the shared mutex to ensure exclusive access to the queue.
 *    b. Wait on the condition variable until:
 *       - The queue is not empty, OR
 *       - The `shouldContinue` flag is set to false (indicating end of production).
 *
 * 2. Check the state after waking up:
 *    a. If the queue is empty AND `shouldContinue` is false, break the loop (no more work).
 *    b. Otherwise, if the queue has items:
 *       i.   Retrieve the front item (base, exponent) from the queue.
 *       ii.  Remove the item from the queue.
 *       iii. Compute the power (base^exponent) and handle any overflow.
 *       iv.  Display the result in the format: "Consumed(id: <id>): <base>^<exponent> = <result>"
 *
 * 3. The lock is automatically released after each iteration (RAII).
 * 4. The loop terminates once all items are processed and production is complete.
 */
void thread2_task(int id)
{
   // TODO: Implement the pseudocode above.
    while (true)
        {
            std::unique_lock<std::mutex> lock(mutex);
            // Wait until the queue is not empty or production has ended.
            cv.wait(lock, []() { return !sharedQueue.empty() || !shouldContinue; });

            // If the queue is empty and production has ended, break out of the loop.
            if (sharedQueue.empty() && !shouldContinue)
            {
                break;
            }

            // If there is an item, process it.
            if (!sharedQueue.empty())
            {
                auto item = sharedQueue.front();
                sharedQueue.pop();
                // Release lock before doing heavy computation.
                lock.unlock();

                // Compute the power.
                long long result = int_power(item.first, item.second);

                // Display the result.
                std::cout << "Consumed(id: " << id << "): "
                          << item.first << "^" << item.second << " = " << result << std::endl;
            }
        }

}

int main()
{
    // Create and launch the producer and consumer threads
    std::thread producer(thread1_task);
    std::thread consumer1(thread2_task, 1);
    std::thread consumer2(thread2_task, 2);

    // Wait for the producer thread to finish and join with the consumer thread
    producer.join();
    consumer1.join();
    consumer2.join();

    return 0;
}
