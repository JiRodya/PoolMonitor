#include "core_onewire_bus.h"   
#include <esp_timer.h> // for precise delay
#include "esp_log.h"


std::unordered_map<gpio_num_t, OneWireBus*> OneWireBus::instances = {};

OneWireBus& OneWireBus::get_instance(gpio_num_t pin)
{
    if (instances.find(pin) == instances.end()) 
    {
        instances[pin] = new OneWireBus(pin);
    }
    return *instances[pin];
}