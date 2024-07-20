//
// Created by symc on 2024/7/21.
//

#ifndef VELOCITY_STRATEGY_TRACE_H
#define VELOCITY_STRATEGY_TRACE_H

#define TARGET_NUM 7
#define TARGET_RADIUS 25
#define MAP_SIZE 500

#include <stdint.h>
typedef struct{
    int16_t id;
    float x;
    float y;
}Position;
extern Position current_position;
extern Position  *target_positions;

void init_targets();
void delete_targets();

void update_control_point();
void update_distances();
void update_current_position(int16_t x, int16_t y);
void current_position_move();
#endif //VELOCITY_STRATEGY_TRACE_H
