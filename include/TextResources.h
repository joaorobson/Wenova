/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.         
 *                                                                              
 * This work is licensed under the terms of the MIT license.                    
 *                                                                              
 * For a copy, see <https://opensource.org/licenses/MIT>.                       
 */                                                                             
/**                                                                             
 * @file Text.cpp                                                               
 * This file contains the atomic functions used by the Text class methods.                 
 */  

#ifndef INCLUDE_TEXTRESOURCES_H_
#define INCLUDE_TEXTRESOURCES_H_

#include "Resources.h"

void check_texture_value(int);
void check_surface_value(SDL_Surface*);



void check_texture_value(int query_texture) {
    if (query_texture) {
        printf("Remake texture: %s\n", SDL_GetError());
        exit(-1);
    } else {
        /* Nothing to do. */
    }
}

void check_surface_value(SDL_Surface *surface) {
    if (surface == nullptr) {
        printf("%s\n", SDL_GetError());
        exit(-3);
    } else {
        /* Nothing to do. */
    }
}

#endif  // INCLUDE_TEXTRESOURCES_H_
