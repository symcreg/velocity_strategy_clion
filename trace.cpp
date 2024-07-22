//
// Created by symc on 2024/7/21.
//

#include "trace.h"
#include "iostream"
#include "random"
#include "ctime"
#include "velocity.h"
using namespace std;
Position current_position;
Position *target_positions;
float *distanceBetweenTargets;
float *thetaBetweenTargets;
float initDistance;
float initTheta;
uint8_t current_control_point_id;
float current_theta = 0;
uint16_t distance2target;
uint16_t distance2targetLast;
uint16_t distance2targetNext;

Position init_position = {0, 0, 0, 0};
static uint16_t get_distance(Position &p1, Position &p2);
static float get_theta(Position &p1, Position &p2);
static bool is_target_overlapping(vector<Position> &v, Position &p);
void init_targets(){
    target_positions = new Position[TARGET_NUM];
    distanceBetweenTargets = new float[TARGET_NUM - 1];
    thetaBetweenTargets = new float[TARGET_NUM - 1];
    vector<Position> v;
    srand(time(NULL));
    for(int i = 0; i < TARGET_NUM - 1; i++){
        target_positions[i].id = i;
        //防止目标点出现在地图边缘
        target_positions[i].x = rand() % (MAP_SIZE - 2 * TARGET_RADIUS) + TARGET_RADIUS;
        target_positions[i].y = rand() % (MAP_SIZE - 2 * TARGET_RADIUS) + TARGET_RADIUS;
        while(is_target_overlapping(v, target_positions[i])){
            target_positions[i].x = rand() % (MAP_SIZE - 2 * TARGET_RADIUS) + TARGET_RADIUS;
            target_positions[i].y = rand() % (MAP_SIZE - 2 * TARGET_RADIUS) + TARGET_RADIUS;
        }
        v.push_back(target_positions[i]);
    }
    target_positions[TARGET_NUM - 1].id = TARGET_NUM - 1;
    target_positions[TARGET_NUM - 1].x = init_position.x;
    target_positions[TARGET_NUM - 1].y = init_position.y;

    initDistance  = get_distance(init_position, target_positions[0]);
    initTheta = get_theta(init_position, target_positions[0]);
    for(int i = 0; i < TARGET_NUM - 1; i++){
        distanceBetweenTargets[i] = get_distance(target_positions[i], target_positions[i + 1]);
        thetaBetweenTargets[i] = get_theta(target_positions[i], target_positions[i + 1]);
    }
}
void init_targets_manual(vector<Position> &target_positions_manual){
    if(target_positions_manual.size() != TARGET_NUM - 1){
        return;
    }
    target_positions = new Position[TARGET_NUM];
    distanceBetweenTargets = new float[TARGET_NUM - 1];
    thetaBetweenTargets = new float[TARGET_NUM - 1];
    for(int i = 0; i < TARGET_NUM - 1; i++){
        target_positions[i].id = target_positions_manual[i].id;
        target_positions[i].x = target_positions_manual[i].x;
        target_positions[i].y = target_positions_manual[i].y;
        cout<<"-Target "<<i<<" position update - position ("<<target_positions[i].x<<", "<<target_positions[i].y<<")"<<endl;
    }
    target_positions[TARGET_NUM - 1].id = TARGET_NUM - 1;
    target_positions[TARGET_NUM - 1].x = init_position.x;
    target_positions[TARGET_NUM - 1].y = init_position.y;

    initDistance  = get_distance(init_position, target_positions[0]);
    initTheta = get_theta(init_position, target_positions[0]);
    for(int i = 0; i < TARGET_NUM - 1; i++){
        distanceBetweenTargets[i] = get_distance(target_positions[i], target_positions[i + 1]);
        thetaBetweenTargets[i] = get_theta(target_positions[i], target_positions[i + 1]);
    }
}
void update_control_point(){
    if(distance2target < TARGET_RADIUS){
        cout<<"*Arrived at target "<<current_control_point_id<<endl;
        current_control_point_id++;
        if(current_control_point_id >= TARGET_NUM){
            current_control_point_id = 0;
        }
    }
}
void update_distances(){
    distance2target = get_distance(current_position, target_positions[current_control_point_id]);
    if(current_control_point_id == 0){
        distance2targetLast = get_distance(current_position, init_position);
    }else{
        distance2targetLast = get_distance(current_position, target_positions[current_control_point_id - 1]);
    }
    if(current_control_point_id == TARGET_NUM - 1){
        distance2targetNext = get_distance(current_position, init_position);
    }else{
        distance2targetNext = get_distance(current_position, target_positions[current_control_point_id + 1]);
    }
}
void current_position_move(){
    current_theta = get_theta(current_position, target_positions[current_control_point_id]);
    current_position.x += (float)(velocity * cos(current_theta));
    current_position.y += (float)(velocity * sin(current_theta));
}
void update_current_position(int16_t x, int16_t y){
    current_position.x = x;
    current_position.y = y;
}
uint16_t get_distance(Position &p1, Position &p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
float get_theta(Position &p1, Position &p2){
    return atan2(p2.y - p1.y, p2.x - p1.x);
}
bool is_target_overlapping(vector<Position> &v, Position &p){
    for(int i = 0; i < v.size(); i++){
        if(get_distance(v[i], p) < TARGET_RADIUS - 5){
            return true;
        }
    }
    return false;
}
void delete_targets(){
    delete[] target_positions;
    delete[] distanceBetweenTargets;
    delete[] thetaBetweenTargets;
}