#include "onewirerom.h"
#include <sstream>
#include <iostream>

OneWireRom::OneWireRom()
: _nb_conflit(0)
{
	for (int i=0; i<8; ++i)
	{
		_rom[i] = 0;
		_bit_conflit[i] = 0;
	}
}
	
OneWireRom::~OneWireRom()
{}

uint8_t OneWireRom::nbConflit()
{
	return _nb_conflit;
}

uint8_t OneWireRom::conflit(uint8_t bit)
{
	uint8_t j = bit >> 3;
	uint8_t k = bit - (j << 3);
	return (_bit_conflit[j] & (1 << k)) ? 1 : 0;
}

void OneWireRom::setConflit(uint8_t bit)
{
	uint8_t j = bit >> 3;
	uint8_t k = bit - (j << 3);

	// pour le 2eme passage suppression du conflit
	if (_bit_conflit[j] & (1 << k))
	{
		//~ std::cout << "2eme passage" << std::endl;
		_nb_conflit -= 1;
	}
	else
	{
		//~ std::cout << "1er passage" << std::endl;
		_bit_conflit[j] |= (1 << k);
		_nb_conflit += 1;
	}
}

uint8_t OneWireRom::bit(uint8_t bit)
{
	uint8_t j = bit >> 3;
	uint8_t k = bit - (j << 3);
	return (_rom[j] & (1 << k)) ? 1 : 0;
}

void OneWireRom::setBit(uint8_t bit, uint8_t valeur)
{
	uint8_t j = bit >> 3;
	uint8_t k = bit - (j << 3);
	_rom[j] |= (valeur << k);
}

void OneWireRom::setRom(uint8_t octet, uint8_t valeur)
{
	_rom[octet] = valeur;
}

uint8_t OneWireRom::rom(uint8_t octet)
{
	return _rom[octet];
}

void OneWireRom::dump()
{
	std::stringstream ss;
	for (int i=0; i<8; ++i)
	{
		ss << std::hex << (int)_rom[i] << ":";
	}
	std::cout << "ROM : " << ss.str() << std::endl;
}

uint8_t OneWireRom::preparerROM(OneWireRom * src)
{
	uint8_t num_bit = 0;

	// recherche du dernier conflit
	for (int i=0; i<64; i+=1)
	{
		uint8_t j = i >> 3;
		uint8_t k = i - (j << 3);
		if (src->_bit_conflit[j] & (1 << k))
			//~ if ((src->_rom[j] & (1 << k)) == 0)
		{
			_nb_conflit += 1;
			num_bit = i;
		}
	}

	if (num_bit)
	{
		// recopie des valeurs de la ROM
		for (int i=0; i<num_bit; i+=1)
		{
			uint8_t j = i >> 3;
			uint8_t k = i - (j << 3);
			_rom[j] |= src->_rom[j] & (1 << k);

			// sauvegarde du conflit
			_bit_conflit[j] |= src->_bit_conflit[j] & (1 << k);
		}

		// suppression du conflit dans la source
		src->_nb_conflit -= 1;

		uint8_t j = num_bit >> 3;
		uint8_t k = num_bit - (j << 3);
		_rom[j] |= (1 << k);
		_bit_conflit[j] |= (1 << k);
	}
	
	return _nb_conflit;
}
