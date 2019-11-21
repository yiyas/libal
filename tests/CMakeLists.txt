file(GLOB test_srcs *.c)

set(TEST_DEP_LIBS pthread)
if(ENABLE_GCOV)
    set(TEST_DEP_LIBS gcov)
endif(ENABLE_GCOV)

function(create_test)
    cmake_parse_arguments(TEST "" "NAME" "SRCS" ${ARGN})
    add_executable(${TEST_NAME} "${TEST_NAME}.c" unity/unity.c ${TEST_SRCS})
    target_link_libraries(${TEST_NAME} ${TEST_DEP_LIBS})
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}> WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    list(APPEND all_tests ${TEST_NAME})
    set(all_tests ${all_tests} PARENT_SCOPE)
endfunction(create_test)

create_test(NAME test_linked_list SRCS ../src/linked_list.c)

message("ALL TESTS: ${all_tests}")

find_program(VALGRIND_FOUND valgrind)
if(ENABLE_VALGRIND_TESTS)
    if(VALGRIND_FOUND)
        foreach(test_name IN LISTS all_tests)
            add_test(${test_name}_valgrind valgrind 
                --error-exitcode=1 
                --leak-check=full 
                --show-leak-kinds=all 
                --errors-for-leak-kinds=all
                ${CMAKE_BINARY_DIR}/tests/${test_name})
        endforeach(test_name)
    else(VALGRIND_FOUND)
        message(WARNING "valgrind executable not found! Disabling memory leaks tests.")
    endif(VALGRIND_FOUND)
endif(ENABLE_VALGRIND_TESTS)
