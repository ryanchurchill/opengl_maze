#include "MazeData.h"

MazeData::MazeData()
{
	size = DEFAULT_SIZE;
	//cells = vector < MazeCell>();
}

MazeCell MazeData::GetCellAtPoint(IntTuple point)
{
	return cells.at(GetCellIndexFromPoint(point));
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
				MazeCell c = m->GetCellAtPoint(IntTuple{ x,y });
				if (c.lineTop) {
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
			MazeCell c = m->GetCellAtPoint(IntTuple{ x,y });
			if (x == 0) {
				if (c.lineLeft) {
					std::cout << "|";
				}
				else {
					std::cout << " ";
				}
			}
			if (c.lineBottom) {
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
			if (c.lineRight) {
				std::cout << "|";
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}
