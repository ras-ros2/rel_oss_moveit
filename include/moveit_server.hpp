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
#include <string>
#include <vector>
#include <oss_interfaces/srv/rotate_effector.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <geometric_shapes/shapes.h>
#include <geometric_shapes/shape_operations.h>

using moveit::planning_interface::MoveGroupInterface;

class MoveitServer : public rclcpp::Node, public std::enable_shared_from_this<MoveitServer>
{
public:
    MoveitServer(std::shared_ptr<rclcpp::Node> move_group_node);
    void move_to_pose_callback(const std::shared_ptr<oss_interfaces::srv::PoseReq::Request> request, std::shared_ptr<oss_interfaces::srv::PoseReq::Response> response);
    void rotate_effector_callback(const std::shared_ptr<oss_interfaces::srv::RotateEffector::Request> request, std::shared_ptr<oss_interfaces::srv::RotateEffector::Response> response);
    void joint_state_callback(const sensor_msgs::msg::JointState::SharedPtr msg);
    void sync_callback(const std::shared_ptr<oss_interfaces::srv::JointSat::Request> request,std::shared_ptr<oss_interfaces::srv::JointSat::Response> response);
    void set_constraints(const geometry_msgs::msg::Pose::_orientation_type& quat);
    bool Execute(geometry_msgs::msg::Pose target_pose);
    // void trajectory_callback(const std::shared_ptr<oss_interfaces::srv::ActionTraj::Request> request,
    //   std::shared_ptr<oss_interfaces::srv::ActionTraj::Response> response);
    void AddScenePlane();

private:
    std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_arm;
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    moveit::core::RobotStatePtr current_state_arm;
    const moveit::core::JointModelGroup *joint_model_group_arm;
    moveit::planning_interface::MoveGroupInterface::Plan my_plan_arm;

    rclcpp::Service<oss_interfaces::srv::PoseReq>::SharedPtr move_to_pose_srv_;
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr trajectory_pub;
    rclcpp::Service<oss_interfaces::srv::RotateEffector>::SharedPtr rotate_effector_srv_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Service<oss_interfaces::srv::JointSat>::SharedPtr sync_srv;
    std::vector<float> joint_angle;

    bool fallback_flag;
};

#endif