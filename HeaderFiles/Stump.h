#pragma once
#include <string>
#include <vector>
class Stump
{
	class Edge;
	class Leaf;

	class Node {
		const std::string* name;
		std::vector<Edge> edges;
	};

	class Leaf {
		const bool condition;

	};

	template<typename DataType>
	class Edge {
		DataType data;
		const Leaf* leaf;
	};
};

