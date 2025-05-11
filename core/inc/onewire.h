#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <stdint.h>         // for uint32_t
#include "driver/gpio.h"    // for gpio_num_t
#include <cmath>            // for NAN
#include <vector>

#define ONEWIRE(pin) (*OneWire::Get(pin))
#define ONEWIRE_WITH_PIN(pin,rom_id) (*OneWire::Get(pin,rom_id))


namespace PM 
{
    class OneWire {

    public:
        void init();
        static OneWire* Get(gpio_num_t pin);
        static OneWire* Get(gpio_num_t pin, uint64_t rom_id);

        gpio_num_t getPin() const;
        uint64_t getROM() const;
        bool reset();
        void writeBit (bool bit);
        void writeByte(uint8_t byte);
        uint8_t readBit();
        uint8_t readByte();
    private:
        gpio_num_t _pin;
        uint64_t _rom = 0;
        static inline std::vector<OneWire*> _instances = {};

        explicit OneWire(gpio_num_t pin);
        explicit OneWire(gpio_num_t pin, uint64_t rom_id);
        ~OneWire();

    };

    #endif // ONEWIRE_H
}