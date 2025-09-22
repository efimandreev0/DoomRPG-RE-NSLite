set(NX_APP_TITLE "DoomRPG")
set(NX_APP_AUTHOR "PG Team, Erick194")
set(NX_APP_VERSION "0.2.2")
set(PROJECT_TID "0x16092009efdd0000")

file(GLOB_RECURSE HEADER_FILES
	"*.hpp"
	"*.h")

file(GLOB_RECURSE SOURCE_FILES
	"*.cpp"
	"*.c")

file(GLOB_RECURSE RESOURCES_FILES
	"*.rc"
	"*.ico")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Resources Files" FILES ${RESOURCES_FILES})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCES_FILES})
target_link_libraries(${PROJECT_NAME}
		SDL2_Mixer
		SDL2::SDL2
		timidity
		opusfile
		opus
		vorbisidec
		ogg
		mpg123
		modplug
		ZLIB::ZLIB
		nx
)
add_custom_command(
		TARGET DoomRPG POST_BUILD
		COMMAND nacptool --create "${NX_APP_TITLE}" "${NX_APP_AUTHOR}" "${NX_APP_VERSION}" "${PROJECT_NAME}.nacp" --titleid=${PROJECT_TID}
		COMMAND elf2nro
		"${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.elf"
		"${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.nro"
		--nacp=${PROJECT_NAME}.nacp
		--icon="${CMAKE_SOURCE_DIR}/icon.png"
)
