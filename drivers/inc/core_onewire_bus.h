#pragma once

// Standard C++ headers
#include <vector>
#include <unordered_map>
#include <cstdint>

// ESP-IDF headers
#include "driver/gpio.h"

/**
 * @class OneWireBus
 * @brief Implements the OneWire protocol for communication with OneWire devices (e.g., DS18B20).
 *
 * This class provides functions to reset the OneWire bus, send and receive data, and manage ROM addressing.
 * It follows the OneWire protocol and allows communication with single or multiple devices.
 */
class OneWireBus {
public:
    /**
     * @brief Get an instance of the OneWireBus for a specific GPIO pin (Singleton).
     *
     * Ensures only one instance per GPIO pin to avoid conflicts.
     * @param pin The GPIO pin used for the OneWire bus.
     * @return A reference to the OneWireBus instance.
     */
    static OneWireBus& get_instance(gpio_num_t pin);

    /**
     * @brief Resets the OneWire bus and detects device presence.
     *
     * The master sends a reset pulse, and devices respond with a presence pulse.
     * @return True if at least one device is present, false otherwise.
     */
    bool reset();

    /**
     * @brief Writes a single bit to the OneWire bus.
     *
     * @param bit The bit to write (true = 1, false = 0).
     */
    void write_bit(bool bit);

    /**
     * @brief Reads a single bit from the OneWire bus.
     *
     * @return The bit read (true = 1, false = 0).
     */
    bool read_bit();

    /**
     * @brief Writes a full byte (8 bits) to the OneWire bus.
     *
     * @param data The byte to write.
     * @return True if the operation is successful.
     */
    bool write_byte(uint8_t data);

    /**
     * @brief Reads a full byte (8 bits) from the OneWire bus.
     *
     * @return The byte read from the bus.
     */
    uint8_t read_byte();

    /**
     * @brief Reads the unique 64-bit ROM ID of a connected OneWire device.
     *
     * This is only valid for single-device configurations.
     * @param rom_id Reference to store the 64-bit ROM ID.
     * @return True if successful, false if no device is detected.
     */
    bool read_rom(uint64_t& rom_id);

    /**
     * @brief Selects a specific device using its 64-bit ROM ID.
     *
     * This is required when multiple devices are connected to the same bus.
     * @param rom_id The 64-bit ROM ID of the target device.
     * @return True if successful, false otherwise.
     */
    bool match_rom(uint64_t rom_id);

    /**
     * @brief Sends a "Skip ROM" command to address all devices on the OneWire bus.
     *
     * This is only recommended when there's exactly one device connected.
     * @return True if successful.
     */
    bool skip_rom();

    /**
     * @brief Searches for all connected OneWire devices and retrieves their ROM IDs.
     *
     * @param device_list Vector to store detected device ROM IDs.
     * @return True if at least one device was found, false otherwise.
     */
    bool search_devices(std::vector<uint64_t>& device_list);

    /**
     * @brief Enables or disables strong pull-up for parasitic power mode.
     *
     * Some OneWire devices (e.g., DS18B20) require strong pull-up during conversions.
     * @param enable Set to true to enable strong pull-up, false to disable.
     */
    void power_strong_pullup(bool enable);

private:
    /**
     * @brief Private constructor (Singleton pattern).
     * @param pin The GPIO pin used for the OneWire bus.
     */
    explicit OneWireBus(gpio_num_t pin);
    static constexpr char* TAG = "OneWireBus";  ///< Tag for logging purposes.

    /**
     * @brief Destructor (not used, as Singleton instances persist).
     */
    ~OneWireBus() = default;

    gpio_num_t _pin;  ///< The GPIO pin used for OneWire communication.

    /**
     * @brief Static map to track instances of OneWireBus per GPIO pin.
     */
    static std::unordered_map<gpio_num_t, OneWireBus*> instances;

    /// OneWire ROM command set (Defined by Dallas Semiconductor)
    static constexpr uint8_t READ_ROM   = 0x33;  ///< Command to read the ROM ID of a device.
    static constexpr uint8_t MATCH_ROM  = 0x55;  ///< Command to select a specific device.
    static constexpr uint8_t SEARCH_ROM = 0xF0;  ///< Command to search for all connected devices.
    static constexpr uint8_t SKIP_ROM   = 0xCC;  ///< Command to address all devices without selecting one.
};