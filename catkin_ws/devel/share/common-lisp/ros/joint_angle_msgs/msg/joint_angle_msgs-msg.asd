
(cl:in-package :asdf)

(defsystem "joint_angle_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "joint_angle_node" :depends-on ("_package_joint_angle_node"))
    (:file "_package_joint_angle_node" :depends-on ("_package"))
  ))