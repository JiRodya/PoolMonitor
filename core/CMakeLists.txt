set(SOURCE_FILES
    "src/onewire.cpp"
)

idf_component_register(
    SRCS "${SOURCE_FILES}"
    INCLUDE_DIRS "inc"
    REQUIRES driver
)
