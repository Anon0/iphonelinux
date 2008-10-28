#ifndef PMU_H
#define PMU_H

#include "openiboot.h"

typedef struct PMURegisterData {
	int bus;
	uint8_t reg;
	uint8_t data;
} PMURegisterData;

int pmu_setup();
int pmu_get_gpmem_reg(int bus, int reg, uint8_t* out);
int pmu_write_reg(int bus, int reg, int data, int verify);
int pmu_write_regs(const PMURegisterData* regs, int num);

#endif