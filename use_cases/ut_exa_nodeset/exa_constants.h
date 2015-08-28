/* $Id$
 *
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef _FUSION_CONSTANTS_H
#define _FUSION_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define EXA_COPYRIGHT "Copyright (C) 2002-2007 Seanodes <http://www.seanodes.com>"

/*
 * general constants
 * -----------------
 */

#define EXA_MAX_NODES_NUMBER    128

#define EXA_MAXSIZE_BUFFER		1023
#define EXA_MAXSIZE_LINE		1023

/** Boolean */
typedef enum exa_bool
  {
    EXA_FALSE,
    EXA_TRUE
  } exa_bool_t;

#ifndef FALSE
/** Alias */
# define FALSE  EXA_FALSE
#endif

#ifndef TRUE
/** Alias */
# define TRUE   EXA_TRUE
#endif

/* WARNING: constants below are used in many places in the code and
 * especially in superblocks. In order to have 64 bit aligned buffers,
 * please make sure the value you set is of the form: A = (8 * B) -1 where B
 * is an integer.
 */

/** Max length of the string representation of an uint64_t \b without the
 * trailing '\\0'
 * stands for log10(UINT_LEAST64_MAX), this means that it is the good value
 * only for base 10 representation */
#define EXA_MAXSIZE_UINT64	20

/** Max node name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NODENAME	63
#if (EXA_MAXSIZE_NODENAME+1) & 0x7
# error "EXA_MAXSIZE_NODENAME+1 is not a multiple of 8 bytes"
#endif

/** Max host name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_HOSTNAME	63
#if (EXA_MAXSIZE_HOSTNAME+1) & 0x7
# error "EXA_MAXSIZE_HOSTNAME+1 is not a multiple of 8 bytes"
#endif

/** Max host list length \b without the trailing '\\0' */
#define EXA_MAXSIZE_HOSTSLIST (EXA_MAX_NODES_NUMBER * (EXA_MAXSIZE_HOSTNAME + 1) - 1) /* NOT_IN_PERL */

/** Max cluster name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_CLUSTERNAME	15
#if (EXA_MAXSIZE_CLUSTERNAME+1) & 0x7
# error "EXA_MAXSIZE_CLUSTERNAME+1 is not a multiple of 8 bytes"
#endif

/** Max group name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_GROUPNAME	15
#if (EXA_MAXSIZE_GROUPNAME+1) & 0x7
# error "EXA_MAXSIZE_GROUPNAME+1 is not a multiple of 8 bytes"
#endif

/** Max network card name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NICNAME		15
#if (EXA_MAXSIZE_NICNAME+1) & 0x7
# error "EXA_MAXSIZE_NICNAME+1 is not a multiple of 8 bytes"
#endif

/** Max network type name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NETTYPE		15
#if (EXA_MAXSIZE_NETTYPE+1) & 0x7
# error "EXA_MAXSIZE_NETTYPE+1 is not a multiple of 8 bytes"
#endif

/** Max network card ident (eg. eth0) length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NICIDENT	15
#if (EXA_MAXSIZE_NICIDENT+1) & 0x7
# error "EXA_MAXSIZE_NICIDENT+1 is not a multiple of 8 bytes"
#endif

/** Max network card ip adress length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NICADDRESS	15
#if (EXA_MAXSIZE_NICADDRESS+1) & 0x7
# error "EXA_MAXSIZE_NICADDRESS+1 is not a multiple of 8 bytes"
#endif

/** Max network name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_NETNAME		15
#if (EXA_MAXSIZE_NETNAME+1) & 0x7
# error "EXA_MAXSIZE_NETNAME+1 is not a multiple of 8 bytes"
#endif

/** Max volume name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_VOLUMENAME	15
#if (EXA_MAXSIZE_VOLUMENAME+1) & 0x7
# error "EXA_MAXSIZE_VOLUMENAME+1 is not a multiple of 8 bytes"
#endif

/** Max snapshot name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_SNAPSHOTNAME	15
#if (EXA_MAXSIZE_SNAPSHOTNAME+1) & 0x7
# error "EXA_MAXSIZE_SNAPSHOTNAME+1 is not a multiple of 8 bytes"
#endif

/** Max layout name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_LAYOUTNAME	15
#if (EXA_MAXSIZE_LAYOUTNAME+1) & 0x7
# error "EXA_MAXSIZE_LAYOUTNAME+1 is not a multiple of 8 bytes"
#endif

/** Max device name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_DISKNAME	15
#if (EXA_MAXSIZE_DISKNAME+1) & 0x7
# error "EXA_MAXSIZE_DISKNAME+1 is not a multiple of 8 bytes"
#endif

/** Max disk path length (/dev/sda/) \b without the trailing '\\0' */
#define EXA_MAXSIZE_DISKPATH	63
#if (EXA_MAXSIZE_DISKPATH+1) & 0x7
# error "EXA_MAXSIZE_DISKPATH+1 is not a multiple of 8 bytes"
#endif

/** Max path length (/mnt/gfs/) \b without the trailing '\\0' */
#define EXA_MAXSIZE_PATH		63
#if (EXA_MAXSIZE_PATH+1) & 0x7
# error "EXA_MAXSIZE_PATH+1 is not a multiple of 8 bytes"
#endif

/** Max filesystem type length \b without the trailing '\\0' */
#define EXA_MAXSIZE_FSTYPE	15
#if (EXA_MAXSIZE_FSTYPE+1) & 0x7
# error "EXA_MAXSIZE_FSTYPE+1 is not a multiple of 8 bytes"
#endif

/** Max filesystem name length (fs) \b without the trailing '\\0' */
#define EXA_MAXSIZE_FSNAME	15
#if (EXA_MAXSIZE_FSNAME+1) & 0x7
# error "EXA_MAXSIZE_FSNAME+1 is not a multiple of 8 bytes"
#endif

/** Max GFS lock protocol name length (lock_gulm/lock_dlm) \b without the trailing '\\0' */
#define EXA_MAXSIZE_GFS_LOCK_PROTO	15
#if (EXA_MAXSIZE_GFS_LOCK_PROTO+1) & 0x7
# error "EXA_MAXSIZE_GFS_LOCK_PROTO+1 is not a multiple of 8 bytes"
#endif

/** Max option string length () \b without the trailing '\\0' */
#define EXA_MAXSIZE_MOUNT_OPTION	31
#if (EXA_MAXSIZE_GFS_LOCK_PROTO+1) & 0x7
# error "EXA_MAXSIZE_GFS_LOCK_PROTO+1 is not a multiple of 8 bytes"
#endif

/** Max filesystem check parameters length \b without the trailing '\\0' */
#define EXA_MAXSIZE_FSCHECK_PARAMETER	63
#if (EXA_MAXSIZE_FSCHECK_PARAMETER+1) & 0x7
# error "EXA_MAXSIZE_FSCHECK_PARAMETER+1 is not a multiple of 8 bytes"
#endif

/** Max device path name length (/dev/xxx) or (/mnt/ext3) \b without the trailing '\\0' */
#define EXA_MAXSIZE_DEVPATH		127
#if (EXA_MAXSIZE_DEVPATH+1) & 0x7
# error "EXA_MAXSIZE_DEVPATH+1 is not a multiple of 8 bytes"
#endif

/** Max service name length \b without the trailing '\\0' */
#define EXA_MAXSIZE_SERVICENAME		15
#if (EXA_MAXSIZE_SERVICENAME+1) & 0x7
# error "EXA_MAXSIZE_SERVICENAME+1 is not a multiple of 8 bytes"
#endif

/* Max regular expansion possible. if using many nodes with very different
 * names, it may be impossible to handle the list as a small regexp
 */
#define EXA_MAXSIZE_REGEXP	511
#if (EXA_MAXSIZE_REGEXP+1) & 0x7
# error "EXA_MAXSIZE_REGEXP+1 is not a multiple of 8 bytes"
#endif
#if (EXA_MAXSIZE_REGEXP) < (EXA_MAXSIZE_HOSTNAME)
# error "EXA_MAXSIZE_REGEXP is probably too small compared to EXA_MAXSIZE_HOSTNAME"
#endif

#define SECTOR_SIZE		512

/* --- Admind constants ------------------------------------------- */

/** Maximum number of network cards handled for each node */
#define NBMAX_NICS_PER_NODE      4

/** Maximum number of parameters */
#define NBMAX_PARAMS 32

#define RUNNING_DIR		"/tmp"

#define ADMIND_THREAD_STACK_SIZE	300000				//!< The size of the stack to pre-initialize.
									//!< To be use with exa_init_stack()

#define ADMIND_PROCESS_NICE	-11					//!< Admind will set its nice value to this.
									//!< Since all daemon are started from admind,
									//!< they will also inherit this value.

#define ADMIND_PROP_OK		"OK"
#define ADMIND_PROP_NOK		"NOK"
#define ADMIND_PROP_STARTED	"STARTED"
#define ADMIND_PROP_STOPPED	"STOPPED"
#define ADMIND_PROP_UP		"UP"
#define ADMIND_PROP_DOWN	"DOWN"
#define ADMIND_PROP_BROKEN	"BROKEN"
#define ADMIND_PROP_DEGRADED	"DEGRADED"
#define ADMIND_PROP_OFFLINE	"OFFLINE"
#define ADMIND_PROP_REBUILDING	"REBUILDING"
#define ADMIND_PROP_UPDATING	"UPDATING"
#define ADMIND_PROP_REPLICATING	"REPLICATING"
#define ADMIND_PROP_USINGSPARE	"USING SPARE"
#define ADMIND_PROP_OUTDATED	"OUT-DATED"
#define ADMIND_PROP_VIRGIN	"VIRGIN"
#define ADMIND_PROP_ALIEN	"ALIEN"
#define ADMIND_PROP_BUSY	"BUSY"
#define ADMIND_PROP_FREE	"FREE"
#define ADMIND_PROP_INUSE	"IN USE"
#define ADMIND_PROP_UNDEFINED	"UNDEFINED"
#define ADMIND_PROP_PRIVATE	"PRIVATE"
#define ADMIND_PROP_SHARED	"SHARED"
#define ADMIND_PROP_TRUE	"TRUE"
#define ADMIND_PROP_FALSE	"FALSE"

/* These constants are related to metadata-recovery */
#define ADMIND_PROP_INPROGRESS  "INPROGRESS" /**< Mark a transaction as "inprogress" */
#define ADMIND_PROP_COMMITTED   "COMMITTED"  /**< Mark a transaction as "committed" */

#define EXA_PARAM_DEFAULT       "default"

/* CONFIG FILE */

#define EXA_CONF_NODE_RELEASE	"2"					//!< The release of the configuration file on the nodes
									//!< It must be changed whenever the format of the file changes
									//!< and is no more compatible with a previous version.

#define EXA_CONF_DIR           "/var/cache/exanodes"                 //!< Where is saved the admind internal state config file
#define ADMIND_CONF_EXANODES_FILE "exanodes.conf"                       //!< Where is saved the admind internal state config file

#define EXA_CONF_CACHE_DIR	"/var/cache/exanodes"			//!< Where are the exanodes CLI cache files saved
									//!< Do not use a variable here for the perl convertion script to work

#define EXA_CONF_CACHE_NODE_EXT	".nodes"				//!< File extension for cluster node cache files

#define EXA_CONF_COMMAND_LOG_DIR ".exanodes"				//!< The UI/CLI save the commands send in this dir under $HOME/
#define EXA_CONF_COMMAND_LOG_EXT ".log"					//!< The UI/CLI save the commands send in this file under EXA_CONF_COMMAND_LOG_DIR
#define EXA_CONF_COMMAND_LOG_FILE_MAXSIZE 5000000			//!< The max size in byte for the UI/CLI command log before a log rotate

/* --- NBD constants ---------------------------------------------- */

/** The TCP port used by the Ethernet plugin of the NBD */
#define SERVERD_DATA_PORT	30796

/** Maximum global number of disks handled by the NBD */
#define NBMAX_DISKS		512

/** Maximum number of locked zone at same time on one disk by serverd */
#define NBMAX_DISK_LOCKED_ZONES 32

/** Number of sector reserverd at beginning of a device,
 * this number is a number of sectors, the size of one sector is 512 bytes
 * so 4096 sectors == 2MiB
 * see bug #1804 for more info */
#define RDEV_RESERVED_AREA_IN_SECTOR 4096

/* Serverd constants */

#define NBD_THREAD_STACK_SIZE	40960

/* --- VRT constants ---------------------------------------------- */

/** Maximum number of real devices that the virtualizer can handle. */
#define NBMAX_DISKS_PER_GROUP	512

/** Maximum number of physical disks handled for each node */
#define NBMAX_DISKS_PER_NODE     16

/** Maximum number of volumes per group that the virtualizer can
    handle. */
#define NBMAX_VOLUMES_PER_GROUP	256

/** Maximum number of groups that the virtualizer can handle. */
#define NBMAX_GROUPS	128

/** Maximum number of started volumes. With 2.4 kernels, it cannot
    easily be increased above 256. */
#define NBMAX_STARTED_VOLUMES 256

/** Maximum number of started snapshots. With 2.4 kernels, it cannot
    easily be increased above 256. */
#define NBMAX_STARTED_SNAPSHOTS 256

/** Maximum number of snapshots per volume */
#define NBMAX_SNAPSHOTS 8

/** Maximum number of spare stripes */
#define NBMAX_SPARES_PER_GROUP 16

#define SSTRIPING_NAME	"sstriping"	//!< name of the layout SSTRIPING
#define RAIN1_NAME	"rain1"		//!< name of the layout RAIN1
#define RAINX_NAME	"rainX"		//!< name for layout RAINS


/** A comma separated list of Layouts supported by Exanodes
 *  It's used by admin command to validate the user configuration file.
 */
#define EXA_LAYOUT_TYPES	SSTRIPING_NAME "," RAIN1_NAME "," RAINX_NAME /* NOT_IN_PERL */

/** A comma separated list of Access modes supported by Exanodes
 *  It's used by admin command to validate the user configuration file.
 */
#define EXA_PRIVATE_MODE        "private"
#define EXA_SHARED_MODE         "shared"
#define EXA_ACCESSMODE_TYPES	EXA_PRIVATE_MODE "," EXA_SHARED_MODE /* NOT_IN_PERL */

#define VRT_DEFAULT_SLOT_SIZE       (128 << 10) /* 128 MB   NOT_IN_PERL */
#define VRT_DEFAULT_SU_SIZE                512  /* 512 kB   NOT_IN_PERL */
#define VRT_DEFAULT_DIRTY_ZONE_SIZE ( 32 << 10) /*  32 MB   NOT_IN_PERL */
#define VRT_DEFAULT_READAHEAD       (  1 << 10) /*   1 MB   NOT_IN_PERL */
#define VRT_DEFAULT_NB_SPARES                0  /*          NOT_IN_PERL */

#define VRT_MIN_SLOT_SIZE           (  1 << 10) /*   1 MB   NOT_IN_PERL */
#define VRT_MIN_DIRTY_ZONE_SIZE     (  1 << 10) /*   1 MB   NOT_IN_PERL */

/* --- FS constants -------------------------------------------------- */

#define FS_MINIMUM_EXT3_SIZE (8*1024)
#define GFS_SIZE_STRING_CLUSTER_FS_ID (8)

  /* mount status constants. Unmounted needs be 0 */
typedef enum exa_fs_mounted_status
  {
    EXA_FS_UNMOUNTED=0,
    EXA_FS_MOUNTED_RW,
    EXA_FS_MOUNTED_RO
  } exa_fs_mounted_status_t;

  /* Compatibility number with GFS. */
  /* It must be the same in GFS, in cluster/gulm/src/config_gulm.h */
#define EXANODES_GFS_COMPATIBILITY_NUMBER 3
#define EXA_SHARED_MEM_FILE_PATH	"/var/cache/exanodes/fs_shm_key"
#define EXA_FS_MOUNT_OPTION_ACCEPTED_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,="

#ifdef __cplusplus
}
#endif

#endif
