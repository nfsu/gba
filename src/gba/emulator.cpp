#include "gba/emulator.hpp"
#include "system/local_file_system.hpp"
using namespace gba;

Emulator::Emulator(DebugLevel level, const Buffer &rom): 
	Armulator(
	{
		{ 0x00000000_u32, u32(16_KiB),	arm::AccessFlag::READ_ONLY, "BIOS", "Basic I/O system" },
		{ 0x02000000_u32, u32(256_KiB), arm::AccessFlag::READ_WRITE, "WRAM", "Work memory (on board)" },
		{ 0x03000000_u32, u32(32_KiB),	arm::AccessFlag::READ_WRITE, "IRAM", "Work memory (in chip)"  },
		{ 0x04000000_u32, u32(0x3FF),	arm::AccessFlag::READ_WRITE, "I/O", "Input/Output registers" },
		{ 0x05000000_u32, u32(1_KiB),	arm::AccessFlag::READ_WRITE, "BG/OBJ RAM", "Palette memory" },
		{ 0x06000000_u32, u32(96_KiB),	arm::AccessFlag::READ_WRITE, "VRAM", "Video memory" },
		{ 0x07000000_u32, u32(1_KiB),	arm::AccessFlag::READ_WRITE, "OAM", "OBJ attributes" },
		{ 0x08000000_u32, u32(32_MiB),	arm::AccessFlag::READ_ONLY, "ROM", "Readonly memory" },
		{ 0x0E000000_u32, u32(64_KiB),	arm::AccessFlag::READ_WRITE, "SRAM", "Save memory" }

	}, level, 0) {

	Buffer bios;

	if(!oic::System::files()->read(oic::System::files()->get("./gba_bios.bin"), bios))
		oic::System::log()->fatal("Please download the gba bios");

	const arm::Memory32::Range	&biosRange = getMemory().getRange("BIOS"),
								&romRange = getMemory().getRange("ROM");

	if (bios.size() > biosRange.size)
		oic::System::log()->fatal("Invalid bios");

	if (rom.size() > romRange.size)
		oic::System::log()->fatal("Invalid rom size");

	memcpy(biosRange.location, bios.data(), bios.size());	//Place bios at 0

	if (bios.size() == 0)
		getRegisters().pc = romRange.start | 1 /* TODO: Temporarily only use ROM in thumb mode */;

}
