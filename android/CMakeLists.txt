cmake_minimum_required(VERSION 3.6)

project(Loki)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(compiler_c_flags "-Wno-error=format-security")
set(compiler_c_flags "-Wno-error=error")


##################################### IMGUI ###################################
add_library(imgui SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/backends/imgui_impl_android.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/cimgui/cimgui.cpp
)

target_compile_definitions(imgui PRIVATE
  IMGUI_IMPL_OPENGL_ES3
  HAVE_COMPLEX_NUMBERS=0 
  HAVE_COMPLEX_TRIG=0
)


target_include_directories(imgui PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/backends
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/cimgui
)

target_link_libraries(imgui PRIVATE
  android
  EGL
  GLESv3
  log
)

##################################### CHIBI ###################################
add_library(chibi_scheme SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/bignum.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/eval.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/gc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/gc_heap.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/opcodes.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/sexp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/simplify.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/vm.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib/imgui/imgui_src.c
)

target_compile_definitions(chibi_scheme PRIVATE
    SEXP_USE_WARN_UNDEFS=1 SEXP_USE_DL=0 SEXP_USE_STATIC_LIBS=1 SEXP_USE_STATIC_LIBS_NO_INCLUDE=0)

target_include_directories(chibi_scheme PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/lib/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../deps/cimgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui
)

target_link_libraries(chibi_scheme PRIVATE
  imgui
)


##################################### Loki ####################################
add_library(${CMAKE_PROJECT_NAME} SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/loki_main.cpp
  ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/
  ${ANDROID_NDK}/sources/android/native_app_glue
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/chibi-scheme-static/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/../deps/imgui/backends
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  android
  EGL
  GLESv3
  log
  imgui
  chibi_scheme
)


