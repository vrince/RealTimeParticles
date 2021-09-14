#include "PhysicsWidget.hpp"

#include <imgui.h>

void UI::PhysicsWidget::display()
{
  auto* boidsEngine = dynamic_cast<Physics::Boids*>(m_physicsEngine);
  auto* fluidsEngine = dynamic_cast<Physics::Fluids*>(m_physicsEngine);

  if (boidsEngine)
    displayBoidsParameters(boidsEngine);
  else if (fluidsEngine)
    displayFluidsParameters(fluidsEngine);
}

void UI::PhysicsWidget::displayFluidsParameters(Physics::Fluids* fluidsEngine)
{
  if (!fluidsEngine)
    return;

  displayBoundaryConditions(fluidsEngine);
}

void UI::PhysicsWidget::displayBoidsParameters(Physics::Boids* boidsEngine)
{
  if (!boidsEngine)
    return;

  // First default pos
  ImGui::SetNextWindowPos(ImVec2(60, 430), ImGuiCond_FirstUseEver);

  ImGui::Begin("Boids Widget", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::PushItemWidth(150);

  ImGui::Spacing();
  ImGui::Text("Target");
  ImGui::Spacing();

  bool isTarget = boidsEngine->isTargetActivated();
  if (ImGui::Checkbox("Activate", &isTarget))
  {
    boidsEngine->activateTarget(isTarget);
    boidsEngine->setTargetVisibility(isTarget);
  }

  if (isTarget)
  {
    bool isTargetVisible = boidsEngine->isTargetVisible();
    if (ImGui::Checkbox("Show", &isTargetVisible))
    {
      boidsEngine->setTargetVisibility(isTargetVisible);
    }

    float targetRadius = boidsEngine->targetRadiusEffect();
    if (ImGui::SliderFloat("##targetRadius", &targetRadius, 30.0f, 1000.0f))
    {
      boidsEngine->setTargetRadiusEffect(targetRadius);
    }

    int targetSign = boidsEngine->targetSignEffect();

    bool repulse = (targetSign < 0);
    if (ImGui::Checkbox("Repulse", &repulse))
    {
      boidsEngine->setTargetSignEffect(-1);
    }

    ImGui::SameLine();

    bool attract = (targetSign > 0);
    if (ImGui::Checkbox("Attract", &attract))
    {
      boidsEngine->setTargetSignEffect(1);
    }
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  ImGui::Text("Boids Rules");
  ImGui::Spacing();

  bool isAlignment = boidsEngine->isAlignmentActivated();
  if (ImGui::Checkbox("Alignment", &isAlignment))
  {
    boidsEngine->activateAlignment(isAlignment);
  }
  if (isAlignment)
  {
    ImGui::PushItemWidth(75);

    float scaleAlignment = boidsEngine->scaleAlignment();
    if (ImGui::SliderFloat("##scaleAlign", &scaleAlignment, 0.0, 3.0f))
    {
      boidsEngine->setScaleAlignment(scaleAlignment);
    }

    ImGui::PushItemWidth(150);
  }

  bool isCohesion = boidsEngine->isCohesionActivated();
  if (ImGui::Checkbox("Cohesion", &isCohesion))
  {
    boidsEngine->activateCohesion(isCohesion);
  }
  if (isCohesion)
  {
    ImGui::PushItemWidth(75);

    float scaleCohesion = boidsEngine->scaleCohesion();
    if (ImGui::SliderFloat("##scaleCoh", &scaleCohesion, 0.0f, 3.0f))
    {
      boidsEngine->setScaleCohesion(scaleCohesion);
    }

    ImGui::PushItemWidth(150);
  }

  bool isSeparation = boidsEngine->isSeparationActivated();
  if (ImGui::Checkbox("Separation", &isSeparation))
  {
    boidsEngine->activateSeparation(isSeparation);
  }
  if (isSeparation)
  {
    ImGui::PushItemWidth(75);

    float scaleSeparation = boidsEngine->scaleSeparation();
    if (ImGui::SliderFloat("##scaleSep", &scaleSeparation, 0.0f, 3.0f))
    {
      boidsEngine->setScaleSeparation(scaleSeparation);
    }

    ImGui::PushItemWidth(150);
  }

  displayBoundaryConditions(boidsEngine);

  ImGui::End();
}

void UI::PhysicsWidget::displayBoundaryConditions(Physics::Model* engine)
{
  if (!engine)
    return;

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();
  ImGui::Text(" Boundary ");
  ImGui::Spacing();

  bool isBouncingWall = (engine->boundary() == Physics::Boundary::BouncingWall);
  if (ImGui::Checkbox("Bouncing Wall", &isBouncingWall))
  {
    if (isBouncingWall)
      engine->setBoundary(Physics::Boundary::BouncingWall);
    else
      engine->setBoundary(Physics::Boundary::CyclicWall);
  }

  ImGui::SameLine();

  bool isCyclicWall = (engine->boundary() == Physics::Boundary::CyclicWall);
  if (ImGui::Checkbox("Cyclic Wall", &isCyclicWall))
  {
    if (isCyclicWall)
      engine->setBoundary(Physics::Boundary::CyclicWall);
    else
      engine->setBoundary(Physics::Boundary::BouncingWall);
  }
}
