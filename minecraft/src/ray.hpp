#pragma once

namespace ray {

    struct cuboid {
        glm::vec3 position;
        glm::vec3 size;

        glm::vec3 vel;
    };

    bool cuboidCollision(glm::vec3& ray_origin, glm::vec3& ray_dir, cuboid target, glm::vec3& contact_point, glm::vec3& contact_normal, float& t_hit_near)
    {
        glm::vec3 t_near = (target.position - (target.size) - ray_origin) / ray_dir;
        glm::vec3 t_far = (target.position + (target.size) - ray_origin) / ray_dir;

        if (isnan(t_far.y) || isnan(t_far.x) || isnan(t_far.y)) return false;
        if (isnan(t_near.y) || isnan(t_near.x) || isnan(t_near.y)) return false;

        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
        if (t_near.z > t_far.z) std::swap(t_near.z, t_far.z);

        if (t_near.x > t_far.y || t_near.x > t_far.z || t_near.y > t_far.x || t_near.y > t_far.z || t_near.z > t_far.x || t_near.z > t_far.y) return false;
        
        t_hit_near = std::max(t_near.x, std::max(t_near.y, t_near.z));
        float t_hit_far = std::min(t_far.x, std::min(t_far.y, t_far.z));

        if (t_hit_far < 0) return false;

        contact_point = ray_origin + t_hit_near * ray_dir;

        if (t_near.x > t_near.y && t_near.x > t_near.z)
        {
            if (ray_dir.x < 0) contact_normal = glm::vec3(1, 0, 0);
            else contact_normal = glm::vec3(-1, 0, 0);
        }
        else if (t_near.y > t_near.x && t_near.y > t_near.z)
        {
            if (ray_dir.y < 0) contact_normal = glm::vec3(0, 1, 0);
            else contact_normal = glm::vec3(0, -1, 0);
        }
        else if (t_near.z > t_near.x && t_near.z > t_near.y)
        {
            if (ray_dir.z < 0) contact_normal = glm::vec3(0, 0, 1);
            else contact_normal = glm::vec3(0, 0, -1);
        }

        return true;
    }

    bool dynamicCuboidCollision(cuboid in, cuboid target, glm::vec3& contact_point, glm::vec3& contact_normal, float& contact_time)
    {
        if (in.vel.x == 0 && in.vel.y == 0 && in.vel.z == 0) return false;

        cuboid expanded_target;
        expanded_target.position = target.position;
        expanded_target.size = target.size + in.size;
        glm::vec3 ray_origin = in.position;
        glm::vec3 direction = glm::normalize(in.vel);
        
        if (cuboidCollision(ray_origin, direction, expanded_target, contact_point, contact_normal, contact_time))
        {
            if (contact_time < 1.0f) return true;
        }

        return false;
    }
}