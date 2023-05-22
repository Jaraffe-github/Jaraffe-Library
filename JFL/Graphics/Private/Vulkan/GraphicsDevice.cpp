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
#include "RenderPipeline.h"
#include "Types.h"

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

	JFArray<const char*> instanceExtensions =
	{
		VK_KHR_SURFACE_EXTENSION_NAME
	};

	// Enable surface extensions depending on os
#if defined(_WIN32)
	instanceExtensions.Add(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	instanceExtensions.Add(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_DIRECT2DISPLAY)
	instanceExtensions.Add(VK_KHR_DISPLAY_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
	instanceExtensions.Add(VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	instanceExtensions.Add(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
	instanceExtensions.Add(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	instanceExtensions.Add(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instanceExtensions.Add(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
	instanceExtensions.Add(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
#endif

	if (GraphicsSettings::VALIDATION)
		instanceExtensions.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	if (!CheckInstanceExtensionsSupport(instanceExtensions))
		throw std::runtime_error("instance extensions requested, but not available!");

	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.Count());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.Data();

	JFArray<const char*> validationLayers;

	if (GraphicsSettings::VALIDATION)
	{
		validationLayers.Add("VK_LAYER_KHRONOS_validation");

		if (!CheckValidationLayersSupport(validationLayers))
			throw std::runtime_error("validation layers requested, but not available!");

		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.Count());
		instanceCreateInfo.ppEnabledLayerNames = validationLayers.Data();
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

	JFArray<VkPhysicalDevice> physicalDevices(deviceCount);
	ThrowIfFailed(vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.Data()));

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

	JFArray<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.Data());

	JFArray<VkDeviceQueueCreateInfo> queueCreateInfos(queueFamilyCount, VkDeviceQueueCreateInfo{});

	JFArray<JFArray<float>> queuePriorities(queueFamilyCount);
	for (size_t i = 0; i < queueFamilyProperties.Count(); ++i)
	{
		VkQueueFamilyProperties& queueFamilyProperty = queueFamilyProperties[i];
		queuePriorities[i].Add(0.0f, queueFamilyProperty.queueCount);

		VkDeviceQueueCreateInfo& createInfo = queueCreateInfos[i];
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		createInfo.queueFamilyIndex = static_cast<uint32_t>(i);
		createInfo.queueCount = queueFamilyProperty.queueCount;
		createInfo.pQueuePriorities = queuePriorities[i].Data();
	}

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.Data();
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.Count());

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

	deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.Count());
	deviceCreateInfo.ppEnabledLayerNames = validationLayers.Data();

	JFArray<const char*> deviceExtensions;

	if (GraphicsSettings::USE_SWAP_CHAIN)
	{
		deviceExtensions.Add(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	if (!CheckDeviceExtensionsSupport(physicalDevice, deviceExtensions))
		throw std::runtime_error("device extensions requested, but not available!");

	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.Count());
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.Data();

	ThrowIfFailed(vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device));

	queueFamilies.Reserve(queueFamilyCount);
	for (size_t i = 0; i < queueFamilyProperties.Count(); ++i)
	{
		VkQueueFamilyProperties& queueFamilyProperty = queueFamilyProperties[i];
		queueFamilies.Add(new QueueFamily(device, queueFamilyProperty, static_cast<uint32_t>(i)));
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

bool GraphicsDevice::CheckValidationLayersSupport(const JFArray<const char*>& validationLayers) const
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	JFArray<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.Data());

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

bool GraphicsDevice::CheckInstanceExtensionsSupport(const JFArray<const char*>& extensions) const
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	JFArray<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.Data());

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

bool GraphicsDevice::CheckDeviceExtensionsSupport(VkPhysicalDevice physicalDevice, const JFArray<const char*>& extensions) const
{
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	JFArray<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.Data());

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

	return new Shader(this, shaderModule, stage, entry);
}

JFObject<JFRenderPipeline> GraphicsDevice::CreateRenderPipeline(const JFRenderPipelineDescriptor& desc)
{
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;

	// Dynamic states.
	JFArray<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.Count());
	dynamicState.pDynamicStates = dynamicStates.Data();

	// Vertex Input.
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

	// Input assembly.
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	switch (desc.inputPrimitiveTopology)
	{
	case JFPrimitiveTopologyType::Line:
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		break;
	case JFPrimitiveTopologyType::Point:
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		break;
	case JFPrimitiveTopologyType::Triangle:
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	}

	VkPipelineShaderStageCreateInfo shaderStages[] = {
		desc.vertexShader.DynamicCast<Shader>()->PipelineShaderStageInfo(),
		desc.fragmentShader.DynamicCast<Shader>()->PipelineShaderStageInfo()
	};

	// Rasterizer.
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	// Color blending.
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f; // Optional
	colorBlending.blendConstants[1] = 0.0f; // Optional
	colorBlending.blendConstants[2] = 0.0f; // Optional
	colorBlending.blendConstants[3] = 0.0f; // Optional

	// Pipeline layout.
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

	ThrowIfFailed(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout));

	// Attachment description.
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = PixelFormat(desc.colorAttachments[0].pixelFormat);
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	// Subpasses and attachment references.
	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	// Render pass.
	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	ThrowIfFailed(vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass));

	// Graphics pipeline.
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;

	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = nullptr;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = nullptr;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	VkPipeline graphicsPipeline;

	ThrowIfFailed(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline));

	return new RenderPipeline(this, graphicsPipeline, renderPass, pipelineLayout);
}
