FILE(REMOVE_RECURSE
  "/home/osboxes/Desktop/Cognitive-Robotics-Project/catkin_ws/devel/lib/libPvAPI.pdb"
  "/home/osboxes/Desktop/Cognitive-Robotics-Project/catkin_ws/devel/lib/libPvAPI.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/PvAPI.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
