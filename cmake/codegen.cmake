find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(SKIN_CONFIG_JSON  "${CMAKE_SOURCE_DIR}/Skins/PyTaikoGreen/Graphics/skin_config.json")
set(SKIN_CONFIG_GEN_H "${CMAKE_BINARY_DIR}/generated/skin_config_generated.h")

add_custom_command(
    OUTPUT  ${SKIN_CONFIG_GEN_H}
    COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_SOURCE_DIR}/tools/gen_skin_config.py"
            "${SKIN_CONFIG_JSON}"
            "${SKIN_CONFIG_GEN_H}"
    DEPENDS "${SKIN_CONFIG_JSON}" "${CMAKE_SOURCE_DIR}/tools/gen_skin_config.py"
    COMMENT "Generating skin_config_generated.h from skin_config.json"
)
add_custom_target(skin_config_gen DEPENDS ${SKIN_CONFIG_GEN_H})

set(SKIN_GRAPHICS_DIR "${CMAKE_SOURCE_DIR}/Skins/PyTaikoGreen/Graphics")
set(TEXTURE_IDS_GEN_H "${CMAKE_BINARY_DIR}/generated/texture_ids_generated.h")

file(GLOB_RECURSE TEXTURE_JSON_FILES "${SKIN_GRAPHICS_DIR}/*/*/texture.json")

add_custom_command(
    OUTPUT  ${TEXTURE_IDS_GEN_H}
    COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_SOURCE_DIR}/tools/gen_textures.py"
            "${SKIN_GRAPHICS_DIR}"
            "${TEXTURE_IDS_GEN_H}"
    DEPENDS "${CMAKE_SOURCE_DIR}/tools/gen_textures.py" ${TEXTURE_JSON_FILES}
    COMMENT "Generating texture_ids_generated.h from skin texture.json files"
)
add_custom_target(texture_ids_gen DEPENDS ${TEXTURE_IDS_GEN_H})
