cmake_minimum_required(VERSION 3.16)

project(Protobuf)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)


set(MODEL_PROTO_FILES
        model-proto/model.proto
)

set(EFFICIO_RPC_PROTO_FILES
        efficio-rpc-proto/efficio.proto
)

add_library(model-proto STATIC ${MODEL_PROTO_FILES})
add_library(efficio-rpc STATIC ${EFFICIO_RPC_PROTO_FILES})
target_link_libraries(model-proto
        PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(model-proto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/model-proto/)

target_link_libraries(efficio-rpc
        PUBLIC
        model-proto
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(efficio-rpc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/model-proto/
        ${CMAKE_CURRENT_SOURCE_DIR}/efficio-rpc-proto/
)


get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(
        TARGET model-proto
        PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/model-proto/
        LANGUAGE cpp)

#protobuf_generate(
#        TARGET model-proto
#        LANGUAGE grpc
#        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
#        PROTOC_OUT_DIR ${PROJECT_SOURCE_DIR}/model-proto/
#        PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
#)

protobuf_generate(
        TARGET efficio-rpc
        PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/efficio-rpc-proto/
        LANGUAGE cpp
        PROTOC_ARGS --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
)

protobuf_generate(
        TARGET efficio-rpc
        LANGUAGE grpc
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
        PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/efficio-rpc-proto/
        PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
        PROTOC_ARGS --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
)