#ifndef _MULIJITTERSAMPLERHEADERGUARD
#define _MULIJITTERSAMPLERHEADERGUARD

#include <assert.h>
#include <random>

#include "ISampler.h"

namespace RRT {

	template <typename T>
	class MultiJitterSampler : public ISampler<T> {

	public:

		MultiJitterSampler() {}

		virtual void Generate(std::vector<SimplePoint2<T>>& samples, size_t number) const {
			
			assert(number != 0);
			assert(IsPerfect(number));

			std::random_device rd;
			std::default_random_engine rnd_engine(rd());
			// [0, 1)
			std::uniform_real_distribution<double> dist(0.0, 1.0);

			if (!IsPerfect(number)) {
				// Hopefully the user gave a perfect number,
				// but if not lets get to the nearest next one.
				number = NextPerfect(number);
			}

			size_t root_number = static_cast<size_t>(std::sqrt(number));
			double subcell_width = 1.0 / static_cast<double>(number);

			samples.reserve(number);
			for (size_t i = 0; i < number; ++i) {
				samples.push_back(SimplePoint2<T>(0, 0));
			}

			// Initialise to canonical.
			for (size_t i = 0; i < root_number; ++i) {
				for (size_t j = 0; j < root_number; ++j) {
					SimplePoint2<T>& p = samples[i * root_number + j];
					p.x = i * root_number * subcell_width + j * subcell_width + dist(rnd_engine) * subcell_width;
					p.y = j * root_number * subcell_width + i * subcell_width + dist(rnd_engine) * subcell_width;
				}
			}

			// Shuffle X within each column and Y within each row.
			for (size_t i = 0; i < root_number; ++i) {
				for (size_t j = 0; j < root_number; ++j) {
					
					int k = j + static_cast<int>(dist(rnd_engine) * (root_number - j - 1));
					T t = samples[i * root_number + j].x;
					samples[i * root_number + j].x = samples[i * root_number + k].x;
					samples[i * root_number + k].x = t;

					k = j + static_cast<int>(dist(rnd_engine) * (root_number - j - 1));
					t = samples[j * root_number + i].y;
					samples[j * root_number + i].y = samples[k * root_number + i].y;
					samples[k * root_number + i].y = t;

				}
			}
		}

	private:

		// Check if the passed number is perfect square.
		bool IsPerfect(size_t number) const {
			int root = static_cast<int>(std::sqrt(number));
			return (number == (root * root));
		}

		// Return the nearest one.
		size_t NextPerfect(size_t number) const {
			return static_cast<size_t>(std::pow(static_cast<size_t>(std::sqrt(number) + .5f), 2));
		}

	};

}

#endif