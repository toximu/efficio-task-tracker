cmake_minimum_required(VERSION 3.10)

project(project-storage-model)

file(GLOB PSMODEL_SRC "src/*")

add_library(${PROJECT_NAME} ${PSMODEL_SRC})

message(${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)