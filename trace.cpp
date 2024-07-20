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
uint16_t current_control_point_id = 0;
float current_theta = 0;
uint16_t distance2target;
uint16_t distance2targetLast;
uint16_t distance2targetNext;

static uint16_t get_distance(Position &p1, Position &p2);
static float get_theta(Position &p1, Position &p2);
static bool is_target_overlapping(vector<Position> &v, Position &p);
void init_targets(){
    target_positions = new Position[TARGET_NUM];
    vector<Position> v;
    srand(time(NULL));
    for(int i = 0; i < TARGET_NUM; i++){
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
        distance2targetLast = get_distance(current_position, target_positions[TARGET_NUM - 1]);
    }else{
        distance2targetLast = get_distance(current_position, target_positions[current_control_point_id - 1]);
    }
    if(current_control_point_id == TARGET_NUM - 1){
        distance2targetNext = get_distance(current_position, target_positions[0]);
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
}