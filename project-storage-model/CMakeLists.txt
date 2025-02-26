cmake_minimum_required(VERSION 3.10)

# Укажите название проекта
project(MyProject)

# Найдите пакет protobuf (для CMake)
find_package(Protobuf REQUIRED)

# Укажите путь к вашим .proto файлам
set(PROTO_FILES
    note.proto
    project.proto
    storage.proto
    user.proto
)

# Сгенерируйте C++ исходники из .proto файлов
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Укажите исходники вашего проекта
set(SOURCES
    main.cpp
    ${PROTO_SRCS}
)

# Укажите директории для заголовочных файлов
include_directories(${Protobuf_INCLUDE_DIRS})

# Добавьте исполнимый файл
add_executable(MyProject ${SOURCES})

# Линкуем с библиотеками protobuf
target_link_libraries(MyProject ${Protobuf_LIBRARIES})
