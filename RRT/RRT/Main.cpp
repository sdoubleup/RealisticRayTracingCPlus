#include <iostream>
#include <fstream>
#include <memory>

#include "RGBImage.h"
#include "PPMWriter.h"
#include "Vector3.h"


int main(int argc, char *argv[])
{
	RRT::RGBImage image(240, 240);
	image.SetGamma(2.2);

	std::ofstream myFile("data.ppm", std::ios::out | std::ios::binary);

	std::unique_ptr<RRT::IWriter> pt(new RRT::PPMWriter());

	bool s = pt->write(image, myFile);

	myFile.close();

	RRT::Vector3<double> d(1.0, 1.0, 2.0);
	RRT::Vector3<int> i(2, 3, 4);
	RRT::Vector3<float> f(2.0f, 4.5f, 6.6f);

	return 0;
}