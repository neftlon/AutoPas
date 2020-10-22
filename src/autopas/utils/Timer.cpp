/**
 * @file Timer.cpp
 * @date 18.01.2011
 * @author tchipev
 */

#include "utils/Timer.h"

#include <x86intrin.h>

#include "ExceptionHandler.h"
#include "WrapOpenMP.h"

autopas::utils::Timer::Timer() : _startTime(autopas_get_max_threads()), _tmpTime(autopas_get_max_threads()) {}

autopas::utils::Timer::~Timer() = default;

void autopas::utils::Timer::start() {
  if (_currentlyRunning) {
    autopas::utils::ExceptionHandler::exception("Trying to start a timer that is already started!");
  }
  _currentlyRunning = true;
#ifdef AUTOPAS_OPENMP
#pragma omp parallel for schedule(static, 1)
#endif
  for (size_t t = 0; t < autopas_get_num_threads(); ++t) {
    _startTime[t] = _rdtsc();
  }
}

long autopas::utils::Timer::stop() {
#ifdef AUTOPAS_OPENMP
#pragma omp parallel for schedule(static, 1)
#endif
  for (size_t t = 0; t < autopas_get_num_threads(); ++t) {
    _tmpTime[t] = _rdtsc();
  }

  if (not _currentlyRunning) {
    autopas::utils::ExceptionHandler::exception("Trying to stop a timer that was not started!");
  }
  _currentlyRunning = false;

  long diff = std::numeric_limits<long>::max();
  for (size_t t = 0; t < autopas_get_num_threads(); ++t) {
    const long diffT = _tmpTime[t] - _startTime[t];
    diff = std::min(diff, diffT);
  }

  _totalTime += diff;

  return diff;
}

void autopas::utils::Timer::addTime(long nanoseconds) { _totalTime += nanoseconds; }
