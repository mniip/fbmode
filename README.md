#Fbmode

A tiny utility for reading and writing framebuffer settings.

#Usage
- `fbmode <device>`  
  Query the framebuffer settings.
- `fbmode <device> fixed`  
  Query the fixed framebuffer settings.
- `fbmode <device> <key> <value> [ <key> <value> [ ... ] ]`  
  Set the framebuffer settings. The value is either a decimal or a hexadecimal number, and key is one of the following:
xres, yres, xres_virtual, yres_virtual, xoffset, yoffset, bits_per_pixel, grayscale, red_offset, red_length, red_msb_right, green_offset, green_length, green_msb_right, blue_offset, blue_length, blue_msb_right, transp_offset, transp_length, transp_msb_right, nonstd, activate, height, width, accel_flags, pixclock, left_margin, right_margin, upper_margin, lower_margin, hsync_len, vsync_len, sync, vmode, rotate, colorspace.
