SET(pwd ${CMAKE_CURRENT_LIST_DIR})

SET(src "")
AUX_SOURCE_DIRECTORY(${pwd} src)
add_executable(texture ${src})
message(STATUS "texture added ${src}")

target_link_libraries(texture ${stdgl_libraries})
FIND_PACKAGE(FLTK REQUIRED)
SET_PROPERTY(TARGET texture APPEND PROPERTY INCLUDE_DIRECTORIES ${FLTK_INCLUDE_DIR})
target_link_libraries(texture ${FLTK_LIBRARIES})
FIND_PACKAGE(JPEG REQUIRED)
TARGET_LINK_LIBRARIES(texture ${JPEG_LIBRARIES})
