//
// A simple ring buffer implementation for embedded systems in C.

#include <stdint.h>

#define BUFFER_SIZE 16

typedef struct {
    uint16_t data[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} RingBuffer;

RingBuffer buffer;

void init_buffer(void) {
    buffer.head = 0;
    buffer.tail = 0;
}

uint8_t is_full(void) {
    return (buffer.head + 1) % BUFFER_SIZE == buffer.tail;
}

uint8_t is_empty(void) {
    return buffer.head == buffer.tail;
}

void push(uint16_t value) {
    if (!is_full()) {
        buffer.data[buffer.head] = value;
        buffer.head = (buffer.head + 1) % BUFFER_SIZE;
    }
}
uint8_t pop(uint16_t* value) {
    if (!is_empty()) {
        *value = buffer.data[buffer.tail];
        buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;
        return 1;
    }
    return 0;
}
int main(void) {
    init_buffer();
    push(50);
    uint16_t value;
    if (pop(&value)) {
        // Use value
    }
    return 0;
}