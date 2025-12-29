#pragma once

struct AABB
{
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

    // ÇáÊÍŞŞ ãä ÊÕÇÏã ãÚ AABB ÂÎÑ
    bool intersects(const AABB& other) const
    {
        return (minX <= other.maxX && maxX >= other.minX) &&
            (minY <= other.maxY && maxY >= other.minY) &&
            (minZ <= other.maxZ && maxZ >= other.minZ);
    }
};
