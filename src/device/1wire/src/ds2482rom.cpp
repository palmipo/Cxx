#include "ds2482rom.h"
#include <sstream>
#include <iostream>

DS2482_ROM::DS2482_ROM()
: _nb_conflit(0)
{
	for (int i=0; i<8; ++i)
	{
		_rom[i] = 0;
		_bit_conflit[i] = 0;
	}
}
	
DS2482_ROM::~DS2482_ROM()
{}

u8 DS2482_ROM::nbConflit()
{
	return _nb_conflit;
}

u8 DS2482_ROM::conflit(u8 bit)
{
	u8 j = bit >> 3;
	u8 k = bit - (j << 3);
	return (_bit_conflit[j] & (1 << k)) ? 1 : 0;
}

void DS2482_ROM::setConflit(u8 bit)
{
	u8 j = bit >> 3;
	u8 k = bit - (j << 3);

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

u8 DS2482_ROM::bit(u8 bit)
{
	u8 j = bit >> 3;
	u8 k = bit - (j << 3);
	return (_rom[j] & (1 << k)) ? 1 : 0;
}

void DS2482_ROM::setBit(u8 bit, u8 valeur)
{
	u8 j = bit >> 3;
	u8 k = bit - (j << 3);
	_rom[j] |= (valeur << k);
}

void DS2482_ROM::setRom(u8 octet, u8 valeur)
{
	_rom[octet] = valeur;
}

u8 DS2482_ROM::rom(u8 octet)
{
	return _rom[octet];
}

void DS2482_ROM::dump()
{
	std::stringstream ss;
	for (int i=0; i<8; ++i)
	{
		ss << std::hex << (int)_rom[i] << ":";
	}
	std::cout << "ROM : " << ss.str() << std::endl;
}

u8 DS2482_ROM::preparerROM(DS2482_ROM * src)
{
	u8 num_bit = 0;

	// recherche du dernier conflit
	for (int i=0; i<64; i+=1)
	{
		u8 j = i >> 3;
		u8 k = i - (j << 3);
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
			u8 j = i >> 3;
			u8 k = i - (j << 3);
			_rom[j] |= src->_rom[j] & (1 << k);

			// sauvegarde du conflit
			_bit_conflit[j] |= src->_bit_conflit[j] & (1 << k);
		}

		// suppression du conflit dans la source
		src->_nb_conflit -= 1;

		u8 j = num_bit >> 3;
		u8 k = num_bit - (j << 3);
		_rom[j] |= (1 << k);
		_bit_conflit[j] |= (1 << k);
	}
	
	return _nb_conflit;
}
