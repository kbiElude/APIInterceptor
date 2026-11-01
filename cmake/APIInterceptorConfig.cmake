# find_package(APIInterceptor): the libraries of the capture (APIInterceptor::APIDumpLoader, ::D3D8Utils, ::InjectionLauncher, and
# what they link: ::Detours, ::Zstd). The include directory of each is the one of the package.
include("${CMAKE_CURRENT_LIST_DIR}/APIInterceptorTargets.cmake")
