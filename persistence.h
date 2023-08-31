#pragma once
#include <stdint.h>
#include "riscv.h"

// set value to 0 in deser first to deal with variable sized fields

#define SER(value, N)					\
  do {							\
      uint8_t *obuf = *obufp;				\
      uint8_t *v = (uint8_t*)&(value);			\
      for (int i=0; i < (N); i++)			\
	  *obuf++ = v[i];				\
      *obufp+=(N);					\
  } while(0);						\

#define DESER(value, N)					\
  do {							\
      (value)=0;					\
      uint8_t *ibuf = *ibufp;				\
      uint8_t *v = (uint8_t*)(&(value));		\
      for (int i=0; i < (N); i++)			\
	  v[i] = *ibuf++;				\
      *ibufp+=(N);					\
  } while(0);						\

#define SER8(value) SER(value, 1)
#define SER32(value) SER(value, 4)
#define DESER8(value) DESER(value, 1)
#define DESER32(value) DESER(value, 4)

extern void save_cpu(const vm_t *vm,
		     uint8_t **obufp);

extern void save_plic(const vm_t *vm,
		     uint8_t **obufp);

extern void save_uart(const vm_t *vm,
		     uint8_t **obufp);

extern void save_all(const vm_t *vm, uint8_t **obufp);

extern void load_cpu(vm_t *vm,
		     uint8_t **ibufp);

extern void load_plic(vm_t *vm,
		     uint8_t **ibufp);

extern void load_uart(vm_t *vm,
		     uint8_t **ibufp);

extern bool load_all(vm_t *vm, uint8_t **ibufp);

#define PERSISTENCE_BASEADR 0xfff000
