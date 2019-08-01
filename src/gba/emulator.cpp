#include "gba/emulator.hpp"
#include "system/local_file_system.hpp"
using namespace gba;

Emulator::Emulator(const Buffer &bios, const Buffer &rom, const Buffer &erom):
	Armulator({
		{ 0x00000000_u32, u32(bios.size()),	false, "BIOS", "Basic I/O system", bios },
		{ 0x02000000_u32, u32(256_KiB),		true,  "WRAM", "Work memory (on board)", {} },
		{ 0x03000000_u32, u32(32_KiB),		true,  "IRAM", "Work memory (in chip)", {}  },
		{ 0x04000000_u32, u32(0x3FF),		true,  "I/O", "Input/Output registers", {} },
		{ 0x05000000_u32, u32(1_KiB),		true,  "BG/OBJ RAM", "Palette memory", {} },
		{ 0x06000000_u32, u32(96_KiB),		true,  "VRAM", "Video memory", {} },
		{ 0x07000000_u32, u32(1_KiB),		true,  "OAM", "OBJ attributes", {} },
		{ 0x08000000_u32, u32(rom.size()),	false, "ROM", "Readonly memory", rom },
		{ 0x0E000000_u32, u32(64_KiB),		true,  "SRAM", "Save memory", {} },
		{ 0x0F000000_u32, u32(erom.size()),	false, "EROM", "Extended readonly memory", erom }
	}) {}
