#pragma once
#include "arm/armulator.hpp"

namespace gba {

	class Emulator : public arm::Armulator {

	public:

		Emulator(const Buffer &rom);

	};

}