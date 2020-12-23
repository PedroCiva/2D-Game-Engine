#include "LayerMatrix.h"
#include <iomanip>
#include <vector>
#include <algorithm>


/*LayerMatrix::LayerMatrix() {
	
}*/
std::string LayerMatrix::LayerNameToString(LayerType layer)
{
	switch (layer)
	{
	case TILEMAP_LAYER: return "TILEMAP_LAYER";       //0
	case VEGETATION_LAYER: return "VEGETATION_LAYER"; //1
	case ENEMY_LAYER: return "ENEMY_LAYER";		      //2
	case PLAYER_LAYER: return "PLAYER_LAYER";		  //3
	case PROJECTILE_LAYER: return "PROJECTILE_LAYER"; //4		
	case UI_LAYER: return "UI_LAYER";	              //5
	}
}

int  LayerMatrix::GetLayerStringLenght(int currentLayer)
{
	int lenght = 0;
	for (int x = 0; LayerNameToString((LayerType)currentLayer)[x] != '\0'; x++) {
		lenght = x;
	}
	return lenght;
}

void  LayerMatrix::PrintCollisionsLayersMatrix()
{
	//Populating layersArray backwards
	for (int x = (NUM_LAYERS - 1); x > -1; x--)
	{
		layersArray[x] = LayerNameToString((LayerType)x);
	}

	//Getting largest layer name to use it to set the horizontal offset for our vertical lines
	for (int layerNum = 1; layerNum < NUM_LAYERS; layerNum++)
	{
		if (largeWidthOffset < GetLayerStringLenght(layerNum))
			largeWidthOffset = GetLayerStringLenght(layerNum);
	}
	largeWidthOffset += EXTRA_OFFSET; //Adding small offset

	//Print layers vertically
	for (int currentLayer = (UI_LAYER); currentLayer > -1; currentLayer--) //For every layer backwards
	{
		if (currentLayer == UI_LAYER)
		{
			std::cout << std::setw(largeWidthOffset) << "";
		}
		if (stringIndex >= layersArray[currentLayer].size()) // if string is over
		{
			std::cout << std::setw(DEFAULT_WIDTH_OFFSET) << "";
		}
		else
		{
			std::cout << std::setw(DEFAULT_WIDTH_OFFSET) << layersArray[currentLayer][stringIndex];
		}
		if (currentLayer == 0) //If we reached the first Layer do a new line and increase string index 
		{
			std::cout << std::endl;
			stringIndex++;
			currentLayer = NUM_LAYERS;
			if (stringIndex >= largeWidthOffset - EXTRA_OFFSET + 1) //If our string index is bigger than the biggest amount of character on all arrays then we are finished, break loop
				break;
		}
	}
	std::cout << std::endl;

	//Print layer horizontally and print checkboxes
	for (int currentLayer = 0; currentLayer < NUM_LAYERS; currentLayer++) //Iterate through all layers
	{
		//Print layer
		std::cout << LayerNameToString((LayerType)currentLayer);

		//Print checkBox
		for (int i = 0; i < columnsIterator; i++)
		{
			//If thats our first checkBox on this line
			if (checkBoxIsFirst)
			{
				//Handling 2 digits
				if (matrixCheckBox < 10)
					std::cout << std::setw((largeWidthOffset + DEFAULT_WIDTH_OFFSET) - layersArray[currentLayer].size() - 1) << "[" << matrixCheckBoxArray2D[currentLayer][i] << "]";
				else
					std::cout << std::setw((largeWidthOffset + DEFAULT_WIDTH_OFFSET) - layersArray[currentLayer].size() - 2) << "[" << matrixCheckBoxArray2D[currentLayer][i] << "]";

				checkBoxIsFirst = false;
			}
			else
			{
				//Handling 2 digits
				if (matrixCheckBox < 10)
					std::cout << std::setw(DEFAULT_WIDTH_OFFSET - 2) << "[" << matrixCheckBoxArray2D[currentLayer][i] << "]";
				else
					std::cout << std::setw(DEFAULT_WIDTH_OFFSET - 3) << "[" << matrixCheckBoxArray2D[currentLayer][i] << "]";
			}
			matrixCheckBox++;
		}
		columnsIterator--; //Every time we finish a line decrease 1 column
		checkBoxIsFirst = true;
		std::cout << std::endl;
	}
	ResetGlobalVariables(); //Reset our global variable
}

void  LayerMatrix::ResetGlobalVariables()
{
	stringIndex = 0;
	largeWidthOffset = 0;
	matrixCheckBox = 0;
	columnsIterator = NUM_COLUMNS;
	checkBoxIsFirst = true;
}

void  LayerMatrix::InitializeGlobalVariables()
{
	//Initializing checkboxes 2D array columns
	for (int i = 0; i < NUM_ROWS; i++)
	{
		//Initializing columns
		matrixCheckBoxArray2D[i] = new std::string[NUM_COLUMNS];
	}

	//Initializing checkboxes 2D array values
	int counter = 0;
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int column = 0; column < NUM_COLUMNS; column++)
		{
			//Little algorithm to tell if the current checkBox should be empty
			bool printEmpty = column > ((NUM_COLUMNS - 1) - row);
			if (printEmpty)
			{
				matrixCheckBoxArray2D[row][column] = "";
			}
			else
			{
				matrixCheckBoxArray2D[row][column] = std::to_string(counter);
				counter++;
			}
		}
	}
}

//Keep in mind that the index values for the Matrix rows match the enum values, but for the Matrix columns the enum values have to be inverted to match the index with what we can see on the screen
bool LayerMatrix::ShouldCollide(LayerType thisLayer, LayerType thatLayer)
{
	//Storing original copy of thatLayer
	LayerType tempThatLayer = thatLayer;

	//Inverting thatLayer to match the row logic
	thatLayer = (LayerType)((NUM_LAYERS - 1) - thatLayer);
	if (matrixCheckBoxArray2D[thisLayer][thatLayer] == "X" || matrixCheckBoxArray2D[thisLayer][thatLayer] == "XX")
	{
		//Layers should collide, return true
		return true;
	}
	else if (matrixCheckBoxArray2D[thisLayer][thatLayer].empty() == true)
	{
		//If string is empty it is null, so invert row and column values and run method again recursively
		thisLayer = (LayerType)((NUM_LAYERS - 1) - thisLayer);
		return ShouldCollide(tempThatLayer, thisLayer, true);
	}
	else
	{
		//If none of the above (i.e is a number), then its a no no
		return false;
	}
}

//Function overload for when we gotta invert the enum value to match its place on the Matrix2D array
bool LayerMatrix::ShouldCollide(LayerType thisLayer, LayerType thatLayer, bool isInverting)
{
	LayerType tempThatLayer = thatLayer;
	if (!isInverting)
		thatLayer = (LayerType)((NUM_LAYERS - 1) - thatLayer);
	if (matrixCheckBoxArray2D[thisLayer][thatLayer] == "X" || matrixCheckBoxArray2D[thisLayer][thatLayer] == "XX")
	{
		//Layers should collide, return true
		return true;
	}
	else if (matrixCheckBoxArray2D[thisLayer][thatLayer].empty() == true)
	{
		//If string is empty it is null, so invert row and column values and run method again recursively
		thisLayer = (LayerType)((NUM_LAYERS - 1) - thatLayer);
		return ShouldCollide(tempThatLayer, thisLayer);
	}
	else
	{
		//If none of the above (i.e is a number), then its a no no
		return false;
	}
}

void LayerMatrix::EnableMenu()
{
	//Find and replace
	std::string number;
	bool wasFound = false;

	while (!wasFound)
	{
		std::cout << "Type the number respective to the Matrix..." << std::endl;
		std::cin >> number;
		for (int row = 0; row < NUM_ROWS; row++)
		{
			for (int column = 0; column < NUM_COLUMNS; column++)
			{
				if (matrixCheckBoxArray2D[row][column] == number)
				{
					if (atoi(number.c_str()) < 10)
						matrixCheckBoxArray2D[row][column] = "X";
					else
						matrixCheckBoxArray2D[row][column] = "XX";
					wasFound = true;
					goto end;
				}
			}
		}
		std::cout << "Error! Element was not found, enter a valid element number." << std::endl;
		if (wasFound)
		{
		end:
			PrintCollisionsLayersMatrix();
			std::cout << "\nSuccess...\n";
		}
	}
}