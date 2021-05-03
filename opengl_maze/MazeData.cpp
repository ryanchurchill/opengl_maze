#include "MazeData.h"

MazeData::MazeData()
{
	size = DEFAULT_SIZE;
	//cells = vector < MazeCell>();
}

MazeCell* MazeData::GetCellAtPoint(IntTuple point)
{
	return &cells.at(GetCellIndexFromPoint(point));
}

int MazeData::GetCellIndexFromPoint(IntTuple point)
{
	return point.y * size.x + point.x;
}

IntTuple MazeData::GetPointFromCellIndex(int index)
{
	int x = index & size.y;
	int y = index - x;
	return IntTuple{x, y};
}



MazeData* MazeData::GetClosedMaze()
{
	MazeData* m = new MazeData();
	for (int y = 0; y < m->size.y; y++) {
		for (int x = 0; x < m->size.x; x++) {
			//int cellIndex = m->GetCellIndexFromPoint(x, y);
			m->cells.push_back(MazeCell{ true, true, true, true, IntTuple{x, y} });
		}
	}

	return m;
}

void MazeData::DrawAsAscii(MazeData* m)
{
	for (int y = 0; y < m->size.y; y++) {
		if (y == 0) {
			cout << " ";
			for (int x = 0; x < m->size.x; x++) {
				MazeCell *c = m->GetCellAtPoint(IntTuple{ x,y });
				if (c->lineTop) {
					std::cout << "_";
				}
				else {
					std::cout << " ";
				}
				std::cout << " ";
			}
			std::cout << "\n";
		}

		for (int x = 0; x < m->size.x; x++) {
			MazeCell *c = m->GetCellAtPoint(IntTuple{ x,y });
			if (x == 0) {
				if (c->lineLeft) {
					std::cout << "|";
				}
				else {
					std::cout << " ";
				}
			}
			if (c->lineBottom) {
				/*if (x == center.x && y == center.y) {
					std::cout << "x\u0332";
				}
				else {*/
				std::cout << "_";
				//}
			}
			else {
				std::cout << " ";
			}
			if (c->lineRight) {
				std::cout << "|";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

IntTuple MazeData::GetSize()
{
	return size;
}

IntTuple MazeData::GetExit()
{
	return exit;
}

IntTuple MazeData::GetStartingPoint()
{
	return startingPoint;
}

// Generator
MazeData* MazeData::GenerateMaze()
{
	// initialize vars
	MazeData *m = MazeData::GetClosedMaze();
	m->CellsVisited = vector<IntTuple>();

	m->CarveClosedMazeIntoPerfectMaze();
	m->AddStartAndExit(1);

	return m;
}

int MazeData::GetRandomInt(int min, int max)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(0, max);

	return distrib(gen);
}

Direction MazeData::GetRandomDirection(vector<Direction> directions)
{
	if (directions.size() == 0) {
		return INVALID;
	}

	int directionIndex = GetRandomInt(0, directions.size() - 1);

	return directions.at(directionIndex);
}

void MazeData::CarveClosedMazeIntoPerfectMaze()
{
	DrawAsAscii(this);

	// start at a random cell
	IntTuple startingCell { GetRandomInt(0, size.x - 1), GetRandomInt(0, size.y - 1) };

	stack<IntTuple> cellTraversalStack;
	cellTraversalStack.push(startingCell);
	CellsVisited.push_back(startingCell);

	int counter = 0;
	while (!AreAllCellsVisited() && !cellTraversalStack.empty()) {
		IntTuple currentCell = cellTraversalStack.top();
		vector<Direction> availableDirections = GetAvailableDirections(currentCell);
		Direction d = GetRandomDirection(availableDirections);
		if (d == INVALID) {
			cellTraversalStack.pop();
		}
		else {
			ConnectCells(currentCell, d);
			IntTuple nextPoint = GetDestinationPoint(currentCell, d);
			cellTraversalStack.push(nextPoint);
			CellsVisited.push_back(nextPoint);
		}
		counter++;

		if (counter % 1000 == 0) {
			cout << "Counter : " << counter << "\n";
			DrawAsAscii(this);
		}
	}
	cout << "Counter : " << counter << "\n";
	DrawAsAscii(this);
}

void MazeData::AddStartAndExit(int numEntrances)
{
	// Exit(s) (also called entrances)
	vector<IntTuple> existingEntrances;
	for (int i = 0; i < numEntrances; i++) {
		// use "direction" to decide which border will get the entrace
		Direction border = GetRandomDirection({ UP, DOWN, LEFT, RIGHT });

		int x = 0;
		int y = 0;

		if (border == UP || border == DOWN) {
			x = GetRandomInt(0, size.x - 1);
			y = (border == UP) ? 0 : size.y - 1;
		}
		else if (border == LEFT || border == RIGHT) {
			x = (border == LEFT) ? 0 : size.x - 1;
			y = GetRandomInt(0, size.y - 1);
		}

		exit = IntTuple{ x, y };
		MazeCell* cellWithExit = GetCellAtPoint(exit);

		switch (border) {
		case UP:
			cellWithExit->lineTop = false;
			break;
		case RIGHT:
			cellWithExit->lineRight = false;
			break;
		case DOWN:
			cellWithExit->lineBottom = false;
			break;
		case LEFT:
			cellWithExit->lineLeft = false;
			break;
		}
	}

	// starting position will go in the opposite quadrant as the exit
	Quadrant exitQuadrant = GetQuadrant(exit);
	Quadrant startingPointQuadrant = GetInverseQuadrant(exitQuadrant);
	startingPoint = GetRandomPointInQuadrant(startingPointQuadrant);
}

bool MazeData::CellHasBeenVisited(IntTuple p)
{
	for (auto it = CellsVisited.begin(); it != CellsVisited.end(); it++) {
		if ((*it).x == p.x && (*it).y == p.y) {
			return true;
		}
	}
	return false;
}

bool MazeData::AreAllCellsVisited()
{
	return (CellsVisited.size() == size.x * size.y);
}

vector<Direction> MazeData::GetAvailableDirections(IntTuple p)
{
	vector<Direction> directions;

	if (p.x > 0) {
		if (!CellHasBeenVisited(GetDestinationPoint(p, Direction::LEFT))) {
			directions.push_back(Direction::LEFT);
		}
	}
	if (p.x < size.x - 1) {
		if (!CellHasBeenVisited(GetDestinationPoint(p, Direction::RIGHT))) {
			directions.push_back(Direction::RIGHT);
		}
	}
	if (p.y > 0) {
		if (!CellHasBeenVisited(GetDestinationPoint(p, Direction::UP))) {
			directions.push_back(Direction::UP);
		}
	}
	if (p.y < size.y - 1) {
		if (!CellHasBeenVisited(GetDestinationPoint(p, Direction::DOWN))) {
			directions.push_back(Direction::DOWN);
		}
	}

	return directions;
}

void MazeData::ConnectCells(IntTuple a, Direction d)
{
	MazeCell* SourceCell = GetCellAtPoint(a);
	MazeCell* DestinationCell = GetCellAtPoint(GetDestinationPoint(a, d));

	switch (d) {
	case UP:
		SourceCell->lineTop = false;
		DestinationCell->lineBottom = false;
		break;
	case RIGHT:
		SourceCell->lineRight = false;
		DestinationCell->lineLeft = false;
		break;
	case DOWN:
		SourceCell->lineBottom = false;
		DestinationCell->lineTop = false;
		break;
	case LEFT:
		SourceCell->lineLeft = false;
		DestinationCell->lineRight = false;
		break;
	}
}

IntTuple MazeData::GetDestinationPoint(IntTuple a, Direction d)
{
	IntTuple ret{ a.x, a.y };

	switch (d) {
	case UP:
		ret.y--;
		break;
	case RIGHT:
		ret.x++;
		break;
	case DOWN:
		ret.y++;
		break;
	case LEFT:
		ret.x--;
		break;
	}

	if (ret.x < 0 || ret.x >= size.x || ret.y < 0 || ret.y >= size.y) {
		throw new exception("bad coordinates");
	}


	return ret;
}

Quadrant MazeData::GetQuadrant(IntTuple p)
{
	bool topElseBottom = (p.y < (size.y / 2));
	bool leftElseRight = (p.x < (size.x / 2));

	if (topElseBottom && leftElseRight) {
		return UPPER_LEFT;
	}
	else if (topElseBottom && !leftElseRight) {
		return UPPER_RIGHT;
	}
	else if (!topElseBottom && leftElseRight) {
		return LOWER_LEFT;
	}
	else {
		return LOWER_RIGHT;
	}
}

Quadrant MazeData::GetInverseQuadrant(Quadrant q)
{
	switch (q) {
	case UPPER_LEFT:
		return LOWER_RIGHT;
		break;
	case UPPER_RIGHT:
		return LOWER_LEFT;
		break;
	case LOWER_RIGHT:
		return UPPER_LEFT;
		break;
	case LOWER_LEFT:
		return UPPER_RIGHT;
		break;
	}

	return UNKNOWN;
}

IntTuple MazeData::GetRandomPointInQuadrant(Quadrant q)
{
	int minX = 0;
	int minY = 0;
	int maxX = size.x - 1;
	int maxY = size.y - 1;

	switch (q) {
	case UPPER_LEFT:
		maxX = ceil(float(maxX) / 2) - 1;
		maxY = ceil(float(maxY) / 2) - 1;
		break;
	case UPPER_RIGHT:
		minX = ceil(float(maxX) / 2);
		maxY = ceil(float(maxY) / 2) - 1;
		break;
	case LOWER_RIGHT:
		minX = ceil(float(maxX) / 2);
		minY = ceil(float(maxY) / 2);
		break;
	case LOWER_LEFT:
		maxX = ceil(float(maxX) / 2) - 1;
		minY = ceil(float(maxY) / 2);
		break;
	}

	return IntTuple{ GetRandomInt(minX, maxX), GetRandomInt(minY, maxY) };
}