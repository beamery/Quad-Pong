#ifndef TESTS_H
#define TESTS_H

#include "tinyxml2.h"
#include "Utils.h"
#include "Actor.h"
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML\Graphics.hpp>

using namespace std;
void testXml();
void testActors();
void testVectors();
void drawCircle(float cx, float cy, float r, int num_segments);
void drawTriangle(Actor *background, double totalTime, double elapsedTime);
void drawSprite();



#endif