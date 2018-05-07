#include "png_loader.h"

PngLoader::PngLoader(std::string _filename) : ImageLoader(_filename) {}

PngLoader::~PngLoader() {
	if (pngPtr && infoPtr) {
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
	} else if (pngPtr) {
		png_destroy_read_struct(&pngPtr, NULL, NULL);
	}
}

ImageData PngLoader::extractImageData() {
	png_bytepp rowPointers;
	png_voidp errorPtr = nullptr;
	int colorType, interlaceType;
	ImageData imageData;

	if (!source.good()) {
		throw ImageLoadException("Unable to read file");
	}

	if (!isPng()) {
		throw ImageLoadException("File is not a png");
	}

	/*
	Create and initialize the png_struct with the desired error handler
	functions.  To avoid having to use libpng's setjmp/longjpm error handler,
	our own exception-based handler is supplied as a lambda. The first argument
	to the lambda is pngPtr, but we don't use it so it is left unnamed.
	We also supply the the compiler header file version, so that we know if the
	application was compiled with a compatible version of the library.  REQUIRED
	*/
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, errorPtr, [](png_structp, png_const_charp errorMessage) {
		throw ImageLoadException(errorMessage);
	}, NULL);

	if (!pngPtr) {
		return imageData;
	}

	/* Allocate/initialize the memory for image information.  REQUIRED. */
	infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) {
		return imageData;
	}

	/*
	Set up the output control for using std::istream, rather than using png_init_io
	which requires a C-style file pointer.
	*/
	png_set_read_fn(pngPtr, reinterpret_cast<png_voidp>(&source), [](png_structp pngPtr, png_bytep data, png_size_t length){
		// Here we get our IO pointer back from the read struct.
		// This is the parameter we passed to the png_set_read_fn() function.
		// Our std::istream pointer.
		std::ifstream* source = reinterpret_cast<std::ifstream*>(png_get_io_ptr(pngPtr));
		// Read 'length' bytes into 'data'
		source->read(reinterpret_cast<char*>(data), length);
	});

	/* Since we have already read some of the signature */
	png_set_sig_bytes(pngPtr, SIG_BYTES);

	/*
	If you have enough memory to read in the entire image at once, and
	you need to specify only transforms that can be controlled
	with one of the PNG_TRANSFORM_* bits (this presently excludes
	dithering, filling, setting background, and doing gamma
	adjustment), then you can read the entire image (including pixels)
	into the info structure with this call

	PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING  forces 8 bit
	PNG_TRANSFORM_EXPAND  forces to expand a palette into RGB
	 */
	png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 png_width, png_height;
	int bit_depth;
	png_get_IHDR(pngPtr, infoPtr, &png_width, &png_height, &bit_depth, &colorType, &interlaceType, NULL, NULL);

	imageData.width = static_cast<int>(png_width);
	imageData.height = static_cast<int>(png_height);
	imageData.alpha = (colorType & PNG_COLOR_MASK_ALPHA);

	/*
	Allocate space to hold the pixel data.
	The pointer to the data is returned from this function and the memory
	is expected to be managed by the caller - the pixel data outlives the
	loader instance.
	*/
	unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
	imageData.pixels = new unsigned char[rowBytes * imageData.height];

	rowPointers = png_get_rows(pngPtr, infoPtr);

	for (int i = 0; i < imageData.height; i++) {
		memcpy(imageData.pixels + (rowBytes * i), rowPointers[i], rowBytes);
	}

	return imageData;
}

bool PngLoader::isPng() {
	unsigned char sig[SIG_BYTES];
	source.read(reinterpret_cast<char*>(sig), SIG_BYTES);
	return png_check_sig(sig, SIG_BYTES);
}
