#pragma 
#include <iostream>
#include <Windows.h>

int Transform(int x, int y, int z, int width, int height) {
	// This function returns which index the specific x, y, z
	// coordinate is in the one dimensional array.
	// Let's test it.
	return (z + (y * height) + (x * width * height));
}

int main() {
	/* Suppose we had a 3D array like so:
		   y1        y2        y3
		z1 z2 z3  z1 z2 z3  z1 z2 z3 [
	x1[[0, 1, 0],[1, 0, 0],[1, 1, 1]],
	x2[[0, 2, 1],[1, 2, 1],[1, 1, 1]],
	x3[[0, 1, 2],[1, 2, 2],[1, 1, 0]] ]
		...        ...       ...

	How could we transform it into a 1D array like this?
	[0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 2, 1, 1, 2, 1, 1, 1, 1, 0, 1, 2, 1, 2, 2, 1, 1, 0, ...]

	And then when given an x, y, z, and width and height, assuming it is square, how
	could we find the index of the one dimensional array?

	This is a linear transformation of a 3D array x, y, z coordinate system into a linear
	x coordinate system. It will be very helpful when we are constructing our chunks in
	Minecraft.
	*/

	int three_d[3][3][4] = {
	//             y1            y2            y3
	//        nz1 z2 z3 z4   z1 z2 z3 z4   z1 z2 z3 z4
	/*x1*/	{ {0, 1, 0, 2}, {1, 0, 0, 1}, {1, 1, 1, 2} },
	/*x2*/  { {0, 2, 1, 0}, {1, 2, 1, 1}, {1, 1, 1, 1} },
	/*x3*/  { {0, 1, 2, 2}, {1, 2, 2, 1}, {1, 1, 0, 0} }
	};

	int one_d[36] = { 0, 1, 0, 2, 1, 0, 0, 1, 1, 1, 1, 2, 0, 2, 1, 0, 
		1, 2, 1, 1, 1, 1, 1, 1, 0, 1, 2, 2, 1, 2, 2, 1, 1, 1, 0, 0 };

	// What is at x2, y3, z1? It should be 1 according to our diagram
	// Remember, since arrays start at 0, it's really 1, 2, 0
	std::cout << three_d[1][2][0] << std::endl;

	// Let's try our 3D transformation
	int index = Transform(1, 2, 0, 3, 4);
	std::cout << one_d[index] << std::endl;

	// Let's print everything
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 4; z++) {
				int one_d_index = Transform(x, y, z, 3, 4);
				std::cout << three_d[x][y][z] << " " << one_d[one_d_index] << std::endl;
			}
		}
	}
	system("pause");
	return 0;
}