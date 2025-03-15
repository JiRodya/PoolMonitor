set(SOURCE_FILES
    "src/chlorine_sensor.cpp"
    "src/dht_sensor.cpp"
    "src/ph_sensor.cpp"
    "src/tds_sensor.cpp"
    "src/turbidity_sensor.cpp" 
    "src/core_onewire_bus.cpp"
)

idf_component_register(
    SRCS ${SOURCE_FILES}
    INCLUDE_DIRS "inc"
    REQUIRES esp_driver_gpio esp_timer
)
