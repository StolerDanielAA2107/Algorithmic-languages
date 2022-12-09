#include <iostream>
#include "Graph.h"

using namespace std;

int main()  // тело программы
{
	Graph gr;
	bool saveobj = true;
	gr.menu();
	while (1) {
		cout << "Выберите пункт:" << endl;
		switch (InputCheck(0, 10))
		{
			case 0: {
				if (!saveobj) {
					cout << "Параметры не были сохранены, сохранить их?" << endl;
					cout << "1.Да" << endl;
					cout << "2.Нет" << endl;
					while (1) {
						switch (InputCheck(1, 2)) {
						case 1:
							&Graph::SaveAll;
							exit(0);
						case 2: exit(0);
						}
					}
				}
				else exit(0);
			}

			case 1: 
				gr.InputPipe();
				saveobj = false;
				break; 

			case 2: 		
				gr.InputKS();
				saveobj = false;
				break; 

			case 3: 
				gr.PrintAll();
				break;
			
			case 4: 
				gr.Search();
				saveobj = false;
				break; 
			case 5: 
				gr.newgraph();
				break;
	
			case 6: 
				gr.printgraph();

			case 7:
				gr.TopologicalSort();
 				break;
			case 8: 
				gr.SaveAll();
				saveobj = true;
				break; 
			
			case 9: 
				gr.LoadAll();
				break;
			
			case 10:
				gr.Delete();
				saveobj = false;
				break;	
		}
	}
}