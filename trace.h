//
// Created by symc on 2024/7/21.
//

#ifndef VELOCITY_STRATEGY_TRACE_H
#define VELOCITY_STRATEGY_TRACE_H

#define TARGET_NUM 7
#define TARGET_RADIUS 25
#define MAP_SIZE 500

#include <stdint.h>
#include <vector>
using namespace std;
typedef struct{
    uint8_t isTarget;
    int16_t id;
    float x;
    float y;
}Position;
extern Position current_position;
extern Position  *target_positions;
extern float *distanceBetweenTargets;
extern float *thetaBetweenTargets;
extern float initDistance;
extern float initTheta;
extern uint8_t current_control_point_id;
extern uint16_t distance2target;
extern uint16_t distance2targetLast;
extern uint16_t distance2targetNext;
void init_targets();
void init_targets_manual(vector<Position> &target_positions_manual);
void delete_targets();

void update_control_point();
void update_distances();
void update_current_position(int16_t x, int16_t y);
void current_position_move();
#endif //VELOCITY_STRATEGY_TRACE_H
