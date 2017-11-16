#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>
#include <iostream>

inline void print_matrix(glm::mat4 matrix) {
	for(int x = 0; x < 4; x++) {
		for(int y = 0; y < 4; y++) {
			std::cout << matrix[y][x] << " ";
		}
		std::cout << "\n";
	}
}

inline void print_3vec(glm::vec3 vec) {
	for(int x = 0; x < 3; x++) {
		std::cout << vec[x] << " ";
	}
	std::cout << "\n";
}

inline void print_4vec(glm::vec4 vec) {
	for(int x = 0; x < 4; x++) {
		std::cout << vec[x] << " ";
	}
	std::cout << "\n";
}

#endif