#include "CircularLinkedList.h"

/*
* 
* Collaborators:
*  - Andrew Nguyen
*  - Jaime Gutierrez
*  - Landon Mendoza
* 
* Date: 9/15/2025
* 
* Description: Chapter 5 Assignment (Linked Lists)
* In this project, we demonstrated and exemplified the
* Usages of Linked Lists (Singly, Doubly, & Circular) 
* and Dynamic Arrays (Vectors).
* 
*/

#include "Application.h"

int main()
{
	circular_list list;

	list.PushBack(12);
	list.PushBack(13);
	list.PushBack(14);
	list.PushBack(15);

	for (const auto& ele : list)
	{

	}

	Application app;

	app.Run();

	app.Clean();
}