//
// Created by symc on 2024/7/21.
//

#ifndef VELOCITY_STRATEGY_DRAWER_H
#define VELOCITY_STRATEGY_DRAWER_H
#include "opencv2/opencv.hpp"
void draw_targets();
void draw_current_position();
void draw_velocity();
void clear_map();
extern cv::Mat map_img;
extern cv::Mat velocity_img;
#endif //VELOCITY_STRATEGY_DRAWER_H
