#include <iostream>
#include <fstream>
#include <memory>

#include <windows.h>
#include <ppl.h>

#include "RGBImage.h"
#include "PPMWriter.h"
#include "Vector3.h"
#include "OrthonormalBasis.h"
#include "Triangle.h"
#include "IShape.h"

using namespace RRT;

int main(int argc, char *argv[])
{
	RGBImage image(500, 500);
	image.SetGamma(2.2);
	std::ofstream myFile("data.ppm", std::ios::out | std::ios::binary);
	std::unique_ptr<IWriter> pt(new PPMWriter());

	Vector3<double> direction(0.0, 0.0, -1.0);

	double tmax = 100000.0;
	double tmin = 0.00001;
	std::vector<std::shared_ptr<IShape<double>>> shapes;

	Vector3<double> tri_pt0(300.0, 600.0, -800.0);
	Vector3<double> tri_pt1(0.0, 100.0, -1000.0);
	Vector3<double> tri_pt2(450.0, 20.0, -1000.0);

	RGBColor tri_col(0.8, 0.2, 0.2);

	std::shared_ptr<IShape<double>> tri = std::shared_ptr<IShape<double>>(new Triangle<double>(tri_pt0, tri_pt1, tri_pt2, tri_col));
	shapes.push_back(tri);

	Concurrency::parallel_for (0, 500, [&image, &direction, &tmin, &tmax, &shapes](int i) {
		// Fill a row at a time.
		std::vector<RGBColor> pixel_row;
		pixel_row.reserve(500);
		for (int j = 0; j < 500; j++) {
			
			Ray<double> r(Vector3<double>(i, j, 0), direction);
			for (auto& v : shapes) {
				ShapeHitRecord<double> hr = v->Hit(r, tmin, tmax, 0.0);
				if (hr.Hit()) {
					pixel_row.push_back(hr.Color());
				} else {
					pixel_row.push_back(RGBColor(1.0, 1.0, 1.0));
				}
			}

			image.SetRow(i, pixel_row);
		}
	});



	bool s = pt->write(image, myFile);
	myFile.close();

			
	return 0;
}