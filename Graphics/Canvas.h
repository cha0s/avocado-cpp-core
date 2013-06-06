#ifndef AVOCADO_CANVAS_H
#define AVOCADO_CANVAS_H

#include "core/avocado-global.h"

#include "core/FS.h"
#include "core/ResourceManager.h"

#include "GraphicsService.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @brief The %Canvas SPI handles drawing and pixel manipulation capabilities.
 *
 * The %Canvas SPI is responsible for constructing, destroying, rendering and
 * various primitive drawing operations that can take place on a canvas. This
 * contrasts with the Image SPI which handles immutable images. %Canvas is
 * slower than Image due to this.
 *
 * @ingroup Resources
 */
class Canvas {

public:

	/**
	 * NULL Canvas constructor.
	 */
	Canvas();

	/**
	 * Build a canvas from a filename.
	 */
	Canvas(const boost::filesystem::path &uri);

	/**
	 * Build a canvas to given width/height specifcations.
	 */
	Canvas(int width, int height);

	virtual ~Canvas();

	/**
	 * Show the canvas.
	 */
	virtual void display() {}

	/**
	 * Draw a circle at the given x, y with the given radius. Draw it with the
	 * given RGBA color, and with the given blend mode.
	 */
	virtual void drawCircle(int x, int y, int radius, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) = 0;

	/**
	 * Draw a filled box at the given x, y with the given width, height
	 * dimensions. Draw it with the given RGBA color, and with the given blend
	 * mode.
	 */
	virtual void drawFilledBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) = 0;

	/**
	 * Draw a line at the given x, y to the x2, y2. Draw it with the given
	 * RGBA color, and with the given blend mode.
	 */
	virtual void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) = 0;

	/**
	 * Draw a box at the given x, y with the given width, height dimensions.
	 * Draw it with the given RGBA color, and with the given blend mode.
	 */
	virtual void drawLineBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) = 0;

	/**
	 * Fill with a specified color.
	 */
	virtual void fill(int r, int g, int b, double a) = 0;

	/**
	 * Get the height of the canvas.
	 */
	virtual int height() const = 0;

	/**
	 * Check whether the Canvas is NULL. Any 0-length axis is the most abstract
	 * way to determine NULL status.
	 */
	virtual bool isNull() const;

	/**
	 * Get the pixel color at a given x, y coordinate.
	 */
	virtual unsigned int pixelAt(int x, int y) const = 0;

	/**
	 * Save the canvas to a file.
	 */
	virtual void saveToFile(const boost::filesystem::path &filename) = 0;

	/**
	 * Set the pixel color at a given x, y coordinate.
	 */
	virtual void setPixelAt(int x, int y, unsigned int pixel) = 0;

	/**
	 * Get the URI (if any) used to load this canvas.
	 */
	boost::filesystem::path uri() const;

	/**
	 * Get the width of the canvas.
	 */
	virtual int width() const = 0;

	/**
	 * Heuristic guess as to how much memory this canvas is using in the system.
	 *
	 * Knowing how much memory a resource consumes is useful because we can
	 * notify any GC of scripting SPIIs using this object. That is, if we
	 * load a huge canvas and are using the V8 JavaScript engine, it's useful
	 * to inform V8 that the object holding the canvas represents a large
	 * amount of memory (since it can't infer this information itself: the
	 * objects are opaque). This way, it can release the object sooner to
	 * keep more memory free in the system.
	 *
	 * This calculation is extremely naive; it is useful as a baseline
	 * estimation. It would be slightly less naive to take the BPP into
	 * account.
	 */
	virtual unsigned int sizeInBytes();

	/**
	 * Helper function to prevent canvas resource mismatches.
	 */
	template<typename T>
	static T *superCast(Canvas *canvas) {

		if (NULL == canvas) {

			throw std::runtime_error(
				"NULL canvas pointer given to cast!"
			);
		}

		T *specializedCanvas = dynamic_cast<T *>(canvas);

		if (!specializedCanvas) {

			throw std::runtime_error(
				"There was a canvas type mismatch!"
			);
		}

		return specializedCanvas;
	}

	/**
	 * Manages the concrete %Canvas factory instance.
	 */
	static FactoryManager<Canvas> factoryManager;

protected:

	void setUri(const boost::filesystem::path &uri);

private:

	boost::filesystem::path m_uri;

};

/**
 * @ingroup Manufacturing
 * @ingroup SPI
 */
template <>
class AbstractFactory<Canvas> {

public:

	virtual ~AbstractFactory<Canvas>() {}

	virtual Canvas *create() = 0;
	virtual Canvas *create(int width, int height) = 0;
	virtual Canvas *create(const boost::filesystem::path &uri) = 0;

};

/**
 * @}
 */

}

#endif // AVOCADO_CANVAS_H
