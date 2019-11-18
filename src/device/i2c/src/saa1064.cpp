#include "saa1064.h"
#include "i2c.h"

#define SAA1064_ADDRESS				0x38
#define SAA1064_CONTROL_REGISTER_CONFIG		0
#define SAA1064_CONTROL_REGISTER_AFF_1_3	1
#define SAA1064_CONTROL_REGISTER_AFF_2_4	2

#define SAA1064_COMMAND_MODE_DYNAMIC		0
#define SAA1064_COMMAND_AFF_1_3			1
#define SAA1064_COMMAND_AFF_2_4			2
#define SAA1064_COMMAND_TEST_SEGMENT		3
#define SAA1064_COMMAND_INTENSITE_LUMINEUSE	4

SAA1064::SAA1064(uint8_t adresse, I2C * i2c)
: DeviceI2C(SAA1064_ADDRESS | (adresse & 0x3), i2c)
, _lumunosite(7)
{}

uint8_t SAA1064::status()
{
	uint8_t buffer;
	_twi->get (_address, &buffer, 1);
	return buffer >> 7;
}

void SAA1064::test_afficheurs (uint8_t valeur)
{
	uint8_t buffer[2];

	buffer[0] = SAA1064_CONTROL_REGISTER_CONFIG;

	buffer[1]  = (_lumunosite & 7) << SAA1064_COMMAND_INTENSITE_LUMINEUSE;
	buffer[1] |= ((valeur & 1) << SAA1064_COMMAND_TEST_SEGMENT);
	buffer[1] |= (1 << SAA1064_COMMAND_AFF_2_4);
	buffer[1] |= (1 << SAA1064_COMMAND_AFF_1_3);
	buffer[1] |= (1 << SAA1064_COMMAND_MODE_DYNAMIC);

	_twi->set (_address, buffer, 2);
}

void SAA1064::set_luminosity (uint8_t valeur)
{
	_lumunosite = valeur & 0x7;

	// test segments afficheur
	uint8_t buffer[2];
	buffer[0] = SAA1064_CONTROL_REGISTER_CONFIG;
	buffer[1]  = (_lumunosite & 7) << SAA1064_COMMAND_INTENSITE_LUMINEUSE;
	buffer[1] |= (1 << SAA1064_COMMAND_AFF_2_4);
	buffer[1] |= (1 << SAA1064_COMMAND_AFF_1_3);
	buffer[1] |= (1 << SAA1064_COMMAND_MODE_DYNAMIC);
	_twi->set (_address, buffer, 2);
}

void SAA1064::afficher (const char *valeurs, int32_t len)
{
	int32_t cpt = 0;
	uint8_t buffer[len+2];
	buffer[cpt]  = SAA1064_CONTROL_REGISTER_CONFIG;
	++cpt;
	buffer[cpt]  = (_lumunosite & 7) << SAA1064_COMMAND_INTENSITE_LUMINEUSE;
	buffer[cpt] |= (1 << SAA1064_COMMAND_AFF_2_4);
	buffer[cpt] |= (1 << SAA1064_COMMAND_AFF_1_3);
	buffer[cpt] |= (1 << SAA1064_COMMAND_MODE_DYNAMIC);
	++cpt;

	for (int32_t i=0; i<len; i++)
	{
		buffer[cpt] = conversion_afficheur(valeurs[i]);

		if ((i < len-1) && ((valeurs[i+1] == '.') || (valeurs[i+1] == ',') || (valeurs[i+1] == ':')))
		{
			i+=1;
			buffer[cpt] |= conversion_afficheur(valeurs[i]);
		}

		++cpt;
	}
	_twi->set (_address, buffer, 6);
}

uint8_t SAA1064::conversion_afficheur (const char digit_p)
{
	switch (digit_p)
	{
		case '0':
		return 0x3F;
		break;
		case '1':
		return 0x06;
		break;
		case '2':
		return 0x5B;
		break;
		case '3':
		return 0x4F;
		break;
		case '4':
		return 0x66;
		break;
		case '5':
		return 0x6D;
		break;
		case '6':
		return 0x7D;
		break;
		case '7':
		return 0x07;
		break;
		case '8':
		return 0x7F;
		break;
		case '9':
		return 0x6F;
		break;
		case ',':
		case ':':
		case '.':
		return 0x80;
		break;
		case 'c':
		case 'C':
		return 0x39;
		break;
		case '°':
		return 0x63;
		break;
		default :
		return 0x40;
		break;
	}
}
