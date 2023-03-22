#include "read_image.h"
#include <fstream>
#include <limits>

Image ReadImage(std::string &file_path) {
    std::ifstream bmp(file_path, std::ios::binary);
    BitMapHeader bmh;
    bmp.read(reinterpret_cast<char *>(&bmh), sizeof(BitMapHeader));
    InfoHeader ih;
    bmp.read(reinterpret_cast<char *>(&ih), sizeof(InfoHeader));

    std::vector<std::vector<Color>> pix(ih.height, std::vector<Color>(ih.width));
    for (uint32_t i = 0; i < ih.height; ++i) {
        for (uint32_t j = 0; j < ih.width; ++j) {
            RGB current;
            bmp.read(reinterpret_cast<char *>(&current), sizeof(RGB));
            pix[ih.height - 1 - i][j].Red = static_cast<double>(current.Red) / std::numeric_limits<uint8_t>::max();
            pix[ih.height - 1 - i][j].Green = static_cast<double>(current.Green) / std::numeric_limits<uint8_t>::max();
            pix[ih.height - 1 - i][j].Blue = static_cast<double>(current.Blue) / std::numeric_limits<uint8_t>::max();
        }
        uint32_t to_read = ((3 * ih.width + 3) / 4) * 4 - 3 * ih.width;
        for (uint32_t j = 0; j < to_read; ++j) {
            bmp.get();
        }
    }
    Image image(bmh, ih, pix);
    return image;
}
