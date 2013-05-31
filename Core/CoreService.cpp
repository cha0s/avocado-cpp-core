#include "core/avocado-global.h"

#include "CoreService.h"

namespace avo {

FactoryManager<CoreService> CoreService::factoryManager;

CoreService::~CoreService() {
}

void CoreService::close() {
}

}
