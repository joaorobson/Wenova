/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file State.cpp
 * Brief Description.
 */

#include "State.h"

#include "Collision.h"

/**
 * Brief Description.
 */
State::State() {
    m_pop_requested = m_quit_requested = false;
}

/**
 * Brief Description.
 */
State::~State() {
}

/**
 * Brief Description.
 *
 * @param object
 */
void State::add_object(GameObject* object) {
    object_array.emplace_back(object);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool State::pop_requested() {
    return m_pop_requested;
}

/**
 * Brief Description.
 *
 * @returns
 */
bool State::quit_requested() {
    return m_quit_requested;
}

/**
 * Brief Description.
 *
 * @param delta
 */
void State::update_array(float delta) {
    // collision tests
    for (unsigned i = 0; i < object_array.size(); ++i) {
        for (unsigned j = i + 1; j < object_array.size(); ++j) {
            auto a = object_array[i].get();
            auto b = object_array[j].get();
            if (Collision::is_colliding(a->box, b->box, a->rotation,
                                        b->rotation)) {
                a->notify_collision(*b);
                b->notify_collision(*a);
            }
        }
    }

    // update
    for (unsigned it = 0; it < object_array.size(); ++it) {
        object_array[it]->update(delta);
    }

    // death check
    for (unsigned it = 0; it < object_array.size(); ++it) {
        if (object_array[it]->is_dead()) {
            object_array.erase(object_array.begin() + it);
            break;
        }
    }
}

/**
 * Brief Description.
 */
void State::render_array() {
    for (auto& go : object_array) {
        go->render();
    }
}

/**
 * Brief Description.
 */
void State::load_assets() {
    // NOTHING TO DO
}
