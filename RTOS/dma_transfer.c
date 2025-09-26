// dma_transfer.c
// Implementation of a thread-safe circular buffer for DMA transfers in an RTOS environment
// using FreeRTOS for synchronization.


#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <semphr.h>

#define BUFFER_SIZE 256

typedef struct {
    uint8_t data[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    SemaphoreHandle_t mutex;
} circular_buffer_t;

void buffer_init(circular_buffer_t *buf) {
    buf->head = 0;
    buf->tail = 0;
    buf->mutex = xSemaphoreCreateMutex();
}
bool buffer_enqueue(circular_buffer_t *buf, const uint8_t *data, uint32_t len) {
        if (xSemaphoreTake(buf->mutex, portMAX_DELAY) == pdTRUE) {
            uint32_t space = (buf->tail + BUFFER_SIZE - buf->head - 1) % BUFFER_SIZE;
            if (len <= space) {
                for (uint32_t i = 0; i < len; i++) {
                buf->data[buf->head] = data[i];
                buf->head = (buf->head + 1) % BUFFER_SIZE;
            }
            xSemaphoreGive(buf->mutex);
                return true;
        }
        xSemaphoreGive(buf->mutex);
            return false;
    }
        return false;
}
bool buffer_dequeue(circular_buffer_t *buf, uint8_t *data, uint32_t len) {
        if (xSemaphoreTake(buf->mutex, portMAX_DELAY) == pdTRUE) {
            uint32_t available = (buf->head + BUFFER_SIZE - buf->tail) % BUFFER_SIZE;
            if (len <= available) {
                for (uint32_t i = 0; i < len; i++) {
                    data[i] = buf->data[buf->tail];
                    buf->tail = (buf->tail + 1) % BUFFER_SIZE;
            }
            xSemaphoreGive(buf->mutex);
                return true;
        }
        xSemaphoreGive(buf->mutex);
            return false;
    }
        return false;
}