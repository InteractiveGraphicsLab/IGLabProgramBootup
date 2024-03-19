#pragma once

#include "OglForCLI.h"
#include "EventManager.h"

class Ball
{
private:
    EVec3f pos_, rot_, velo_, veloangle_;
    float radi_;

public:
    Ball(const EVec3f& pos, const EVec3f& rot, const EVec3f& velo, const EVec3f& veloangle, float radi);
    Ball(const Ball& src);
    EVec3f GetPos() const;
    EVec3f GetVelo() const;
    float GetRadi() const;
    void SetPos(const EVec3f& pos);
    void SetVelo(const EVec3f& velo);
    void Step();
    void Draw() const;
    void DrawSphere() const;
};