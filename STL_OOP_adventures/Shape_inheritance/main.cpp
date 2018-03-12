#include "Shape.hpp"

#include <vector>

using namespace std;

int main(){
	int select;
	int id_request;
	int count = 0;
	Square * square;
	Box * box;
	Cube * cube;
	double length, width, height;
	vector<Shape*> vec;
	vector<TwoDShape*> vec_2d;
	vector<ThreeDShape*> vec_3d;
	attr_box * attr_shuttle;

	do{
		cout << "1 to create a square, 2 to create a box, 3 to create a cube,\n"\
		"4 to visualize list, 5 to get contents of box\n" << endl;
		cin >> select;
	
		switch(select){

			case 1:	
				cout << "enter the dimension for the square!" << endl;
				cin >> length ;
				count++;
				square = new Square(length,count);
				vec.push_back(square);
				vec_2d.push_back(square);
				break;

			case 2:
				cout << "enter the dimensions for the box!" << endl;
				cin >> length >> width >> height;
				count++;
				box = new Box(length,width,height,count);
				vec.push_back(box);
				vec_3d.push_back(box);
				break;

			case 3:
				cout << "enter the dimensions for the Cube!" << endl;
				cin >> length;
				count++;
				cube = new Cube(length,count);
				vec.push_back(cube);
				vec_3d.push_back(cube);
				break;

			case 4:
				cout << "shape master list " << endl;
				for (Shape * shape : vec){
					shape->display();
				}

				cout << "2d shape list" << endl;
				for (TwoDShape* shape : vec_2d)
					shape->display();

				cout << "3d shape list" << endl;
				for (ThreeDShape * shape : vec_3d)
					shape->display();

				break;
			case 5:
				cout << "what is the id of the requested object?" << endl;
				cin >> id_request;
				for (Shape * shape : vec){
					
					if (shape->get_id() == id_request){	
						
						attr_shuttle = new attr_box;
						box = dynamic_cast<Box*> (shape);
						box->get_dim_attr(attr_shuttle);
					}
				}
				cout << attr_shuttle->length << " " << attr_shuttle->width << " " <<attr_shuttle->height << endl;
				delete attr_shuttle;
				break;
			case 0:
				break;
			default:
				break;
			}
		} while( select != 0 );
	return 0;
}

