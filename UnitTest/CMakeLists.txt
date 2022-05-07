set(SOURCE
	main.cpp
	Application/Application.cpp
	Math/AffineTransform.cpp
	Math/LinearTransform.cpp
	Math/Matrix.cpp
	Math/Vector.cpp
)

add_executable(UnitTest ${SOURCE})
target_compile_features(JFL PRIVATE cxx_std_20)

target_include_directories(UnitTest 
	PUBLIC 
	${CMAKE_HOME_DIRECTORY}/JFL 
	${CMAKE_HOME_DIRECTORY}/ThirdParty/googletest/googletest/include
)
target_link_libraries(UnitTest PUBLIC JFL googletest)

target_compile_features(UnitTest PRIVATE cxx_std_20)

if (BUILD_SHARED_LIBS)
	target_compile_definitions(UnitTest PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY)
endif()
