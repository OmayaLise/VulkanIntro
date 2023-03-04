#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <limits>
#include <fstream>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


//Struct 
struct SwapChainSupportDetails 
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices 
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool IsComplete() 
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class App 
{
public:
    void Run();
    bool framebufferResized = false;

private:
    GLFWwindow* window;
    VkInstance instance;

    VkDebugUtilsMessengerEXT debugMessenger;

    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;

    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkPipeline graphicsPipeline;
    VkDescriptorSetLayout descriptorSetLayout;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    VkResult result;

    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t currentFrame = 0;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    Texture texture;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    Mesh mesh;
    Camera camera;
    float time;

    void MainLoop();

    void InitWindow();
    void InitVulkan();

    void CreateInstance();

    void CreateLogicalDevice();
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    void CreateSwapChain();
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    void RecreateSwapChain();

    void CreateImageViews();
    void CreateGraphicsPipeline();
    VkShaderModule CreateShaderModule(const std::vector<char>& code);

    void CreateRenderPass();

    void CreateFrameBuffers();

    void CreateCommandPool();
    void CreateCommandBuffer();
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void CreateSyncObjects();
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void CreateUniformBuffers();

    void CreateDescriptorSetLayout();
    void CreateDescriptorPool();
    void CreateDescriptorSets();

    void CreateTextureImage();
    void CreateImage(uint32_t width, uint32_t height, VkFormat format, 
        VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
        VkImage& image, VkDeviceMemory& imageMemory);
    void TransitionImageLayout(VkImage image, VkFormat format,
        VkImageLayout oldLayout, VkImageLayout newLayout);

    VkCommandBuffer BeginSingleTimeCommands();
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
    void CopyBufferToImage(VkBuffer buffer, VkImage image,
        uint32_t width, uint32_t height);

    void CreateTextureImageView();
    void CreateTextureSampler();
    VkImageView CreateImageView(VkImage image, VkFormat format,
        VkImageAspectFlags aspectFlags);

    void CreateDepthResources();
    VkFormat FindDepthFormat();
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling,
        VkFormatFeatureFlags features);
    bool HasStencilComponent(VkFormat format);

    void DrawFrame();
    void UpdateUniformBuffer(uint32_t currentImage);

    void CleanupSwapChain();
    void Cleanup();
   
    //Debug
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation"};
    const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator);
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void SetupDebugMessenger();
    void CreateSurface();
    std::vector<const char*> GetRequiredExtensions();
    bool CheckValidationLayerSupport();

    void ProcessInput(GLFWwindow* window, float deltaTime);
    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
