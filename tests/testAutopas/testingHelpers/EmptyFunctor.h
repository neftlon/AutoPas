/**
 * @file EmptyFunctor.h
 * @author seckler
 * @date 26.03.20
 */

#pragma once

#if defined(AUTOPAS_CUDA)
#include "cuda_runtime.h"
#endif

#include "autopas/cells/ParticleCell.h"
#include "autopas/containers/verletListsCellBased/verletLists/VerletListHelpers.h"
#include "autopas/options/DataLayoutOption.h"
#include "autopas/pairwiseFunctors/Functor.h"
#if defined(AUTOPAS_CUDA)
#include "EmptyCudaWrapper.cuh"
#include "autopas/utils/CudaSoA.h"
#endif

/**
 * Empty Functor, this functor is empty and can be used for testing purposes.
 * It returns that it is applicable for everything.
 */
template <class Particle>
class EmptyFunctor : public autopas::Functor<Particle, EmptyFunctor<Particle>> {
 private:
#ifdef AUTOPAS_CUDA
  EmptyCudaWrapper<typename Particle::ParticleSoAFloatPrecision> emptyCudaWrapper;
#endif
 public:
  /**
   * Structure of the SoAs defined by the particle.
   */
  using SoAArraysType = typename Particle::SoAArraysType;

  /**
   * Default constructor.
   */
  EmptyFunctor() : autopas::Functor<Particle, EmptyFunctor<Particle>>(0.){};

  /**
   * @copydoc autopas::Functor::AoSFunctor()
   */
  void AoSFunctor(Particle &i, Particle &j, bool newton3) override {}

  /**
   * @copydoc autopas::Functor::SoAFunctorSingle()
   */
  void SoAFunctorSingle(autopas::SoAView<typename Particle::SoAArraysType> soa, bool newton3) override {}

  /**
   * SoAFunctor for a pair of SoAs.
   * @param soa1 An autopas::SoAView for the Functor
   * @param soa2 A second autopas::SoAView for the Functor
   * @param newton3 A boolean to indicate whether to allow newton3
   */
  void SoAFunctorPair(autopas::SoAView<typename Particle::SoAArraysType> soa1,
                      autopas::SoAView<typename Particle::SoAArraysType> soa2, bool newton3) override {}

#ifdef AUTOPAS_CUDA
  autopas::CudaWrapperInterface<typename Particle::ParticleSoAFloatPrecision> *getCudaWrapper() override {
    return &emptyCudaWrapper;
  }
#endif

  /**
   * @copydoc autopas::Functor::SoAFunctorVerlet()
   */
  void SoAFunctorVerlet(autopas::SoAView<typename Particle::SoAArraysType> soa, size_t indexFirst,
                        const std::vector<size_t, autopas::AlignedAllocator<size_t>> &neighborList,
                        bool newton3) override{};

  /**
   * @copydoc autopas::Functor::allowsNewton3()
   */
  bool allowsNewton3() override { return true; }

  /**
   * @copydoc autopas::Functor::allowsNonNewton3()
   */
  bool allowsNonNewton3() override { return true; }

  /**
   * @copydoc autopas::Functor::isAppropriateClusterSize()
   */
  bool isAppropriateClusterSize(unsigned int clusterSize, autopas::DataLayoutOption::Value dataLayout) const override {
    return true;
  }

  /**
   * @copydoc autopas::Functor::isRelevantForTuning()
   */
  bool isRelevantForTuning() override { return true; }

#if defined(AUTOPAS_CUDA)
  void CudaFunctor(autopas::CudaSoA<typename Particle::CudaDeviceArraysType> &device_handle, bool newton3) override {}

  void CudaFunctor(autopas::CudaSoA<typename Particle::CudaDeviceArraysType> &device_handle1,
                   autopas::CudaSoA<typename Particle::CudaDeviceArraysType> &device_handle2, bool newton3) override {}

  /**
   * @copydoc autopas::Functor::deviceSoALoader()
   */
  void deviceSoALoader(autopas::SoA<SoAArraysType> &soa,
                       autopas::CudaSoA<typename Particle::CudaDeviceArraysType> &device_handle) override {}

  /**
   * @copydoc autopas::Functor::deviceSoAExtractor()
   */
  void deviceSoAExtractor(autopas::SoA<SoAArraysType> &soa,
                          autopas::CudaSoA<typename Particle::CudaDeviceArraysType> &device_handle) override {}

#endif
};
