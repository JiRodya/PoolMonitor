set(SOURCE_FILES
    "src/app_pool.cpp"
    "src/app_timer_main.cpp"
    "src/app_cli_main.cpp"
)


idf_component_register(
    SRCS "${SOURCE_FILES}"
    INCLUDE_DIRS "inc"
)
