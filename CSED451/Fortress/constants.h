#pragma once

#define M_PI 3.14159265358979323846
#define RATIO 1.5
#define SCREEN_HEIGHT 300
#define SCREEN_WIDTH (SCREEN_HEIGHT * RATIO)
#define GROUND_HEIGHT 15.0
#define GROUND_BOUNDARY 80

typedef enum class color {
	BLACK,
	BLUE,
	BEIGE,
	PINK,
	SKYBLUE,
	LIGHTSKYBLUE,
	WHITE,
	YELLOW,
	LIGHTGRAY
} color;

typedef enum class view_t {
	THIRD_PERSON,
	FIRST_PERSON,
	TOP_VIEW,
} view_t;
