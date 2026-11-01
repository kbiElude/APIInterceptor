# Putting the targets of a solution in folders: shared with a project which builds on this one.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(assign_folder in_folder)
    foreach(target ${ARGN})
        if (TARGET ${target})
            set_target_properties(${target} PROPERTIES FOLDER "${in_folder}")
        endif()
    endforeach()
endfunction()

# The targets of a directory and the ones below it (the third party code makes its own).
function(assign_folder_to_directory in_folder in_directory)
    get_property(targets DIRECTORY ${in_directory} PROPERTY BUILDSYSTEM_TARGETS)
    foreach(target ${targets})
        set_target_properties(${target} PROPERTIES FOLDER "${in_folder}")
    endforeach()

    get_property(subdirectories DIRECTORY ${in_directory} PROPERTY SUBDIRECTORIES)
    foreach(subdirectory ${subdirectories})
        assign_folder_to_directory("${in_folder}" ${subdirectory})
    endforeach()
endfunction()
