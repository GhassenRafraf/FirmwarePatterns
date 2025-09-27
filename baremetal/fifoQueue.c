//
// A simple FIFO queue implementation in C for bare-metal systems.
//

#include <stdint.h>

#define QUEUE_SIZE 16
typedef struct {
    uint16_t data[QUEUE_SIZE];
    uint8_t head, tail, count;
} Queue;

Queue queue;
void init_queue(void) {
    queue.head = 0;
    queue.tail = 0;
    queue.count = 0;
}
uint8_t is_full(void) {
    return queue.count == QUEUE_SIZE;
}
uint8_t is_empty(void) {
    return queue.count == 0;
}
void enqueue(uint16_t value) {
    if (!is_full()) {
        queue.data[queue.head] = value;
        queue.head = (queue.head + 1) % QUEUE_SIZE;
        queue.count++;
    }
}
uint8_t dequeue(uint16_t* value) {
    if (!is_empty()) {
        *value = queue.data[queue.tail];
        queue.tail = (queue.tail + 1) % QUEUE_SIZE;
        queue.count--;
        return 1;
    }
    return 0;
}
int main(void) {
    init_queue();
    enqueue(50);
    uint16_t value;
    dequeue(&value);
    // Use value
    return 0;
}