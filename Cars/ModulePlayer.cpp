#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Light.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2.4f, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 12, 10);
	vehicleRot = vehicle->GetRotation();

	l = new Light;
	l->diffuse.Set(1.0f, 1.0f, 1.0f);
	l->on = true;

	turbo = false;
	turboCooldown = 0;

	App->audio->LoadFx("Assets/idle.wav");
	App->audio->LoadFx("Assets/turbo.wav");

	App->audio->PlayFx(3, 0);
	engineSound = false;

	lives = 2;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (engineSound == false) {
		App->audio->PlayFx(1, 1000);
		engineSound = true;
	}
	
	turn = 0.0f;

	vehicle->ApplyEngineForce(0.0f);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		debug = !debug;
	}
	if (!debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			vehicle->ApplyEngineForce(MAX_ACCELERATION * 0.6);
		}
		else {
			if (vehicle->GetKmh() > 0) vehicle->ApplyEngineForce(-MAX_ACCELERATION * 0.4f);
			else vehicle->ApplyEngineForce(MAX_ACCELERATION * 0.4f);
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			if (vehicle->GetKmh() < 0) vehicle->ApplyEngineForce(-MAX_ACCELERATION * 0.3f);
			else vehicle->ApplyEngineForce(-MAX_ACCELERATION * 5.0f);
		}

		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
		{
			if (turboCooldown <= 0) { 
				turbo = true; 
				turboCooldown = 400; 
				App->audio->PlayFx(2, 0);
			}
		}
	}

	// Apply forces

	// Turbo
	vehicle->Turn(turn);
	if (turbo == true) {
		if (turboCooldown > 300) vehicle->ApplyEngineForce(MAX_ACCELERATION * 5.0f);
		--turboCooldown;
	}
	// Drag
	NewSpeed.x = vehicle->GetLinearVelocity().x * vehicle->GetLinearVelocity().x * DRAG_COEFICIENT;
	if (vehicle->GetPos().y > 3) NewSpeed.y = vehicle->GetLinearVelocity().y - MAX_ACCELERATION * 0.01f;
	else NewSpeed.y = 0.0f;
	NewSpeed.z = vehicle->GetLinearVelocity().z * vehicle->GetLinearVelocity().z * DRAG_COEFICIENT;

	// render
	if (App->scene_intro->gameState == ModuleSceneIntro::Game_State::PLAY)
	{
		vehicle->Render();
		l->Render();
	}

	// reset state
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		RestartPlayer(5, 5, 5);

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);


	//Camera position
	float speed_cam = 0.09;
	vec3 p = vehicle->GetPos();
	vec3 f = vehicle->GetForwardVector();

	vec3 dist_to_car = { -16.0f, 12.0f, -25.0f };
	vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
	vec3 speed_camera = camera_new_position - App->camera->Position;

	l->SetPos(vehicle->GetPos().x, vehicle->GetPos().y, vehicle->GetPos().z);

	if (!debug)
	{
		App->camera->Look(App->camera->Position + (speed_cam * speed_camera), p);
	}

	vehiclePos = vehicle->GetPos();
	
	if (vehicle->GetPos().y < -30.0f && lives > 0)
	{
		vehicle->SetPos(App->scene_intro->posBeforeDeath.x, App->scene_intro->posBeforeDeath.y, App->scene_intro->posBeforeDeath.z);
		vehicle->SetLinearVelocity(0, 0, 0);
		vehicle->SetRotation(vehicleRot);
		lives--;
	}
	else if (lives <= 0)
	{
		App->scene_intro->gameState = ModuleSceneIntro::Game_State::DEFEAT;
	}
	
	if (App->scene_intro->gameState == ModuleSceneIntro::Game_State::DEFEAT)
	{
		vehicle->SetPos(0, 12, 10);
		vehicle->SetLinearVelocity(0, 0, 0);
		vehicle->SetRotation(vehicleRot);
		lives = 2;
	}

	return UPDATE_CONTINUE;
}



void ModulePlayer::RestartPlayer(int x, int y, int z)
{
	//brake = BRAKE_POWER;
	vehicle->SetLinearVelocity(0,0,0);
	vehicle->SetAngularVelocity(0,0,0);
	vehicle->SetPos(x, y, z);
}