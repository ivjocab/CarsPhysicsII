#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "ModulePhysics3D.h"
#include "Color.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Scene
	createPlatform({ -150, -80, 0 }, { 20000.0f, 0.1, 20000.0f }, 0, 0);
	createPlatform({ -150, 120, 0 }, { 20000.0f, 0.1, 20000.0f }, 0, 0);
	createPlatform({ -80.0f, -100.0f, 60.0f }, { 70.0f, 500.0f, 70.0f }, 0, 0);
	createCircularPlatform({ -179.0f, -100.0f, 142.0f }, 20, 280);

	//Circuit
	createPlatform({ 0, 1.0f, 10.0f }, { 30.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ 0, 1.0f, 40.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ 0, 1.0f, 70.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ 0, 1.0f, 100.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -8, 1.0f, 122.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -38, 1.0f, 122.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -68, 1.0f, 122.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -98, 1.0f, 122.0f }, { 30.0f, 2.0f, 24.0f }, 180, {0, 180, 45});
	createPlatform({ -128, 1.0f, 122.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -136, 1.0f, 144.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -136, 1.0f, 174.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -144, 1.0f, 196.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -174, 1.0f, 196.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -204, 1.0f, 196.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -226, 1.0f, 188.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -226, 1.0f, 158.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -226, 1.0f, 128.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createRampPlatformZ({ -226, -6.0f, 100.0f }, { 14.0f, 2.0f, 30.0f });
	createRampPlatformZ({ -226, -20.0f, 74.0f }, { 14.0f, 2.0f, 30.0f });
	createPlatform({ -226, -27.0f, 46.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -248, -27.0f, 38.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createRampPlatformX({ -276, -20.0f, 38.0f }, { 30.0f, 2.0f, 14.0f });
	createPlatform({ -330, -14.0f, 38.0f }, { 30.0f, 2.0f, 30.0f }, 0, 0); //checkpoint
	createPlatform({ -360, -14.0f, 38.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -390, -14.0f, 38.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -420, -14.0f, 38.0f }, { 30.0f, 2.0f, 24.0f }, 180, { 0, 180, 45 });
	createPlatform({ -450, -14.0f, 38.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -472, -14.0f, 30.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -472, -14.0f, 0.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -472, -14.0f, -30.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -464, -14.0f, -52.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -434, -14.0f, -52.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -404, -14.0f, -52.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -374, -14.0f, -52.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -366, -14.0f, -74.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -366, -7, -102.0f }, { 14.0f, 2.0f, 30.0f }, 180, { 0, 180, 45 });
	createPlatform({ -366, 0.0f, -130.0f }, { 30.0f, 2.0f, 30.0f }, 0, 0); //checkpoint
	createPlatform({ -366, 0.0f, -160.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -366, 0.0f, -190.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -388, 0.0f, -198.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -438, -14.0f, -198.0f }, { 30.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -468, -14.0f, -198.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -498, -14.0f, -198.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -506, -14.0f, -176.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -506, -14.0f, -146.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -484, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -454, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -424, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -394, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -364, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -334, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -304, -14.0f, -138.0f }, { 30.0f, 2.0f, 24.0f }, 180, { 0, 180, 45 });
	createPlatform({ -274, -14.0f, -138.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -266, -14.0f, -116.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -258, -14.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -228, -14.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -198, -14.0f, -94.0f }, { 30.0f, 2.0f, 24.0f }, 180, { 0, 180, 45 });
	createPlatform({ -168, -14.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -138, -14.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -110, -7.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 180, { 180, 45, 0 });
	createPlatform({ -82, 0.0f, -94.0f }, { 30.0f, 2.0f, 30.0f }, 0, 0); //checkpoint
	createPlatform({ -52, 0.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ -22, 0.0f, -94.0f }, { 30.0f, 2.0f, 14.0f }, 0, 0);
	createPlatform({ 0, 0.0f, -86.0f }, { 14.0f, 2.0f, 30.0f }, 0, 0);
	createPlatform({ -0, 0.0f, -56.0f }, { 24.0f, 2.0f, 30.0f }, 180, { 45, 180, 0 });
	createPlatform({ 0, 1.0f, -23.0f }, { 14.0f, 2.0f, 36.0f }, 0, 0);

	//Checkpoints
	createCheckPoint({ -330, -12.99f, 38.0f }, { 30.0f, 0.01f, 30.0f });
	createCheckPoint({ -366, 1.01f, -130.0f }, { 30.0f, 0.01f, 30.0f });
	createCheckPoint({ -82, 1.01f, -94.0f }, { 30.0f, 0.01f, 30.0f });

	posBeforeDeath = App->player->vehiclePos;
	posBeforeDeath.y += 5;

	return ret;
}

void angleAndAxisFromEuler(float psi, float theta, float phi, float& angle, vec3& axis)
{
	float m[3][3];

	m[0][0] = cos(theta) * cos(psi);
	m[0][1] = cos(psi) * sin(theta) * sin(phi) - cos(phi) * sin(psi);
	m[0][2] = cos(psi) * cos(psi) * sin(theta) + sin(psi) * sin(phi);
	m[1][0] = cos(theta) * sin(psi);
	m[1][1] = sin(psi) * sin(theta) * sin(phi) + cos(phi) * cos(psi);
	m[1][2] = cos(phi) * sin(psi) * sin(theta) - cos(psi) * sin(phi);
	m[2][0] = -sin(theta);
	m[2][1] = cos(theta) * sin(phi);
	m[2][2] = cos(theta) * cos(phi);

	angle = acos((m[0][0] + m[1][1] + m[2][2] - 1) / 2.0f);

	axis.x = (m[2][1] - m[1][2]) / (2 * sin(angle));
	axis.y = (m[0][2] - m[2][0]) / (2 * sin(angle));
	axis.z = (m[1][0] - m[0][1]) / (2 * sin(angle));

	axis = normalize(axis);
}

void angleAndAxisFromRotMat(mat4x4 m, float& angle, vec3& axis)
{
	angle = acos((m[0] + m[5] + m[10] - 1) / 2.0f);

	axis.x = (m[9] - m[6]) / (2 * sin(angle));
	axis.y = (m[2] - m[8]) / (2 * sin(angle));
	axis.z = (m[4] - m[1]) / (2 * sin(angle));

	axis = normalize(axis);
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	for (int i = 0; i < cube_circuit_pieces.prim_bodies.Count(); i++)
		cube_circuit_pieces.prim_bodies[i].Render();

	for (int i = 0; i < prim_check_points.Count(); i++)
		prim_check_points[i].Render();

	for (int i = 0; i < platform_list.Count(); i++)
		platform_list[i].Render();

	for (int i = 0; i < circular_platform_list.Count(); i++)
		circular_platform_list[i].Render();

	for (int i = 0; i < checkpoints.Count(); i++)
		checkpoints[i].Render();

	isPlayerOnCheckpoint();
	if (checkpointsObtained > 0)
	{
		posBeforeDeath = checkpoints[checkpointsObtained - 1].pos;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

void ModuleSceneIntro::createRamp(const vec3 i_pos, const vec3 f_pos)
{
	vec3 final_projection = { f_pos.x, 0, f_pos.z };
	vec3 direction = normalize(f_pos - i_pos);
	vec3 planar_direction = normalize(final_projection - i_pos);
	float distance = length(f_pos - i_pos);
	float planar_distance = length(final_projection - i_pos);

	float heading = 0.0f;
	if (f_pos.z >= i_pos.z && f_pos.x < i_pos.x)
		heading = acos(dot(planar_direction, { 1, 0, 0 }));
	else if (f_pos.z >= i_pos.z && f_pos.x >= i_pos.x)
		heading = acos(dot(planar_direction, { 1, 0, 0 }));
	else if (f_pos.z < i_pos.z && f_pos.x >= i_pos.x)
		heading = 2 * M_PI - acos(dot(planar_direction, { 1, 0, 0 }));
	else if (f_pos.z < i_pos.z && f_pos.x < i_pos.x)
		heading = 2 * M_PI - acos(dot(planar_direction, { 1, 0, 0 }));

	float slope = asin(f_pos.y / distance);

	Cube c;
	c.size = { distance, 0.25f, TRACK_WIDTH - 2 };
	c.color = White;

	c.SetPos(i_pos.x + (direction.x * distance / 2.0f), i_pos.y + (sin(slope) * (c.size.x / 2.0f)), i_pos.z + (direction.z * distance / 2.0f));

	c.SetRotation(slope * 180.0f / M_PI, { 0, 0, 1 });
	mat4x4 R1;
	for (uint i = 0; i < 16; i++)
		R1[i] = c.transform.M[i];
	c.SetRotation(-heading * 180.0f / M_PI, { 0, 1, 0 });
	mat4x4 R2;
	for (uint i = 0; i < 16; i++)
		R2[i] = c.transform.M[i];
	mat4x4 R3 = R2 * R1;

	float angle;
	vec3 axis;
	angleAndAxisFromRotMat(R3, angle, axis);
	c.SetRotation(-angle * 180.0f / M_PI, { axis.x, axis.y, axis.z });

	cube_circuit_pieces.prim_bodies.PushBack(c);
	cube_circuit_pieces.phys_bodies.PushBack(App->physics->AddBody(c, this, 0.0f));
}

void ModuleSceneIntro::createPlatform(const vec3 pos, const vec3 size, float angle, vec3 dir)
{
	Cube c;
	c.SetPos(pos.x, pos.y, pos.z);
	c.size = size;
	if (size.x > 1000) c.color = Orange;
	if (angle != 0) c.SetRotation(angle, dir);
	platform_list.PushBack(c);
	App->physics->AddBody(c, this, 0.0f, false);
}

void ModuleSceneIntro::createCircularPlatform(const vec3 pos, const float radius, const float height)
{
	Cylinder c;
	c.SetPos(pos.x, pos.y, pos.z);
	c.radius = radius;
	c.height = height;
	c.wire = false;

	c.SetRotation(180, {180, 180, 0});

	circular_platform_list.PushBack(c);
	App->physics->AddBody(c, this, 0.0f, false);
}

void ModuleSceneIntro::createRampPlatformZ(const vec3 pos, const vec3 size)
{
	Cube c;
	c.SetPos(pos.x, pos.y, pos.z);
	c.size = size;
	c.SetRotation(180, {0, 45, 180});
	platform_list.PushBack(c);
	App->physics->AddBody(c, this, 0.0f, false);
}

void ModuleSceneIntro::createRampPlatformX(const vec3 pos, const vec3 size)
{
	Cube c;
	c.SetPos(pos.x, pos.y, pos.z);
	c.size = size;
	c.SetRotation(180, { -180, 45, 0 });
	platform_list.PushBack(c);
	App->physics->AddBody(c, this, 0.0f, false);
}

void ModuleSceneIntro::createCheckPoint(const vec3 pos, const vec3 size)
{
	p = new Cube(size.x, size.y, size.z);
	p->SetPos(pos.x, pos.y, pos.z);
	p->n = checkpoints.Count();
	p->color = Yellow;
	checkpoints.PushBack(*p);
	p->pos = pos;
}

void ModuleSceneIntro::isPlayerOnCheckpoint()
{
	for (int i = 0; i < checkpoints.Count(); i++)
	{
		if (App->player->vehiclePos.x < checkpoints[i].pos.x && App->player->vehiclePos.x > checkpoints[i].pos.x + 30 &&
			App->player->vehiclePos.z < checkpoints[i].pos.z && App->player->vehiclePos.z > checkpoints[i].pos.z + 30 &&
			App->player->vehiclePos.y < checkpoints[i].pos.y - 1 && App->player->vehiclePos.y > checkpoints[i].pos.y + 1)
		{
			if (checkpoints[i].n == 0 && checkpointsObtained == 0)
			{
				checkpointsObtained = 1;
			}
			if (checkpoints[i].n == 1 && checkpointsObtained == 1)
			{
				checkpointsObtained = 2;
			}
			if (checkpoints[i].n == 2 && checkpointsObtained == 0)
			{
				checkpointsObtained = 3;
			}
			/*createCheckPoint({ -330, -12.99f, 38.0f }, { 30.0f, 0.01f, 30.0f });
			createCheckPoint({ -366, 1.01f, -130.0f }, { 30.0f, 0.01f, 30.0f });
			createCheckPoint({ -82, 1.01f, -94.0f }, { 30.0f, 0.01f, 30.0f });*/
		}
	}
}


