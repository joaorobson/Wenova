/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file GameObject.h
 * Brief Description.
 */

#ifndef INCLUDE_GAMEOBJECT_H_
#define INCLUDE_GAMEOBJECT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Rectangle.h"

using std::string;
using std::stringstream;
using std::unordered_map;

class GameObject {
 public:
    virtual ~GameObject() {
    }
    virtual void update(float delta) = 0;

    virtual void render() = 0;
    virtual bool is_dead() = 0;
    virtual void notify_collision(GameObject& object) = 0;
    virtual bool is(string type) {
        stringstream types(type);
        string tag;
        while (types >> tag) {
            if (not tags[tag])
                return false;
        }
        return true;
    }

    virtual void add_tags(string ctags) {
        stringstream types(ctags);
        string tag;
        while (types >> tag) {
            tags[tag] = true;
        }
    }

    virtual void remove_tags(string ctags) {
        stringstream types(ctags);
        string tag;
        while (types >> tag) {
            tags[tag] = false;
        }
    }

    Rectangle box;
    float rotation = 0;

    unordered_map<string, bool> tags;
};

#endif  // INCLUDE_GAMEOBJECT_H_
