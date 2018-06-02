#include "./camera.h"

#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 Camera::up_axis {0.0f, 0.0f, 1.0f};

Camera::Camera(glm::vec3 pos, glm::vec3 focus) : position(pos), focal_point(focus) {
	// Temporarily hardcoding
	field_of_view = glm::radians(45.0f);
	aspect_ratio = 640.0f / 480.0f;
	near_plane = 1.0f;
	far_plane = 10.0f;

	view = glm::lookAt(position, focal_point, Camera::up_axis);
	projection = glm::perspective(field_of_view, aspect_ratio, near_plane, far_plane);
}

glm::mat4 Camera::getView() const {
	return view;
}

glm::mat4 Camera::getProjection() const {
	return projection;
}
