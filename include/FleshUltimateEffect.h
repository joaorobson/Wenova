#ifndef INCLUDE_FLESHULTIMATEEFFECT_H_
#define INCLUDE_FLESHULTIMATEEFFECT_H_

#include "Effect.h"
#include <string>

class FleshUltimateEffect : public Effect{
 public:
  FleshUltimateEffect(Fighter * cparent, string csprite, string ctags,
                        int frames = 1);

  void update(float delta);
  void render();
  bool is_dead();
};

#endif  // INCLUDE_FLESHULTIMATEEFFECT_H_
