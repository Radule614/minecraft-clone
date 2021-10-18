#pragma once

#include "model/cube.hpp"

namespace ray {

    bool cubeCollision(glm::vec3& ray_origin, glm::vec3& ray_dir, Cube* target, glm::vec3& contact_point, glm::vec3& contact_normal, float& t_hit_near)
    {
        glm::vec3 t_near = (target->position - glm::vec3(1) - ray_origin) / ray_dir;
        glm::vec3 t_far = (target->position + glm::vec3(1) - ray_origin) / ray_dir;

        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
        if (t_near.z > t_far.z) std::swap(t_near.z, t_far.z);

        if (t_near.x > t_far.y || t_near.x > t_far.z || t_near.y > t_far.x || t_near.y > t_far.z || t_near.z > t_far.x || t_near.z > t_far.y) return false;
        
        t_hit_near = std::max(t_near.x, std::max(t_near.y, t_near.z));
        float t_hit_far = std::min(t_far.x, std::min(t_far.y, t_far.z));

        if (t_hit_far < 0) return false;

        contact_point = ray_origin + t_hit_near * ray_dir;

        return true;
    }
}