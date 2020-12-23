#ifndef LAYERMATRIX_H
#define LAYERMATRIX_H

#include <iostream>
#include <string>
#include "Constants.h"

class LayerMatrix {

private:
#pragma region Variables
	const int DEFAULT_WIDTH_OFFSET = 5; //Default width offset between vertical lines
	const int  EXTRA_OFFSET = 3; //Extra horizontal offset amount for the first vertical line
	const int NUM_ROWS = NUM_LAYERS;
	const int NUM_COLUMNS = NUM_LAYERS;
	int stringIndex = 0;
	int largeWidthOffset = 0;
	int columnsIterator = NUM_COLUMNS;
	int matrixCheckBox = 0;
	bool checkBoxIsFirst = true;
	std::string layersArray[LayerType::NUM_LAYERS];
	//Initializing rows to the num of layers (inline because we are initializing a static member variable in the header)
	inline static std::string** matrixCheckBoxArray2D = new std::string * [NUM_LAYERS];
#pragma endregion Variables

#pragma region PrivateMethods
	 
	std::string LayerNameToString(LayerType layer);
	int GetLayerStringLenght(int currentLayer);
	void PrintCollisionsLayersMatrix();
	void ResetGlobalVariables();
	void InitializeGlobalVariables();
	void EnableMenu();
	
#pragma endregion PrivateMethods
public:
	LayerMatrix() {
		std::cout << "Calling layer matrix constructor" << std::endl;
		InitializeGlobalVariables();
		PrintCollisionsLayersMatrix();
		EnableMenu();
	};
	static bool ShouldCollide(LayerType thisLayer, LayerType thatLayer);
	static bool ShouldCollide(LayerType thisLayer, LayerType thatLayer, bool isInverting);
};
#endif // !LAYERMATRIX_H

