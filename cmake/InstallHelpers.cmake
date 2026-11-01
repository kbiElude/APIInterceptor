# Installing a program of a release: shared with a project which builds on this one and has a release of its own.

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(RELEASE_ARCH_SUFFIX "_x64")
else()
    set(RELEASE_ARCH_SUFFIX "_x86")
endif()

# A target, as the file it builds, into a folder of the release; the name is the one of the target with the suffix of the architecture.
function(install_with_suffix in_target in_folder)
    get_target_property(target_type ${in_target} TYPE)

    if (target_type STREQUAL "EXECUTABLE")
        set(extension ".exe")
    else()
        set(extension ".dll")
    endif()

    install(FILES       "$<TARGET_FILE:${in_target}>"
            DESTINATION "${in_folder}"
            RENAME      "${in_target}${RELEASE_ARCH_SUFFIX}${extension}")
endfunction()

# A target, as the file it builds, into a folder of the release, under the name it is built with.
function(install_as_built in_target in_folder)
    install(FILES       "$<TARGET_FILE:${in_target}>"
            DESTINATION "${in_folder}")
endfunction()
