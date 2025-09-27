//
// Simple push button debounce implementation for a bare-metal embedded system.

#include <stdint.h>

uint8_t read_button(void) { /* Hardware-specific */ return 0; }
volatile uint8_t last_state, current_state, counter;

void init_debounce(void) {
    last_state = read_button();
    current_state = last_state;
    counter = 0;
}

uint8_t debounce_button(void) {
    uint8_t state = read_button();
    if (state == last_state) {
        counter++;
        if (counter >= 2) {
            current_state = state;
            counter = 2;
        }
    } else {
        last_state = state;
        counter = 0;
    }
    return current_state;
}

void timer_isr(void) {
    debounce_button();
}

int main(void) {
    init_debounce();
    while (1) {
        // Check current_state
    }
    return 0;
}