#pragma once
#include <vector>
#include <iostream>
#include "math/vector.h"

using namespace std;

#define G 6.67408e-3f
#define PI 3.14159265358979323846f
#define TAU PI * 2

#define PHI  0.5f
#define EPS  0.4

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define QUADSIZE 8192

static float FPS = 0;

static vector2d ORIGIN = vector2d(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
