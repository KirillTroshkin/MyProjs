#include "Grayscale.h"

const double RED_PARAM = 0.299;
const double GREEN_PARAM = 0.587;
const double BLUE_PARAM = 0.114;

Image Grayscale::Change(Image &image) {
    std::vector<std::vector<Color>> colors2(image.colors_.size());
    for (size_t i = 0; i < colors2.size(); ++i) {
        colors2[i].resize(image.colors_[0].size());
    }
    for (size_t i = 0; i < image.colors_.size(); ++i) {
        for (size_t j = 0; j < image.colors_[0].size(); ++j) {
            (colors2[i][j]).Red = (image.colors_[i][j]).Red * RED_PARAM + (image.colors_[i][j]).Green * GREEN_PARAM +
                                  (image.colors_[i][j]).Blue * BLUE_PARAM;
            (colors2[i][j]).Green = (image.colors_[i][j]).Red * RED_PARAM + (image.colors_[i][j]).Green * GREEN_PARAM +
                                    (image.colors_[i][j]).Blue * BLUE_PARAM;
            (colors2[i][j]).Blue = (image.colors_[i][j]).Red * RED_PARAM + (image.colors_[i][j]).Green * GREEN_PARAM +
                                   (image.colors_[i][j]).Blue * BLUE_PARAM;
        }
    }
    image.colors_ = colors2;
    return image;
}
