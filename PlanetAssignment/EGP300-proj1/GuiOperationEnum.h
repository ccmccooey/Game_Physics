#ifndef _GUI_OPERATION_ENUM_H
#define _GUI_OPERATION_ENUM_H

enum GuiOperationEnum
{
	INVALID_OPERATION = -1,

	//main buttons
	Play,
	Stop,
	Reset,
	SingleStep,
	IncreaseSpeed,
	DecreaseSpeed,
	AddCustomPlanet,
	RemoveCustomPlanet,
	RemoveAllCustomPlanets,

	//planet buttons
	ViewSolarSystem,
	ViewMercury,
	ViewVenus,
	ViewEarth,
	ViewMars,
	ViewJupiter,
	ViewSaturn,
	ViewUranus,
	ViewNeptune,
	ViewPluto,
	ViewEris,

	//moon buttons
	ViewMoon,

	TOTAL_OPERATIONS
};

#endif