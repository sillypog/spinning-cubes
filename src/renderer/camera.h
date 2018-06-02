#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
	const static glm::vec3 up_axis;
	glm::mat4 view;
	glm::mat4 projection;	// Do we need these or can we just calculate as needed?

	glm::vec3 position;
    glm::vec3 focal_point;
    float field_of_view;
    float aspect_ratio;
    float near_plane;
    float far_plane;

public:
	Camera(glm::vec3 pos, glm::vec3 focus);
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
};

#endif
