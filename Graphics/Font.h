#ifndef AVOCADO_SFMLFONT_H
#define AVOCADO_SFMLFONT_H

#include "../avocado-global.h"

#include "../FS.h"
#include "../ResourceManager.h"

#include "Canvas.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @brief The %Font SPI handles loading and rendering with fonts.
 *
 * @ingroup Resources
 */
class Font {

public:

	/**
	 * List of font styles.
	 */
	enum FontStyle {

		FontStyle_Default     = 0
		, FontStyle_Bold      = 1
		, FontStyle_Italic    = 2
		, FontStyle_Underline = 4
	};

	/**
	 * NULL Font constructor.
	 */
	Font();

	/**
	 * Build a font from a filename.
	 */
	Font(const boost::filesystem::path &uri);

	virtual ~Font() {}

	/**
	 * Render text at x, y onto a Canvas with the given color and alpha
	 * blending.
	 */
	virtual void render(int x, int y, const std::string &text, Canvas *destination, int r, int g, int b, double a) const = 0;

	/**
	 * Set the font size.
	 */
	virtual void setSize(int size) = 0;

	/**
	 * Set the font style.
	 */
	virtual void setStyle(FontStyle style = FontStyle_Default) = 0;

	/**
	 * Get the height of some text.
	 */
	virtual int textHeight(const std::string &text) = 0;

	/**
	 * Get the height of some text.
	 */
	virtual int textWidth(const std::string &text) = 0;

	/**
	 * Get the size in bytes this font takes up in memory. Default to 4KB.
	 */
	virtual int sizeInBytes();

	/**
	 * Get the URI (if any) used to load this image.
	 */
	boost::filesystem::path uri() const;

	/**
	 * Manages image resources.
	 */
	static ResourceManager<Font> manager;

	/**
	 * Manages the concrete %Font factory instance.
	 */
	static FactoryManager<Font> factoryManager;

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
class AbstractFactory<Font> {

public:

	virtual ~AbstractFactory<Font>() {}

	virtual Font *create() = 0;
	virtual Font *create(const boost::filesystem::path &uri) = 0;

};

/**
 * @}
 */

}

#endif // AVOCADO_SFMLFONT_H
