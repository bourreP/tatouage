cmake_minimum_required (VERSION 2.8)
#Nom du projet

Project (Tatouage)

ADD_DEFINITIONS(-g -O2 -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline) #Options de compilations avec gcc

#Inclusion d'OpenCV

find_package (OpenCV REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set (
    
	EXECUTABLE_OUTPUT_PATH

    ${CMAKE_CURRENT_LIST_DIR}/bin/
	)

macro (creation EXECUTABLES)
	foreach (EXECUTABLE ${EXECUTABLES})
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${EXECUTABLE}/include)
		include_directories(${GTK3_INCLUDE_DIRS})
		link_directories(${GTK3_LIBRARY_DIRS})
		set(${EXECUTABLE}_SRC)
		AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/${EXECUTABLE}/src ${EXECUTABLE}_SRC)
		AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/${EXECUTABLE}/ ${EXECUTABLE}_SRC)

		add_executable(${EXECUTABLE} ${${EXECUTABLE}_SRC})

		target_link_libraries (

			${EXECUTABLE}

			${OpenCV_LIBS}
			${GTK3_LIBRARIES}

		)

	endforeach()
endmacro()

add_subdirectory(${CMAKE_SOURCE_DIR}/src/)
