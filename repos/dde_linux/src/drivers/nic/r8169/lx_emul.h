#ifndef _SRC__DRIVERS__NIC__R8169__LX_EMUL_H_
#define _SRC__DRIVERS__NIC__R8169__LX_EMUL_H_

#include <base/fixed_stdint.h>

#include <lx_emul/types.h>
#include <lx_emul/pci.h>
#include <lx_emul/module.h>

enum {
	ETH_HLEN = 14,
	ETH_DATA_LEN = 1500,
};

typedef __u16 __le16;
typedef __u32 __le32;
typedef __u64 __le64;

void msleep(unsigned int);

#endif /* _SRC__DRIVERS__NIC__R8169__LX_EMUL_H_ */
