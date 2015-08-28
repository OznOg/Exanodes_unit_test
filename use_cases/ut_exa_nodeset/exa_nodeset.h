/* $Id$
 *
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef __EXA_NODESET_H__
#define __EXA_NODESET_H__

#include "exa_constants.h"

/* Bit field for node sets has to be larger than the host bus size.
 * So we use a table of EXA_NODESET_BITS_PER_CELL unsigned ints.
 * The the number of cells needed to hold EXA_MAX_NODES_NUMBER bits is
 * computed as floor (EXA_MAX_NODES_NUMBER / EXA_NODESET_BITS_PER_CELL),
 * and floor(x / y) = ((x - 1) / y) + 1
 */

/** Number of bits in a bitfield cell. We choose 64 bits so we do not need
 *  padding in examsg. */
#define EXA_NODESET_BITS_PER_CELL 64

/** Number of cells in a bitfield */
#define EXA_NODESET_NB_CELLS (((EXA_MAX_NODES_NUMBER - 1) / EXA_NODESET_BITS_PER_CELL) + 1)

/** Numerical id for a node. We choose an int to simplify padding in examsg */
typedef unsigned int exa_nodeid_t;

/** Special node id for localhost */
#define EXA_NODEID_LOCALHOST  (EXA_MAX_NODES_NUMBER + 1)

/** Special node id for 'no node' */
#define EXA_NODEID_NONE  (EXA_MAX_NODES_NUMBER + 5)

/** Check whether a node id is valid */
#define EXA_NODEID_VALID(id)  ((id) >= 0 && (id) < EXA_MAX_NODES_NUMBER)

/** bitfield to store a node set */
typedef struct {
  unsigned long long cells[EXA_NODESET_NB_CELLS];
} exa_nodeset_t;


/** Iterator on a node set */
typedef exa_nodeset_t exa_nodeset_iter_t;


void exa_nodeset_reset(exa_nodeset_t *set);
void exa_nodeset_copy(exa_nodeset_t *to, const exa_nodeset_t *from);
void exa_nodeset_cpu_to_exa(exa_nodeset_t *to, const exa_nodeset_t *from);
void exa_nodeset_exa_to_cpu(exa_nodeset_t *to, const exa_nodeset_t *from);
int  exa_nodeset_is_empty(const exa_nodeset_t *set);
void exa_nodeset_add(exa_nodeset_t *set, exa_nodeid_t node);
void exa_nodeset_del(exa_nodeset_t *set, exa_nodeid_t node);
int  exa_nodeset_contains(const exa_nodeset_t *set, exa_nodeid_t node);
int  exa_nodeset_equals(const exa_nodeset_t *set1, const exa_nodeset_t *set2);
void exa_nodeset_sum(exa_nodeset_t *to, const exa_nodeset_t *from);
void exa_nodeset_substract(exa_nodeset_t *to, const exa_nodeset_t *from);
void exa_nodeset_intersect(exa_nodeset_t *to, const exa_nodeset_t *from);
int  exa_nodeset_count(const exa_nodeset_t *set);
unsigned exa_nodeset_num_bits(const exa_nodeset_t *set);
exa_nodeid_t exa_nodeset_first_at(const exa_nodeset_t *set, exa_nodeid_t node);
exa_nodeid_t exa_nodeset_first(const exa_nodeset_t *set);
void exa_nodeset_iter_init(const exa_nodeset_t *set, exa_nodeset_iter_t *iter);
int  exa_nodeset_iter(exa_nodeset_iter_t *iter, exa_nodeid_t *node);
void exa_nodeset_from_hex(exa_nodeset_t *set, const char *hex);
void exa_nodeset_to_hex(const exa_nodeset_t *set, char *hex);
void exa_nodeset_to_bin(const exa_nodeset_t *set, char *bin);

/* Build a set containing a single specified node.
   If the node is localhost, builds an empty set */
#define exa_nodeset_single(set, node)		\
  do {						\
    exa_nodeset_reset(set);			\
    if ((node) != EXA_NODEID_LOCALHOST)		\
      exa_nodeset_add((set), (node));		\
  } while (0)

/**
 * A simple iterator. You can use it like a for loop.
 *
 * Usage:
 *   exa_nodeid_t node;
 *   exa_nodeset_foreach(set, node)
 *   {
 *     foo(node);
 *   }
 */
#define exa_nodeset_foreach(set, node)           \
  for(node = exa_nodeset_first_at(set, 0);       \
      node < EXA_MAX_NODES_NUMBER;               \
      node = (node + 1 < EXA_MAX_NODES_NUMBER) ? \
       exa_nodeset_first_at(set, node + 1): node + 1 \
      )


#if EXA_NODESET_NB_CELLS != 2
#error "please fix EXA_NODESET_* below to match EXA_NODESET_NB_CELLS"
#endif

#define EXA_NODESET_CELL_FORMAT "%016llx"
#define EXA_NODESET_FMT EXA_NODESET_CELL_FORMAT EXA_NODESET_CELL_FORMAT
#define EXA_NODESET_VAL(set) (set)->cells[1], (set)->cells[0]
#define EXA_NODESET_EMPTY ((exa_nodeset_t){ .cells = { 0ull, 0ull } })
#define EXA_NODESET_FULL  ((exa_nodeset_t){ .cells = { ~0ull, ~0ull } })
#define EXA_NODESET_HEX_SIZE (EXA_NODESET_NB_CELLS * 16)
#define EXA_NODESET_PROP_EMPTY "00000000000000000000000000000000"

#endif /* __EXA_NODESET_H__ */
