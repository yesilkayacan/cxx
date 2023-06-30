# Add source files in the src directory
file(GLOB_RECURSE FILES_SRC CONFIGURE_DEPENDS "*.cpp")
add_library(app_lib ${FILES_SRC})
target_compile_features(app_lib PUBLIC cxx_std_17)