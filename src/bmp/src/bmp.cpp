FILE * fic = fopen("img.bmp", "wb");
if (fic)
{
	int32_t cpt1;
	uint8_t entete[14];cpt1=0;
	
	entete[cpt1] = 0x42;
	cpt1+=1;
	
	entete[cpt1] = 0x4D;
	cpt1+=1;
	
	int32_t *taille_fichier = entete + cpt1;
	*taille_fichier = 4147254;
	cpt1+=4;
	
	int32_t *reserve = &entete[cpt1];
	*reserve = 0;
	cpt1+=4;
	
	int32_t *offset_img = &entete[cpt1];
	*offset_img = 54;
	cpt1+=4;
	
	fwrite((const void *)entete, 1, cpt1, fic);
	
	int32_t cpt2;
	uint8_t entete_image[33];cpt2=0;
	
	int32_t *taille_entete = &entete_image[cpt2];
	*taille_entete = 0x28;
	cpt2+=4;
	
	int32_t *largeur = &entete_image[cpt2];
	*largeur = 1920;
	cpt2+=4;
	
	int32_t *hauteur = &entete_image[cpt2];
	*hauteur = 1080;
	cpt2+=4;
	
	int16_t *nb_plan = &entete_image[cpt2];
	*nb_plan = 1;
	cpt2+=2;
	
	int16_t *bit_couleur = &entete_image[cpt2];
	*bit_couleur = 16;
	cpt2+=2;
	
	int32_t *compression = &entete_image[cpt2];
	*compression = 0;
	cpt2+=4;
	
	int32_t *taille_img = &entete_image[cpt2];
	*taille_img = map.size;
	cpt2+=4;
	
	int32_t *resolution_horizontale= &entete_image[cpt2];
	*resolution_horizontale = 72;
	cpt2+=4;
	
	int32_t *resolution_verticale = &entete_image[cpt2];
	*resolution_verticale = 72;
	cpt2+=4;
	
	int32_t *couleur_palette = &entete_image[cpt2];
	*couleur_palette = 0;
	cpt2+=4;
	
	int32_t *couleur_importante = &entete_image[cpt2];
	*couleur_importante = 0;
	cpt2+=4;
	
	fwrite((const void *)entete_image, 1, cpt2, fic);

	fwrite((const void *)map.data, 1, map.size, fic);

	fclose(fic);
}
