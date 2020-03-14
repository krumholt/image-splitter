Splits an image into multiple images. Useful for creating single images from a tileset.

The implementation uses stb_image.h and stb_image_write.h from the excellent stb libraries. https://github.com/nothings/stb

usage
-----
split_image.exe <inputfile_path> <outputfolder_path> <split_images_filename_prefix> <width> <height>

inputfile_path: complete path to the source file
outputfolder_path: must be an existing folder
split_images_filename_prefix: resulting images will be named with this prefix and 2 numbers coresponding to the row and column they were created from.
width: width of the resulting images
height: height of the resulting images

example
-------
split_image.exe my_tilemap.png .\output_folder tiles 32 32

