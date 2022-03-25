#pragma once

#define M_PI 3.14159265358979323846
#define RATIO 1.5
#define SCREEN_HEIGHT 300
#define SCREEN_WIDTH (SCREEN_HEIGHT * RATIO)
#define GROUND_HEIGHT 15.0

typedef enum class ori_t {
	LEFT = 0,
	RIGHT = 1,
} ori_t;

typedef enum class color {
	BLACK,
	BLUE,
	BEIGE,
	PINK,
	SKYBLUE,
	LIGHTSKYBLUE,
	WHITE,
	YELLOW
} color;