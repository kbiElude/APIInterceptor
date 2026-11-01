# What a project which builds this one as a subproject (add_subdirectory) needs to compile against its libraries: their include
# directories, which the targets of this project have from include_directories() in the root file, and a parent does not.
foreach(library APIDumpLoader APIInterceptor D3D8Utils InjectionLauncher)
    if (TARGET ${library})
        target_include_directories(${library} PUBLIC ${APIINTERCEPTOR_INCLUDE_DIRECTORIES})
    endif()
endforeach()
