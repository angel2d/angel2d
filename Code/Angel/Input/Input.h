/** 
 * @file Input.h
 *  This file contains the C-level interface for accepting keyboard input.
 *   Because our windowing/input toolkit (GLFW) is C-based, it needs these 
 *   loose functions to operate. 
 */
#pragma once

void keyboardInput(int key, int state);
void charInput(int key, int state);