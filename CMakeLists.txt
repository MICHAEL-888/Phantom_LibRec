cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

project(librec_static_demo LANGUAGES CXX)

option(LIBREC_ENABLE_DEPS "Enable vcpkg dependencies" ON)

function(librec_setup_target target)
  target_compile_features(${target} PRIVATE cxx_std_17)
  if(MSVC)
    set_property(TARGET ${target} PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
  endif()
endfunction()

set(librec_targets)

add_executable(librec_static_demo
  src/main.cpp
)
list(APPEND librec_targets librec_static_demo)
librec_setup_target(librec_static_demo)

if(LIBREC_ENABLE_DEPS)
  find_package(fmt CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)
  find_package(ZLIB REQUIRED)
  find_package(OpenSSL REQUIRED)
  find_package(CURL CONFIG REQUIRED)
  find_package(Qt6 CONFIG REQUIRED COMPONENTS Core)

  target_compile_definitions(librec_static_demo PRIVATE LIBREC_DEPS_ENABLED=1)
  target_link_libraries(librec_static_demo PRIVATE
    fmt::fmt
    spdlog::spdlog
    ZLIB::ZLIB
    OpenSSL::Crypto
    CURL::libcurl
  )

  add_executable(librec_fmt_demo
    src/fmt_demo.cpp
  )
  list(APPEND librec_targets librec_fmt_demo)
  librec_setup_target(librec_fmt_demo)
  target_link_libraries(librec_fmt_demo PRIVATE fmt::fmt)

  add_executable(librec_spdlog_demo
    src/spdlog_demo.cpp
  )
  list(APPEND librec_targets librec_spdlog_demo)
  librec_setup_target(librec_spdlog_demo)
  target_link_libraries(librec_spdlog_demo PRIVATE spdlog::spdlog)

  add_executable(librec_zlib_demo
    src/zlib_demo.cpp
  )
  list(APPEND librec_targets librec_zlib_demo)
  librec_setup_target(librec_zlib_demo)
  target_link_libraries(librec_zlib_demo PRIVATE ZLIB::ZLIB)

  add_executable(librec_openssl_demo
    src/openssl_demo.cpp
  )
  list(APPEND librec_targets librec_openssl_demo)
  librec_setup_target(librec_openssl_demo)
  target_link_libraries(librec_openssl_demo PRIVATE OpenSSL::Crypto)

  add_executable(librec_curl_demo
    src/curl_demo.cpp
  )
  list(APPEND librec_targets librec_curl_demo)
  librec_setup_target(librec_curl_demo)
  target_link_libraries(librec_curl_demo PRIVATE CURL::libcurl)

  add_executable(librec_qt_demo
    src/qt_demo.cpp
  )
  list(APPEND librec_targets librec_qt_demo)
  librec_setup_target(librec_qt_demo)
  set_property(TARGET librec_qt_demo PROPERTY AUTOMOC ON)
  target_link_libraries(librec_qt_demo PRIVATE Qt6::Core)
endif()

install(TARGETS ${librec_targets} RUNTIME DESTINATION bin)
