/**
 * @file YamlParser.cpp
 * @author N. Fottner
 * @date 15.07.2019
 */

#include "YamlParser.h"

#include <sys/stat.h>

#include <ostream>

namespace YamlParser {

bool parseYamlFile(MDFlexConfig &config) {
  YAML::Node node = YAML::LoadFile(config.yamlFilename.value);

  if (node[config.containerOptions.name]) {
    config.containerOptions.value = autopas::ContainerOption::parseOptions(
        autopas::utils::ArrayUtils::to_string(node[config.containerOptions.name], ", ", {"", ""}));
  }
  if (node[config.boxMin.name]) {
    auto tmpNode = node[config.boxMin.name];
    config.boxMin.value = {tmpNode[0].as<double>(), tmpNode[1].as<double>(), tmpNode[2].as<double>()};
  }
  if (node[config.boxMax.name]) {
    auto tmpNode = node[config.boxMax.name];
    config.boxMax.value = {tmpNode[0].as<double>(), tmpNode[1].as<double>(), tmpNode[2].as<double>()};
  }
  if (node[config.selectorStrategy.name]) {
    auto parsedOptions =
        autopas::SelectorStrategyOption::parseOptions(node[config.selectorStrategy.name].as<std::string>());
    if (parsedOptions.size() != 1) {
      throw std::runtime_error("YamlParser::parseYamlFile: Pass exactly one selector strategy option!");
    }
    config.selectorStrategy.value = *parsedOptions.begin();
  }
  if (node[config.periodic.name]) {
    config.periodic.value = node[config.periodic.name].as<bool>();
  }
  if (node[config.cutoff.name]) {
    config.cutoff.value = node[config.cutoff.name].as<double>();
  }
  if (node[config.cellSizeFactors.name]) {
    config.cellSizeFactors.value = autopas::utils::StringUtils::parseNumberSet(
        autopas::utils::ArrayUtils::to_string(node[config.cellSizeFactors.name], ", ", {"", ""}));
  }
  if (node[config.dataLayoutOptions.name]) {
    config.dataLayoutOptions.value = autopas::DataLayoutOption::parseOptions(
        autopas::utils::ArrayUtils::to_string(node[config.dataLayoutOptions.name], ", ", {"", ""}));
  }
  if (node[config.functorOption.name]) {
    auto strArg = node[config.functorOption.name].as<std::string>();
    if (strArg.find("avx") != std::string::npos) {
      config.functorOption.value = MDFlexConfig::FunctorOption::lj12_6_AVX;
    } else if (strArg.find("glob") != std::string::npos) {
      config.functorOption.value = MDFlexConfig::FunctorOption::lj12_6_Globals;
    } else if (strArg.find("lj") != std::string::npos || strArg.find("lennard-jones") != std::string::npos) {
      config.functorOption.value = MDFlexConfig::FunctorOption::lj12_6;
    }
  }
  if (node[config.iterations.name]) {
    config.iterations.value = node[config.iterations.name].as<unsigned long>();
  }
  if (node[config.tuningPhases.name]) {
    config.tuningPhases.value = node[config.tuningPhases.name].as<unsigned long>();
  }
  if (node[config.dontMeasureFlops.name]) {
    // "not" needed because of semantics
    config.dontMeasureFlops.value = not node[config.dontMeasureFlops.name].as<bool>();
  }
  if (node[config.dontCreateEndConfig.name]) {
    // "not" needed because of semantics
    config.dontCreateEndConfig.value = not node[config.dontCreateEndConfig.name].as<bool>();
  }
  if (node[config.newton3Options.name]) {
    config.newton3Options.value = autopas::Newton3Option::parseOptions(
        autopas::utils::ArrayUtils::to_string(node[config.newton3Options.name], ", ", {"", ""}));
  }
  if (node[config.deltaT.name]) {
    config.deltaT.value = node[config.deltaT.name].as<double>();
  }
  if (node[config.traversalOptions.name]) {
    config.traversalOptions.value = autopas::TraversalOption::parseOptions(
        autopas::utils::ArrayUtils::to_string(node[config.traversalOptions.name], ", ", {"", ""}));
  }
  if (node[config.tuningInterval.name]) {
    config.tuningInterval.value = node[config.tuningInterval.name].as<unsigned int>();
  }
  if (node[config.tuningSamples.name]) {
    config.tuningSamples.value = node[config.tuningSamples.name].as<unsigned int>();
  }
  if (node[config.tuningMaxEvidence.name]) {
    config.tuningMaxEvidence.value = node[config.tuningMaxEvidence.name].as<unsigned int>();
  }
  if (node[config.relativeOptimumRange.name]) {
    config.relativeOptimumRange.value = node[config.relativeOptimumRange.name].as<double>();
  }
  if (node[config.maxTuningPhasesWithoutTest.name]) {
    config.maxTuningPhasesWithoutTest.value = node[config.maxTuningPhasesWithoutTest.name].as<unsigned int>();
  }
  if (node[config.tuningStrategyOption.name]) {
    auto parsedOptions =
        autopas::TuningStrategyOption::parseOptions(node[config.tuningStrategyOption.name].as<std::string>());
    if (parsedOptions.size() != 1) {
      throw std::runtime_error("YamlParser::parseYamlFile: Pass exactly one tuning strategy option!");
    }
    config.tuningStrategyOption.value = *parsedOptions.begin();
  }
  if (node[config.logLevel.name]) {
    auto strArg = node[config.logLevel.name].as<std::string>();
    switch (strArg[0]) {
      case 't': {
        config.logLevel.value = autopas::Logger::LogLevel::trace;
        break;
      }
      case 'd': {
        config.logLevel.value = autopas::Logger::LogLevel::debug;
        break;
      }
      case 'i': {
        config.logLevel.value = autopas::Logger::LogLevel::info;
        break;
      }
      case 'w': {
        config.logLevel.value = autopas::Logger::LogLevel::warn;
        break;
      }
      case 'e': {
        config.logLevel.value = autopas::Logger::LogLevel::err;
        break;
      }
      case 'c': {
        config.logLevel.value = autopas::Logger::LogLevel::critical;
        break;
      }
      case 'o': {
        config.logLevel.value = autopas::Logger::LogLevel::off;
        break;
      }
    }
  }
  if (node[config.checkpointfile.name]) {
    config.checkpointfile.value = node[config.checkpointfile.name].as<std::string>();
  }
  if (node[config.logFileName.name]) {
    config.logFileName.value = node[config.logFileName.name].as<std::string>();
  }
  if (node[config.verletRebuildFrequency.name]) {
    config.verletRebuildFrequency.value = node[config.verletRebuildFrequency.name].as<unsigned int>();
  }
  if (node[config.verletSkinRadius.name]) {
    config.verletSkinRadius.value = node[config.verletSkinRadius.name].as<double>();
  }
  if (node[config.verletClusterSize.name]) {
    config.verletClusterSize.value = node[config.verletClusterSize.name].as<unsigned int>();
  }
  if (node[config.vtkFileName.name]) {
    config.vtkFileName.value = node[config.vtkFileName.name].as<std::string>();
  }
  if (node[config.vtkWriteFrequency.name]) {
    config.vtkWriteFrequency.value = node[config.vtkWriteFrequency.name].as<size_t>();
  }
  if (node[config.objectsStr]) {
    // remove default objects
    config.cubeGridObjects.clear();
    config.cubeGaussObjects.clear();
    config.cubeUniformObjects.clear();
    config.sphereObjects.clear();
    config.epsilonMap.value.clear();
    config.sigmaMap.value.clear();
    config.massMap.value.clear();

    for (YAML::const_iterator objectIterator = node[config.objectsStr].begin();
         objectIterator != node[config.objectsStr].end(); ++objectIterator) {
      if (objectIterator->first.as<std::string>() == config.cubeGridObjectsStr) {
        for (YAML::const_iterator it = objectIterator->second.begin(); it != objectIterator->second.end(); ++it) {
          CubeGrid cubeGrid({it->second[MDFlexConfig::velocityStr][0].as<double>(),
                             it->second[MDFlexConfig::velocityStr][1].as<double>(),
                             it->second[MDFlexConfig::velocityStr][2].as<double>()},
                            it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                            it->second[config.epsilonMap.name].as<double>(),
                            it->second[config.sigmaMap.name].as<double>(),
                            it->second[config.massMap.name].as<double>(),
                            {it->second[config.particlesPerDim.name][0].as<unsigned long>(),
                             it->second[config.particlesPerDim.name][1].as<unsigned long>(),
                             it->second[config.particlesPerDim.name][2].as<unsigned long>()},
                            it->second[config.particleSpacing.name].as<double>(),
                            {it->second[MDFlexConfig::bottomLeftBackCornerStr][0].as<double>(),
                             it->second[MDFlexConfig::bottomLeftBackCornerStr][1].as<double>(),
                             it->second[MDFlexConfig::bottomLeftBackCornerStr][2].as<double>()});

          config.cubeGridObjects.emplace_back(cubeGrid);
          config.addParticleType(it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                                 it->second[config.epsilonMap.name].as<double>(),
                                 it->second[config.sigmaMap.name].as<double>(),
                                 it->second[config.massMap.name].as<double>());
        }
        continue;
      }
      if (objectIterator->first.as<std::string>() == config.cubeGaussObjectsStr) {
        for (YAML::const_iterator it = objectIterator->second.begin(); it != objectIterator->second.end(); ++it) {
          CubeGauss cubeGauss({it->second[MDFlexConfig::velocityStr][0].as<double>(),
                               it->second[MDFlexConfig::velocityStr][1].as<double>(),
                               it->second[MDFlexConfig::velocityStr][2].as<double>()},
                              it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                              it->second[config.epsilonMap.name].as<double>(),
                              it->second[config.sigmaMap.name].as<double>(),
                              it->second[config.massMap.name].as<double>(),
                              it->second[MDFlexConfig::particlesPerObjectStr].as<size_t>(),
                              {it->second[config.boxLength.name][0].as<double>(),
                               it->second[config.boxLength.name][1].as<double>(),
                               it->second[config.boxLength.name][2].as<double>()},
                              {it->second[config.distributionMean.name][0].as<double>(),
                               it->second[config.distributionMean.name][1].as<double>(),
                               it->second[config.distributionMean.name][2].as<double>()},
                              {it->second[config.distributionStdDev.name][0].as<double>(),
                               it->second[config.distributionStdDev.name][1].as<double>(),
                               it->second[config.distributionStdDev.name][2].as<double>()},
                              {it->second[MDFlexConfig::bottomLeftBackCornerStr][0].as<double>(),
                               it->second[MDFlexConfig::bottomLeftBackCornerStr][1].as<double>(),
                               it->second[MDFlexConfig::bottomLeftBackCornerStr][2].as<double>()});
          config.cubeGaussObjects.emplace_back(cubeGauss);
          config.addParticleType(it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                                 it->second[config.epsilonMap.name].as<double>(),
                                 it->second[config.sigmaMap.name].as<double>(),
                                 it->second[config.massMap.name].as<double>());
        }
        continue;
      }
      if (objectIterator->first.as<std::string>() == config.cubeUniformObjectsStr) {
        for (YAML::const_iterator it = objectIterator->second.begin(); it != objectIterator->second.end(); ++it) {
          CubeUniform cubeUniform({it->second[MDFlexConfig::velocityStr][0].as<double>(),
                                   it->second[MDFlexConfig::velocityStr][1].as<double>(),
                                   it->second[MDFlexConfig::velocityStr][2].as<double>()},
                                  it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                                  it->second[config.epsilonMap.name].as<double>(),
                                  it->second[config.sigmaMap.name].as<double>(),
                                  it->second[config.massMap.name].as<double>(),
                                  it->second[MDFlexConfig::particlesPerObjectStr].as<size_t>(),
                                  {it->second[config.boxLength.name][0].as<double>(),
                                   it->second[config.boxLength.name][1].as<double>(),
                                   it->second[config.boxLength.name][2].as<double>()},
                                  {it->second[MDFlexConfig::bottomLeftBackCornerStr][0].as<double>(),
                                   it->second[MDFlexConfig::bottomLeftBackCornerStr][1].as<double>(),
                                   it->second[MDFlexConfig::bottomLeftBackCornerStr][2].as<double>()});
          config.cubeUniformObjects.emplace_back(cubeUniform);
          config.addParticleType(it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                                 it->second[config.epsilonMap.name].as<double>(),
                                 it->second[config.sigmaMap.name].as<double>(),
                                 it->second[config.massMap.name].as<double>());
        }
        continue;
      }
      if (objectIterator->first.as<std::string>() == config.sphereObjectsStr) {
        for (YAML::const_iterator it = objectIterator->second.begin(); it != objectIterator->second.end(); ++it) {
          Sphere sphere({it->second[MDFlexConfig::velocityStr][0].as<double>(),
                         it->second[MDFlexConfig::velocityStr][1].as<double>(),
                         it->second[MDFlexConfig::velocityStr][2].as<double>()},
                        it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                        it->second[config.epsilonMap.name].as<double>(),
                        it->second[config.sigmaMap.name].as<double>(), it->second[config.massMap.name].as<double>(),
                        {it->second[MDFlexConfig::sphereCenterStr][0].as<double>(),
                         it->second[MDFlexConfig::sphereCenterStr][1].as<double>(),
                         it->second[MDFlexConfig::sphereCenterStr][2].as<double>()},
                        it->second[MDFlexConfig::sphereRadiusStr].as<int>(),
                        it->second[config.particleSpacing.name].as<double>());
          config.sphereObjects.emplace_back(sphere);
          config.addParticleType(it->second[MDFlexConfig::particleTypeStr].as<unsigned long>(),
                                 it->second[config.epsilonMap.name].as<double>(),
                                 it->second[config.sigmaMap.name].as<double>(),
                                 it->second[config.massMap.name].as<double>());
        }
        continue;
      }
    }
  }
  if (node[config.useThermostat.name]) {
    config.useThermostat.value = true;

    config.initTemperature.value = node[config.useThermostat.name][config.initTemperature.name].as<double>();
    config.thermostatInterval.value = node[config.useThermostat.name][config.thermostatInterval.name].as<size_t>();
    config.targetTemperature.value = node[config.useThermostat.name][config.targetTemperature.name].as<double>();
    config.deltaTemp.value = node[config.useThermostat.name][config.deltaTemp.name].as<double>();
    config.addBrownianMotion.value = node[config.useThermostat.name][config.addBrownianMotion.name].as<bool>();
  }
  return true;
}

}  // namespace YamlParser