set(SOURCE
	googlemock/src/gmock-all.cc
	googletest/src/gtest-all.cc
)

add_library(googletest ${SOURCE})

target_include_directories(googletest
PUBLIC
    googlemock
	googlemock/include
    googletest
	googletest/include
)

target_compile_features(googletest PRIVATE cxx_std_20)

if (BUILD_SHARED_LIBS)
	target_compile_definitions(googletest PRIVATE GTEST_CREATE_SHARED_LIBRARY)
endif()
