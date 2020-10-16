cmake_minimum_required(VERSION 3.17)
project(multiThreadPE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Threads REQUIRED)
add_executable(multiThreadPE
	check.hh
	main.cc
	multisearcher.cc
	multisearcher.hh
)
target_link_libraries(multiThreadPE
	Threads::Threads)
