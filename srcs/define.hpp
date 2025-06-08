/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:55:17 by aderouba          #+#    #+#             */
/*   Updated: 2025/06/08 12:45:39 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

// GLFW and Vulkan
# define VK_USE_PLATFORM_XCB_KHR
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# define GLFW_EXPOSE_NATIVE_XCB
# include <GLFW/glfw3native.h>

// Global defines
# define PRINT_FPS_TIME 1.0

// Window defines
# define WIN_TITLE "scop"
# define ENGINE_TITLE "gvEngine"
# define WIN_W 1600
# define WIN_H 900

// Camera defines
# define FOV 80.0f
# define NEAR 0.1f
# define FAR 1000.0f
# define SPEED 3.0f
# define SPRINT 5.0f
# define ROTATE 45.0f

const int MAX_FRAMES_IN_FLIGHT = 2;

// Chunk defines
# define CHUNK_SIZE 32
const int	CHUNK_SIZE2 = CHUNK_SIZE * CHUNK_SIZE;
const int	CHUNK_SIZE3 = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

#endif
