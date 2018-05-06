#include "png_loader.h"

#include <iostream>

PngLoader::PngLoader(std::string _filename) : filename(_filename) {
	source.open(filename, std::ios::binary);
}

PngLoader::~PngLoader() {
	if (pngPtr && infoPtr) {
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
	} else if (pngPtr) {
		png_destroy_read_struct(&pngPtr, NULL, NULL);
	}
}

ImageData PngLoader::extractImageData() {
	png_bytepp rowPointers;
	int colorType, interlaceType;
	ImageData imageData;

	if (!source.good()) {
		std::cout << "Unable to read file " << filename << std::endl;
		return imageData;
	}

	if (!isPng()) {
		std::cout << filename << " is not a png " << std::endl;
		return imageData;
	}

	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also supply the
	 * the compiler header file version, so that we know if the application
	 * was compiled with a compatible version of the library.  REQUIRED
	 */
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!pngPtr) {
		return imageData;
	}

	/* Allocate/initialize the memory for image information.  REQUIRED. */
	infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) {
		return imageData;
	}

	/* Set error handling if you are using the setjmp/longjmp method
	 * (this is the normal method of doing things with libpng).
	 * REQUIRED unless you set up your own error handlers in
	 * the png_create_read_struct() earlier.
	 */
	if (setjmp(png_jmpbuf(pngPtr))) {
		// If we get here, we had a problem reading the file
		return imageData;
	}

	/* Set up the output control for using std::istream */
	png_set_read_fn(pngPtr, reinterpret_cast<png_voidp>(&source), [](png_structp pngPtr, png_bytep data, png_size_t length){
		// Here we get our IO pointer back from the read struct.
		// This is the parameter we passed to the png_set_read_fn() function.
		// Our std::istream pointer.
		png_voidp source = png_get_io_ptr(pngPtr);
		// Cast the pointer to std::istream* and read 'length' bytes into 'data'
		(reinterpret_cast<std::istream*>(source))->read(reinterpret_cast<char*>(data), length);
	});

	/* If we have already read some of the signature */
	png_set_sig_bytes(pngPtr, SIG_BYTES);

	/*
	 * If you have enough memory to read in the entire image at once, and
	 * you need to specify only transforms that can be controlled
	 * with one of the PNG_TRANSFORM_* bits (this presently excludes
	 * dithering, filling, setting background, and doing gamma
	 * adjustment), then you can read the entire image (including pixels)
	 * into the info structure with this call
	 *
	 * PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING  forces 8 bit
	 * PNG_TRANSFORM_EXPAND  forces to expand a palette into RGB
	 */
	png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 png_width, png_height;
	int bit_depth;
	png_get_IHDR(pngPtr, infoPtr, &png_width, &png_height, &bit_depth, &colorType, &interlaceType, NULL, NULL);

	imageData.width = static_cast<int>(png_width);
	imageData.height = static_cast<int>(png_height);
	imageData.alpha = (colorType & PNG_COLOR_MASK_ALPHA);

	unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
	imageData.pixels = new unsigned char[rowBytes * imageData.height];

	rowPointers = png_get_rows(pngPtr, infoPtr);

	for (int i = 0; i < imageData.height; i++) {
		memcpy(imageData.pixels + (rowBytes * i), rowPointers[i], rowBytes);
	}

	imageData.success = true;
	return imageData;
}

bool PngLoader::isPng() {
	unsigned char sig[SIG_BYTES];
	source.read(reinterpret_cast<char*>(sig), SIG_BYTES);
	return png_check_sig(sig, SIG_BYTES);
}
