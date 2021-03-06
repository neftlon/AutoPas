/**
 * @file Generator.h
 * @author N. Fottner
 * @date 1/8/19
 */

#pragma once

#include <vector>

#include "Objects/CubeClosestPacked.h"
#include "Objects/CubeGauss.h"
#include "Objects/CubeGrid.h"
#include "Objects/CubeUniform.h"
#include "Objects/Sphere.h"
#include "PrintableMolecule.h"
#include "autopas/AutoPas.h"
#include "autopas/utils/ArrayMath.h"
#include "autopasTools/generators/ClosestPackingGenerator.h"
#include "autopasTools/generators/GaussianGenerator.h"
#include "autopasTools/generators/GridGenerator.h"
#include "autopasTools/generators/RandomGenerator.h"
/**
 * Class for contructing a container and generating Objects and Shapes filled with Particles
 */
class Generator {
 public:
  /**
   * Generates a 3d grid of particles that is specified by the given CubeGrid object.
   * @tparam Particle
   * @tparam ParticleCell
   * @param autopas
   * @param object
   */
  template <class Particle>
  static void cubeGrid(autopas::AutoPas<Particle> &autopas, const CubeGrid &object);

  /**
   * Generates particles 3d gaussian distributed within a cube that is specified by the given CubeGauss object.
   * @tparam Particle
   * @tparam ParticleCell
   * @param autopas
   * @param object
   */
  template <class Particle>
  static void cubeGauss(autopas::AutoPas<Particle> &autopas, const CubeGauss &object);

  /**
   * Generates particles uniformly distributed within a cube that is specified by the given CubeUniform object.
   * @tparam Particle
   * @tparam ParticleCell
   * @param autopas
   * @param object
   */
  template <class Particle>
  static void cubeRandom(autopas::AutoPas<Particle> &autopas, const CubeUniform &object);

  /**
   * Generates a sphere of particles that is specified by the given Sphere object.
   * @tparam Particle
   * @param autopas
   * @param object
   */
  template <class Particle>
  static void sphere(autopas::AutoPas<Particle> &autopas, const Sphere &object);

  /**
   * Generates a cube of particles that are arranged with the hexagonal closest packing.
   * @tparam Particle
   * @param autopas
   * @param object
   */
  template <class Particle>
  static void cubeClosestPacked(autopas::AutoPas<Particle> &autopas, const CubeClosestPacked &object);
};

template <class Particle>
void Generator::cubeGrid(autopas::AutoPas<Particle> &autopas, const CubeGrid &object) {
  Particle dummyParticle;
  dummyParticle.setV(object.getVelocity());
  dummyParticle.setID(autopas.getNumberOfParticles());
  dummyParticle.setTypeId(object.getTypeId());
  autopasTools::generators::GridGenerator::fillWithParticles(
      autopas, object.getParticlesPerDim(), dummyParticle,
      {object.getParticleSpacing(), object.getParticleSpacing(), object.getParticleSpacing()}, object.getBoxMin());
}

template <class Particle>
void Generator::cubeGauss(autopas::AutoPas<Particle> &autopas, const CubeGauss &object) {
  Particle dummyParticle;
  dummyParticle.setV(object.getVelocity());
  dummyParticle.setID(autopas.getNumberOfParticles());
  dummyParticle.setTypeId(object.getTypeId());
  autopasTools::generators::GaussianGenerator::fillWithParticles(
      autopas, object.getBoxMin(), object.getBoxMax(), object.getParticlesTotal(), dummyParticle,
      object.getDistributionMean(), object.getDistributionStdDev());
}

template <class Particle>
void Generator::cubeRandom(autopas::AutoPas<Particle> &autopas, const CubeUniform &object) {
  Particle dummyParticle;
  dummyParticle.setV(object.getVelocity());
  dummyParticle.setTypeId(object.getTypeId());
  dummyParticle.setID(autopas.getNumberOfParticles());
  autopasTools::generators::RandomGenerator::fillWithParticles(autopas, dummyParticle, object.getBoxMin(),
                                                               object.getBoxMax(), object.getParticlesTotal());
}

template <class Particle>
void Generator::sphere(autopas::AutoPas<Particle> &autopas, const Sphere &object) {
  Particle dummyParticle({0, 0, 0}, object.getVelocity(), autopas.getNumberOfParticles(), object.getTypeId());
  object.iteratePositions([&](auto pos) {
    dummyParticle.setR(pos);
    autopas.addParticle(dummyParticle);
    dummyParticle.setID(dummyParticle.getID() + 1);
  });
}

template <class Particle>
void Generator::cubeClosestPacked(autopas::AutoPas<Particle> &autopas, const CubeClosestPacked &object) {
  Particle dummyParticle;
  dummyParticle.setV(object.getVelocity());
  dummyParticle.setID(autopas.getNumberOfParticles());
  dummyParticle.setTypeId(object.getTypeId());
  autopasTools::generators::ClosestPackingGenerator::fillWithParticles(autopas, object.getBoxMin(), object.getBoxMax(),
                                                                       dummyParticle, object.getParticleSpacing());
}
