#include <stdio.h>
#include <malloc.h>

#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#pragma warning(pop)

void
main(int number_of_arguments, char **arguments)
{
    if (number_of_arguments == 2)
    {
        printf("usage: split_image.exe <inputfile_path> <outputfolder_path> <split_images_filename_prefix> <width> <height>\n");
        printf("example:\n  split_image.exe my_tilemap.png .\\output_folder tiles 32 32\n");
        printf("inputfile_path:\n   The complete path to the image that is going to be split\n");
        printf("outputfolder_path:\n   The complete path to folder in which the resulting images should be stored.\n");
        exit(-1);
    }
    if (number_of_arguments != 6)
    {
        printf("usage: split_image.exe <inputfile_path> <outputfolder_path> <split_images_filename_prefix> <width> <height>\n");
        printf("example:\n  split_image.exe my_tilemap.png .\\output_folder tiles 32 32\n");
        printf("type split_image.exe help for more information.\n");
        exit(-1);
    }

    char *inputfile_path = arguments[1];
    char *outputfolder_path = arguments[2];
    size_t outputfolder_path_length = strlen(outputfolder_path);
    if (outputfolder_path_length > 0 && (outputfolder_path[outputfolder_path_length-1] == '\\' || outputfolder_path[outputfolder_path_length-1] == '/'))
    {
        outputfolder_path[outputfolder_path_length-1] = 0;
    }
    char *filename = arguments[3];
    int width = 0;
    sscanf_s(arguments[4], "%d", &width);
    int height = 0;
    sscanf_s(arguments[5], "%d", &height);

    int x = 0, y = 0, channels_in_file = 0;
    int number_of_components = 4;
    unsigned char *image_data = stbi_load(inputfile_path, &x, &y, &channels_in_file, number_of_components);

    if (image_data == 0)
    {
        printf("could not find image %s\n", inputfile_path);
        exit(-1);
    }
    int number_of_tiles_x = x / width;

    for (int x_tile = 0; x_tile < number_of_tiles_x; ++x_tile)
    {
        for (int y_tile = 0; y_tile < number_of_tiles_x; ++y_tile)
        {
            unsigned char *output_data = (unsigned char *)calloc((size_t)(width * height * number_of_components), sizeof(unsigned char));
            for (int i = 0; i < width * height; ++i)
            {
                int scan_line = i/width;
                int index = (scan_line*x) + i%width;
                int tile_offset = x_tile * width + y_tile * x * height;
                output_data[i * number_of_components + 0] = image_data[(index + tile_offset) * number_of_components + 0];
                output_data[i * number_of_components + 1] = image_data[(index + tile_offset) * number_of_components + 1];
                output_data[i * number_of_components + 2] = image_data[(index + tile_offset) * number_of_components + 2];
                output_data[i * number_of_components + 3] = image_data[(index + tile_offset) * number_of_components + 3];
            }

            char output_filename[1024] = {0};
            sprintf_s(output_filename, 1024, "%s\\%s_%d_%d.png", outputfolder_path, filename, x_tile, y_tile);
            //printf("%s\n", output_filename);

            int bytes_written = stbi_write_png(output_filename, width, height, number_of_components, output_data, width * number_of_components * (int)sizeof(unsigned char));
            if (bytes_written == 0)
            {
                printf("could not write file %s\n", output_filename);
            }
            free(output_data);
        }
    }
    stbi_image_free(image_data);
}
