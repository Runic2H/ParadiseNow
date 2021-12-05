/*---------------------------------------------------------
 * file:	main.c

 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG
			ABDUL HADI

 * email:	e.teo@digipen.edu
 			louismineo.l@digipen.edu
			r.choo@digipen.edu
			abdulhadi.b@digipen.edu
* 
 * brief:	Main entry point for the sample project
			Slime Rush of the CProcessing library
* 
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
* 
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/
#include <stdio.h>
#include "cprocessing.h"


/* Forward declarations */
void digipen_init(void);
void digipen_update(void);
void digipen_exit(void);

/* Entry point */
int main(void)
{
    CP_Engine_SetNextGameState(digipen_init, digipen_update, digipen_exit);
    CP_Engine_Run();
    return 0;
}
