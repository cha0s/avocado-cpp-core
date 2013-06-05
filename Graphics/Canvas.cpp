#include "core/avocado-global.h"

#include "Canvas.h"

namespace avo {

FactoryManager<Canvas> Canvas::factoryManager;

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

bool Canvas::isNull() const {
	return width() != 0 && height() != 0;
}

void Canvas::setUri(const boost::filesystem::path &uri) {
	m_uri = uri;
}

boost::filesystem::path Canvas::uri() const {
	return m_uri;
}

unsigned int Canvas::sizeInBytes() {
	return width() * height() * 4;
}

}
