#pragma once

// 전역 좌표계에서 로봇의 위치와 방향
extern double _robot_x;
extern double _robot_y;
extern double _robot_theta;

// 차동바퀴형 로봇의 바퀴 크기 및 바퀴간 거리
extern double _wheel_radius;
extern double _axle_length;


// 좌우 모터 공통 파라메터
extern double _motor_acceleration;
extern double _motor_max_velocity;

// 왼쪽 모터
extern double _target_velocity_left;
extern double _current_position_left;
// 오른쪽 모터
extern double _target_velocity_right;
extern double _current_position_right;


extern void robot_move (double dt);
