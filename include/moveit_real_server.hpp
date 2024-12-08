#ifndef MOVEIT_SERVER_HPP
#define MOVEIT_SERVER_HPP

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <oss_interfaces/srv/pose_req.hpp>
#include <oss_interfaces/srv/joint_sat.hpp>
#include <oss_interfaces/srv/load_exp.hpp>
#include <std_srvs/srv/set_bool.hpp>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.h>
#include <geometry_msgs/msg/point.h>
#include <moveit_msgs/msg/constraints.h>
#include <moveit_msgs/msg/orientation_constraint.h>
#include <moveit_msgs/msg/position_constraint.h>
#include <moveit_msgs/msg/robot_state.h>
#include <moveit_msgs/msg/workspace_parameters.h>
#include <oss_interfaces/srv/action_traj.hpp>
#include <string>
#include <vector>

class MoveitRealServer : public rclcpp::Node
{
public:
    MoveitRealServer(std::shared_ptr<rclcpp::Node> move_group_node);
    void trajectory_callback(const std::shared_ptr<oss_interfaces::srv::ActionTraj::Request> request,
      std::shared_ptr<oss_interfaces::srv::ActionTraj::Response> response);

private:
    std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_arm;
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    moveit::core::RobotStatePtr current_state_arm;
    const moveit::core::JointModelGroup *joint_model_group_arm;
    moveit::planning_interface::MoveGroupInterface::Plan my_plan_arm;

    rclcpp::Service<oss_interfaces::srv::ActionTraj>::SharedPtr execute_traj_srv;
};

#endif