/* Disassembler interface for targets using CGEN. -*- C -*-
   CGEN: Cpu tools GENerator

THIS FILE IS MACHINE GENERATED WITH CGEN.
- the resultant file is machine generated, cgen-dis.in isn't

Copyright (C) 1996, 1997, 1998, 1999 Free Software Foundation, Inc.

This file is part of the GNU Binutils and GDB, the GNU debugger.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* ??? Eventually more and more of this stuff can go to cpu-independent files.
   Keep that in mind.  */

#include "sysdep.h"
#include <stdio.h>
#include "ansidecl.h"
#include "dis-asm.h"
#include "bfd.h"
#include "symcat.h"
#include "fr30-desc.h"
#include "fr30-opc.h"
#include "opintl.h"

/* Default text to print if an instruction isn't recognized.  */
#define UNKNOWN_INSN_MSG _("*unknown*")

static void print_normal
     PARAMS ((CGEN_CPU_DESC, PTR, long, unsigned int, bfd_vma, int));
static void print_address
     PARAMS ((CGEN_CPU_DESC, PTR, bfd_vma, unsigned int, bfd_vma, int));
static void print_keyword
     PARAMS ((CGEN_CPU_DESC, PTR, CGEN_KEYWORD *, long, unsigned int));
static void print_insn_normal
     PARAMS ((CGEN_CPU_DESC, PTR, const CGEN_INSN *, CGEN_FIELDS *,
	      bfd_vma, int));
static int print_insn PARAMS ((CGEN_CPU_DESC, bfd_vma,
			       disassemble_info *, char *, int));
static int default_print_insn
     PARAMS ((CGEN_CPU_DESC, bfd_vma, disassemble_info *));

/* -- disassembler routines inserted here */

/* -- dis.c */

static void
print_register_list (dis_info, value, offset, load_store)
     PTR dis_info;
     long value;
     long offset;
     int load_store; /* 0 == load, 1 == store */
{
  disassemble_info *info = dis_info;
  int mask;
  int index = 0;
  char* comma = "";

  if (load_store)
    mask = 0x80;
  else
    mask = 1;

  if (value & mask)
    {
      (*info->fprintf_func) (info->stream, "r%i", index + offset);
      comma = ",";
    }
    
  for (index = 1; index <= 7; ++index)
    {
      if (load_store)
	mask >>= 1;
      else
	mask <<= 1;

      if (value & mask)
	{
	  (*info->fprintf_func) (info->stream, "%sr%i", comma, index + offset);
	  comma = ",";
	}
    }
}

static void
print_hi_register_list_ld (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  print_register_list (dis_info, value, 8, 0/*load*/);
}

static void
print_low_register_list_ld (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  print_register_list (dis_info, value, 0, 0/*load*/);
}

static void
print_hi_register_list_st (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  print_register_list (dis_info, value, 8, 1/*store*/);
}

static void
print_low_register_list_st (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  print_register_list (dis_info, value, 0, 1/*store*/);
}

static void
print_m4 (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  disassemble_info *info = (disassemble_info *) dis_info;
  (*info->fprintf_func) (info->stream, "%ld", value);
}
/* -- */

/* Main entry point for printing operands.
   XINFO is a `void *' and not a `disassemble_info *' to not put a requirement
   of dis-asm.h on cgen.h.

   This function is basically just a big switch statement.  Earlier versions
   used tables to look up the function to use, but
   - if the table contains both assembler and disassembler functions then
     the disassembler contains much of the assembler and vice-versa,
   - there's a lot of inlining possibilities as things grow,
   - using a switch statement avoids the function call overhead.

   This function could be moved into `print_insn_normal', but keeping it
   separate makes clear the interface between `print_insn_normal' and each of
   the handlers.
*/

void
fr30_cgen_print_operand (cd, opindex, xinfo, fields, attrs, pc, length)
     CGEN_CPU_DESC cd;
     int opindex;
     PTR xinfo;
     CGEN_FIELDS *fields;
     void const *attrs;
     bfd_vma pc;
     int length;
{
 disassemble_info *info = (disassemble_info *) xinfo;

  switch (opindex)
    {
    case FR30_OPERAND_RI :
      print_keyword (cd, info, & fr30_cgen_opval_h_gr, fields->f_Ri, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_RJ :
      print_keyword (cd, info, & fr30_cgen_opval_h_gr, fields->f_Rj, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_RIC :
      print_keyword (cd, info, & fr30_cgen_opval_h_gr, fields->f_Ric, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_RJC :
      print_keyword (cd, info, & fr30_cgen_opval_h_gr, fields->f_Rjc, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_CRI :
      print_keyword (cd, info, & fr30_cgen_opval_h_cr, fields->f_CRi, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_CRJ :
      print_keyword (cd, info, & fr30_cgen_opval_h_cr, fields->f_CRj, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_RS1 :
      print_keyword (cd, info, & fr30_cgen_opval_h_dr, fields->f_Rs1, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_RS2 :
      print_keyword (cd, info, & fr30_cgen_opval_h_dr, fields->f_Rs2, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)));
      break;
    case FR30_OPERAND_R13 :
      print_keyword (cd, info, & fr30_cgen_opval_h_r13, fields->f_nil, 0);
      break;
    case FR30_OPERAND_R14 :
      print_keyword (cd, info, & fr30_cgen_opval_h_r14, fields->f_nil, 0);
      break;
    case FR30_OPERAND_R15 :
      print_keyword (cd, info, & fr30_cgen_opval_h_r15, fields->f_nil, 0);
      break;
    case FR30_OPERAND_PS :
      print_keyword (cd, info, & fr30_cgen_opval_h_ps, fields->f_nil, 0);
      break;
    case FR30_OPERAND_U4 :
      print_normal (cd, info, fields->f_u4, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_U4C :
      print_normal (cd, info, fields->f_u4c, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_U8 :
      print_normal (cd, info, fields->f_u8, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_I8 :
      print_normal (cd, info, fields->f_i8, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_UDISP6 :
      print_normal (cd, info, fields->f_udisp6, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DISP8 :
      print_normal (cd, info, fields->f_disp8, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DISP9 :
      print_normal (cd, info, fields->f_disp9, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DISP10 :
      print_normal (cd, info, fields->f_disp10, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_S10 :
      print_normal (cd, info, fields->f_s10, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_U10 :
      print_normal (cd, info, fields->f_u10, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_I32 :
      print_normal (cd, info, fields->f_i32, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_SIGN_OPT-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_M4 :
      print_m4 (cd, info, fields->f_m4, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_I20 :
      print_normal (cd, info, fields->f_i20, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_VIRTUAL-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DIR8 :
      print_normal (cd, info, fields->f_dir8, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DIR9 :
      print_normal (cd, info, fields->f_dir9, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_DIR10 :
      print_normal (cd, info, fields->f_dir10, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_LABEL9 :
      print_address (cd, info, fields->f_rel9, 0|(1<<(CGEN_OPERAND_PCREL_ADDR-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_LABEL12 :
      print_address (cd, info, fields->f_rel12, 0|(1<<(CGEN_OPERAND_PCREL_ADDR-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_REGLIST_LOW_LD :
      print_low_register_list_ld (cd, info, fields->f_reglist_low_ld, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_REGLIST_HI_LD :
      print_hi_register_list_ld (cd, info, fields->f_reglist_hi_ld, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_REGLIST_LOW_ST :
      print_low_register_list_st (cd, info, fields->f_reglist_low_st, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_REGLIST_HI_ST :
      print_hi_register_list_st (cd, info, fields->f_reglist_hi_st, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_CC :
      print_normal (cd, info, fields->f_cc, 0|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;
    case FR30_OPERAND_CCC :
      print_normal (cd, info, fields->f_ccc, 0|(1<<(CGEN_OPERAND_HASH_PREFIX-CGEN_ATTR_BOOL_OFFSET))|(1<<(CGEN_OPERAND_UNSIGNED-CGEN_ATTR_BOOL_OFFSET)), pc, length);
      break;

    default :
      /* xgettext:c-format */
      fprintf (stderr, _("Unrecognized field %d while printing insn.\n"),
	       opindex);
    abort ();
  }
}

cgen_print_fn * const fr30_cgen_print_handlers[] = 
{
  print_insn_normal,
};


void
fr30_cgen_init_dis (cd)
     CGEN_CPU_DESC cd;
{
  fr30_cgen_init_opcode_table (cd);
  fr30_cgen_init_ibld_table (cd);
  cd->print_handlers = & fr30_cgen_print_handlers[0];
  cd->print_operand = fr30_cgen_print_operand;
}


/* Default print handler.  */

static void
print_normal (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     long value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  disassemble_info *info = (disassemble_info *) dis_info;

#ifdef CGEN_PRINT_NORMAL
  CGEN_PRINT_NORMAL (cd, info, value, attrs, pc, length);
#endif

  /* Print the operand as directed by the attributes.  */
  if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_SEM_ONLY))
    ; /* nothing to do */
  else if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_UNSIGNED))
    (*info->fprintf_func) (info->stream, "0x%lx", value);
  else
    (*info->fprintf_func) (info->stream, "%ld", value);
}

/* Default address handler.  */

static void
print_address (cd, dis_info, value, attrs, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     bfd_vma value;
     unsigned int attrs;
     bfd_vma pc;
     int length;
{
  disassemble_info *info = (disassemble_info *) dis_info;

#ifdef CGEN_PRINT_ADDRESS
  CGEN_PRINT_ADDRESS (cd, info, value, attrs, pc, length);
#endif

  /* Print the operand as directed by the attributes.  */
  if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_SEM_ONLY))
    ; /* nothing to do */
  else if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_PCREL_ADDR))
    (*info->print_address_func) (value, info);
  else if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_ABS_ADDR))
    (*info->print_address_func) (value, info);
  else if (CGEN_BOOL_ATTR (attrs, CGEN_OPERAND_UNSIGNED))
    (*info->fprintf_func) (info->stream, "0x%lx", (long) value);
  else
    (*info->fprintf_func) (info->stream, "%ld", (long) value);
}

/* Keyword print handler.  */

static void
print_keyword (cd, dis_info, keyword_table, value, attrs)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     CGEN_KEYWORD *keyword_table;
     long value;
     unsigned int attrs;
{
  disassemble_info *info = (disassemble_info *) dis_info;
  const CGEN_KEYWORD_ENTRY *ke;

  ke = cgen_keyword_lookup_value (keyword_table, value);
  if (ke != NULL)
    (*info->fprintf_func) (info->stream, "%s", ke->name);
  else
    (*info->fprintf_func) (info->stream, "???");
}

/* Default insn printer.

   DIS_INFO is defined as `PTR' so the disassembler needn't know anything
   about disassemble_info.  */

static void
print_insn_normal (cd, dis_info, insn, fields, pc, length)
     CGEN_CPU_DESC cd;
     PTR dis_info;
     const CGEN_INSN *insn;
     CGEN_FIELDS *fields;
     bfd_vma pc;
     int length;
{
  const CGEN_SYNTAX *syntax = CGEN_INSN_SYNTAX (insn);
  disassemble_info *info = (disassemble_info *) dis_info;
  const unsigned char *syn;

  CGEN_INIT_PRINT (cd);

  for (syn = CGEN_SYNTAX_STRING (syntax); *syn; ++syn)
    {
      if (CGEN_SYNTAX_MNEMONIC_P (*syn))
	{
	  (*info->fprintf_func) (info->stream, "%s", CGEN_INSN_MNEMONIC (insn));
	  continue;
	}
      if (CGEN_SYNTAX_CHAR_P (*syn))
	{
	  (*info->fprintf_func) (info->stream, "%c", CGEN_SYNTAX_CHAR (*syn));
	  continue;
	}

      /* We have an operand.  */
      fr30_cgen_print_operand (cd, CGEN_SYNTAX_FIELD (*syn), info,
				 fields, CGEN_INSN_ATTRS (insn), pc, length);
    }
}

/* Utility to print an insn.
   BUF is the base part of the insn, target byte order, BUFLEN bytes long.
   The result is the size of the insn in bytes or zero for an unknown insn
   or -1 if an error occurs fetching data (memory_error_func will have
   been called).  */

static int
print_insn (cd, pc, info, buf, buflen)
     CGEN_CPU_DESC cd;
     bfd_vma pc;
     disassemble_info *info;
     char *buf;
     int buflen;
{
  unsigned long insn_value;
  const CGEN_INSN_LIST *insn_list;
  CGEN_EXTRACT_INFO ex_info;

  ex_info.dis_info = info;
  ex_info.valid = (1 << CGEN_BASE_INSN_SIZE) - 1;
  ex_info.insn_bytes = buf;

  switch (buflen)
    {
    case 1:
      insn_value = buf[0];
      break;
    case 2:
      insn_value = info->endian == BFD_ENDIAN_BIG ? bfd_getb16 (buf) : bfd_getl16 (buf);
      break;
    case 4:
      insn_value = info->endian == BFD_ENDIAN_BIG ? bfd_getb32 (buf) : bfd_getl32 (buf);
      break;
    default:
      abort ();
    }

  /* The instructions are stored in hash lists.
     Pick the first one and keep trying until we find the right one.  */

  insn_list = CGEN_DIS_LOOKUP_INSN (cd, buf, insn_value);
  while (insn_list != NULL)
    {
      const CGEN_INSN *insn = insn_list->insn;
      CGEN_FIELDS fields;
      int length;

#if 0 /* not needed as insn shouldn't be in hash lists if not supported */
      /* Supported by this cpu?  */
      if (! fr30_cgen_insn_supported (cd, insn))
	continue;
#endif

      /* Basic bit mask must be correct.  */
      /* ??? May wish to allow target to defer this check until the extract
	 handler.  */
      if ((insn_value & CGEN_INSN_BASE_MASK (insn))
	  == CGEN_INSN_BASE_VALUE (insn))
	{
	  /* Printing is handled in two passes.  The first pass parses the
	     machine insn and extracts the fields.  The second pass prints
	     them.  */

	  length = CGEN_EXTRACT_FN (cd, insn)
	    (cd, insn, &ex_info, insn_value, &fields, pc);
	  /* length < 0 -> error */
	  if (length < 0)
	    return length;
	  if (length > 0)
	    {
	      CGEN_PRINT_FN (cd, insn) (cd, info, insn, &fields, pc, length);
	      /* length is in bits, result is in bytes */
	      return length / 8;
	    }
	}

      insn_list = CGEN_DIS_NEXT_INSN (insn_list);
    }

  return 0;
}

/* Default value for CGEN_PRINT_INSN.
   The result is the size of the insn in bytes or zero for an unknown insn
   or -1 if an error occured fetching bytes.  */

#ifndef CGEN_PRINT_INSN
#define CGEN_PRINT_INSN default_print_insn
#endif

static int
default_print_insn (cd, pc, info)
     CGEN_CPU_DESC cd;
     bfd_vma pc;
     disassemble_info *info;
{
  char buf[CGEN_MAX_INSN_SIZE];
  int status;

  /* Read the base part of the insn.  */

  status = (*info->read_memory_func) (pc, buf, CGEN_BASE_INSN_SIZE, info);
  if (status != 0)
    {
      (*info->memory_error_func) (status, pc, info);
      return -1;
    }

  return print_insn (cd, pc, info, buf, CGEN_BASE_INSN_SIZE);
}

/* Main entry point.
   Print one instruction from PC on INFO->STREAM.
   Return the size of the instruction (in bytes).  */

int
print_insn_fr30 (pc, info)
     bfd_vma pc;
     disassemble_info *info;
{
  int length;
  static CGEN_CPU_DESC cd = 0;
  int mach = info->mach;
  int big_p = info->endian == BFD_ENDIAN_BIG;

  /* If we haven't initialized yet, initialize the opcode table.  */
  if (! cd)
    {
      cd = fr30_cgen_cpu_open (mach,
				 big_p ?
				 CGEN_ENDIAN_BIG
				 : CGEN_ENDIAN_LITTLE);
      fr30_cgen_init_dis (cd);
    }
  /* If we've switched cpu's, re-initialize.  */
  /* ??? Perhaps we should use BFD_ENDIAN.  */
  else if (mach != cd->mach
	   || (cd->endian
	       != (big_p ? CGEN_ENDIAN_BIG : CGEN_ENDIAN_LITTLE)))
    {
      cgen_set_cpu (cd, mach, big_p ? CGEN_ENDIAN_BIG : CGEN_ENDIAN_LITTLE);
    }

  /* We try to have as much common code as possible.
     But at this point some targets need to take over.  */
  /* ??? Some targets may need a hook elsewhere.  Try to avoid this,
     but if not possible try to move this hook elsewhere rather than
     have two hooks.  */
  length = CGEN_PRINT_INSN (cd, pc, info);
  if (length > 0)
    return length;
  if (length < 0)
    return -1;

  (*info->fprintf_func) (info->stream, UNKNOWN_INSN_MSG);
  return CGEN_DEFAULT_INSN_SIZE;
}
