// BinarySearchTreeCLI.h

#pragma once
#include "..\BinarySearchTreeCpp\Tree.h"
#include "..\BinarySearchTreeCpp\Tree.cpp"
#include <vector>

using namespace System;

namespace BinarySearchTreeCLI {

	public ref class TreeWrapper
	{
	private:
		BinarySearchTree *bts;
	public:
		void AddW(int item);
		int RemoveW(int item);
		void DeleteW();
		cli::array<int> ^InOrderW();
		TreeWrapper();
		~TreeWrapper();
		!TreeWrapper();
		void Destroy();
	};
}
