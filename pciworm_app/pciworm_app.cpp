
#include "stdafx.h"
#include "pciworm_if.h"


int __cdecl
main(
	_In_ int argc,
	_In_reads_(argc) char* argv[]
)
{
	pciworm_if pcie;
	ULONG64 data = 0;
	int i;
	pcie.open();

	pcie.fpgaRead64(0x0, &data);
	printf("\nFPGA Version Register: 0x%016llX (BAR0:0x0)\n", data);
	pcie.fpgaWrite64(0x8, 0x0);
	pcie.fpgaRead64(0x8, &data);
	printf("Read FPGA Scratch: 0x%016llX (BAR0:0x8)\n", data);
	printf("Writing FPGA Scratch (0xa5a5...)\n", data);
	pcie.fpgaWrite64(0x8, 0xa5a5a5a5a5a5a5a5);
	pcie.fpgaRead64(0x8, &data);
	printf("Read FPGA Scratch: 0x%016llX (BAR0:0x8)\n", data);
	for (i = 0; i < 0x51; i = i + 8) {
		pcie.fpgaRead64(i, &data);
		printf("(FPGA BAR0:0x%04X) 0x%016llX \n", i, data);
	}
	printf("\nReading Physical Memory via FPGA...\n");
	for (i = 0; i < 0x51; i = i + 8) {
		pcie.memRead64(i, &data);
		printf("(PMEM 0x%04X) 0x%016llX \n", i, data);
	}
	printf("\n");
	pcie.close();
	return 0;
}