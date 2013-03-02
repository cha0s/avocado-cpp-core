#ifndef AVOCADO_GLOBAL_H
#define AVOCADO_GLOBAL_H

#include <map>
#include <stddef.h>
#include <stdexcept>

namespace avo {

/**
 * @addtogroup Global
 * @{
 */

/**
 * Thanks, Vite Falcon @ http://stackoverflow.com/a/1730798 !
 */
template<typename T, typename U>
class addMapValues {
private:
	std::map<T,U>& m_map;
public:
	addMapValues(std::map<T, U>& _map):m_map(_map) {}
	addMapValues& operator()(const T& _key, const U& _val) {
		m_map[_key] = _val;
		return *this;
	}
};

/** Macro to differentiate implementSpi functions for doxygen. */
#ifndef DOXYGEN_IS_RUNNING
#	define AVOCADO_SPI(x, y) avo::x ## Service
#else
#	define AVOCADO_SPI(x, y) avo::y ## x ## Service
#endif

/** Macro to clean up dead code to keep warnings down about intentionally
 *  unused parameters. */
#define AVOCADO_UNUSED(__var) (void)(__var)

/** Stack frame alignment madness for bunk GCC versions on Windows. See
 *  <http://stackoverflow.com/questions/2386408/qt-gcc-sse-and-stack-alignment>.
 */
#if defined(_WIN32)
#	define AVOCADO_ENSURE_STACK_ALIGNED_FOR_SSE __attribute__ ((force_align_arg_pointer))
#else
# 	define AVOCADO_ENSURE_STACK_ALIGNED_FOR_SSE
#endif

/**
 * @}
 */

}

#endif // AVOCADO_GLOBAL_H
