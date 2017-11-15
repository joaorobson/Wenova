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

class GameObject {
 public:
    Rectangle box;
    float rotation = 0;

    mutable std::unordered_map<std::string, bool> tags;

 public:
    virtual ~GameObject() {
    }
    virtual void update(float delta) = 0;

    virtual void render() = 0;

    virtual bool is_dead() = 0;

    virtual void notify_collision(const GameObject& object) = 0;

    virtual bool is(const std::string& type) const {
        std::stringstream types(type);
        std::string tag;

        while (types >> tag) {
            if (not tags[tag])
                return false;
        }
        return true;
    }

    virtual void add_tags(std::string ctags) {
        std::stringstream types(ctags);
        std::string tag;

        while (types >> tag) {
            tags[tag] = true;
        }
    }

    virtual void remove_tags(std::string ctags) {
        std::stringstream types(ctags);
        std::string tag;

        while (types >> tag) {
            tags[tag] = false;
        }
    }
};

#endif  // INCLUDE_GAMEOBJECT_H_
