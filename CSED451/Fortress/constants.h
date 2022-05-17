#pragma once

#define M_PI 3.14159265358979323846
#define GROUND_BOUNDARY 80
#define UPDATE_INTERVAL 50

#define SPRING_FORCE 1.0f
#define DAMPING 3.0f
#define RECOIL_DELAY 2000

typedef enum class color {
	BLACK,
	DARKGRAY,
	BLUE,
	BEIGE,
	PINK,
	SKYBLUE,
	LIGHTSKYBLUE,
	WHITE,
	YELLOW,
	LIGHTGRAY,
	GREEN,
} color;

typedef enum class view_t {
	THIRD_PERSON,
	FIRST_PERSON,
	TOP_VIEW,
} view_t;

typedef enum class texture_t {
	GROUND,
	DUCK,
	SHELL,
} texture_t;
