#ifndef ANT_HR_H
#define ANT_HR_H

#include "antslave.h"

namespace ANT
{
	class Ant;
	class HeartRate: public Slave
	{
		public:
			HeartRate(uint8_t, uint8_t, Ant *);
			virtual ~HeartRate();

			enum eSportMode
			{
				Running = 1,
				Cycling = 2,
				Swimming = 4
			};

			virtual void setSportMode(eSportMode mode);

		protected:
			virtual int32_t specialEventPageRecv(uint8_t, uint8_t *, int32_t);

		protected:
			int32_t Cumulative_Operating_Time;
			uint8_t  Manufacturer_ID;
			uint16_t Serial_Number;
			uint8_t  Hardware_Version;
			uint8_t  Software_Version;
			uint8_t  Model_Number;
			uint8_t  Manufacturer_Specific;
			uint16_t Previous_Heart_Beat_Event_Time;
			uint8_t  Heart_Beat_Event_Time;
			uint8_t  Heart_Beat_Count;
			uint8_t  Computed_Heart_Rate;
			uint8_t  Interval_Average_Heart_Rate;
			uint8_t  Interval_Maximum_Heart_Rate;
			uint8_t  Session_Average_Heart_Rate;
			uint8_t  Features_Supported;
			uint8_t  Features_Enabled;
			uint8_t  Battery_Level;
			uint8_t  Fractional_Battery_Voltage;
			uint8_t  Descriptive_Bit_Field;
	};
}

#endif
