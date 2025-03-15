#include "core_onewire_bus.h"   
#include <esp_timer.h> // for precise delay


std::unordered_map<gpio_num_t, OneWireBus*> OneWireBus::instances = {};