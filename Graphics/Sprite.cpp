#include "../avocado-global.h"

#include "Sprite.h"

namespace avo {

FactoryManager<Sprite> Sprite::factoryManager;

Sprite::Sprite()
	: _canvas(NULL)
	, _image(NULL)
{
}

Sprite::~Sprite() {
}

void Sprite::setSource(Canvas *canvas) {
	_canvas = canvas;
}

void Sprite::setSource(Image *image) {
	_image = image;
}

Canvas *Sprite::canvas() const {
	return _canvas;
}

Image *Sprite::image() const {
	return _image;
}

}
