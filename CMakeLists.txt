#EXECUTABLES A CREER

set (
	executables 
	
	test

)
cmake_minimum_required (VERSION 2.8)

#Nom du projet

Project (Tatouage)

#Inclusion d'OpenCV

find_package (OpenCV REQUIRED)


set (
    
	EXECUTABLE_OUTPUT_PATH

    ${CMAKE_CURRENT_LIST_DIR}/bin/
)

#Configuration de l'exécutable

file (
	
	GLOB_RECURSE
	
	fichiers_sources
	
	src/*

)

add_executable (
	
	${executables}

	${fichiers_sources}
)	

#Configuration de l'édition de liens

target_link_libraries (
        
		${executables}

        ${OpenCV_LIBS}
)
