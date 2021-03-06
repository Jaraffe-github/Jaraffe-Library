//
//  File: GraphicsDevice.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "../GraphicsAPI.h"
#include "GraphicsDevice.h"
#include "Log/JFLog.h"
#include "FileSystem/JFFileSystem.h"
#include "CommandQueue.h"
#include "Shader.h"
#include "GraphicsDevice.h"

namespace JFL::Private::Vulkan
{
	JFGraphicsDevice* CreateGraphicsDevice()
	{
		return new GraphicsDevice();
	}
}

using namespace JFL;
using namespace JFL::Private::Vulkan;

namespace Debug
{
	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
	VkDebugUtilsMessengerEXT debugUtilsMessenger;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData)
	{
		// Select prefix depending on flags passed to the callback
		JFLogLevel logLevel = JFLogLevel::Info;
		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) 
		{
			logLevel = JFLogLevel::Verbose;
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) 
		{
			logLevel = JFLogLevel::Info;
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
		{
			logLevel = JFLogLevel::Warning;
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {

			logLevel = JFLogLevel::Error;
		}

		JFLog(logLevel, "[{}][{}]{}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage);

		// The return value of this callback controls whether the Vulkan call that caused the validation message will be aborted or not
		// We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message to abort
		// If you instead want to have calls abort, pass in VK_TRUE and the function will return VK_ERROR_VALIDATION_FAILED_EXT 
		return VK_FALSE;
	}

	void SetupDebugMessenger(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callBack)
	{
		vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
		vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCI{};
		debugUtilsMessengerCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugUtilsMessengerCI.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugUtilsMessengerCI.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		debugUtilsMessengerCI.pfnUserCallback = debugUtilsMessengerCallback;
		ThrowIfFailed(vkCreateDebugUtilsMessengerEXT(instance, &debugUtilsMessengerCI, nullptr, &debugUtilsMessenger));
		JFLogInfo("Created debug messenger.");
	}

	void DestoryDebugMessenger(VkInstance instance)
	{
		if (debugUtilsMessenger != VK_NULL_HANDLE)
		{
			vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
			JFLogInfo("Destroyed debug messenger.");
		}
	}
}

GraphicsDevice::GraphicsDevice()
	: instance(nullptr)
	, device(nullptr)
	, physicalDevice(nullptr)
{
	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	std::vector<const char*> instanceExtensions =
	{
		VK_KHR_SURFACE_EXTENSION_NAME
	};

	// Enable surface extensions depending on os
#if defined(_WIN32)
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	instanceExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_DIRECT2DISPLAY)
	instanceExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
	instanceExtensions.push_back(VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	instanceExtensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
	instanceExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	instanceExtensions.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
	instanceExtensions.push_back(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
#endif

	if (GraphicsSettings::VALIDATION)
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	if (!CheckInstanceExtensionsSupport(instanceExtensions))
		throw std::runtime_error("instance extensions requested, but not available!");

	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

	std::vector<const char*> validationLayers;
	if (GraphicsSettings::VALIDATION)
	{
		validationLayers.push_back("VK_LAYER_KHRONOS_validation");

		if (!CheckValidationLayersSupport(validationLayers))
			throw std::runtime_error("validation layers requested, but not available!");

		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
	}

	ThrowIfFailed(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
	JFLogInfo("Succeed created vulkan instance.");

	if (GraphicsSettings::VALIDATION)
	{
		// The report flags determine what type of messages for the layers will be displayed
		// For validating (debugging) an application the error and warning bits should suffice
		VkDebugReportFlagsEXT debugReportFlags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		// Additional flags include performance info, loader and layer debug messages, etc.
		Debug::SetupDebugMessenger(instance, debugReportFlags, VK_NULL_HANDLE);
	}

	// Get number of available physical devices
	uint32_t deviceCount = 0;
	ThrowIfFailed(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));
	if (deviceCount == 0)
		throw std::runtime_error("failed to find GPUs with Vulkan support!");

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	ThrowIfFailed(vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data()));

	for (const auto& physicalDevice : physicalDevices)
	{
		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader)
		{
			this->physicalDevice = physicalDevice;
			JFLogInfo("Usable hardware info: {}", deviceProperties.deviceName);
			break;
		}
	}

	if (physicalDevice == nullptr)
		throw std::runtime_error("failed to find physical device suitable");

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(queueFamilyCount, VkDeviceQueueCreateInfo{});

	std::vector<std::vector<float>> queuePriorities(queueFamilyCount);
	for (size_t i = 0; i < queueFamilyProperties.size(); ++i)
	{
		VkQueueFamilyProperties& queueFamilyProperty = queueFamilyProperties[i];
		queuePriorities[i].resize(queueFamilyProperty.queueCount, 0.0f);

		VkDeviceQueueCreateInfo& createInfo = queueCreateInfos[i];
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		createInfo.queueFamilyIndex = static_cast<uint32_t>(i);
		createInfo.queueCount = queueFamilyProperty.queueCount;
		createInfo.pQueuePriorities = queuePriorities[i].data();
	}

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

	deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();

	std::vector<const char*> deviceExtensions;

	if (GraphicsSettings::USE_SWAP_CHAIN)
	{
		deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	if (!CheckDeviceExtensionsSupport(physicalDevice, deviceExtensions))
		throw std::runtime_error("device extensions requested, but not available!");

	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

	ThrowIfFailed(vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device));

	queueFamilies.reserve(queueFamilyCount);
	for (size_t i = 0; i < queueFamilyProperties.size(); ++i)
	{
		VkQueueFamilyProperties& queueFamilyProperty = queueFamilyProperties[i];
		queueFamilies.push_back(new QueueFamily(device, queueFamilyProperty, static_cast<uint32_t>(i)));
	}
}

GraphicsDevice::~GraphicsDevice()
{
	Debug::DestoryDebugMessenger(instance);
	vkDestroyDevice(device, nullptr);
	vkDestroyInstance(instance, nullptr);
}

JFObject<JFCommandQueue> GraphicsDevice::CreateCommandQueue()
{
	for (JFObject<QueueFamily> queueFamily : queueFamilies)
	{
		// TODO: support other types.
		if (queueFamily->IsFlagSupported(VK_QUEUE_GRAPHICS_BIT))
			return queueFamily->CreateCommandQueue(this);
	}
	return nullptr;
}

JFObject<JFGPUBuffer> GraphicsDevice::CreateGPUBuffer(size_t, JFGPUBuffer::CPUCacheMode)
{
	return nullptr;
}

JFObject<JFTexture> GraphicsDevice::CreateTexture(const JFTextureDescriptor&)
{
	return nullptr;
}

bool GraphicsDevice::CheckValidationLayersSupport(const std::vector<const char*>& validationLayers) const
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		if (std::find_if(availableLayers.begin(),
						 availableLayers.end(),
						 [layerName](VkLayerProperties property)
						 {
							 return strcmp(property.layerName, layerName) == 0;
						 }) != availableLayers.end())
		{
			JFLogInfo("Supported validation layer: {}", layerName);
		}
		else
		{
			JFLogWarning("Not supported validation layer: {}", layerName);
			return false;
		}
	}
	return true;
}

bool GraphicsDevice::CheckInstanceExtensionsSupport(const std::vector<const char*>& extensions) const
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	for (const char* extensionName : extensions)
	{
		if (std::find_if(availableExtensions.begin(),
						 availableExtensions.end(),
						 [extensionName](VkExtensionProperties property) 
						 { 
							 return strcmp(property.extensionName, extensionName) == 0; 
						 }) != availableExtensions.end())
		{
			JFLogInfo("Supported extension {}", extensionName);
		}
		else
		{
			JFLogWarning("Not supported extension {}", extensionName);
			return false;
		}
	}
	return true;
}

bool GraphicsDevice::CheckDeviceExtensionsSupport(VkPhysicalDevice physicalDevice, const std::vector<const char*>& extensions) const
{
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

	for (const char* extensionName : extensions)
	{
		if (std::find_if(availableExtensions.begin(),
						 availableExtensions.end(),
						 [extensionName](VkExtensionProperties property)
						 {
							 return strcmp(property.extensionName, extensionName) == 0;
						 }) != availableExtensions.end())
		{
			JFLogInfo("Supported extension {}", extensionName);
		}
		else
		{
			JFLogWarning("Not supported extension {}", extensionName);
			return false;
		}
	}
	return true;
}

JFObject<JFShader> GraphicsDevice::CreateShader(const JFArray<uint8_t>& code, const JFStringA& entry, JFShader::StageType stage)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.Count();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.Data());

	VkShaderModule shaderModule;
	ThrowIfFailed(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));

	return new Shader(shaderModule, stage, entry);
}

JFObject<JFRenderPipeline> GraphicsDevice::CreateRenderPipeline(const JFRenderPipelineDescriptor&)
{
	return JFObject<JFRenderPipeline>();
}
