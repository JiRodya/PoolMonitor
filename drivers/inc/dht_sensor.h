#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <stdint.h>         // for uint32_tß
#include "driver/gpio.h"    // for gpio_num_t
#include <cmath>            // for NAN

class DHTSensor {

public:
    // ========= Non-blocking API =========
    // Starts temperature read sequence (returns false if busy)
    bool requestTemperature();  
    bool requestHumidity();    

    // Call periodically (or from timer/task) to advance FSM
    void tick();                    

    // Check if reading is ready
    bool hasTemperature();  
    bool hasHumidity();       

    // Get temperature after ready (returns NAN if invalid)
    float getTemperature();    
    float getHumidity();    

    // ========= Blocking API =========
    // Full read (blocking); returns NAN on error
    float readTemperature(); 
    float readHumidity();      

private:
    enum class State {
        INIT,
        READY,
        RESET_SIGNAL,
        WAIT_PRESENCE,
        WRITE_CMD,
        WAIT_ANSWER,
        DECODE_ANSWER,
        ERROR
    };

    State _state = State::READY;
    gpio_num_t _pin;

    // Timers, raw data buffer, result, etc.
    uint32_t _timer_ms = 0;
    float _temp = NAN;
    bool _valid = false;
};

class DHT11 : public DHTSensor {
    // DHT11 specific implementation
    // ...
};

class DHT22 : public DHTSensor {
    // DHT22 specific implementation
    // ...
public:
    DHT22(gpio_num_t pin);

 
    // ...
};


#endif // DHT_SENSOR_H
