#include "controller.h"
#include "image.h"
#include "parser.h"
#include "read_image.h"
#include "write_image.h"

int main(int argc, char** argv) {
    auto parser_results = Parse(argc, argv);
    auto filters = CreateFilters(parser_results.filters);
    Image image = ReadImage(parser_results.input);
    image = UseFilters(image, filters);
    WriteImage(image, parser_results.output);
    return 0;
}
