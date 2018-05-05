#include "./texture.h"

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
    png_structp png_ptr;
    png_infop info_ptr;
    const unsigned int SIG_BYTES = 8;
    int color_type, interlace_type;
    FILE *fp;

   	if ((fp = fopen(filename.c_str(), "rb")) == NULL) {
        return false;
    }

    // Read PNG signature
    unsigned char sig[SIG_BYTES];
    fread(sig, 1, 8, fp);
    if (!png_check_sig(sig, SIG_BYTES)) {
        std::cout << filename << " is not a .png" << std::endl;
        fclose(fp);
        return false;
    }

    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, SIG_BYTES);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 png_width, png_height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &png_width, &png_height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

    width = static_cast<int>(png_width);
    height = static_cast<int>(png_height);
    alpha = (color_type & PNG_COLOR_MASK_ALPHA);

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    data = new GLubyte[row_bytes * height];

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < height; i++) {
        memcpy(data + (row_bytes * i), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    /* Close the file */
    fclose(fp);

    /* That's it */
    return true;
}


