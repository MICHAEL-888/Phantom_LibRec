cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

project(librec_static_demo LANGUAGES CXX)

option(LIBREC_ENABLE_DEPS "Enable vcpkg dependencies" ON)

add_executable(librec_static_demo
  src/main.cpp
)

target_compile_features(librec_static_demo PRIVATE cxx_std_17)

if(MSVC)
  set_property(TARGET librec_static_demo PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
  )
endif()

if(LIBREC_ENABLE_DEPS)
  find_package(fmt CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)
  find_package(ZLIB REQUIRED)
  find_package(OpenSSL REQUIRED)
  find_package(CURL CONFIG REQUIRED)

  target_compile_definitions(librec_static_demo PRIVATE LIBREC_DEPS_ENABLED=1)
  target_link_libraries(librec_static_demo PRIVATE
    fmt::fmt
    spdlog::spdlog
    ZLIB::ZLIB
    OpenSSL::Crypto
    CURL::libcurl
  )
endif()

install(TARGETS librec_static_demo RUNTIME DESTINATION bin)
