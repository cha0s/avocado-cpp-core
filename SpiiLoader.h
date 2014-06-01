#ifndef AVOCADO_SPIILOADER_H
#define AVOCADO_SPIILOADER_H

#include "avocado-global.h"

#include <map>

#include <boost/extension/shared_library.hpp>
#include <boost/function.hpp>

#include "FS.h"

namespace avo {

/**
 * @addtogroup SPI
 * @{
 */

typedef std::map<std::string, boost::extensions::shared_library *> LibraryMap;

/**
 * %SpiiLoader handles dynamically loading SPI implementations (SPIIs). By
 * default, SPIIs are located within [EXEPATH]/SPII.
 *
 * SPIIs follow the naming convention:
 *
 *     [SPI_NAME]-[SPI_IMPLEMENTATION].spi
 *
 * For example, by default the v8 ScriptService SPII will be
 * located at [EXEPATH]/SPII/ScriptService-v8.spi.
 */
class SpiiLoader {

public:

	/**
	 * @brief Thrown when loading an SPII fails.
	 */
	class spi_implementation_error : public std::runtime_error {

	public:

		spi_implementation_error(const std::string &text)
			: std::runtime_error("SPII load failure: " + text)
		{
		}

	};

	SpiiLoader()
		: m_libraryMap()
	{
	}

	~SpiiLoader() {

		// Unload any implementation.
		for (LibraryMap::iterator i = m_libraryMap.begin(); i != m_libraryMap.end(); i++) {
			delete i->second;
		}
	}

	/**
	 * This function handles dynamically loading an SPII. It will clean up any
	 * previous SPII (if any), then it'll pass T's factory manager to the
	 * %implementSpi() function located within the SPII.
	 */
	template<typename T>
	void implementSpi(const std::string &implementation, const boost::filesystem::path &path = "") {

		// Only one implementation may be loaded at once. If any previous
		// implementation exists, unload it.
		if (NULL != m_libraryMap[T::name()]) delete m_libraryMap[T::name()];

		// By default, load SPIIs from
		// [EXEPATH]/SPII/[SPI_NAME]-[SPI_IMPLEMENTATION].
		boost::filesystem::path spiPath = path;
		if ("" == spiPath) {
			spiPath = avo::FS::exePath();
		}
		spiPath /= "SPII";
		spiPath /= T::name() + "-" + implementation + ".spii";

		// Load the shared library.
		boost::extensions::shared_library *library;
		library = m_libraryMap[T::name()] = new boost::extensions::shared_library(
			spiPath.string()
		);

		// Try opening it.
		if (!library->open()) {

			throw spi_implementation_error(
				"Couldn't load " + T::name() + "'s " + implementation + " SPII. dlerror() says: " + dlerror()
			);
		}

		// Extract the implementSPI function from within the shared library.
		boost::function<void (FactoryManager<T> &)> implementSpi(
			library->get<void, FactoryManager<T> &>("implementSpi")
		);
		if (!implementSpi) {

			throw spi_implementation_error(
				"Couldn't find implementSpi() within " + T::name() + "'s " + implementation + " SPII. dlerror() says: " + dlerror()
			);
		}

		// Pass the manager to implementSpi().
		implementSpi(T::factoryManager);
	}

private:

	LibraryMap m_libraryMap;

};

/**
 * @}
 */

}

#endif // AVOCADO_SPIILOADER_H
