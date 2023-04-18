
add_library(leatherjacket SHARED leatherjacket.c)

set_target_properties(leatherjacket PROPERTIES
    PUBLIC_HEADER leatherjacket.h
    INTERFACE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(TARGETS leatherjacket
    EXPORT leatherjacket-target
    INCLUDES DESTINATION ${INCLUDE_DIR})
install(EXPORT leatherjacket-target
    DESTINATION ${CONFIG_INSTALL_DIR}
    NAMESPACE CoolLib::)
