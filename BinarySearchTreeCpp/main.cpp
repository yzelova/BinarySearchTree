#include "Tree.h"
#include<iostream>
using namespace std;
using namespace BTS;

int main()
{
	BinarySearchTree wrapper;
	wrapper.Add(5);
	wrapper.Add(10);
	wrapper.Add(6);
	wrapper.Add(15);
	wrapper.Add(8);
	wrapper.Add(12);
	wrapper.Add(17);
	for (int i = 0; i < wrapper.InOrder().size(); i++)
	{
		printf("%d ", wrapper.InOrder()[i]);
	}
	printf("\n");
}