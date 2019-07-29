#pragma once
#include "arm/armulator.hpp"

namespace gba {

	class Emulator : public arm::Armulator {

	public:

		Emulator(const Buffer &rom);
		~Emulator() = default;

		inline void wait() {
			Armulator::wait(ARM7TDMI);
		}

	};

}