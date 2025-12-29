#pragma once
#include <vector>
#include "Collision.h"

class CollisionManager
{
public:
    //  Œ“Ì‰ ﬂ· «·√Ã”«„ «·’·»…
    static std::vector<AABB> collidables;

    // √÷› Ã”„ ’·»
    static void addCollidable(const AABB& box)
    {
        collidables.push_back(box);
    }

    //  Õﬁﬁ „‰ ≈„ﬂ«‰Ì… «·Õ—ﬂ…
    static bool canMove(const AABB& playerBox)
    {
        for (auto& box : collidables)
        {
            if (playerBox.intersects(box))
                return false; // Â‰«ﬂ  ’«œ„
        }
        return true; // ·« ÌÊÃœ  ’«œ„
    }

    //  ‰ŸÌ› ﬂ· «·√‘Ì«¡
    static void clear()
    {
        collidables.clear();
    }
};