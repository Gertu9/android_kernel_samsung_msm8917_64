#ifndef LINUX_MMC_IOCTL_H
#define LINUX_MMC_IOCTL_H

#include <linux/types.h>

struct mmc_ioc_cmd {
	/* Implies direction of data.  true = write, false = read */
	int write_flag;

	/* Application-specific command.  true = precede with CMD55 */
	int is_acmd;

	__u32 opcode;
	__u32 arg;
	__u32 response[4];  /* CMD response */
	unsigned int flags;
	unsigned int blksz;
	unsigned int blocks;

	/*
	 * Sleep at least postsleep_min_us useconds, and at most
	 * postsleep_max_us useconds *after* issuing command.  Needed for
	 * some read commands for which cards have no other way of indicating
	 * they're ready for the next command (i.e. there is no equivalent of
	 * a "busy" indicator for read operations).
	 */
	unsigned int postsleep_min_us;
	unsigned int postsleep_max_us;

	/*
	 * Override driver-computed timeouts.  Note the difference in units!
	 */
	unsigned int data_timeout_ns;
	unsigned int cmd_timeout_ms;

	/*
	 * For 64-bit machines, the next member, ``__u64 data_ptr``, wants to
	 * be 8-byte aligned.  Make sure this struct is the same size when
	 * built for 32-bit.
	 */
	__u32 __pad;

	/* DAT buffer */
	__u64 data_ptr;
};
#define mmc_ioc_cmd_set_data(ic, ptr) ic.data_ptr = (__u64)(unsigned long) ptr

/**
 * struct mmc_ioc_multi_cmd - multi command information
 * @num_of_cmds: Number of commands to send. Must be equal to or less than
 *	MMC_IOC_MAX_CMDS.
 * @cmds: Array of commands with length equal to 'num_of_cmds'
 */
struct mmc_ioc_multi_cmd {
	__u64 num_of_cmds;
	struct mmc_ioc_cmd cmds[0];
};

#define MMC_IOC_CMD _IOWR(MMC_BLOCK_MAJOR, 0, struct mmc_ioc_cmd)
<<<<<<< HEAD
#define MMC_IOC_BUSWIDTH _IO(MMC_BLOCK_MAJOR, 0xCB)
#define MMC_IOC_CLOCK _IO(MMC_BLOCK_MAJOR, 0xCC)
=======
>>>>>>> f89f092a37445f02bad1cd3d01e8412588a548f5
/*
 * MMC_IOC_MULTI_CMD: Used to send an array of MMC commands described by
 *	the structure mmc_ioc_multi_cmd. The MMC driver will issue all
 *	commands in array in sequence to card.
 */
#define MMC_IOC_MULTI_CMD _IOWR(MMC_BLOCK_MAJOR, 1, struct mmc_ioc_multi_cmd)
<<<<<<< HEAD

=======
>>>>>>> f89f092a37445f02bad1cd3d01e8412588a548f5

/**
 * There are four request types that are applicable for rpmb accesses- two
 * under read category and two under write. They are
 *
 *  Reads
 *  -------
 *  1. Read Write Counter
 *  2. Authenticated data read
 *
 *
 *  Writes
 *  -------
 *  1. Provision RPMB key (though it might be done in a secure environment)
 *  2. Authenticated data write
 *
 *  While its given that the rpmb data frames are going to have that
 *  information encoded in it and the frames should be generated by a secure
 *  piece of code, the request types can be classified as above.
 *
 *  So here are the set of commands that should be executed atomically in the
 *  ioctl for rpmb read operation
 *  1. Switch partition
 *  2. Set block count
 *  3. Write data frame - CMD25 to write the rpmb data frame
 *  4. Set block count
 *  5. Read the data - CMD18 to do the actual read
 *
 *  Similarly for rpmb write operation, these are the commands that should be
 *  executed atomically in the ioctl for rpmb write operation
 *  1. Switch partition
 *  2. Set block count
 *  3. Write data frame - CMD25 to write the rpmb data frame with data
 *  4. Set block count
 *  5. Read the data - CMD25 to write rpmb data frame indicating that rpmb
 *     result register is about to be read
 *  6. Set block count
 *  7. Read rpmb result - CMD18 to read the rpmb result register
 *
 * Each of the above commands should be sent individually via struct mmc_ioc_cmd
 * and fields like is_acmd that are not needed for rpmb operations will be
 * ignored.
 */
#define MMC_IOC_MAX_RPMB_CMD	3
struct mmc_ioc_rpmb {
	struct mmc_ioc_cmd cmds[MMC_IOC_MAX_RPMB_CMD];
};

/*
 * This ioctl is meant for use with rpmb partitions. This is needed since the
 * access procedure for this particular partition is different from regular
 * or normal partitions.
 */
#define MMC_IOC_RPMB_CMD _IOWR(MMC_BLOCK_MAJOR, 0, struct mmc_ioc_rpmb)

/*
 * Since this ioctl is only meant to enhance (and not replace) normal access
 * to the mmc bus device, an upper data transfer limit of MMC_IOC_MAX_BYTES
 * is enforced per ioctl call.  For larger data transfers, use the normal
 * block device operations.
 */
<<<<<<< HEAD

#define MMC_IOC_MAX_BYTES  (512L * 512 * 2)
#define MMC_IOC_MAX_CMDS    255

=======
#define MMC_IOC_MAX_BYTES  (512L * 256)
#define MMC_IOC_MAX_CMDS    255
>>>>>>> f89f092a37445f02bad1cd3d01e8412588a548f5
#endif /* LINUX_MMC_IOCTL_H */
