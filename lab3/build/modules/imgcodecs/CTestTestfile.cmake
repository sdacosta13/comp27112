# CMake generated Testfile for 
# Source directory: /home/sam/Downloads/opencv-master/modules/imgcodecs
# Build directory: /home/sam/Downloads/build/modules/imgcodecs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_imgcodecs "/home/sam/Downloads/build/bin/opencv_test_imgcodecs" "--gtest_output=xml:opencv_test_imgcodecs.xml")
set_tests_properties(opencv_test_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Accuracy" WORKING_DIRECTORY "/home/sam/Downloads/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/sam/Downloads/opencv-master/cmake/OpenCVUtils.cmake;1707;add_test;/home/sam/Downloads/opencv-master/cmake/OpenCVModule.cmake;1315;ocv_add_test_from_target;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;166;ocv_add_accuracy_tests;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;0;")
add_test(opencv_perf_imgcodecs "/home/sam/Downloads/build/bin/opencv_perf_imgcodecs" "--gtest_output=xml:opencv_perf_imgcodecs.xml")
set_tests_properties(opencv_perf_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Performance" WORKING_DIRECTORY "/home/sam/Downloads/build/test-reports/performance" _BACKTRACE_TRIPLES "/home/sam/Downloads/opencv-master/cmake/OpenCVUtils.cmake;1707;add_test;/home/sam/Downloads/opencv-master/cmake/OpenCVModule.cmake;1217;ocv_add_test_from_target;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;174;ocv_add_perf_tests;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;0;")
add_test(opencv_sanity_imgcodecs "/home/sam/Downloads/build/bin/opencv_perf_imgcodecs" "--gtest_output=xml:opencv_perf_imgcodecs.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Sanity" WORKING_DIRECTORY "/home/sam/Downloads/build/test-reports/sanity" _BACKTRACE_TRIPLES "/home/sam/Downloads/opencv-master/cmake/OpenCVUtils.cmake;1707;add_test;/home/sam/Downloads/opencv-master/cmake/OpenCVModule.cmake;1218;ocv_add_test_from_target;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;174;ocv_add_perf_tests;/home/sam/Downloads/opencv-master/modules/imgcodecs/CMakeLists.txt;0;")
