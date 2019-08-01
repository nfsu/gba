#include "gba/emulator.hpp"
#include "system/local_file_system.hpp"
using namespace gba;

Emulator::Emulator(const Buffer &bios, const Buffer &rom):
	Armulator(
	{
		{ 0x00000000_u32, u32(16_KiB),	false, "BIOS", "Basic I/O system", bios },
		{ 0x02000000_u32, u32(256_KiB), true, "WRAM", "Work memory (on board)", {} },
		{ 0x03000000_u32, u32(32_KiB),	true, "IRAM", "Work memory (in chip)", {}  },
		{ 0x04000000_u32, u32(0x3FF),	true, "I/O", "Input/Output registers", {} },
		{ 0x05000000_u32, u32(1_KiB),	true, "BG/OBJ RAM", "Palette memory", {} },
		{ 0x06000000_u32, u32(96_KiB),	true, "VRAM", "Video memory", {} },
		{ 0x07000000_u32, u32(1_KiB),	true, "OAM", "OBJ attributes", {} },
		{ 0x08000000_u32, u32(rom.size()),	false, "ROM", "Readonly memory", rom },
		{ 0x0E000000_u32, u32(64_KiB),	true, "SRAM", "Save memory", {} }

	}, 0) {

	/* TODO: Temporarily only use ROM in thumb mode */
	if (bios.size() == 0) {
		r.pc = memory.getRanges()[7 /* ROM */].start;
		r.cpsr.thumb(true);
	}

}
