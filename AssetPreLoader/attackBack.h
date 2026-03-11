

#pragma once

typedef struct {
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[96 * 29 * 4 + 1];
} PlayerAttackBackImageData;

extern const PlayerAttackBackImageData Player_AttackBack;

