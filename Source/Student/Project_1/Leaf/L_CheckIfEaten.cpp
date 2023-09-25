#include <pch.h>
#include "L_CheckIfEaten.h"

L_CheckIfEaten::L_CheckIfEaten() : timer(0.0f)
{}

void L_CheckIfEaten::on_enter()
{
    timer = RNG::range(1.0f, 2.0f);

	BehaviorNode::on_leaf_enter();
}

void L_CheckIfEaten::on_update(float dt)
{
    timer -= dt;

    if (timer < 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
