/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file State.h
 * Brief Description.
 */

#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

#include "GameObject.h"

#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;

class State {
 protected:
    bool m_pop_requested;
    bool m_quit_requested;

    vector<unique_ptr<GameObject>> object_array;

    virtual void update_array(float delta);
    virtual void render_array();

 public:
    State();
    virtual ~State();

    virtual void update(float delta) = 0;
    virtual void render() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void add_object(GameObject* object);

    virtual void load_assets();

    bool pop_requested();
    bool quit_requested();
};

#endif  // INCLUDE_STATE_H_
