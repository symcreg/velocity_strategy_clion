#include <iostream>
#include "trace.h"
#include "drawer.h"
#include "velocity.h"
#include "time_sys.h"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

void onClick(int event, int x, int y, int flags, void* userdata);

int main() {
    namedWindow("map", WINDOW_AUTOSIZE);
    namedWindow("velocity", WINDOW_AUTOSIZE);
    setMouseCallback("map", onClick, NULL);
    init_targets();
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
}