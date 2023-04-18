add_library(shades SHARED shades.c)

set_target_properties(shades PROPERTIES
    PUBLIC_HEADER shades.h
    INTERFACE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(TARGETS shades
    EXPORT shades-target
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDE_DIR})
install(EXPORT shades-target
    DESTINATION ${CONFIG_INSTALL_DIR}
    NAMESPACE CoolLib::)
