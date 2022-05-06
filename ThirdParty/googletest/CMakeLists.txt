set(SOURCE
	googlemock/src/gmock-all.cc
	googletest/src/gtest-all.cc
)

add_library(googletest STATIC ${SOURCE})

target_include_directories(googletest
PUBLIC
    googlemock
	googlemock/include
    googletest
	googletest/include
)

target_compile_features(googletest PRIVATE cxx_std_20)