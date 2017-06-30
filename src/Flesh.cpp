#include "Flesh.h"

Flesh::Flesh(string skin, float x, float y, int cid, Fighter *cpartner) : Fighter(cid, x, cpartner){
	path = "flesh/" + skin + "/";

	sprite[IDLE] = Sprite(path + "idle.png", 8, 10);
	sprite[RUNNING] = Sprite(path + "running.png", 8, 10);
	sprite[JUMPING] = Sprite(path + "jumping.png", 6, 10);
	sprite[FALLING] = Sprite(path + "falling.png", 7, 10);
	sprite[CROUCH] = Sprite(path + "crouch.png", 6, 20);
	sprite[IDLE_ATK_NEUTRAL_1] = Sprite(path + "idle_atk_neutral.png", 12, 10);
	sprite[IDLE_ATK_NEUTRAL_2] = Sprite(path + "idle_atk_neutral.png", 12, 10);
	sprite[IDLE_ATK_NEUTRAL_3] = Sprite(path + "idle_atk_neutral.png", 12, 10);
	sprite[IDLE_ATK_FRONT] = Sprite(path + "idle_atk_front.png", 4, 10);
	sprite[JUMP_ATK_DOWN_FALLLOOP] = Sprite(path + "jump_atk_down_fallloop.png", 3, 10);
	sprite[JUMP_ATK_DOWN_DMG] = Sprite(path + "jump_atk_down_dmg.png", 3, 10);
	sprite[IDLE_ATK_DOWN] = Sprite(path + "idle_atk_down.png", 4, 10);

	crouching_size = Vector(84, 59);
	not_crouching_size = Vector(84, 84);

	tags["flesh"] = true;
	tags[skin] = true;
	box = Rectangle(x, y, 84, 84);
}


void Flesh::update_machine_state(float delta){
	switch(state){
		case FighterState::IDLE_ATK_NEUTRAL_1:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
				check_idle_atk_neutral_2();
			}else if(pressed[ATTACK_BUTTON]){
				combo++;
			}
		break;

		case FighterState::IDLE_ATK_NEUTRAL_2:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
				check_idle_atk_neutral_3();
			}else if(pressed[ATTACK_BUTTON]){
				combo++;
			}
		break;

		case FighterState::IDLE_ATK_NEUTRAL_3:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
			}
		break;

		case FighterState::IDLE_ATK_FRONT:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
			}
		break;

		case FighterState::JUMP_ATK_DOWN_FALLLOOP:
			speed.x = 3 * (orientation == LEFT ? -1 : 1);
			speed.y = 3;

			check_jump_atk_down_dmg();
			if(on_floor){
				printf("to no chao, parsa\n");
				speed.x = 0;
				speed.y = 0;
				check_idle();
				check_left();
				check_right();
			}
		break;

		case FighterState::JUMP_ATK_DOWN_DMG:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
			}
		break;

		case FighterState::IDLE_ATK_DOWN:
			if(sprite[state].is_finished()){
				check_idle();
				check_crouch();
			}
		break;

		case FighterState::IDLE:
			combo = 0;
			check_jump();
			check_left();
			check_right();
			check_idle_atk_down();
			check_crouch();
			check_fall();
			check_idle_atk_neutral_1();
			check_idle_atk_front();
		break;

		case FighterState::JUMPING:
			check_left(false);
			check_right(false);
			check_fall();
			check_jump_atk_down_fallloop();
			check_idle();
		break;

		case FighterState::FALLING:
			check_idle();
			check_left(false);
			check_right(false);
			check_fall();
			check_crouch();
			check_jump_atk_down_fallloop();
		break;

		case FighterState::RUNNING:
			check_jump();
			check_left(false);
			check_right(false);
			check_idle();
			check_crouch();
			check_idle_atk_neutral_1();
			check_idle_atk_front();
			check_fall();
		break;

		case FighterState::CROUCH:
			check_idle();
			check_fall();
		break;
	}
}

void Flesh::check_jump(bool change){
	if(pressed[JUMP_BUTTON]){
		if(change) temporary_state = FighterState::JUMPING;
		speed.y = -5;
		on_floor = false;
	}
}

void Flesh::check_fall(bool change){
	if(speed.y > 0){
		if(change) temporary_state = FighterState::FALLING;
	}
}

void Flesh::check_left(bool change){
	if(is_holding[LEFT_BUTTON]){
		if(change) temporary_state = FighterState::RUNNING;
		speed.x = -2;
		orientation = Orientation::LEFT;
	}
}

void Flesh::check_right(bool change){
	if(is_holding[RIGHT_BUTTON]){
		if(change) temporary_state = FighterState::RUNNING;
		speed.x = 2;
		orientation = Orientation::RIGHT;
	}
}

void Flesh::check_idle(bool change){
	if(speed.x == 0 and on_floor and not is_holding[DOWN_BUTTON]){
		if(change) temporary_state = FighterState::IDLE;
		printf("Temporary state = %d\n", temporary_state);
	}
}

void Flesh::check_crouch(bool change){
	if(is_holding[DOWN_BUTTON] and not is_holding[ATTACK_BUTTON] and on_floor){
   		if(change) temporary_state = FighterState::CROUCH;
    }
}

void Flesh::check_idle_atk_neutral_1(bool change){
	if(pressed[ATTACK_BUTTON] and not is_holding[DOWN_BUTTON]){
		if(change) temporary_state = FighterState::IDLE_ATK_NEUTRAL_1;
	}
}

void Flesh::check_idle_atk_neutral_2(bool change){
	printf("Pressing: %d\n", is_holding[ATTACK_BUTTON]);
	if(combo){
		combo--;
		if(change) temporary_state = FighterState::IDLE_ATK_NEUTRAL_2;
	}
}

void Flesh::check_idle_atk_neutral_3(bool change){
	if(combo){
		combo--;
		if(change) temporary_state = FighterState::IDLE_ATK_NEUTRAL_3;
	}
}

void Flesh::check_idle_atk_front(bool change){
	if(pressed[ATTACK_BUTTON] and (is_holding[LEFT_BUTTON] or is_holding[RIGHT_BUTTON])){
		if(change) temporary_state = FighterState::IDLE_ATK_FRONT;
		orientation = is_holding[LEFT_BUTTON] ? Orientation::LEFT : Orientation::RIGHT;
	}
}

void Flesh::check_jump_atk_down_fallloop(bool change){
	if(pressed[ATTACK_BUTTON] and is_holding[DOWN_BUTTON]){
		if(change) temporary_state = FighterState::JUMP_ATK_DOWN_FALLLOOP;
	}
}

void Flesh::check_jump_atk_down_dmg(bool change){
	if(grab){
		if(change) temporary_state = FighterState::JUMP_ATK_DOWN_DMG;
	}
}

void Flesh::check_idle_atk_down(bool change){
	if(is_holding[ATTACK_BUTTON] and is_holding[DOWN_BUTTON]){
		if(change) temporary_state = FighterState::IDLE_ATK_DOWN;
	}
}

void Flesh::check_pass_through_platform(bool change){

}

void Flesh::check_defense(bool change){

}

void Flesh::check_stunt(bool change){

}

void Flesh::check_dead(bool change){

}