#include <stdio.h>
#include "cprocessing.h" 
#include "character.h"


void c_CharacterWASD(float *objPositionX, float *objPositionY)
{
	CP_Vector direction = {10,10};
	CP_Vector velocity = CP_Vector_Scale(CP_Vector_Normalize(direction), 400.f * CP_System_GetDt());
	CP_Matrix rotate = CP_Matrix_Rotate(45.0f);
	CP_Vector movement = CP_Vector_MatrixMultiply(rotate, velocity);
	if (CP_Input_MouseDown(MOUSE_BUTTON_2))
	{

	}
	else
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			if (CP_Input_KeyDown(KEY_A))
			{
				*objPositionX += movement.x/2;
				*objPositionY -= movement.y/2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				*objPositionX -= movement.x/2;
				*objPositionY -= movement.y/2;
			}
			else
			{
				*objPositionY -= velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_S))
		{
			if (CP_Input_KeyDown(KEY_A))
			{
				*objPositionX -= movement.x/2;
				*objPositionY += movement.y/2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				*objPositionX -= movement.x/2;
				*objPositionY += movement.y/2;
			}
			else
			{
				*objPositionY += velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_A))
		{
			*objPositionX -= velocity.x;
		}
		if (CP_Input_KeyDown(KEY_D))
		{
			*objPositionX += velocity.x;
		}
	}

}

void c_CharacterMouse(float* objPositionX, float* objPositionY)
{
	CP_Vector playerVector = CP_Vector_Set(*objPositionX, *objPositionY);
	CP_Vector mouseVector = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	CP_Vector directionVector = CP_Vector_Subtract(mouseVector, playerVector);
	CP_Vector speed = CP_Vector_Scale(CP_Vector_Normalize(directionVector), 300.f * CP_System_GetDt());
	if (CP_Input_MouseDown(MOUSE_BUTTON_2))
	{

	}
	else
	{
		*objPositionX += speed.x;
		*objPositionY += speed.y;
	}
}
