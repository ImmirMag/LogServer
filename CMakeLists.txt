cmake_minimum_required(VERSION 3.13)
project(InfoServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(InfoServer main.cpp)

find_package(Poco REQUIRED COMPONENTS Foundation Net Zip Data DataSQLite Crypto)

target_link_libraries(InfoServer PUBLIC Poco::Foundation Poco::Zip Poco::Net Poco::Data Poco::DataSQLite Poco::Crypto)