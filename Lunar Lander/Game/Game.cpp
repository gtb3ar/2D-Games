#include "Main.h"
#include "CommonStruct.h"
#include "CommonMath.h"
#include "time.h"
#include <stdio.h>
#include "CommonSpline.h"
#include "CommonShape.h"
#include "Particles.h"

// Define variables which determine how big the window will be
float screenWidth = 800;
float screenHeight = 600;

class raycaster {

};

class InputManager {
private:

	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;

public:

	void Init(sf::Keyboard::Key u, sf::Keyboard::Key d, sf::Keyboard::Key l, sf::Keyboard::Key r) {
		up = u;
		down = d;
		left = l;
		right = r;
	}

	bool inputUp() {
		if (sf::Keyboard::isKeyPressed(up)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool inputDown() {
		if (sf::Keyboard::isKeyPressed(down)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool inputLeft() {
		if (sf::Keyboard::isKeyPressed(left)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool inputRight() {
		if (sf::Keyboard::isKeyPressed(right)) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Lander {
private:
	FloatVector2 position;
	FloatVector2 velocity;
	FloatVector2 accelertation;
	float gravity;
	float rotation;
	bool thrustToggle;
	float maxThrust;
	sf::Color color;
	MeshMapStore rocket;
	Polygon meshRocket;
	MeshMapStore window;
	Polygon meshWindow;
	
	//ParticleSystem thruster;
	ParticleSystem thruster;

	float magicNumber = 1;
	
	void CalculateThrust() {
		if (thrustToggle) {
			FloatVector2 thrustVertex = CalculateVertexFromRadian(rotation, 5, position.x, position.y);
			float diffX = abs(position.x - thrustVertex.x);
			float diffY = abs(position.y - thrustVertex.y);
			float holdX = ((diffY + diffX) / diffX) * maxThrust;
			float holdY = ((diffY + diffX) / diffY) * maxThrust;
			holdY = -holdY;
			if (rotation < 0) {
				holdX = -holdX;
			}
			accelertation.x = holdX;
			accelertation.y = holdY;
			//printf("%f :x ... %f :y", accelertation.x, accelertation.y);
		}
		else {
			accelertation.x = 0;
			accelertation.y = 0;
		}
	}

	void ApplyForce(float timeElapsed) {
		SetPosition(position.x + velocity.x * timeElapsed * magicNumber, position.y + velocity.y * timeElapsed * magicNumber);
		float xLimiter = ReMapF(abs(rotation), 1.5, 0, 30, 10);
		velocity.x = ClampF(velocity.x + accelertation.x * timeElapsed * magicNumber, xLimiter, -xLimiter);
		velocity.y = ClampF(velocity.y + gravity * timeElapsed * magicNumber + accelertation.y * timeElapsed * magicNumber, 40, -40);
	}

public:

	

	void Init( FloatVector2 location, FloatVector2 landerVelocity, FloatVector2 landerAcceleration, float landerGravity, float thrustMax) {
		rotation = 0;
		position = location;
		velocity = landerVelocity;
		accelertation = landerAcceleration;
		gravity = landerGravity;
		thrustToggle = false;
		maxThrust = thrustMax;
		color = sf::Color::White;
		rocket.storeMap({ {0,-5},{1,-3},{2,1},{2,3},{1,2},{-1,2},{-2,3},{-2,1},{-1,-3} });
		meshRocket.InitPoly(position.x, position.y, 5, 5, rotation, rocket.getNOV(), rocket.readMap());
		window.storeMap({ {0,-3}, {2,-2}, {3,0}, {2,2}, {0,3}, {-2,2}, {-3,0}, {-2,-2} });
		meshWindow.InitPoly(position.x, position.y, 2, 2, rotation, window.getNOV(), window.readMap());
		thruster.Init(position, rotation+1, 20, 1, { {0,-3}, {2,-2}, {3,0}, {2,2}, {0,3}, {-2,2}, {-3,0}, {-2,-2} }, 0.1f, 0.05f, 0.3f);
		
	}

	void AddRotation(float rotInput) {
		rotation = ClampF(rotation + rotInput,1.5,-1.5);
	}

	void SetPosition(float x, float y) {
		position.x = x;
		position.y = y;
		
	}

	void ThrustToggleOn() {
		thrustToggle = true;
		thruster.on = true;
		color = sf::Color::Red;
	}

	void ThrustToggleOff() {
		thrustToggle = false;
		thruster.on = false;
		color = sf::Color::White;
	}

	void Update(float timeElapsed) {
		CalculateThrust();
		ApplyForce(timeElapsed);
		meshRocket.PosRotUpdate(position, rotation);
		meshWindow.PosRotUpdate(position, rotation);		
		thruster.Update(position, rotation);
	}



};

Lander lander;
Spline terrain;
InputManager inputManager;
// GameInit is called once, when the program starts. Its job is to do things which only happen once, at the start.
void GameInit()
{
	// Create a window for the game
	window = new sf::RenderWindow(sf::VideoMode(static_cast<int>(screenWidth), static_cast<int>(screenHeight)), "Lunar Lander");
	FloatVector2 size = { 10,15 };
	FloatVector2 position = { 100,100 };
	FloatVector2 velocity = { 0,0 };
	FloatVector2 acceleration = { 0,0 };

	lander.Init(position, velocity, acceleration, 12, 10);

	terrain.GeneratePoints(-200, 1000, 10, 400, 150);

	inputManager.Init(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);

}
float totalTime = 0.0f;		// Total number of seconds since the program started

// GameLoop is called repeatedly. Its job is to update the 'game', and draw the screen.
void GameLoop(float elapsedSeconds)
{
	// Keep a running total of how much time has passed
	totalTime = totalTime + elapsedSeconds;

	if (inputManager.inputLeft()) {
		lander.AddRotation(-1.0f * elapsedSeconds);
	}
	else if (inputManager.inputRight()) {
		lander.AddRotation(1.0f * elapsedSeconds);
	}

	if (inputManager.inputUp()) {
		lander.ThrustToggleOn();
	}
	else {
		lander.ThrustToggleOff();
	}

	terrain.Update();
	lander.Update(elapsedSeconds);
}
