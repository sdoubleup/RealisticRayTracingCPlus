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
#include "MultiJitterSampler.h"

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

	Vector3<double> tri_pt0(500.0 / 2 - 10, 0.0, -200.0);
	Vector3<double> tri_pt1(500.0 / 2, 100.0, -200.0);
	Vector3<double> tri_pt2(500.0 / 2 + 10, 0.0, -200.0);

	RGBColor tri_col(0.8, 0.2, 0.2);

	std::shared_ptr<IShape<double>> tri = std::shared_ptr<IShape<double>>(new Triangle<double>(tri_pt0, tri_pt1, tri_pt2, tri_col));
	shapes.push_back(tri);

	std::unique_ptr<ISampler<double>> sampler(new MultiJitterSampler<double>());
	size_t number_samples = 5;

	Concurrency::parallel_for (0, 500, [&image, direction, tmin, tmax, &shapes, &sampler, number_samples](int i) {
		// Fill a row at a time.
		std::vector<RGBColor> pixel_row;
		pixel_row.reserve(500);
		for (int j = 0; j < 500; j++) {
			
			std::vector<RGBColor> color_samples;
			std::vector<SimplePoint2<double>> ray_samples;
			sampler->Generate(ray_samples, number_samples);

			for (auto& s : ray_samples) {
				Ray<double> r(Vector3<double>(static_cast<double>(i) + s.x, static_cast<double>(j) + s.y, 0), direction);
				for (auto& v : shapes) {
					ShapeHitRecord<double> hr = v->Hit(r, tmin, tmax, 0.0);
					if (hr.Hit()) {
						color_samples.push_back(hr.Color());
					} else {
						color_samples.push_back(RGBColor(1.0, 1.0, 1.0));
					}
				}
			}

			// Average the color.
			double r = 0.0;
			double g = 0.0;
			double b = 0.0;
			for (auto& c : color_samples) {
				r += c.R();
				g += c.G();
				b += c.B();
			}
			pixel_row.push_back(RGBColor(r / number_samples, g / number_samples, b / number_samples));

		}

		image.SetRow(i, pixel_row);
	});



	bool s = pt->write(image, myFile);
	myFile.close();

			
	return 0;
}