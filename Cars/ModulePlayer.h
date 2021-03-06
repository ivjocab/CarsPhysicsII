#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 12.0f * DEGTORAD
#define BRAKE_POWER 3000.0f
#define DRAG_COEFICIENT 0.03f;

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
	vec3 NewSpeed;

	bool turbo;
	int turboCooldown;
	
	bool engineSound;

	PhysVehicle3D* vehicle;
	PhysBody3D* vehicleCollider;
	vec3 vehiclePos;
	btQuaternion vehicleRot;
	float turn;
	float acceleration;
	float brake;
	int lives;

	bool debug = false;

	Light* l;
};