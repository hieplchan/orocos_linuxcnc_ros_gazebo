#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <string>

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "joint_angle_node.h"



namespace gazebo
{
  class JointAngleControl : public ModelPlugin
  {
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
      // Store the pointer to the model
      this->model = _parent;

      // Joint Controller
      this->myJointController = new physics::JointController(model);

      // Set joint names
      joint1 = "robotarm::joint1";
      joint2 = "robotarm::joint2";
      joint3 = "robotarm::joint3";
      joint4 = "robotarm::joint4";
      joint5 = "robotarm::joint5";
      joint6 = "robotarm::joint6";

      // Get Pointer to the joints
      joint1_ptr = this->model->GetJoint(joint1);
      joint2_ptr = this->model->GetJoint(joint2);
      joint3_ptr = this->model->GetJoint(joint3);
      joint4_ptr = this->model->GetJoint(joint4);
      joint5_ptr = this->model->GetJoint(joint5);
      joint6_ptr = this->model->GetJoint(joint6);

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&JointAngleControl::OnUpdate, this));

      /*------------------------ROS-------------------------*/
      // Initialize ros, if it has not already bee initialized.
      if (!ros::isInitialized())
      {
        int argc = 0;
        char **argv = NULL;
        ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
      }


      // Create our ROS node. This acts in a similar manner to
      // the Gazebo node
      this->rosNode.reset(new ros::NodeHandle("gazebo_client"));

      // Create a named topic, and subscribe to it.
      ros::SubscribeOptions so = ros::SubscribeOptions::create<joint_angle_msgs::joint_angle_node>("/joint_angle", 1, boost::bind(&JointAngleControl::OnRosMsg, this, _1), ros::VoidPtr(), &this->rosQueue);

      this->rosSub = this->rosNode->subscribe(so);

      // Spin up the queue helper thread.
      this->rosQueueThread = std::thread(std::bind(&JointAngleControl::QueueThread, this));
      /*---------------------ENDROS-------------------------*/

    }


    // Called by the world update start event
    public: void OnUpdate()
    {
      // Set joint positions
      myJointController->SetJointPosition(joint1_ptr, joint1_pos);
      myJointController->SetJointPosition(joint2_ptr, joint2_pos);
      myJointController->SetJointPosition(joint3_ptr, joint3_pos);
      myJointController->SetJointPosition(joint4_ptr, joint4_pos);
      myJointController->SetJointPosition(joint5_ptr, joint5_pos);
      myJointController->SetJointPosition(joint6_ptr, joint6_pos);
    }

    /*------------------------ROS-------------------------*/

    /// \brief Handle an incoming message from ROS
    /// \param[in] _msg A float value that is used to set the velocity
    /// of the Velodyne.
    public: void OnRosMsg(const joint_angle_msgs::joint_angle_node::ConstPtr& msg)
    {
      joint1_pos = msg->joint1;
      joint2_pos = msg->joint2;
      joint3_pos = msg->joint3;
      joint4_pos = msg->joint4;
      joint5_pos = msg->joint5;
      joint6_pos = msg->joint6;

      ROS_INFO("Joint1: %f\n", joint1_pos);
      ROS_INFO("Joint2: %f\n", joint2_pos);
      ROS_INFO("Joint3: %f\n", joint3_pos);
      ROS_INFO("Joint4: %f\n", joint4_pos);
      ROS_INFO("Joint5: %f\n", joint5_pos);
      ROS_INFO("Joint6: %f\n", joint6_pos);

      ROS_INFO("------------");
    }

    /// \brief ROS helper function that processes messages
    private: void QueueThread()
    {
      static const double timeout = 0.01;
      while (this->rosNode->ok())
      {
        this->rosQueue.callAvailable(ros::WallDuration(timeout));
      }
    }
    /*---------------------ENDROS-------------------------*/


    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    // Pointer to the JointContoller
    private: physics::JointController * myJointController;
    //private: physics::JointControllerPtr myJointController2;

    // Joint name variables
    private:
    std::string joint1;
    std::string joint2;
    std::string joint3;
    std::string joint4;
    std::string joint5;
    std::string joint6;

    // Pointer to the joints
    private:
    physics::JointPtr joint1_ptr;
    physics::JointPtr joint2_ptr;
    physics::JointPtr joint3_ptr;
    physics::JointPtr joint4_ptr;
    physics::JointPtr joint5_ptr;
    physics::JointPtr joint6_ptr;

    /// \brief A node use for ROS transport
    private: std::unique_ptr<ros::NodeHandle> rosNode;

    /// \brief A ROS subscriber
    private: ros::Subscriber rosSub;

    /// \brief A ROS callbackqueue that helps process messages
    private: ros::CallbackQueue rosQueue;

    /// \brief A thread the keeps running the rosQueue
    private: std::thread rosQueueThread;

    private: float joint1_pos = 1.0;
    private: float joint2_pos = 1.0;
    private: float joint3_pos = 1.0;
    private: float joint4_pos = 1.0;
    private: float joint5_pos = 1.0;
    private: float joint6_pos = 1.0;

    private: double PI = 3.141592654;

  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(JointAngleControl)
}
