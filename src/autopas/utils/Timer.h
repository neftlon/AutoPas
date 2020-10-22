/**
 * @file Timer.h
 *
 * @date 11.01.2011
 * @author eckhardw
 */

#pragma once

#include <time.h>

#include <vector>

namespace autopas::utils {

/**
 * Timer class to stop times.
 */
class Timer {
 public:
  Timer();

  virtual ~Timer();

  /**
   * Start the timer.
   */
  void start();

  /**
   * Stops the timer and returns the time elapsed in nanoseconds since the last call to start.
   * It also adds the duration to the total time.
   * @return Elapsed time in nanoseconds
   */
  long stop();

  /**
   * Adds the given amount of nanoseconds to the total time.
   * @param nanoseconds
   */
  void addTime(long nanoseconds);

  /**
   * Get total accumulated time.
   * @return Total time in nanoseconds.
   */
  [[nodiscard]] long getTotalTime() const { return _totalTime; }

 private:
  /**
   * Time point of last call of start().
   */
  std::vector<unsigned long long> _startTime;

  /**
   * Helper time struct buffer.
   */
  std::vector<unsigned long long> _tmpTime;

  /**
   * Accumulated total time in nanoseconds.
   */
  long _totalTime = 0;

  /**
   * Indicator if this timer currently is measuring.
   */
  bool _currentlyRunning = false;
};
}  // namespace autopas::utils
