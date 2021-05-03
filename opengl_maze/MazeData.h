#pragma once

#include <vector>
#include <iostream>

#include "Tuple.h"

using namespace std;

struct MazeCell
{
	bool lineTop;
	bool lineRight;
	bool lineLeft;
	bool lineBottom;
	IntTuple gridCoord;
};

class MazeData
{
public:
	MazeData();

	static MazeData* GetClosedMaze();
	static void DrawAsAscii(MazeData* m);

private:
	const IntTuple DEFAULT_SIZE = { 20, 20 };

	IntTuple size;
	IntTuple exit;
	IntTuple startingPoint;
	std::vector<MazeCell> cells;
	
	MazeCell GetCellAtPoint(IntTuple point);
	int GetCellIndexFromPoint(IntTuple point);
	IntTuple GetPointFromCellIndex(int index);

	
	
};

