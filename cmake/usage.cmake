# What a project which builds this one as a subproject (add_subdirectory) needs to compile against its libraries: their include
# directories, which the targets of this project have from include_directories() in the root file, and a parent does not. In the
# installed package (see package.cmake) the headers are in the include directory of the package.
foreach(library APIDumpLoader APIInterceptor D3D8Utils InjectionLauncher)
    if (TARGET ${library})
        foreach(directory ${APIINTERCEPTOR_INCLUDE_DIRECTORIES})
            target_include_directories(${library} PUBLIC "$<BUILD_INTERFACE:${directory}>")
        endforeach()

        target_include_directories(${library} INTERFACE "$<INSTALL_INTERFACE:include>")
    endif()
endforeach()
