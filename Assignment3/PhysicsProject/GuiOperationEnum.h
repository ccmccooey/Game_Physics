#ifndef _GUI_OPERATION_ENUM_H
#define _GUI_OPERATION_ENUM_H

enum GuiOperationEnum
{
	INVALID_OPERATION = -1,

	//main buttons
	Play,
	Stop,
	SingleStep,
	Reset,
	DebugInfo,
	Help,

	//simulation buttons
	Create_Sphere,
	Create_Box,
	Set_Size_Small,
	Set_Size_Medium,
	Set_Size_Large,
	Set_Material_Airfilled,
	Set_Material_Plastic,
	Set_Material_Wood,
	Set_Material_Steel,
	Set_Material_Iron,

	TOTAL_OPERATIONS
};

#endif