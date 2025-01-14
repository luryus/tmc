#include "global.h"
#include "sound.h"
#include "entity.h"
#include "functions.h"
#include "npc.h"

extern void sub_08060528(Entity*);
extern void sub_080604DC(Entity*);
extern void sub_080606D8(Entity*);
extern void sub_080606C0(Entity*);

extern const s8 gUnk_0810AA70[][4][4];

typedef struct {
    s16 x;
    s16 y;
} Coords16;

extern Coords16 gUnk_0810A66C[];
extern s8* gUnk_0810A918[];

extern void (*const gUnk_0810AA24[])(Entity*);
extern Dialog gUnk_0810AA30[];

void Postman(Entity* this) {
    if ((this->flags & ENT_SCRIPTED) != 0) {
        sub_08060528(this);
    } else {
        gUnk_0810AA24[this->action](this);
    }
}

void sub_08060428(Entity* this) {
    void* data;

    this->timer = 90;
    this->speed = 0x180;
    if (this->type2 != 0) {
        data = GetCurrentRoomProperty(this->type2);
    } else {
        data = NULL;
    }
    sub_0806EE04(this, data, 0);
    this->action = 1;
    InitAnimationForceUpdate(this, 4);
}

void sub_0806045C(Entity* this) {
    u8 bVar1;
    u32 bVar3;
    s32 temp;

    UpdateAnimationSingleFrame(this);
    sub_080604DC(this);
    switch (this->interactType) {
        case 1:
        case 2:
            this->action = 2;
            MessageFromTarget(0);
            break;
        default:
            bVar1 = this->knockbackDirection;
            if (bVar1 != this->animationState) {
                this->animationState = bVar1;
                InitAnimationForceUpdate(this, 4 + bVar1);
            }
            temp = GetAnimationStateInRectRadius(this, 0x18, 0x18);
            if ((temp > -1) && (temp == this->animationState)) {
                bVar3 = 1;
            } else {
                bVar3 = 0;
            }
            if (!bVar3) {
                sub_0806EE20(this);
            }
    }
    sub_0806ED78(this);
}

void sub_080604C8(Entity* this) {
    UpdateAnimationSingleFrame(this);
    sub_080604DC(this);
    this->action = 1;
}

void sub_080604DC(Entity* this) {
    Entity* ent;

    if (this->spriteSettings.draw == 1 && CheckOnScreen(this)) {
        if ((this->frame & 1) != 0) {
            this->frame &= 0xfe;
            ent = CreateFx(this, FX_DASH, 0x40);
            if (ent != NULL) {
                ent->y.HALF.HI++;
                SetDefaultPriority(ent, 3);
            }
        }
    }
}

void sub_08060528(Entity* this) {
    switch (this->action) {
        case 0:
            this->action = 1;
            this->spriteSettings.draw = TRUE;
            this->field_0x68.HALF.LO = 0;
            this->field_0x68.HALF.HI = 0;
            this->field_0x6a.HWORD = 0;
            this->field_0x6c.HALF.HI = 0;
            this->field_0x6c.HALF.LO = sub_0801E99C(this);
            sub_0807DD50(this);
            break;
        case 1:
            if (this->interactType == 2) {
                this->action = 3;
                this->interactType = 0;
                sub_0806F118(this);
                InitAnimationForceUpdate(this, sub_0806F5A4(GetFacingDirection(this, &gPlayerEntity)));
            } else {
                if (this->interactType != 0) {
                    this->action = 2;
                    this->interactType = 0;
                    sub_080606D8(this);
                    InitAnimationForceUpdate(this, sub_0806F5A4(GetFacingDirection(this, &gPlayerEntity)));
                } else {
                    sub_0807DD94(this, NULL);
                }
            }
            break;
        case 2:
            UpdateAnimationSingleFrame(this);
            if ((gMessage.doTextBox & 0x7f) != 0) {
                break;
            }
            this->action = 1;
            break;
        case 3:
            UpdateAnimationSingleFrame(this);
            if (!UpdateFuseInteraction(this)) {
                break;
            }
            this->action = 1;
    }
    sub_080604DC(this);
    if (0 < (s16)this->field_0x6a.HWORD) {
        if ((s16)this->field_0x6a.HWORD > 0x12b) {
            this->field_0x6a.HWORD = 0;
            this->zVelocity = Q_16_16(2.0);
            this->field_0x6c.HALF.HI = 1;
            sub_080788E0(this);
            EnqueueSFX(SFX_PLY_JUMP);
        } else {
            this->field_0x6a.HWORD--;
        }
    }
    GravityUpdate(this, Q_8_8(24.0));
    if (((this->field_0x6c.HALF.HI != 0) && (this->zVelocity == 0)) && this->z.WORD == 0) {
        this->field_0x6c.HALF.HI = 0;
        sub_080606C0(this);
    }
    if (this->z.WORD >= 0 &&
        ((gPlayerEntity.collisionLayer == 0 || (this->collisionLayer == gPlayerEntity.collisionLayer)))) {
        sub_0806ED78(this);
    }
    sub_0800451C(this);
}

void sub_080606C0(Entity* this) {
    this->field_0x6c.HALF.LO = sub_0801E99C(this);
    sub_08078784(this, this->field_0x6c.HALF.LO);
}

void sub_080606D8(Entity* this) {
    s32 index;

    index = gSave.global_progress - 2;
    if (index < 0) {
        index = 0;
    }
    ShowNPCDialogue(this, &gUnk_0810AA30[index]);
}

void sub_08060700(Entity* entity, ScriptExecutionContext* context) {
    s8* var0 = gUnk_0810A918[(s8)entity->field_0x68.HALF.LO];
    Coords16* coords = &gUnk_0810A66C[var0[(s8)entity->field_0x68.HALF.HI]];
    u32 x = coords->x + gRoomControls.origin_x;
    u32 y = coords->y + gRoomControls.origin_y;
    sub_0807DEDC(entity, context, x, y);
    gActiveScriptInfo.flags |= 1;
}

void sub_0806075C(Entity* this) {
    this->field_0x68.HALF.LO = 0xb;
    this->field_0x68.HALF.HI = 0xff;
}

void sub_0806076C(Entity* this, ScriptExecutionContext* context) {
    s32 cVar2;
    int iVar4;
    u32 uVar6;
    s32 uVar9;
    int local_24;
    Coords16* ptr;
    s8* pbVar10;

    if (this->z.WORD < 0) {
        gActiveScriptInfo.commandSize = 0;
        return;
    }
    this->field_0x68.HALF.HI++;
    this->collisionLayer = 1;
    sub_080606C0(this);
    pbVar10 = gUnk_0810A918[(s8)this->field_0x68.HALF.LO];
    pbVar10 += (s8)this->field_0x68.HALF.HI;
    do {
        switch ((s8)(pbVar10[0] + 5)) {
            case 5:
                pbVar10++;
                uVar9 = pbVar10[0];
                pbVar10++;
                iVar4 = (s32)Random() % uVar9;
                this->field_0x68.HALF.LO = pbVar10[iVar4];
                this->field_0x68.HALF.HI = 0;
                return;
            case 4:
                this->field_0x6a.HWORD = 300;
                break;
            case 3:
                this->collisionLayer = 1;
                break;
            case 2:
                this->collisionLayer = 2;
                break;
            case 1:
                context->wait = 0x1e;
                this->spriteSettings.draw = 0;
                break;
            case 0:
                pbVar10++;
                uVar9 = *pbVar10++;
                local_24 = ((s32)Random()) % uVar9;

                for (uVar6 = 0; uVar6 < uVar9; uVar6++) {
                    this->field_0x68.HALF.LO = pbVar10[local_24];
                    cVar2 = gUnk_0810A918[(s8)this->field_0x68.HALF.LO][0];
                    ptr = &gUnk_0810A66C[cVar2];
                    this->x.HALF_U.HI = gRoomControls.origin_x + ptr->x;
                    this->y.HALF_U.HI = gRoomControls.origin_y + ptr->y;
                    if (CheckOnScreen(this) == 0)
                        break;
                    local_24 = (s32)(local_24 + 1) % uVar9;
                }
                this->field_0x68.HALF.HI = 0;
                return;
            default:
                return;
        }
        this->field_0x68.HALF.HI++;
        pbVar10++;
    } while (TRUE);
}

void sub_080608E4(Entity* this, ScriptExecutionContext* context) {
    context->condition = 0;
    if (this->z.WORD >= 0) {
        if ((this->collisionLayer != 1 || gPlayerEntity.collisionLayer != 2) &&
            (this->collisionLayer != 2 || gPlayerEntity.collisionLayer != 1)) {
            const s8* ptr = gUnk_0810AA70[context->intVariable][this->animationState >> 1];
            u32 x = this->x.HALF.HI + ptr[0];
            u32 y = this->y.HALF.HI + ptr[1];
            x = gPlayerEntity.x.HALF.HI - x;
            y = gPlayerEntity.y.HALF.HI - y;
            x += ptr[2];
            y += ptr[3];
            if (ptr[2] * 2 > x && ptr[3] * 2 > y) {
                context->condition = 1;
                this->field_0x6a.HWORD += 2;
            }
        }
    }
}

void Postman_Fusion(Entity* this) {
    if (this->action == 0) {
        this->action++;
        this->spriteSettings.draw = 1;
        InitAnimationForceUpdate(this, 2);
    } else {
        UpdateAnimationSingleFrame(this);
    }
}
