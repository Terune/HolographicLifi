#pragma once
namespace HolographicLifiTracker
{
	class LightSensors;

	class LightSensors
	{
		public:
			LightSensors();

			~LightSensors(void);

			std::vector<int> location;
			std::int32_t height;
			std::int32_t width;

	};

}