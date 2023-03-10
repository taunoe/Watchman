/*
File: utils_debug.h
Source: https://www.youtube.com/watch?v=7kRlQDxGR9A
Tauno Erik
30.12.2022
*/

#ifdef DEBUG
  #define DEBUG_PRINT(x) \
  Serial.print(x);

  #define DEBUG_PRINTLN(x) \
  Serial.println(x);

  #define DEBUG_PRINT_ALL(x) \
  Serial.print(millis()); \
  Serial.print(": "); \
  Serial.print(__PRETTY_FUNCTION__); \
  Serial.print(" in "); \
  Serial.print(__FILE__); \
  Serial.print(":"); \
  Serial.print(__LINE__); \
  Serial.print(" "); \
  Serial.println(x);
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINT_ALL(x)
#endif