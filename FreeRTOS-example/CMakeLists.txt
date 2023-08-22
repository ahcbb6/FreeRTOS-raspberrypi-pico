add_executable(FreeRTOS-example
  main.c
)

# pull in common dependencies
target_link_libraries(FreeRTOS-example pico_stdlib FreeRTOS)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(FreeRTOS-example)
