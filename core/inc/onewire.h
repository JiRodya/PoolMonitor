#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <stdint.h>         // for uint32_t
#include "driver/gpio.h"    // for gpio_num_t
#include <cmath>            // for NAN
#include <vector>

#define ONEWIRE(pin) (*OneWire::getInstance(pin))
#define ONEWIRE_WITH_PIN(pin,rom_id) (*OneWire::getInstance(pin,rom_id))


class OneWire {

public:
    static OneWire* getInstance(gpio_num_t pin);
    static OneWire* getInstance(gpio_num_t pin, uint64_t rom_id);

    gpio_num_t getPin() const;
    uint64_t getROM() const;
private:
    gpio_num_t _pin;
    uint64_t _rom = 0;
    static inline std::vector<OneWire*> _instances = {};

    OneWire(gpio_num_t pin);   
    OneWire(gpio_num_t pin, uint64_t rom_id);
    ~OneWire();

};

#endif // ONEWIRE_H