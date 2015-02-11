#pragma once

// ���� ��ǥ�迡�� �κ��� ��ġ�� ����
extern double _robot_x;
extern double _robot_y;
extern double _robot_theta;

// ���������� �κ��� ���� ũ�� �� ������ �Ÿ�
extern double _wheel_radius;
extern double _axle_length;


// �¿� ���� ���� �Ķ����
extern double _motor_acceleration;
extern double _motor_max_velocity;

// ���� ����
extern double _target_velocity_left;
extern double _current_position_left;
// ������ ����
extern double _target_velocity_right;
extern double _current_position_right;


extern void robot_move (double dt);
