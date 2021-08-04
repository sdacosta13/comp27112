# CMake generated Testfile for 
# Source directory: /home/sam/Downloads/opencv-master/modules/ml
# Build directory: /home/sam/Downloads/build/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "/home/sam/Downloads/build/bin/opencv_test_ml" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "/home/sam/Downloads/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/sam/Downloads/opencv-master/cmake/OpenCVUtils.cmake;1707;add_test;/home/sam/Downloads/opencv-master/cmake/OpenCVModule.cmake;1315;ocv_add_test_from_target;/home/sam/Downloads/opencv-master/cmake/OpenCVModule.cmake;1079;ocv_add_accuracy_tests;/home/sam/Downloads/opencv-master/modules/ml/CMakeLists.txt;2;ocv_define_module;/home/sam/Downloads/opencv-master/modules/ml/CMakeLists.txt;0;")
