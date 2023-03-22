add_executable(
        image_processor
        image_processor.cpp
        color.h controller.h controller.cpp image.h crop.h crop.cpp filterwithmatrix.h parser.h parser.cpp read_image.h read_image.cpp write_image.h write_image.cpp image.cpp filterwithmatrix.cpp sharpening.h "edge_detection.h" Grayscale.h Grayscale.cpp negative.h negative.cpp filter.h "edge_detection.cpp")
