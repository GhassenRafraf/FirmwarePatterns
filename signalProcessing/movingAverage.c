//
// Moving Average Filter for ADC readings
//

#include <stdint.h>
#define WINDOW_SIZE 8

typedef struct {
    uint16_t data[WINDOW_SIZE];
    uint8_t head;
    uint32_t sum;
} MovingAvg;
MovingAvg avg;
uint16_t read_adc(void) { return 0; } // mock function
void init_moving_avg(void) {
    avg.head = 0;
    avg.sum = 0;
    for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
        avg.data[i] = 0;
    }
}
float update_moving_avg(uint16_t new_sample) {
    avg.sum -= avg.data[avg.head];
    avg.data[avg.head] = new_sample;
    avg.sum += new_sample;
    avg.head = (avg.head + 1) % WINDOW_SIZE;
    return (float)avg.sum / WINDOW_SIZE;
}
int main(void) {
    init_moving_avg();
    while (1) {
        uint16_t sample = read_adc();
        float result = update_moving_avg(sample);
        // Use result
    }
    return 0;
}