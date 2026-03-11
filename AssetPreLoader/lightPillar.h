

#pragma once

typedef struct {
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[12 * 26 * 4 + 1];
} LightPillarImageData;

extern const LightPillarImageData TheLight_Pillar;

