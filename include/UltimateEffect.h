#ifndef INCLUDE_ULTIMATEEFFECT_H_
#define INCLUDE_ULTIMATEEFFECT_H_

#include <string>
#include "Effect.h"

class UltimateEffect : public Effect{
 private:
  Sprite aura;
  Rectangle sprite_box;
  float healing_factor;

 public:
  UltimateEffect(Fighter * cparent, string csprite, string caura, string ctags,
                 int frames = 1);

  void update(float delta);
  void render();
  bool is_dead();
  void notify_collision(const GameObject & object);
};

#endif  // INCLUDE_ULTIMATEEFFECT_H_
