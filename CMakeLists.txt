cmake_minimum_required(VERSION 3.16)

project(Efficio)

#add_compile_options(-fsanitize=address,undefined,leak)
#add_link_options(-fsanitize=address,undefined,leak)
add_subdirectory(proto)
add_subdirectory(server)
add_subdirectory(tests)
add_subdirectory(client)
