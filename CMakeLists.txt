cmake_minimum_required(VERSION 3.27)
project(native-code C)

set(CMAKE_C_STANDARD 23)

function(add TARGET)
    add_executable(${TARGET} ${ARGN})
    target_compile_options(${TARGET} PRIVATE -save-temps)
endfunction()

add(asm asm.c)
add(factorial factorial.c)
target_link_libraries(factorial PRIVATE gmp)
add(memory memory.c)
add(swap swap.c)
