#include "onewire.h"
#include "esp_log.h"

OneWire* OneWire::getInstance(gpio_num_t pin, uint64_t rom_id) {
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


OneWire* OneWire::getInstance(gpio_num_t pin) {
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

