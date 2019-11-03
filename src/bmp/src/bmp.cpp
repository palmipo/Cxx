#include "bmp.h"
#include "endianness.h"

BMP::write(const std::string & file_name)
{
	FILE * fic = fopen(file_name, "wb");
	if (fic)
	{
		endianness<int32_t> conv32_t;
		endianness<int16_t> conv16_t;

		int32_t cpt1=0;
		uint8_t entete[14];
		
		entete[cpt1] = 0x42;
		cpt1+=1;
		
		entete[cpt1] = 0x4D;
		cpt1+=1;
		
		int32_t *taille_fichier = entete + cpt1;
		*taille_fichier = conv32_t.toLittleEndian(4147254);
		cpt1+=4;
		
		int32_t *reserve = &entete[cpt1];
		*reserve = conv32_t.toLittleEndian(0);
		cpt1+=4;
		
		int32_t *offset_img = &entete[cpt1];
		*offset_img = conv32_t.toLittleEndian(54);
		cpt1+=4;
		
		fwrite((const void *)entete, 1, cpt1, fic);
		
		int32_t cpt2=0;
		uint8_t entete_image[40];
		
		int32_t *taille_entete = &entete_image[cpt2];
		*taille_entete = conv32_t.toLittleEndian(0x28);
		cpt2+=4;
		
		int32_t *largeur = &entete_image[cpt2];
		*largeur = conv32_t.toLittleEndian(1920);
		cpt2+=4;
		
		int32_t *hauteur = &entete_image[cpt2];
		*hauteur = conv32_t.toLittleEndian(1080);
		cpt2+=4;
		
		int16_t *nb_plan = &entete_image[cpt2];
		*nb_plan = conv16_t.toLittleEndian(1);
		cpt2+=2;
		
		int16_t *bit_couleur = &entete_image[cpt2];
		*bit_couleur = conv16_t.toLittleEndian(16);
		cpt2+=2;
		
		int32_t *compression = &entete_image[cpt2];
		*compression = conv32_t.toLittleEndian(0);
		cpt2+=4;
		
		int32_t *taille_img = &entete_image[cpt2];
		*taille_img = conv32_t.toLittleEndian(map.size);
		cpt2+=4;
		
		int32_t *resolution_horizontale= &entete_image[cpt2];
		*resolution_horizontale = conv32_t.toLittleEndian(72);
		cpt2+=4;
		
		int32_t *resolution_verticale = &entete_image[cpt2];
		*resolution_verticale = conv32_t.toLittleEndian(72);
		cpt2+=4;
		
		int32_t *couleur_palette = &entete_image[cpt2];
		*couleur_palette = conv32_t.toLittleEndian(0);
		cpt2+=4;
		
		int32_t *couleur_importante = &entete_image[cpt2];
		*couleur_importante = conv32_t.toLittleEndian(0);
		cpt2+=4;
		
		fwrite((const void *)entete_image, 1, cpt2, fic);

		fwrite((const void *)map.data, 1, map.size, fic);

		fclose(fic);
	}
}
