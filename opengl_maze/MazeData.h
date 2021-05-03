#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <stack>
#include <cmath>

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

enum Direction {
	UP, RIGHT, DOWN, LEFT, INVALID
};

enum Quadrant {
	UPPER_LEFT, UPPER_RIGHT, LOWER_RIGHT, LOWER_LEFT, UNKNOWN
};

class MazeData
{
public:
	static MazeData* GenerateMaze();
	
	static void DrawAsAscii(MazeData* m);

	IntTuple GetSize();
	IntTuple GetExit();
	IntTuple GetStartingPoint();
	MazeCell* GetCellAtPoint(IntTuple point);
private:
	MazeData();

	const IntTuple DEFAULT_SIZE = { 20, 20 };

	IntTuple size;
	IntTuple exit;
	IntTuple startingPoint;
	std::vector<MazeCell> cells;
	
	
	int GetCellIndexFromPoint(IntTuple point);
	IntTuple GetPointFromCellIndex(int index);

	// Generator
	static MazeData* GetClosedMaze();
	static int GetRandomInt(int min, int max);
	static Direction GetRandomDirection(vector<Direction>);
	vector<IntTuple> CellsVisited;
	void CarveClosedMazeIntoPerfectMaze();
	void AddStartAndExit(int numEntrances);
	bool CellHasBeenVisited(IntTuple p);
	bool AreAllCellsVisited();
	vector<Direction> GetAvailableDirections(IntTuple p);
	void ConnectCells(IntTuple a, Direction d);
	IntTuple GetDestinationPoint(IntTuple a, Direction d);

	Quadrant GetQuadrant(IntTuple p);
	Quadrant GetInverseQuadrant(Quadrant q);
	IntTuple GetRandomPointInQuadrant(Quadrant q);
	
};

