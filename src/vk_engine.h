﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <vk_types.h>
#include <vector>

#include "RingBuffer.h"

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int frameNumber {0};

	VkExtent2D _windowExtent{ 1700 , 900 };

	struct SDL_Window* _window{ nullptr };

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();
private:

	// basic vulkan
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice gpuDevice;
	VkDevice device;
	VkSurfaceKHR surface;

	// vulkan swapchain
	VkSwapchainKHR swapchain;
	VkFormat swapchainImageFormat;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;

	// vulkan command buffer & graphics queue
	VkQueue graphicsQueue; //queue we will submit to
	uint32_t graphicsQueueFamily; //family of that queue

	std::vector<VkCommandPool> commandPool; //the command pool for our commands
	std::vector<VkCommandBuffer> mainCommandBuffer; //the buffer we will record into

	// render pass
	VkRenderPass renderPass;
	std::vector<VkFramebuffer> frameBuffers;

	// Sync Object
	RingSyncObjects ringBuffer;

	//loads a shader module from a spir-v file. Returns false if it errors
	bool load_shader_module(const char* filePath, VkShaderModule* outShaderModule);
	

	void initVulkan();
	void initSwapchain();
	void initCommands();
	void initDefaultRenderpass();
	void initFrameBuffers();
	void initSyncStructures();
	void initPipeline();
};