#ifndef TIME_H
#define TIME_H

/**
 * @brief get the curren time in simulator tick
 *
 * @return double the current time in tick
 */
double get_time();

/**
 * @brief update the current time in simulator tick
 * 
 * @param delta the new time in tick
 */
void update_time(double delta);

/**
 * @brief reset the current time to 0
 * 
 */
void reset_time();

#endif // TIME_H