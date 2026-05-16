
/**
 * Behavior for WDW arrow lifts.
 * When a player stands on an arrow lift, it starts moving between
 * two positions 384 units apart.
 * Arrow lifts move either along the X axis or the Z axis.
 * Their facing angle is always perpendicular to the axis they move on.
 * The angle the arrow lifts move initially is 90º clockwise of the face angle.
 * This means an arrow lift at (0, 0, 0) with face angle 0 (positive Z) will
 * move between (0, 0, 0) and (-384, 0, 0).
 */

/**
 * Move the arrow lift away from its original position.
 */
static s32 arrow_lift_move_away(void) {
    s8 doneMoving = FALSE;

    o->oMoveAngleYaw = o->oFaceAngleYaw - 0x4000;
    o->oVelY = 0;
    o->oForwardVel = 12;
    // Cumulative displacement is used to keep track of how far the platform
    // has travelled, so that it can stop.
    o->oArrowLiftDisplacement += o->oForwardVel;

    // Stop the platform after moving 384 units.
    if (o->oArrowLiftDisplacement > 500) {
        o->oForwardVel = 0;
        o->oArrowLiftDisplacement = 500;
        doneMoving = TRUE;
    }

    obj_move_xyz_using_fvel_and_yaw(o);
    return doneMoving;
}

/**
 * Move the arrow lift back to its original position.
 */
static s8 arrow_lift_move_back(void) {
    s8 doneMoving = FALSE;

    o->oMoveAngleYaw = o->oFaceAngleYaw + 0x4000;
    o->oVelY = 0;
    o->oForwardVel = 12;
    o->oArrowLiftDisplacement -= o->oForwardVel;

    // Stop the platform after returning back to its original position.
    if (o->oArrowLiftDisplacement < 0) {
        o->oForwardVel = 0;
        o->oArrowLiftDisplacement = 0;
        doneMoving = TRUE;
    }

    obj_move_xyz_using_fvel_and_yaw(o);
    return doneMoving;
}

/**
 * Arrow lift update function.
 */
void bhv_arrow_lift_loop(void) {
    switch (o->oAction) {
        case ARROW_LIFT_ACT_IDLE:
            // Wait 61 frames before moving.
            if (o->oTimer > 60) {
                if (gMarioObject->platform == o) {
                    o->oAction = ARROW_LIFT_ACT_MOVING_AWAY;
                }
            }

            break;

        case ARROW_LIFT_ACT_MOVING_AWAY:
            if (arrow_lift_move_away()) {
                o->oAction = ARROW_LIFT_ACT_MOVING_BACK;
            }

            break;

        case ARROW_LIFT_ACT_MOVING_BACK:
            // Wait 61 frames before moving (after stopping after moving forwards).
            if (o->oTimer > 60) {
                if (arrow_lift_move_back()) {
                    o->oAction = ARROW_LIFT_ACT_IDLE;
                }
            }

            break;
    }
}
void bhv_trigger_lava_loop(void) {

    struct Object *lava = cur_obj_nearest_object_with_behavior(bhvRisingLava);
    struct Object *door = cur_obj_nearest_object_with_behavior(bhvDoorCustom);
    if (o->oDistanceToMario < 200.0f && door->oF4 == 0) {
            
            
           
            lava->oF4 = 1;
            door->oF4 = 1;
        
        
    }
}
void bhv_rising_lava_loop(void) {
    if (o->oTimer == 950) o->oF4 = 0;
    if (o->oF4 == 1) {
        if (o->oTimer > 59) o->oPosY += 5.2f;
        
    }
    else {
        o->oTimer = 1;
    }

    
}
void bhv_door_custom_loop(void) {
    
    if (o->oTimer == 20 && o->oF4 == 1) {
        play_sound(SOUND_OBJ_BOWSER_WALK, gGlobalSoundSource);
        set_camera_shake_from_hit(SHAKE_POS_LARGE);
        o->oF4 = 2;
    }
     if (o->oF4 == 1 && o->oTimer < 30) {
         o->oPosY -= 40.0f;
        
    }
    else {
        o->oTimer = 1;
    }
        
}
void bhv_pushable_rolling_log_loop(void) {
f32 distToMario = o->oDistanceToMario;
print_text_fmt_int(20, 20, "DIST TO MARIO: %d", (s32) o->oTimer);
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 450.0f && gMarioState->action == ACT_JUMP_KICK) {
                o->oAction = 1;
                o->oPosY += 20.0f;
            }
            o->oTimer = 0;
        

        

          
        
    
            break;
        case 1: //avance de malade
            if(o->oTimer < 4) {
                o->oPosY += 10.0f;
            }
            o->oPosZ -= 32.0f;
            o->oPosX -= 38.0f;
             if(o->oTimer >= 4) {
                o->oPosY -= o->oTimer*1.18; ;
            }
            if (o->oTimer ==45) {
                o->oAction = 2;
            }
            break;
            case 2:
            break;
    }
    

}