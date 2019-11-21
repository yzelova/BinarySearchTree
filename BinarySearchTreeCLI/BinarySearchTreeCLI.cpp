// This is the main DLL file.

#include "stdafx.h"

#include "BinarySearchTreeCLI.h"
#include"..\BinarySearchTreeCpp\Tree.h"

using namespace BinarySearchTreeCLI;

TreeWrapper::TreeWrapper()
{
	bts = new BinarySearchTree();
}

void TreeWrapper::Destroy()
{
	if (!(bts == nullptr))
	{
		delete bts;
		bts = nullptr;
	}
}

TreeWrapper::~TreeWrapper()
{
	Destroy();
}

TreeWrapper::!TreeWrapper()
{
	Destroy();
}

void TreeWrapper::AddW(int item)
{
	if (!(bts == nullptr))
	{
		bts->Add(item);
	}
}

int TreeWrapper::RemoveW(int item)
{
	return bts->Remove(item);
}

void TreeWrapper::DeleteW()
{
	bts->Delete();
}

cli::array<int> ^TreeWrapper::InOrderW()
{
	std::vector<int> v = bts->InOrder();
	cli::array<int> ^tempArr = gcnew cli::array<int>(v.size());
	for (int i = 0; i < v.size(); i++)
	{
		tempArr[i] = v[i];
	}
	return tempArr;
}

