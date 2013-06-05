#ifndef AVOCADO_IMAGE_H
#define AVOCADO_IMAGE_H

#include "core/avocado-global.h"

#include "core/FS.h"
#include "core/ResourceManager.h"

#include "Canvas.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @brief The %Image SPI handles everything related to images.
 *
 * The %Image SPI is responsible for constructing, destroying, rendering and
 * various primitive drawing operations that can take place on an image.
 *
 * @ingroup Resources
 */
class Image {

public:

	/**
	 * NULL Image constructor.
	 */
	Image();

	/**
	 * Build an image from a filename.
	 */
	Image(const boost::filesystem::path &uri);

	virtual ~Image() {}

	/**
	 * Get the height of the image.
	 */
	virtual int height() const = 0;

	/**
	 * Check whether the Image is NULL. Any 0-length axis is the most abstract
	 * way to determine NULL status.
	 */
	virtual bool isNull() const;

	/**
	 * Get the URI (if any) used to load this image.
	 */
	boost::filesystem::path uri() const;

	/**
	 * Get the width of the image.
	 */
	virtual int width() const = 0;

	/**
	 * Heuristic guess as to how much memory this image is using in the system.
	 *
	 * Knowing how much memory a resource consumes is useful because we can
	 * notify any GC of scripting SPIIs using this object. That is, if we
	 * load a huge image and are using the V8 JavaScript engine, it's useful
	 * to inform V8 that the object holding the image represents a large
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
	 * Helper function to prevent image resource mismatches.
	 */
	template<typename T>
	static T *superCast(Image *image) {

		if (NULL == image) {

			throw std::runtime_error(
				"NULL image pointer given to cast!"
			);
		}

		T *specializedImage = dynamic_cast<T *>(image);

		if (!specializedImage) {

			throw std::runtime_error(
				"There was an image type mismatch!"
			);
		}

		return specializedImage;
	}

	/**
	 * Manages image resources.
	 */
	static ResourceManager<Image> manager;

	/**
	 * Manages the concrete %Image factory instance.
	 */
	static FactoryManager<Image> factoryManager;

protected:

	void setUri(const boost::filesystem::path &uri);

private:

	boost::filesystem::path m_uri;

};

/**
 * @ingroup Manufacturing
 * @ingroup Resources
 * @ingroup SPI
 */
template <>
class AbstractFactory<Image> {

public:

	virtual ~AbstractFactory<Image>() {}

	virtual Image *create() = 0;
	virtual Image *create(const boost::filesystem::path &uri) = 0;

};

/**
 * @}
 */

}

#endif // AVOCADO_IMAGE_H
