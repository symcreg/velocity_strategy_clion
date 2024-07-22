//
// Created by symc on 2024/7/21.
//

#include "velocity.h"
#include "trace.h"
#include "math.h"
#include "stdint.h"
#include <iostream>

float velocity = 1;
float bandwidth = 5.0f;
//static void velocity_switch(float ratio);
void velocity_strategy(){
    static float v_max = 1.0f;
    static float v_min = 0.5f;
    static float v = 0;
    // 判断是否在控制点附近
    if(distance2targetLast < TARGET_RADIUS){ //在上一个控制点range内
        v = v_min;
    }else if(distance2targetLast > TARGET_RADIUS + bandwidth) { //添加带宽，防止震荡
        // 根据两个控制点的距离，计算最大速度
        float distanceBetween = 0;
        if(current_control_point_id == 0){
            distanceBetween = initDistance;
        }else{
            distanceBetween = distanceBetweenTargets[current_control_point_id - 1];
        }
        v_max = sqrt(2 * distanceBetween * 0.05f);
        v_min = 0.5f;
        // 根据当前距离，计算当前速度，使用二次函数，在中点速度最大，两端速度v_min，在target_radius处速度为v_min
        float x = ((float)distance2target - TARGET_RADIUS - bandwidth) / (distanceBetween -  2 * (TARGET_RADIUS + bandwidth));
        if(x > 1.0f){
            x = 1.0f;
        }
        if(x < 0.0f){
            x = 0.0f;
        }
        std::cout<<"x:"<<x<<std::endl;
        std::cout<<"distance2targetLast:"<<distance2targetLast<<std::endl;
        std::cout<<"distanceBetween:"<<distanceBetween<<std::endl;
        v = v_min + (v_max - v_min) * ( 1.0f - pow(2 * x - 1, 2));
    }else{ //在缓冲区内
        // 速度不变
    }
    // 速度限制
    if(v > v_max){
        v = v_max;
    }
    if(v < v_min){
        v = v_min;
    }
    velocity = v;

}
//void velocity_switch(float ratio){
//    velocity *= ratio;
//}