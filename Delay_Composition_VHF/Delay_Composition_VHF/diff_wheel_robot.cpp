#include "stdafx.h"
#include "common.h"
#include "diff_wheel_robot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 전역 좌표계에서 로봇의 위치와 방향
double _robot_x = 0.;
double _robot_y = 0.;
double _robot_theta = _DEG2RAD*0;

// 차동바퀴형 로봇의 바퀴 크기 및 바퀴간 거리
double _wheel_radius = 0.2;
double _axle_length = 0.4;


// 좌우 모터 공통 파라메터
double _motor_acceleration = M_PI*2;
double _motor_max_velocity = M_PI*2;

// 왼쪽 모터
double _target_velocity_left = 0.;
double _current_velocity_left = 0.;
double _current_position_left = 0.;

// 오른쪽 모터
double _target_velocity_right = 0.;
double _current_velocity_right = 0.;
double _current_position_right = 0.;


void limit_velocity (double &velocity)
{
	if (velocity < -_motor_max_velocity) velocity = -_motor_max_velocity;
	else if (velocity > _motor_max_velocity) velocity = _motor_max_velocity;
}

void control_motor_current_velocity (double &current_velocity, double target_velocity, double dt)
{
	if (target_velocity == current_velocity) {
	}
	else if (target_velocity > current_velocity) {
		current_velocity += _motor_acceleration*dt;
		if (target_velocity < current_velocity) {
			current_velocity = target_velocity;
		}
	}
	else { // (target_velocity < current_velocity) {
		current_velocity -= _motor_acceleration*dt;
		if (target_velocity > current_velocity) {
			current_velocity = target_velocity;
		}
	}
}

void robot_move (double dt)
{
	limit_velocity (_target_velocity_left);
	limit_velocity (_target_velocity_right);

	control_motor_current_velocity (_current_velocity_left, _target_velocity_left, dt);
	control_motor_current_velocity (_current_velocity_right, _target_velocity_right, dt);

	limit_velocity (_current_velocity_left);
	limit_velocity (_current_velocity_right);

	_current_position_left  += _current_velocity_left*dt;
	_current_position_right += _current_velocity_right*dt;

	double v = (_current_velocity_right + _current_velocity_left)*_wheel_radius/2;
	double w = (_current_velocity_right - _current_velocity_left)*_wheel_radius/_axle_length;

	if (-0.001 < w && w < 0.001) {
		_robot_x += v*dt*cos(_robot_theta);
		_robot_y += v*dt*sin(_robot_theta);
	}
	else {
		_robot_x += v/w*(sin(_robot_theta + w*dt) - sin(_robot_theta));
		_robot_y -= v/w*(cos(_robot_theta + w*dt) - cos(_robot_theta));
	}
	_robot_theta += w*dt;
}
