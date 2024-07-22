#include <iostream>
#include "trace.h"
#include "drawer.h"
#include "velocity.h"
#include "time_sys.h"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
uint8_t r_click_num = 0;
vector<Position> r_click_positions;
void onClick(int event, int x, int y, int flags, void* userdata);

int main() {
    namedWindow("map", WINDOW_AUTOSIZE);
    namedWindow("velocity", WINDOW_AUTOSIZE);
    setMouseCallback("map", onClick, NULL);
//    init_targets();
    while (1){
        imshow("map", map_img);
        imshow("velocity", velocity_img);
        init_targets_manual(r_click_positions);
        waitKey(10);
        if(target_positions != NULL){
            break;
        }
    }
    cout<<"-Initialization completed"<<endl;
    while(waitKey(10) != 27){
        update_time();
        current_position_move();
        update_distances();
        update_control_point();
        velocity_strategy();
        draw_targets();
        draw_current_position();
        draw_velocity();
        imshow("map", map_img);
        imshow("velocity", velocity_img);
        clear_map();
    }
    delete_targets();
    return 0;
}
void onClick(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        update_time();
        cout << "-Current point position update - position (" << x << ", " << y << ")" << endl;
        update_current_position((int16_t)x, (int16_t)y);
    }
    if (event == EVENT_RBUTTONDOWN){
        cout << "-Control point position update - position (" << x << ", " << y << ")" << endl;
        r_click_positions.push_back({1, r_click_num, (float)x, (float)y});
        circle(map_img, Point(x, y), 1, Scalar(0, 0, 255), -1);
        circle(map_img, Point(x, y), TARGET_RADIUS, Scalar(0, 0, 255), 1);
        r_click_num++;
    }
}