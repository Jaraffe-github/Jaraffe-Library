set(INCLUDE
    Application/JFApplication.h
	Application/JFApplicationContextInterface.h
	Application/Private/ApplicationPlatform.h
	Application/Private/Cocoa/ApplicationContext.h
	Application/Private/CocoaTouch/ApplicationContext.h
	Application/Private/Win32/ApplicationContext.h
	Window/JFWindow.h
	Window/Private/WindowPlatform.h
	Window/Private/Cocoa/WindowContext.h
	Window/Private/CocoaTouch/WindowContext.h
	Window/Private/Win32/Window.h
	Graphics/JFGraphics.h
	Graphics/JFGraphicsDevice.h
	Graphics/Private/GraphicsAPI.h
	Graphics/Private/Direct3D12/d3d12_headers.h
	Graphics/Private/Direct3D12/d3dx12.h
	Graphics/Private/Direct3D12/GraphicsDevice.h
	Math/JFAffineTransform2.h
	Math/JFAffineTransform2.inl
	Math/JFAffineTransform3.h
	Math/JFAffineTransform3.inl
	Math/JFLinearTransform2.h
	Math/JFLinearTransform2.inl
	Math/JFLinearTransform3.h
	Math/JFLinearTransform3.inl
	Math/JFMath.h
	Math/JFMatrix2.h
	Math/JFMatrix2.inl
	Math/JFMatrix3.h
	Math/JFMatrix3.inl
	Math/JFMatrix4.h
	Math/JFMatrix4.inl
	Math/JFVector2.h
	Math/JFVector2.inl
	Math/JFVector3.h
	Math/JFVector3.inl
	Math/JFVector4.h
	Math/JFVector4.inl
)

set(SOURCE
	Application/JFApplication.cpp
	Application/Private/Cocoa/ApplicationContext.m
	Application/Private/CocoaTouch/ApplicationContext.m
	Application/Private/Win32/ApplicationContext.cpp
	Window/JFWindow.cpp
	Window/Private/Cocoa/WindowContext.m
	Window/Private/CocoaTouch/WindowContext.m
	Window/Private/Win32/WindowContext.cpp
	Graphics/JFGraphicsDevice.cpp
	Graphics/Private/Direct3D12/GraphicsDevice.cpp
)

add_library(JFL ${SOURCE} ${INCLUDE})

target_include_directories(JFL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(JFL PRIVATE cxx_std_20)

if (BUILD_SHARED_LIBS)
	target_compile_definitions(JFL PUBLIC JFL_DYNAMIC)
	target_compile_definitions(JFL PRIVATE DLL_EXPORTS)
endif()
