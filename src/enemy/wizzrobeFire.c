/**
 * @file wizzrobeFire.c
 * @ingroup Enemies
 *
 * @brief Wizzrobe Fire enemy
 */

#define NENT_DEPRECATED
#include "global.h"
#include "enemy.h"
#include "enemy/wizzrobe.h"
#include "functions.h"

extern void (*const WizzrobeFire_Functions[])(WizzrobeEntity*);
extern void (*const WizzrobeFire_Actions[])(WizzrobeEntity*);

void WizzrobeFire(WizzrobeEntity* this) {
    WizzrobeFire_Functions[GetNextFunction(super)](this);
    SetChildOffset(super, 0, 1, -0x10);
}

void WizzrobeFire_OnTick(WizzrobeEntity* this) {
    WizzrobeFire_Actions[super->action](this);
}

void sub_0802FB74(WizzrobeEntity* this) {
    if (super->field_0x43 != 0) {
        sub_0804A9FC(super, 0x1c);
    }
    sub_0804AA30(super, WizzrobeFire_Functions);
    if (super->health == 0) {
        SetTile(this->tileIndex, this->tilePosition, super->collisionLayer);
    }
}

void WizzrobeFire_Init(WizzrobeEntity* this) {
    Entity* projectile;

    sub_0804A720(super);
    super->action = 1;
    this->timer2 = 0xff;
    this->timer1 = 0x28;
    super->actionDelay = 0x28;
    super->field_0xf = 0x60;
    sub_0802F888(this);
    projectile = CreateProjectileWithParent(super, FIRE_PROJECTILE, 0);
    if (projectile != NULL) {
        super->child = projectile;
        projectile->parent = super;
        projectile->direction = super->direction;
    }
    InitializeAnimation(super, super->direction >> 3);
}

void WizzrobeFire_Action1(WizzrobeEntity* this) {
    u8 tmp;
    Entity* child;

    switch (this->timer2) {
        case 0xff:
            if (--super->field_0xf == 0) {
                this->timer2 = 0;
            }
            break;
        case 0:
            if (--super->actionDelay == 0) {
                this->timer2 += 1;
                super->actionDelay = 0x0e;
                super->flags |= 0x80;
            }
            break;
        case 1:
            if (--super->actionDelay == 0) {
                super->action = 2;
                this->timer2 = 0;
                super->actionDelay = 0x20;
                tmp = super->direction >> 3;
                child = super->child;
                child->actionDelay = 1;
                child->spriteSettings.draw = 1;
                InitializeAnimation(super, tmp | 4);
            }

            break;
    }

    sub_0802F9C8(this);
}

void WizzrobeFire_Action2(WizzrobeEntity* this) {
    switch (this->timer2) {
        case 0:
            switch (--super->actionDelay) {
                case 0:
                    this->timer2 += 1;
                    super->actionDelay = 0x38;
                    super->field_0xf = 0;
                    super->child->spriteSettings.draw = 0;
                    break;
                case 6:
                    if (EntityInRectRadius(super, &gPlayerEntity, 0xa0, 0xa0) && CheckOnScreen(super)) {
                        Entity* projectile = CreateProjectileWithParent(super, FIRE_PROJECTILE, 1);
                        if (projectile != NULL) {
                            projectile->direction = super->direction & 0x18;
                        }
                    }
                    break;
            }
            break;
        case 1:
            if (--super->actionDelay == 0) {
                this->timer2++;
                this->timer1 = 0x28;
                super->actionDelay = 0x28;
                super->field_0xf = 0;
                super->flags &= 0x7f;
                SetTile(this->tileIndex, this->tilePosition, super->collisionLayer);
                EnqueueSFX(SFX_156);
                InitializeAnimation(super, super->direction >> 3);
            }
            break;

        case 2:
            if (--super->actionDelay == 0) {
                this->timer2++;
                super->actionDelay = (Random() & 0x3f) + 0x1c;
                super->spriteSettings.draw = 0;
            }
            break;
        case 3:
            if (--super->actionDelay == 0) {
                super->action = 1;
                this->timer2 = 0;
                this->timer1 = 0x28;
                super->actionDelay = 0x28;
                EnqueueSFX(SFX_156);
                sub_0802F8E4(this);
                InitializeAnimation(super, super->direction >> 3);
            }
            break;
    }
    sub_0802F9C8(this);
}

void (*const WizzrobeFire_Functions[])(WizzrobeEntity*) = {
    WizzrobeFire_OnTick,
    sub_0802FB74,
    (void (*)(WizzrobeEntity*))sub_08001324,
    (void (*)(WizzrobeEntity*))sub_0804A7D4,
    (void (*)(WizzrobeEntity*))sub_08001242,
    WizzrobeFire_OnTick,
};
void (*const WizzrobeFire_Actions[])(WizzrobeEntity*) = {
    WizzrobeFire_Init,
    WizzrobeFire_Action1,
    WizzrobeFire_Action2,
};