/**
 * @file AoSvsCudaTest.h
 * @author jspahl
 * @date 11.02.19
 */

#if defined(AUTOPAS_CUDA)

#pragma once

#include <gtest/gtest.h>

#include <chrono>

#include "AutoPasTestBase.h"
#include "testingHelpers/commonTypedefs.h"

using TestingTuple = std::tuple<bool /*withDeletions*/>;

class AoSvsCudaTest : public AutoPasTestBase, public ::testing::WithParamInterface<TestingTuple> {
 public:
  void generateParticles(std::vector<Molecule> *particles, bool withDeletions);
};

#endif  // AUTOPAS_CUDA
