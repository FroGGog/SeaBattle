cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (SeaBattle)

# Добавьте источник в исполняемый файл этого проекта.
set(SOURCE_FILES

	"src/main.cpp"

	"src/GameField.cpp"
	"src/GameField.h"

	"src/Player.cpp"
	"src/Player.h"

	"src/Enemy.cpp"
	"src/Enemy.h"
	
)

add_executable(SeaBattle ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SeaBattle PROPERTY CXX_STANDARD 20)
endif()


