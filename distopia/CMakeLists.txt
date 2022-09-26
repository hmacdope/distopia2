# distopia python layer
add_cython_target(distopia CXX PY3)
add_library(pydistopia MODULE ${distopia})
python_extension_module(pydistopia)
target_link_libraries(pydistopia libdistopia)
install(TARGETS pydistopia DESTINATION distopia)