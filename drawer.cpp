//
// Created by symc on 2024/7/21.
//

#include "time_sys.h"
#include "drawer.h"
#include "trace.h"
#include "velocity.h"
#include "iostream"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
Mat map_img = Mat::zeros(MAP_SIZE, MAP_SIZE, CV_8UC3);
Mat velocity_img = Mat::zeros(MAP_SIZE, MAP_SIZE, CV_8UC3);
void draw_targets(){
    for(int i = 0; i < TARGET_NUM; i++){
        circle(map_img, Point(target_positions[i].x, target_positions[i].y), 1, Scalar(0, 0, 255), -1);
        circle(map_img, Point(target_positions[i].x, target_positions[i].y), TARGET_RADIUS, Scalar(0, 0, 255), 1);
        putText(map_img, to_string(i), Point(target_positions[i].x, target_positions[i].y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
    }
}
void draw_current_position(){
    rectangle(map_img, Point(current_position.x - 2, current_position.y - 2), Point(current_position.x + 5, current_position.y + 5), Scalar(0, 255, 0), -1);
}
void draw_velocity(){
    if(current_time * 2 > MAP_SIZE){
        velocity_img = Mat::zeros(MAP_SIZE, MAP_SIZE, CV_8UC3);
        current_time = 0;
    }
    line(velocity_img, Point(current_time * 2, MAP_SIZE), Point(current_time * 2, MAP_SIZE - (int)(velocity * 10)), Scalar(0, 255, 0), 1);
}

void clear_map(){
    map_img = Mat::zeros(MAP_SIZE, MAP_SIZE, CV_8UC3);
}