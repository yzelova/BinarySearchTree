#pragma once

#include <stdexcept>
#include <vector>
using namespace std;

namespace BTS
{
	class BinarySearchTree
	{
	public:
		void Add(int item);
		vector<int> InOrder();
		int Remove(int item);
		void Delete();
	};
}
