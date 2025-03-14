idf_component_register(SRCS "hello_world_main.cpp"
                    PRIV_REQUIRES spi_flash
                    REQUIRES application drivers
                    INCLUDE_DIRS ".")
