#include "gba/emulator.hpp"
#include "arm/thumb/instructions.hpp"
using namespace arm::thumb;

int main() {

	static const TI instructions[] = {

		add(r0, r0, 5),		//a = 5
		add(r1, 9),			//b = 9

		lsl(r2, r0, 2),		//c = 5 << 2 = 20
		lsr(r3, r1, 3),		//d = 9 >> 3 = 1
		asr(r4, r1, 1),		//e = 9 ASR 1 = 4
		mov(r5, 1),			//f = 1

		add(r4, r3, r2),	//e = 20 + 1 = 21
		sub(r4, r4, r0),	//e = 21 - 5 = 16
		sub(r4, r4, 2),		//e = 16 - 2 = 14
		sub(r3, 12),		//d = 1 - 12 = -11
		asr(r3, r3, 2),		//d = -11 ASR 2 = -3
		asr(r3, r5),		//f = -3 ASR 1 = -2

		mov(r0, 237),		//a = 237
		cmp(r0, 236),		//; sets flags: 237 and 236; >=, >, !=

		//b(-2),			//Goto and operation

		and(r0, r5),		//a = 237 & 1 = 1
		eor(r0, r4),		//a = 1 ^ 14 = 15
		mov(r1, 3),			//b = 3
		lsl(r0, r1),		//a = 15 << 3 = 120
		lsr(r0, r1),		//a = 120 >> 3 = 15
		bic(r0, r5),		//a = 15 & ~1 = 14
		orr(r0, r1),		//a = 14 | 3 = 15
		mvn(r0, r0),		//a = ~15 = -16
		mul(r0, r1),		//a = -16 * 3 = -48
		mov(r7, 48),		//g = 48
		neg(r6, r7),		//g = -48
		cmp(r6, r0),		//g == 48?
		cmn(r6, r0),		//g != 48?
		tst(r6, r1),		//g & 3?
		ror(r6, r1),		//Shift 3 bits right and take 3 bits from back at front
		ror(r6, r1),		//^
		ror(r6, r1),		//^
		b(PL, 2),			//if r6 > 0 ? jump 2 bytes; to DEAD C0DE

		bll(4),				//Jump over DEAD C0DE
		blh(4),

		0xC0DE, 0xDEAD,

		mov(r0, 1),			//Set to 1
		b(EQ, 68),			//Jump that won't be executed
		b(NE, -2),			//Jump that will be executed

		mov(r0, 33),		//Set to 33

		addPc(r0, 8),		//Get pc at ldrPc(r5, 6) instruction
		addSp(r1, 4),		//Get sp+2

		addSp(8),			//Add 5 to sp
		addSp(-8),			//Remove sp again

		addSp(r1, 4),		//Get sp again

		ldrPc(r4, 4),		//e = 0x42AC4D01
		ldrPc(r5, 4),		//f = 0xC0DEDEAD
		cmp(r4, r5),		//Test e == f
		b(EQ, 0),			//Jumps into the dead beefs if equal
		b(NE, 6),			//Jumps to beyond the dead beefs if nequal

		0xC0DE, 0xDEAD,
		0xC0DE, 0xDEAD,

		mov(r2, 123),
		mov(r0, 23),

		nop(),

		//TODO: BX, LDR/STR
		0xC0DE,
		0xDEAD

	};

	Buffer rom((u8*)instructions, (u8*)instructions + sizeof(instructions));

	gba::Emulator gba = gba::Emulator({}, rom);
	rom.clear();

	usz count{};
	while (++count < 64) {

		try {

			//Reset GBA
			gba.r = {};
			gba.r.cpsr.mode(arm::Mode::E::USR);
			gba.r.pc = 0;
			gba.r.pc = gba.memory.getRanges()[7 /* ROM */].start;
			gba.r.cpsr.thumb(true);

			//Run gba
			gba.wait();

		} catch (std::exception) {}

	}

	return 0;
}