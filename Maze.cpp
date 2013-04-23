#include "Maze.h"

Maze::Maze(string filename)
{

}

// creates a maze with width and length n
Maze::Maze(int n)
{
	size = n;
	// N is the total number of rooms in the maze
	int N = n*n;
	// make nodes hold the correct number of rooms
	nodes.resize(N);
	int count = 0;
	// close every door to every room in the maze
	while(count < N)
	{
		nodes[count].north = 1;
		nodes[count].south = 1;
		nodes[count].east = 1;
		nodes[count].west = 1;
		count++;
	}

	// now create a starting and ending point
	nodes[0].north = 0;
	nodes[N-1].south = 0;

	// for creating the maze
	DisjointSets s(N);

	// a loop to create the maze, picks a random room and connects it with an adjacent room until room 0 and room N-1 are connected
	while (s.find(0) != s.find(N-1))
	{
		// first pick a random room
		int i = rand() %N;
		// this will be the adjacent room to room i
		int j;

		int k;
		// upper left room
		if(i == 0)
			{
				k = rand() %2;
				// union starting room with the room to the east
				if(k == 0)
				{
					j = i+1;
				}
				// union starting room with the room to the south
				else
				{
					j = i+n;
				}

			}
		// upper right room
			else if (i == (n-1))
			{
				k = rand() %2;
				// union room with the room to the west
				if (k == 0)
				{
					j = i-1;
				}
				// union room with the room to the south
				else
				{
					j = i+n;
				}
			
			}

		// Top mid rooms of maze
		else if(i < n)
		{
			k = rand() %3;
			// union room i with room to the south
			if(k == 0)
			{
				j = i+n;
			}
			// union room i with the room to the east
			else if(k == 1)
			{
				j = i+1;
			}
			// union room i with the room to the west
			else
			{
				j = i-1;
			}

		}

		// bottom left room
		else if(i == (N-n))
		{
			k = rand() %2;

			// union i with the room to the east
			if(k == 0)
			{
				j = i+1;
			}
			// union i with the room to the north
			else
			{
				j = i-n;
			}
		}
		// bottom right room
		else if (i == (N-1))
		{
			k = rand() %2;

			// union i with the room to the west
			if(k == 0)
			{
				j = i-1;
			}
			// union i with the room to the north
			else
			{
				j = i-n;
			}
		}
		// Bottom row of maze
		else if(i >= (N-n) ) 
		{
			k = rand() %3;
			// union room i with room to the north
			if(k == 0)
			{
				j = i-n;
			}
			// union room i with the room to the east
			else if(k == 1)
			{
				j = i+1;
			}
			// union room i with the room to the west
			else
			{
				j = i-1;
			}
			
		}
		// Left column of maze
		else if((i%n) == 0)
		{
			k = rand() %3;
			// union i with the room to the north
			if(k == 0)
			{
				j = i-n;
			}
			// union i with the room to the south
			else if(k == 1)
			{
				j = i+n;
			}
			// union i with the room to the east
			else
			{
				j = i+1;
			}

		}
		// Right column of maze
		else if((i%n) == (n-1) )
		{
			k = rand() %3;
			// union i with the room to the north
			if(k == 0)
			{
				j = i-n;
			}
			// union i with the room to the south
			else if(k == 1)
			{
				j = i+n;
			}
			// union i with the room to the west
			else
			{
				j = i-1;
			}
		}
		// all the rooms in the center
		else
		{
			k = rand() %4;
			// union i with the room to the north
			if(k == 0)
			{
				j = i-n;
			}
			// union i with the room to the south
			else if(k == 1)
			{
				j = i+n;
			}
			// union i with the room to the east
			else if(k == 2)
			{
				j = i+1;
			}
			// union i with the room to the west
			else
			{
				j = i-1;
			}
		}
		if(s.find(i) != s.find(j))
		{
			s.unionSets(i,j);
			// if j is north of i
			if(j == (i-n))
			{
				nodes[i].north = 0;
				nodes[j].south = 0;
			}
			// if j is south if i
			else if(j == (i+n))
			{
				nodes[i].south = 0;
				nodes[j].north = 0;
			}
			// if j is east of i
			else if(j == (i+1))
			{
				nodes[i].east = 0;
				nodes[j].west = 0;
			}
			// if j is west if i
			else
			{
				nodes[i].west = 0;
				nodes[j].east = 0;
			}
		}
	}

}

Maze::Maze(const Maze &rhs)
{
	*this = rhs;
}

Maze::~Maze()
{
	// Nothing here!
}

const Maze & Maze::operator=(const Maze &rhs)
{
	size = rhs.size;
	nodes = rhs.nodes;
	return *this;
}

void Maze::readFromFile(string filename)
{
	ifstream inFile(filename.c_str());
	if (inFile == NULL || !inFile.is_open())
	{
		cerr << "Unable to open file: " << filename << endl;
		exit(EXIT_FAILURE);
	}

	inFile >> size;

	nodes = vector<Node>();
	nodes.reserve(size * size);

	for (int i = 0; i < size * size; ++i)
	{
		int northDoor, southDoor, eastDoor, westDoor;

		inFile >> northDoor >> southDoor >> eastDoor >> westDoor;

		Node node;
		node.north = northDoor;
		node.south = southDoor;
		node.east = eastDoor;
		node.west = westDoor;

		nodes.push_back(node);
	}
}

void Maze::print() const
{
	// This algorithm first prints the north edges of the first row
	// Then it loops through each cell and prints the west and south edges
	// If the current room is the last in the row, print the west edge

	// Print the top edges (if necessary)
	cout << " "; // Align the top walls
	for (int i = 0; i < size; ++i)
	{
		Node node = nodes[i];
		
		// Print the top walls or a space if there is none
		if (node.north)
			cout << "_ ";
		else
			cout << "  ";
	}
	cout << endl;

	for (int i = 0; i < size * size; ++i)
	{
		Node node = nodes[i];

		// Print the west wall or a space if there is none
		if (node.west)
			cout << "|";
		else
			cout << " ";

		// Print the south wall or a space if there is none
		if (node.south)
			cout << "_";
		else
			cout << " ";

		// If the current node is the last in the row, print the east wall if necessary
		if (i % size == (size - 1))
		{
			if (node.east)
				cout << "|";
			else
				cout << " ";
		}

		// If we are ending a row, put the next row on a new line
		if (i % size == (size - 1))
			cout << endl;
	}
	cout << endl;
}

vector<int> Maze::solve(SolutionType solutionType) const
{
	if (solutionType == SolutionType::BREADTH_FIRST)
	{
		Queue<int> q;
	}

	return vector<int>();
}

void Maze::printSolution(SolutionType solutionType) const   
{ 
	cout << "Rooms visited by ";
	if (solutionType == SolutionType::BREADTH_FIRST)
		cout << "BFS";
	else if (solutionType = SolutionType::DEPTH_FIRST)
		cout << "DFS";

	cout << ": ";

	// TODO: Print the rooms visited

	cout << endl;
	cout << "This is the path (in reverse): ";
	vector<int> path = solve(solutionType);

	for(std::vector<int>::const_iterator i = path.begin(); i != path.end(); ++i)
		std::cout << *i << " ";

	cout << endl;
	cout << "This is the path." << endl;

	for (int i = 0; i < size * size; ++i)
	{
		if (find(path.begin(), path.end(), i) != path.end())
			cout << "X ";
		else
			cout << "  ";

		if (i % size == 0)
			cout << endl;
	}

	cout << endl;
}