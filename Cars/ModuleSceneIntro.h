#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define TRACK_WIDTH 20.0f

struct PhysBody3D;
struct PhysMotor3D;

struct cubePieces
{
	p2DynArray<PhysBody3D*>		phys_bodies;
	p2DynArray<Cube>			prim_bodies;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	p2DynArray<PhysBody3D*> check_points;
	p2DynArray<Cube> checkpoints;
	p2DynArray<Cube> prim_check_points;
	p2DynArray<Cube> platform_list;
	p2DynArray<Cylinder> circular_platform_list;
	uint current_checkpoint;

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void createRamp(const vec3 i, const vec3 f);
	void createPlatform(const vec3 pos, const vec3 size, float angle, vec3 dir);
	void createCircularPlatform(const vec3 pos, const float radius, const float height);
	void createRampPlatformZ(const vec3 pos, const vec3 size);
	void createRampPlatformX(const vec3 pos, const vec3 size);
	void createCheckPoint(const vec3 pos, const vec3 size);
	void isPlayerOnCheckpoint();

public:

	//Checkpoints & player death
	vec3 posBeforeDeath;
	int checkpointsObtained = 0;

	//...
	p2List<Plane> plane_list;

	cubePieces cube_circuit_pieces;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube* p;
};
