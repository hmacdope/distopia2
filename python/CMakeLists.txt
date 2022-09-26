

add_cython_target(libdistopia CXX PY3 )
add_library(distopia_py MODULE ${libdistopia})

python_extension_module(distopia_py)
target_link_libraries(distopia_py distopia)

#install(TARGETS libdistopia LIBRARY DESTINATION libdistopia)