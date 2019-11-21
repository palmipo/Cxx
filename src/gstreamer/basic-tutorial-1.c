#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/base/gstbasesink.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void eos_function(GstAppSink *appsink, gpointer user_data)
{
	printf("eos_function\n");
}

GstFlowReturn new_preroll(GstAppSink *appsink, gpointer user_data)
{
	printf("new_preroll\n");

	return GST_FLOW_OK;
}

static int cpt0=0;
GstFlowReturn new_sample_function(GstAppSink *appsink, gpointer user_data)
{
	printf("new_sample_function\n");

	if (!gst_app_sink_is_eos(appsink))
	{
		GstSample* sample = gst_app_sink_pull_sample(appsink);

		if(!sample)
		{
			fprintf(stderr, "gst_app_sink_pull_sample returned null\n");
			return FALSE;
		}

		// Actual compressed image is stored inside GstSample.
		GstCaps * caps = gst_sample_get_caps (sample);
		if (!caps)
		{
			fprintf(stderr, "gst_sample_get_caps returned null\n");
			return FALSE;
		}

		GstStructure * st = gst_caps_get_structure(caps, 0);
		if (!st)
		{
			fprintf(stderr, "gst_caps_get_structure returned null\n");
			return FALSE;
		}

		int32_t width = 1920;
		gst_structure_get_int(st, "width", &width);

		int32_t height = 1080;
		gst_structure_get_int(st, "height", &height);

		int32_t nb_couleur = 24;

		//~ gst_structure_free(st);
		//~ gst_caps_unref(caps);

		GstBuffer* buffer = gst_sample_get_buffer (sample);
		if (!buffer)
		{
			fprintf(stderr, "gst_sample_get_buffer returned null\n");
			return FALSE;
		}

		GstMapInfo map;
		gst_buffer_map (buffer, &map, GST_MAP_READ);
		fprintf(stderr, "%d %d %d\n", width, height, map.size);
		nb_couleur = ((map.size / width) / height) * 8;

		/* map.data, map.size */
		//~ if (cpt0 == 2)
		{
			char nom[100];
			sprintf(nom, "img%d.bmp", cpt0);
			FILE * fic = fopen(nom, "wb");
			if (fic)
			{
				int32_t cpt1;
				uint8_t entete[14];cpt1=0;
				
				entete[cpt1] = 0x42;
				cpt1+=1;
				
				entete[cpt1] = 0x4D;
				cpt1+=1;
				
				int32_t *taille_fichier = entete + cpt1;
				*taille_fichier = map.size + 54;
				cpt1+=4;
				
				int32_t *reserve = &entete[cpt1];
				*reserve = 0;
				cpt1+=4;
				
				int32_t *offset_img = &entete[cpt1];
				*offset_img = 54;
				cpt1+=4;
				
				fwrite((const void *)entete, 1, cpt1, fic);
				
				int32_t cpt2;
				uint8_t entete_image[40];cpt2=0;
				
				int32_t *taille_entete = &entete_image[cpt2];
				*taille_entete = 0x28;
				cpt2+=4;
				
				int32_t *largeur = &entete_image[cpt2];
				*largeur = width;
				cpt2+=4;
				
				int32_t *hauteur = &entete_image[cpt2];
				*hauteur = height;
				cpt2+=4;
				
				int16_t *nb_plan = &entete_image[cpt2];
				*nb_plan = 1;
				cpt2+=2;
				
				int16_t *bit_couleur = &entete_image[cpt2];
				*bit_couleur = nb_couleur;
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
		}
		cpt0 += 1;

		gst_buffer_unmap (buffer, &map);
		gst_sample_unref (sample);
	}
	//~ return TRUE;
	return GST_FLOW_OK;
}


int main(int argc, char *argv[])
{
	/* Initialize GStreamer */
	gst_init (&argc, &argv);

	/* Create the empty pipeline */
	GstElement *pipeline = gst_parse_launch ("v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=RGB ! appsink name=sink0", 0);
	//~ GstElement *pipeline = gst_parse_launch ("v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=RGB ! cverode iterations=10 ! appsink name=sink0", 0);
	//~ GstElement *pipeline = gst_parse_launch ("v4l2src device=/dev/video0 ! videoconvert ! video/x-raw,format=RGB,width=640,height=480 ! cverode iterations=10 ! appsink name=sink0", 0);
	//~ GstElement *pipeline = gst_parse_launch ("v4l2src device=/dev/video0 ! videocrop top=450 left=900 bottom=550 right=1200 ! videoconvert ! video/x-raw,format=RGB ! cverode iterations=1 ! appsink name=sink0", 0);
	GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink0");
	if (!pipeline || !sink)
	{
		g_printerr ("Not all elements could be created.\n");
		return -1;
	}

	/* Create the elements */
	GstAppSinkCallbacks callbacks;
	callbacks.eos = eos_function;
	callbacks.new_preroll = new_preroll;
	callbacks.new_sample = new_sample_function;
	gpointer user_data = 0;
	GDestroyNotify notify = FALSE;
	gst_app_sink_set_callbacks ((GstAppSink *)sink, &callbacks, user_data, notify); 

	/* Start playing */
	GstStateChangeReturn ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
	{
		g_printerr ("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (pipeline);
		return -1;
	}

	/* Wait until error or EOS */
	GstBus *bus = gst_element_get_bus (pipeline);
	GstMessage *msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Parse message */
	if (msg != NULL)
	{
		GError *err;
		gchar *debug_info;

		switch (GST_MESSAGE_TYPE (msg))
		{
			case GST_MESSAGE_ERROR:
				gst_message_parse_error (msg, &err, &debug_info);
				g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
				g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
				g_clear_error (&err);
				g_free (debug_info);
			break;
			case GST_MESSAGE_EOS:
				g_print ("End-Of-Stream reached.\n");
			break;
			default:
				/* We should not reach here because we only asked for ERRORs and EOS */
				g_printerr ("Unexpected message received.\n");
			break;
		}
		gst_message_unref (msg);
	}

	/* Free resources */
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	return 0;
}
