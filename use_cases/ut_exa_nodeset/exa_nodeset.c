/* $Id$
 *
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */


#ifdef __KERNEL__

#include <linux/kernel.h>
#include <linux/module.h>

#include "exa_kernel.h"

#else

#include <stdio.h>
#include "common.h"

#endif

#include "exa_byteorder.h"
#include "exa_constants.h"
#include "exa_nodeset.h"

static const exa_nodeset_t exa_nodeset_empty = EXA_NODESET_EMPTY;

#define CHECK_NODE(node)						\
  EXA_ASSERT_VERBOSE(EXA_NODEID_VALID(node), "invalide node id: %d", node)

/* --- exa_nodeset_reset ------------------------------------------ */

/**
 * Return TRUE if and only if the node set does not contain any node.
 */
void
exa_nodeset_reset(exa_nodeset_t *set)
{
  *set = exa_nodeset_empty;
}


/* --- exa_nodeset_copy ------------------------------------------- */

/**
 * Copy a nodes set to another.
 */
void
exa_nodeset_copy(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  *to = *from;
}

/* --- exa_nodeset_cpu_to_exa ------------------------------------- */

/**
 * Copy a nodes set in order to write it on disk.
 */
void
exa_nodeset_cpu_to_exa(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  int i;
  for (i = 0 ; i < EXA_NODESET_NB_CELLS ; i++)
    to->cells[i] = cpu_to_exa64(from->cells[i]);
}

/* --- exa_nodeset_exa_to_cpu ------------------------------------- */

/**
 * Copy a nodes set in order to read it from disk.
 */
void
exa_nodeset_exa_to_cpu(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  int i;
  for (i = 0 ; i < EXA_NODESET_NB_CELLS ; i++)
    to->cells[i] = exa64_to_cpu(from->cells[i]);
}

/* --- exa_nodeset_is_empty --------------------------------------- */

/**
 * Return TRUE if and only if the node set does not contain any node.
 */
int
exa_nodeset_is_empty(const exa_nodeset_t *set)
{
  int i;
  for (i = 0; i < EXA_NODESET_NB_CELLS; i++)
    if (set->cells[i])
      return FALSE;
  return TRUE;
}


/* --- exa_nodeset_add -------------------------------------------- */

/**
 * Add a node to a set of nodes.
 * Adding localhost is forbidden.
 */
void
exa_nodeset_add(exa_nodeset_t *set, exa_nodeid_t node)
{
  CHECK_NODE(node);
  set->cells[node / EXA_NODESET_BITS_PER_CELL] |=
      1ull << (node % EXA_NODESET_BITS_PER_CELL);
}


/* --- exa_nodeset_del -------------------------------------------- */

/**
 * Remove a node to a set of nodes.
 * Removing localhost is forbidden.
 */
void
exa_nodeset_del(exa_nodeset_t *set, exa_nodeid_t node)
{
  CHECK_NODE(node);
  set->cells[node / EXA_NODESET_BITS_PER_CELL] &=
      ~(1ull << (node % EXA_NODESET_BITS_PER_CELL));
}


/* --- exa_nodeset_contains --------------------------------------- */

/**
 * Return TRUE if and only if a node belongs to the set.
 * Localhost doesn't belong to any set.
 */
int
exa_nodeset_contains(const exa_nodeset_t *set, exa_nodeid_t node)
{
  if (node == EXA_NODEID_NONE || node == EXA_NODEID_LOCALHOST)
    return FALSE;

  CHECK_NODE(node);
  return (set->cells[node / EXA_NODESET_BITS_PER_CELL] &
      1ull << (node % EXA_NODESET_BITS_PER_CELL))
      ?TRUE:FALSE;
}

/* --- exa_nodeset_equals ----------------------------------------- */

/**
 * Return TRUE iff two node sets are equal.
 */
int
exa_nodeset_equals(const exa_nodeset_t *set1, const exa_nodeset_t *set2)
{
  int i;

  for (i = 0; i < EXA_NODESET_NB_CELLS; i++)
    if (set1->cells[i] != set2->cells[i])
      return FALSE;

  return TRUE;
}

/* --- exa_nodeset_sum -------------------------------------------- */

/**
 * Compute the union of two node sets.
 */
void
exa_nodeset_sum(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  int i;
  for (i = 0; i < EXA_NODESET_NB_CELLS; i++)
    to->cells[i] |= from->cells[i];
}


/* --- exa_nodeset_substract -------------------------------------- */

/**
 * Compute the substraction of two node sets.
 */
void
exa_nodeset_substract(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  int i;
  for (i = 0; i < EXA_NODESET_NB_CELLS; i++)
    to->cells[i] &= ~(from->cells[i]);
}


/* --- exa_nodeset_intersect -------------------------------------- */

/**
 * Compute the intersection of two node sets.
 */
void
exa_nodeset_intersect(exa_nodeset_t *to, const exa_nodeset_t *from)
{
  int i;
  for (i = 0; i < EXA_NODESET_NB_CELLS; i++)
    to->cells[i] &= from->cells[i];
}


/* --- exa_nodeset_count ------------------------------------------ */

/**
 * Count the number of nodes belonging to a set.
 */
int
exa_nodeset_count(const exa_nodeset_t *set)
{
  exa_nodeid_t node;
  int count = 0;
  for (node = 0; node < EXA_MAX_NODES_NUMBER; node++)
    if (exa_nodeset_contains(set, node))
      count++;
  return count;
}

/* --- exa_nodeset_num_bits --------------------------------------- */

/**
 * Get the number of significant bits to represent a node set.
 *
 * \param[in] set  Node set
 *
 * \return Number of significant bits
 */
unsigned
exa_nodeset_num_bits(const exa_nodeset_t *set)
{
  exa_nodeset_iter_t iter;
  exa_nodeid_t node_id, max_node_id = 0;

  exa_nodeset_iter_init(set, &iter);
  while (exa_nodeset_iter(&iter, &node_id))
    max_node_id = node_id;

  return max_node_id + 1;
}

/* --- exa_nodeset_first_at --------------------------------------- */

/**
 * Return the smallest id greather or equal to node of the nodes
 * belonging to a set.
 * If the set is empty, it returns EXA_MAX_NODES_NUMBER.
 */
exa_nodeid_t
exa_nodeset_first_at(const exa_nodeset_t *set, exa_nodeid_t node)
{
  CHECK_NODE(node);
  while (node < EXA_MAX_NODES_NUMBER && !exa_nodeset_contains(set, node))
    node++;
  return node;
}


/* --- exa_nodeset_first ------------------------------------------ */

/**
 * Return the smallest id of the nodes belonging to a set.
 * If the set is empty, it returns EXA_MAX_NODES_NUMBER.
 */
exa_nodeid_t
exa_nodeset_first(const exa_nodeset_t *set)
{
  return exa_nodeset_first_at(set, 0);
}


/* --- exa_nodeset_iter_init -------------------------------------- */

/**
 * Initialise an iterator with a node set
 */
void
exa_nodeset_iter_init(const exa_nodeset_t *set, exa_nodeset_iter_t *iter)
{
  exa_nodeset_copy(iter, set);
}


/* --- exa_nodeset_iter ------------------------------------------- */

/**
 * Give the next node in the iterator. Return FALSE when there is
 * no more node to iterate.
 *
 * Usage:
 *   exa_nodeset_iter_t iterator;
 *   exa_nodeid_t node;
 *   exa_nodeset_iter_init(iterator, set);
 *   while(exa_nodeset_iter(iterator, node)
 *   {
 *     foo(node);
 *   }
 */
int
exa_nodeset_iter(exa_nodeset_iter_t *iter, exa_nodeid_t *node)
{
  *node = exa_nodeset_first_at(iter, 0);
  if (*node >= EXA_MAX_NODES_NUMBER)
    return FALSE;
  exa_nodeset_del(iter, *node);
  return TRUE;
}


/* --- exa_nodeset_from_hex --------------------------------------- */

/**
 * Parse an hex string to initialise a node set.
 * The string should be EXA_NODESET_HEX_SIZE.
 */
void
exa_nodeset_from_hex(exa_nodeset_t *set, const char *hex)
{
  int i;
  for (i = EXA_NODESET_NB_CELLS - 1; i >= 0; i--)
  {
    sscanf(hex, EXA_NODESET_CELL_FORMAT, &set->cells[i]);
    hex += EXA_NODESET_BITS_PER_CELL / 4;
  }
}


/* --- exa_nodeset_to_hex ----------------------------------------- */

/**
 * Create an hex string representing a node set.
 * The buffer should be EXA_NODESET_HEX_SIZE + 1.
 */
void
exa_nodeset_to_hex(const exa_nodeset_t *set, char *hex)
{
  int i;
  for (i = EXA_NODESET_NB_CELLS - 1; i >= 0; i--)
    hex += sprintf(hex, EXA_NODESET_CELL_FORMAT, set->cells[i]);
}

/**
 * Create a binary string representing a node set.
 *
 * \param[in]  set  Node set to represent
 * \param[out] bin  Binary string
 *
 * String #bin should be at least EXA_MAX_NODES_NUMBER + 1 chars long
 * (including '\0').
 */
void
exa_nodeset_to_bin(const exa_nodeset_t *set, char *bin)
{
  unsigned n;
  exa_nodeid_t node_id;
  int i = 0;

  n = exa_nodeset_num_bits(set);
  if (n > 0)
    {
      node_id = n - 1;
      while (TRUE)
	{
	  bin[i++] = exa_nodeset_contains(set, node_id) ? '1' : '0';
	  if (node_id == 0)
	    break;

	  node_id--;
	}
    }

  bin[i] = '\0';
}

#ifdef __KERNEL__
EXPORT_SYMBOL(exa_nodeset_reset);
EXPORT_SYMBOL(exa_nodeset_copy);
EXPORT_SYMBOL(exa_nodeset_exa_to_cpu);
EXPORT_SYMBOL(exa_nodeset_cpu_to_exa);
EXPORT_SYMBOL(exa_nodeset_is_empty);
EXPORT_SYMBOL(exa_nodeset_add);
EXPORT_SYMBOL(exa_nodeset_del);
EXPORT_SYMBOL(exa_nodeset_contains);
EXPORT_SYMBOL(exa_nodeset_equals);
EXPORT_SYMBOL(exa_nodeset_sum);
EXPORT_SYMBOL(exa_nodeset_substract);
EXPORT_SYMBOL(exa_nodeset_intersect);
EXPORT_SYMBOL(exa_nodeset_count);
EXPORT_SYMBOL(exa_nodeset_first_at);
EXPORT_SYMBOL(exa_nodeset_first);
EXPORT_SYMBOL(exa_nodeset_iter_init);
EXPORT_SYMBOL(exa_nodeset_iter);
EXPORT_SYMBOL(exa_nodeset_from_hex);
EXPORT_SYMBOL(exa_nodeset_to_hex);
#endif
