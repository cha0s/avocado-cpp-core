#ifndef AVOCADO_SPRITE_H
#define AVOCADO_SPRITE_H

#include "core/avocado-global.h"

#include "Canvas.h"
#include "GraphicsService.h"
#include "Window.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @brief The %Sprite SPI handles drawing and pixel manipulation capabilities.
 *
 * The %Sprite SPI is responsible for rendering Image and Canvas objects to
 * Canvas or Window objects.
 *
 * @ingroup Resources
 */
class Sprite {

public:

	Sprite();

	virtual ~Sprite();

	/**
	 * Render to a Canvas.
	 */
	virtual void renderTo(Canvas *destination) const = 0;

	/**
	 * Render to a Window.
	 */
	virtual void renderTo(Window *destination) const = 0;

	/**
	 * Set the alpha blending factor.
	 */
	virtual void setAlpha(double alpha) = 0;

	/**
	 * Set the pixel blending mode used.
	 */
	virtual void setBlendMode(GraphicsService::BlendMode blendMode) = 0;

	/**
	 * Set the position where rendering will take place upon the destination.
	 */
	virtual void setPosition(int x, int y) = 0;

	/**
	 * Set the angle of rotation in degrees.
	 */
	virtual void setRotation(double angle, int orientX, int orientY) = 0;

	/**
	 * Set the scale factor.
	 */
	virtual void setScale(double factorX, double factorY) = 0;

	/**
	 * Set source Canvas.
	 */
	void setSource(Canvas *source);

	/**
	 * Set source Image.
	 */
	void setSource(Image *source);

	/**
	 * Set the source rectangle from which data will be blitted to the
	 * destination.
	 */
	virtual void setSourceRectangle(int x, int y, int w, int h) = 0;

	/**
	 * Helper function to prevent sprite resource mismatches.
	 */
	template<typename T>
	static T *superCast(Sprite *sprite) {

		if (NULL == sprite) {
			throw std::runtime_error(
				"NULL canvas pointer given to cast!"
			);
		}

		T *specializedSprite = dynamic_cast<T *>(sprite);

		if (!specializedSprite) {
			throw std::runtime_error("There was a sprite type mismatch!");
		}

		return specializedSprite;
	}

	/**
	 * Manages the concrete %Sprite factory instance.
	 */
	static FactoryManager<Sprite> factoryManager;

protected:

	Canvas *canvas() const;
	Image *image() const;

private:

	Canvas *_canvas;
	Image *_image;

};

/**
 * @ingroup Manufacturing
 * @ingroup SPI
 */
template <>
class AbstractFactory<Sprite> {

public:

	virtual ~AbstractFactory<Sprite>() {}

	virtual Sprite *create() = 0;

};

/**
 * @}
 */

}

#endif // AVOCADO_SPRITE_H
