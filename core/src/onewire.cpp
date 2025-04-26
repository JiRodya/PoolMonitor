#include "onewire.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


OneWire* OneWire::Get(gpio_num_t pin, uint64_t rom_id) {
    // If the exact (pin + rom) instance exists, reuse it
    for (auto* inst : _instances) {
        if (inst->_pin == pin && inst->_rom == rom_id)
            return inst;
    }

    // Else, create a new instance (ROM-aware)
    auto* newInst = new OneWire(pin, rom_id);
    _instances.push_back(newInst);
    return newInst;
}


OneWire* OneWire::Get(gpio_num_t pin) {
    for (auto* inst : _instances) {
        if (inst->_pin == pin) {
            if (inst->_rom == 0) return inst;  // Exact match
            ESP_LOGE("OneWire", "GPIO already in use by ROM-aware device");
            return nullptr; // TODO: handle

        }
    }

    auto* newInst = new OneWire(pin);
    _instances.push_back(newInst);
    return newInst;
}

void OneWire::writeBit(bool bit) {
    gpio_set_direction(_pin, GPIO_MODE_OUTPUT);

    if (bit) {
        // Write '1' bit
        gpio_set_level(_pin, 0);
        esp_rom_delay_us(6);      // Pull low for 6 us
        gpio_set_level(_pin, 1);
        esp_rom_delay_us(64);     // Release line and wait for rest of the timeslot
    } else {
        // Write '0' bit
        gpio_set_level(_pin, 0);
        esp_rom_delay_us(60);     // Pull low for 60 us
        gpio_set_level(_pin, 1);
        esp_rom_delay_us(10);     // Release line
    }
}

uint8_t OneWire::readBit(){
    gpio_set_direction(_pin, GPIO_MODE_OUTPUT);

    // Write '0' bit for 1-15 us to start the read
    gpio_set_level(_pin, 0);
    esp_rom_delay_us(6);

    gpio_set_direction(_pin, GPIO_MODE_INPUT);
    // slave sending '1' -> do nothing, bus goes to pull-up
    // slave sending '0' -> bus goes low for 60 us
    esp_rom_delay_us(15); // wait 15 us
    uint8_t bit = gpio_get_level(_pin);
    esp_rom_delay_us(45); // wait 45 us
    return bit;
}

void OneWire::writeByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        bool bit = byte & 0x01;    // Get the least significant bit (LSB)
        writeBit(bit);             // Write that bit
        byte >>= 1;                // Shift right to get the next bit
    }
}

uint8_t OneWire::readByte() {
    uint8_t value = 0;
    for (int i = 0; i < 8; i++) {
        if (readBit()) {
            value |= (1 << i); // Set the i-th bit if readBit() returned 1
        }
    }
    return value;
}