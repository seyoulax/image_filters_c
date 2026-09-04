set(CMAKE_CXX_STANDARD 17)
project(image_processor)

add_executable(
    image_processor
    image_processor.cpp
        app.cpp
        app.h
        error_handlers.cpp
        error_handlers.h
)

add_subdirectory(parser)
add_subdirectory(bmp_worker)
add_subdirectory(filters_logic)
add_subdirectory(filters_logic/filters)

target_link_libraries(image_processor
    PRIVATE
    image_processor::parser
    image_processor::bmp_worker
    image_processor::filters
    image_processor::filters_logic
)