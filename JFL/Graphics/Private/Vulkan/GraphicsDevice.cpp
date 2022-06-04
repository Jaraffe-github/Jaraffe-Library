//
//  File: GraphicsDevice.cpp
//  Author: Seungmin Choi (jaraffe2@gmail.com)
//
//  Copyright (c) 2022 Seungmin Choi. All rights reserved.
//

#include "GraphicsDevice.h"
#include "Log/JFLog.h"

using namespace JFL;
using namespace JFL::Vulkan;

namespace JFL::Private
{
	namespace Vulkan
	{
		JFGraphicsDevice* CreateGraphicsDevice()
		{
			return new GraphicsDevice();
		}
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData)
	{
		JFLogError("validation layer: {}", callbackData->pMessage);
		return VK_FALSE;
	}
}

GraphicsDevice::GraphicsDevice()
	: instance(nullptr)
{
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	std::vector<const char*> extensions =
	{
#if defined(DEBUG) || defined(_DEBUG)
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
	};

	if (!CheckExtensionsSupport(extensions))
		throw std::runtime_error("extensions requested, but not available!");

	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	const std::vector<const char*> validationLayers =
	{
#if defined(DEBUG) || defined(_DEBUG)
		"VK_LAYER_KHRONOS_validation"
#endif
	};

	if (!CheckValidationLayersSupport(validationLayers))
		throw std::runtime_error("validation layers requested, but not available!");

	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	createInfo.ppEnabledLayerNames = validationLayers.data();

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("failed to create vkInstance!");
	JFLogInfo("Succeed created vulkan instance.");

#if defined(DEBUG) || defined(_DEBUG)
	SetupDebugMessenger();
#endif
}	

GraphicsDevice::~GraphicsDevice()
{
	vkDestroyInstance(instance, nullptr);
}

JFObject<JFCommandQueue> GraphicsDevice::CreateCommandQueue()
{
	return nullptr;
}

JFObject<JFCommandList> GraphicsDevice::CreateCommandList()
{
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
		bool layerFound = false;
		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			JFLogError("Not supported validation layer: {}", layerName);
			return false;
		}
		else
		{
			JFLogInfo("Supported validation layer: {}", layerName);
		}
	}
	return true;
}

bool GraphicsDevice::CheckExtensionsSupport(const std::vector<const char*>& extensions) const
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	for (const char* extensionName : extensions)
	{
		bool extensionFound = false;
		for (const auto& extension : availableExtensions)
		{
			if (strcmp(extensionName, extension.extensionName) == 0)
			{
				extensionFound = true;
				break;
			}
		}

		if (!extensionFound)
		{
			JFLogInfo("not supported extension {}", extensionName);
			return false;
		}
		else
		{
			JFLogInfo("supported extension {}", extensionName);
		}
	}
	return true;
}

void GraphicsDevice::SetupDebugMessenger()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = Private::debugCallback;
	createInfo.pUserData = nullptr;

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func && func(instance, &createInfo, nullptr, &debugMessenger) == VK_SUCCESS)
	{
		JFLogInfo("Enabled debug messenger.");
		return;
	}
	throw std::runtime_error("failed to set up debug messenger!");
}
