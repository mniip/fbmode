#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>

char const *fields[] = {
		"xres", "yres",
		"xres_virtual", "yres_virtual",
		"xoffset", "yoffset",
		"bits_per_pixel",
		"grayscale",
		"red_offset", "red_length", "red_msb_right",
		"green_offset", "green_length", "green_msb_right",
		"blue_offset", "blue_length", "blue_msb_right",
		"transp_offset", "transp_length", "transp_msb_right",
		"nonstd",
		"activate",
		"height", "width",
		"accel_flags",
		"pixclock",
		"left_margin", "right_margin",
		"upper_margin", "lower_margin",
		"hsync_len", "vsync_len",
		"sync",
		"vmode",
		"rotate",
		"colorspace",
		NULL,
		NULL,
		NULL,
		NULL
	};
const size_t num_fields = sizeof fields / sizeof *fields;

int main(int argc, const char *argv[])
{
	if(argc == 2)
	{
		int fb = open(argv[1], O_ACCMODE);
		if(fb < 0)
		{
			perror("Could not open framebuffer");
			exit(EXIT_FAILURE);
		}
		uint32_t si[num_fields];
		if(0 > ioctl(fb, FBIOGET_VSCREENINFO, &si))
		{
			perror("Could not get screen info");
			exit(EXIT_FAILURE);
		}
		size_t i;
		for(i = 0; i < num_fields; i++)
		{
			if(!fields[i])
				break;
			printf("%s %d\n", fields[i], si[i]);
		}
	}
	else if(argc > 3 && argc % 2 == 0)
	{
		int fb = open(argv[1], O_ACCMODE);
		if(fb < 0)
		{
			perror("Could not open framebuffer");
			exit(EXIT_FAILURE);
		}
		uint32_t si[num_fields];
		if(0 > ioctl(fb, FBIOGET_VSCREENINFO, &si))
		{
			perror("Could not get screen info");
			exit(EXIT_FAILURE);
		}
		size_t i, j;
		for(i = 2; i < argc; i += 2)
		{
			int found = 0;
			int offset = 0;
			for(j = 0; j < num_fields; j++)
			{
				if(!fields[j])
					break;
				if(!strcmp(argv[i], fields[j]))
				{
					found = 1;
					uint32_t value;
					if(!sscanf(argv[i + 1], "%d", &value))
					{
						fprintf(stderr, "'%s': not a number\n", argv[i + 1]);
						exit(EXIT_FAILURE);
					}
					si[j] = value;
					break;
				}
			}
			if(!found)
			{
				fprintf(stderr, "'%s': invalid field\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
		if(0 > ioctl(fb, FBIOPUT_VSCREENINFO, &si))
		{
			perror("Could not set screen info");
			exit(EXIT_FAILURE);
		}
	}
	else if(argc == 3 && !strcmp(argv[2], "fixed"))
	{
		int fb = open(argv[1], O_ACCMODE);
		if(fb < 0)
		{
			perror("Could not open framebuffer");
			exit(EXIT_FAILURE);
		}
		struct fb_fix_screeninfo fsi;
		if(0 > ioctl(fb, FBIOGET_FSCREENINFO, &fsi))
		{
			perror("Could not get fixed screen info");
			exit(EXIT_FAILURE);
		}
		printf("id '%s'\n", fsi.id);
		printf("smem_len 0x%x\n", fsi.smem_len);
		printf("type 0x%x\n", fsi.type);
		printf("type_aux 0x%x\n", fsi.type_aux);
		printf("visual 0x%x\n", fsi.visual);
		printf("xpanstep %d\n", fsi.xpanstep);
		printf("ypanstep %d\n", fsi.ypanstep);
		printf("ywrapstep %d\n", fsi.ywrapstep);
		printf("line_length 0x%x\n", fsi.line_length);
		printf("mmio_start 0x%lx\n", fsi.mmio_start);
		printf("mmio_len 0x%x\n", fsi.mmio_len);
		printf("accel 0x%x\n", fsi.accel);
		printf("capabilities 0x%x\n", fsi.capabilities);

	}
	else
	{
		printf("Usage:\n");
		printf("    fbmode <device>\n");
		printf("        Query the framebuffer settings.\n");
		printf("    fbmode <device> fixed\n");
		printf("        Query the fixed framebuffer settings.\n");
		printf("    fbmode <device> <key> <value> [ <key> <value> [ ... ] ]\n");
		printf("        Set the framebuffer settings. The value is either a decimal or a\n");
		printf("        hexadecimal number, and key is one of the following:\n");
		size_t j;
		for(j = 0; j < num_fields; j++)
		{
			if(!fields[j])
				break;
			if(j)
				printf(", ");
			printf("%s", fields[j]);
		}
		printf(".\n");
	}
}
