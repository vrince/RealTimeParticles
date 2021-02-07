#pragma once

//#include "CL/cl.h"
#include <array>
#include <vector>

#include "Physics.hpp"
#include "ocl/Context.hpp"
#include "utils/RadixSort.hpp"

namespace Core
{
class Boids : public Physics
{
  public:
  Boids(size_t numEntities, size_t boxSize, size_t gridRes,
      unsigned int pointCloudCoordVBO,
      unsigned int pointCloudColorVBO,
      unsigned int gridDetectorVBO);
  ~Boids() = default;

  void update() override;
  void reset() override;

  //
  void setVelocity(float velocity) override
  {
    m_velocity = velocity;
    updateBoidsParamsInKernel();
  }

  void setScaleAlignment(float alignment)
  {
    m_scaleAlignment = alignment;
    updateBoidsParamsInKernel();
  }
  float scaleAlignment() const { return m_scaleAlignment; }

  void activateAlignment(bool alignment)
  {
    m_activeAlignment = alignment;
    updateBoidsParamsInKernel();
  }
  bool isAlignmentActivated() const { return m_activeAlignment; }

  //

  void setScaleCohesion(float cohesion)
  {
    m_scaleCohesion = cohesion;
    updateBoidsParamsInKernel();
  }
  float scaleCohesion() const { return m_scaleCohesion; }

  void activateCohesion(bool cohesion)
  {
    m_activeCohesion = cohesion;
    updateBoidsParamsInKernel();
  }
  bool isCohesionActivated() const { return m_activeCohesion; }

  //

  void setScaleSeparation(float separation)
  {
    m_scaleSeparation = separation;
    updateBoidsParamsInKernel();
  }
  float scaleSeparation() const { return m_scaleSeparation; }

  void activateSeparation(bool separation)
  {
    m_activeSeparation = separation;
    updateBoidsParamsInKernel();
  }
  bool isSeparationActivated() const { return m_activeSeparation; }

  //

  void activateTarget(bool targets)
  {
    m_activeTargets = targets;
    updateBoidsParamsInKernel();
  }
  bool isTargetActivated() const { return m_activeTargets; }

  private:
  bool createProgram() const;
  bool createBuffers(unsigned int pointCloudCoordVBO, unsigned int pointCloudColorVBO, unsigned int gridDetectorVBO) const;
  bool createKernels() const;
  void updateBoidsParamsInKernel();
  void updateGridParamsInKernel();

  bool m_activeAlignment;
  bool m_activeCohesion;
  bool m_activeSeparation;

  float m_scaleAlignment;
  float m_scaleCohesion;
  float m_scaleSeparation;

  bool m_activeTargets;

  size_t m_maxNbPartsInCell;

  Math::float3 m_target;

  RadixSort m_radixSort;
};
}