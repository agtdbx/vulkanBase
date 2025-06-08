/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderStruct.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gugus <gugus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:55:17 by aderouba          #+#    #+#             */
/*   Updated: 2025/06/08 12:35:48 by gugus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_STRUCT_HPP
# define SHADER_STRUCT_HPP

# include <define.hpp>

# include <gmath.hpp>

// Uniform buffer object
struct UBOMesh3D {
	gm::Mat4f	model;
	gm::Mat4f	view;
	gm::Mat4f	proj;
	gm::Vec4f	pos;
};


#endif
