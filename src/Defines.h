#pragma once
#include <iostream>
#define VK_CHECK(x)						\
	do									\
	{									\
		VkResult err = x;				\
		if (err)						\
		{								\
			std::cout << "Detected Vulkan error: " << err << std::endl;\
			abort();					\
		}								\
	} while (0);						\

#define ONE_SECOND 1000000000
