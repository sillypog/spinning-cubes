#include "./texture.h"

#include <fstream>
#include <iostream>

#include <png.h>

Texture::Texture(const std::string &filename){
	bool success = loadPNGImage("assets/textures/" + filename);

	std::cout << "Outcome of loading " << filename << ": " << (success ? "success" : "fail") << std::endl;
	if (success){
		std::cout << filename << ": " << width << "x" << height << ", alpha: " << alpha << std::endl;
	} else {
		// Assign a placeholder texture
		width = 2;
		height = 2;
		data = new GLubyte[RGB_BYTES * width * height] {
			255, 255, 255, 0, 0, 0,
			0, 0, 0, 255, 255, 255
		};
	}
}

Texture::~Texture() {
	delete [] data;
}

GLuint Texture::getBufferId() const {
	return bufferId;
}

void Texture::setBufferId(GLuint id) {
	bufferId = id;
}

bool Texture::hasAlpha() const {
	return alpha;
}

int Texture::getWidth() const {
	std::cout << "Width " << width << std::endl;
	return width;
}

int Texture::getHeight() const {
	std::cout << "Height " << height << std::endl;
	return height;
}

const GLubyte* Texture::getDataPointer() const {
	std::cout << "Data ";
	for (int i = 0; i < 20; i++) {
		std::cout << data[i];
	}
	std::cout << "..." << std::endl;
	return data;
}

bool Texture::loadPNGImage(const std::string &filename) {
	const unsigned int SIG_BYTES = 8;
	png_structp pngPtr;
	png_infop infoPtr;
	png_bytepp rowPointers;
	int colorType, interlaceType;

	std::ifstream source(filename, std::ios::binary);
	if (!source.good()) {
		std::cout << "Unable to read file " << filename << std::endl;
		return false;
	}

	// Read PNG signature
	unsigned char sig[SIG_BYTES];
	source.read(reinterpret_cast<char*>(sig), SIG_BYTES);
	if (!png_check_sig(sig, SIG_BYTES)) {
		std::cout << filename << " is not a .png" << std::endl;
		return false;
	}



	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also supply the
	 * the compiler header file version, so that we know if the application
	 * was compiled with a compatible version of the library.  REQUIRED
	 */
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!pngPtr) {
		return false;
	}

	/* Allocate/initialize the memory for image information.  REQUIRED. */
	infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) {
		png_destroy_read_struct(&pngPtr, NULL, NULL);
		return false;
	}

	/* Set error handling if you are using the setjmp/longjmp method
	 * (this is the normal method of doing things with libpng).
	 * REQUIRED unless you set up your own error handlers in
	 * the png_create_read_struct() earlier.
	 */
	if (setjmp(png_jmpbuf(pngPtr))) {
		// Free all of the memory associated with the pngPtr and infoPtr
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

		// If we get here, we had a problem reading the file
		return false;
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

	width = static_cast<int>(png_width);
	height = static_cast<int>(png_height);
	alpha = (colorType & PNG_COLOR_MASK_ALPHA);

	unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
	data = new GLubyte[rowBytes * height];

	rowPointers = png_get_rows(pngPtr, infoPtr);

	for (int i = 0; i < height; i++) {
		memcpy(data + (rowBytes * i), rowPointers[i], rowBytes);
	}

	/* Clean up after the read, and free any memory allocated */
	png_destroy_read_struct(&pngPtr, &infoPtr, NULL);

	return true;
}


