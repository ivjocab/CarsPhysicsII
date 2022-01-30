#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 3000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void RestartPlayer(int x, int y, int z);

public:

	PhysVehicle3D* vehicle;
	PhysBody3D* vehicleCollider;
	vec3 vehiclePos;
	btQuaternion vehicleRot;
	float turn;
	float acceleration;
	float brake;
	int lives;

	bool debug = false;
};