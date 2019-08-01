#pragma once
#include "arm/armulator.hpp"

namespace gba {

	class Emulator : public arm::Armulator {

	public:

		//Max bios size: 32_MiB
		//Max rom size: 96_MiB
		//Extended rom is at 0F000000 -> 7FFF0000 (1807 MiB; 1 GiB + 783 MiB)
		Emulator(const Buffer &bios, const Buffer &rom, const Buffer &erom);
		~Emulator() = default;

		inline void wait() {
			Armulator::wait(ARM7TDMI);
		}

	};

}