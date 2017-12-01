/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.    
 *                                                                         
 * This work is licensed under the terms of the MIT license.    
                       
 * For a copy, see <https://opensource.org/licenses/MIT>.                  
 */                                                                        
/**                                                                        
 * @file SpriteResources.h                                                      
 * This file contains the atomic functions used by the Sprite class methods.          
 */ 
#ifndef INCLUDE_SPRITERESOURCES_H_
#define INCLUDE_SPRITERESOURCES_H_

void check_render_copy_value(int);
void check_query_texture_value(int);

void check_render_copy_value(int render_copy) {
    if (render_copy) {
        printf("Render: %s\n", SDL_GetError());
        exit(-1);
    } else {
        /* Nothing to do. */
    }
}

void check_query_texture_value(int query_texture) {
    if (query_texture) {
        printf("Open: %s\n", SDL_GetError());
        exit(-1);
    } else {
        /* Nothing to do. */
    }
}

#endif  // INCLUDE_SPRITERESOURCES_H_
