# distopia python layer
add_cython_target(_distopia CXX PY3)
add_library(_distopia MODULE ${_distopia})
python_extension_module(_distopia)
target_link_libraries(_distopia libdistopia)
set_target_properties(_distopia PROPERTIES INSTALL_RPATH_USE_LINK_PATH FALSE)
install(TARGETS _distopia LIBRARY DESTINATION distopia)