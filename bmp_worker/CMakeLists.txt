add_library(bmp_worker
        bmp_reader.cpp
        bmp_reader.h
        bmp_writer.cpp
        bmp_writer.h
        bmp.cpp
        bmp.h
)
target_include_directories(bmp_worker PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(image_processor::bmp_worker ALIAS bmp_worker)
target_compile_features(bmp_worker PUBLIC cxx_std_20)