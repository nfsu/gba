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

		//b(0),				TODO: Add support for branchless and print op

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
		b(PL, 4),			//if r6 > 0 ? jump 4 bytes

		ldrPc(r4, 8),		//e = 0xDEADBEEF
		ldrPc(r5, 4),		//f = 0xDEADBEEF
		cmp(r4, r5),		//Test e == f
		b(EQ, 16),			//; Jumps to beyond the dead beefs if equal

		0xDEAD, 0xBEEF, 0xDEAD, 0xBEEF,
		0xDEAD, 0xBEEF, 0xDEAD, 0xBEEF

		//TODO: Write this for every instruction (except main memory access)

	};

	Buffer rom((u8*)instructions, (u8*)instructions + sizeof(instructions));

	gba::Emulator gba = gba::Emulator(arm::Armulator::DebugLevel::MODIFIED, rom);
	gba.wait();

	return 0;
}