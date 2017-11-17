/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2017 Bruno Haible <bruno@clisp.org>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*----------------------------------------------------------------------
  Some test routines for avcall foreign function interface.
  The coverage is entirely random, this just contains some of the things
  that I think are likely to break.

  We really need to add some more pointer (void* / char* / func*) tests
  and some varargs ones, and also try to test structure alignment more
  throughly.
 ----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avcall.h"

#include "testcases.c"

#if defined(__hppa__) && defined(__GNUC__)
#if (__GNUC__ == 2 && __GNUC_MINOR__ < 6)
/* gcc-2.5.2 bugs prevent the T test from working. */
#define SKIP_T
#endif
#endif
#if defined(__m68k__) && defined(__GNUC__)
/* "gcc-2.6.3 -freg-struct-return" returns  T = struct { char c[3]; }  (which
 * has size 4 !) in memory, in contrast to  struct { char a,b,c; }  and
 * struct { char c[4]; }  and  struct { char a,b,c,d; }  which have the same
 * size and the same alignment but are returned in registers. I don't know why.
 */
#define SKIP_T
#endif


/*
 * The way we run these tests - first call the function directly, then
 * through av_call() - there is the danger that arguments or results seem
 * to be passed correctly, but what we are seeing are in fact the vestiges
 * (traces) or the previous call. This may seriously fake the test.
 * Avoid this by clearing the registers between the first and the second call.
 */
long clear_traces_i (long a, long b, long c, long d, long e, long f, long g, long h,
                     long i, long j, long k, long l, long m, long n, long o, long p)
{ return 0; }
float clear_traces_f (float a, float b, float c, float d, float e, float f, float g,
                      float h, float i, float j, float k, float l, float m, float n,
                      float o, float p)
{ return 0.0; }
double clear_traces_d (double a, double b, double c, double d, double e, double f, double g,
                       double h, double i, double j, double k, double l, double m, double n,
                       double o, double p)
{ return 0.0; }
J clear_traces_J (void)
{ J j; j.l1 = j.l2 = 0; return j; }
void clear_traces (void)
{ clear_traces_i(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  clear_traces_f(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_d(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_J();
}

void
  void_tests (void)
{
  av_alist a;
  v_v();
  clear_traces();
  av_start_void(a,v_v);
  av_call(a);
  return;
}
void
  int_tests (void)
{
  av_alist a;
  int ir;

  ir = i_v();
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_v,&ir);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i(i1);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i,&ir);
  av_int(a,i1);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i2(i1,i2);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i2,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i4(i1,i2,i3,i4);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i4,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i8(i1,i2,i3,i4,i5,i6,i7,i8);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i8,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_int(a,i5);
  av_int(a,i6);
  av_int(a,i7);
  av_int(a,i8);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  ir = i_i16(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
  fprintf(out,"->%d\n",ir);
  fflush(out);
  ir = 0; clear_traces();
  av_start_int(a,i_i16,&ir);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_int(a,i4);
  av_int(a,i5);
  av_int(a,i6);
  av_int(a,i7);
  av_int(a,i8);
  av_int(a,i9);
  av_int(a,i10);
  av_int(a,i11);
  av_int(a,i12);
  av_int(a,i13);
  av_int(a,i14);
  av_int(a,i15);
  av_int(a,i16);
  av_call(a);
  fprintf(out,"->%d\n",ir);
  fflush(out);

  return;
}
void
  float_tests (void)
{
  av_alist a;
  float fr;

  fr = f_f(f1);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f,&fr);
  av_float(a,f1);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f2(f1,f2);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f2,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f4(f1,f2,f3,f4);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f4,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f8(f1,f2,f3,f4,f5,f6,f7,f8);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f8,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f16(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f16,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_float(a,f13);
  av_float(a,f14);
  av_float(a,f15);
  av_float(a,f16);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f24(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f24,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_float(a,f13);
  av_float(a,f14);
  av_float(a,f15);
  av_float(a,f16);
  av_float(a,f17);
  av_float(a,f18);
  av_float(a,f19);
  av_float(a,f20);
  av_float(a,f21);
  av_float(a,f22);
  av_float(a,f23);
  av_float(a,f24);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);
}
void
  double_tests (void)
{
  av_alist a;
  double dr;

  dr = d_d(d1);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d,&dr);
  av_double(a,d1);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d2(d1,d2);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d2,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d4(d1,d2,d3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d4,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d8(d1,d2,d3,d4,d5,d6,d7,d8);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d8,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d16(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d16,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_double(a,d9);
  av_double(a,d10);
  av_double(a,d11);
  av_double(a,d12);
  av_double(a,d13);
  av_double(a,d14);
  av_double(a,d15);
  av_double(a,d16);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  return;
}
void
  mixed_number_tests (void)
{
  av_alist a;
  uchar ucr;
  ushort usr;
  float fr;
  double dr;
  long long llr;

  /* Unsigned types.
   */
  ucr = uc_ucsil(uc1,us2,ui3,ul4);
  fprintf(out,"->%u\n",ucr);
  fflush(out);
  ucr = 0; clear_traces();
  av_start_uchar(a,uc_ucsil,&ucr);
  av_uchar(a,uc1);
  av_ushort(a,us2);
  av_uint(a,ui3);
  av_ulong(a,ul4);
  av_call(a);
  fprintf(out,"->%u\n",ucr);
  fflush(out);

  /* Mixed int & float types.
   */
  dr = d_iidd(i1,i2,d3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_iidd,&dr);
  av_int(a,i1);
  av_int(a,i2);
  av_double(a,d3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_iiidi(i1,i2,i3,d4,i5);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_iiidi,&dr);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_double(a,d4);
  av_int(a,i5);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_idid(i1,d2,i3,d4);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_idid,&dr);
  av_int(a,i1);
  av_double(a,d2);
  av_int(a,i3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_fdi(f1,d2,i3);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_fdi,&dr);
  av_float(a,f1);
  av_double(a,d2);
  av_int(a,i3);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  usr = us_cdcd(c1,d2,c3,d4);
  fprintf(out,"->%u\n",usr);
  fflush(out);
  usr = 0; clear_traces();
  av_start_ushort(a,us_cdcd,&usr);
  av_char(a,c1);
  av_double(a,d2);
  av_char(a,c3);
  av_double(a,d4);
  av_call(a);
  fprintf(out,"->%u\n",usr);
  fflush(out);

  /* Long long types.
   */
  llr = ll_iiilli(i1,i2,i3,ll1,i13);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_iiilli,&llr);
  av_int(a,i1);
  av_int(a,i2);
  av_int(a,i3);
  av_longlong(a,ll1);
  av_int(a,i13);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_flli(f13,ll1,i13);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_flli,&llr);
  av_float(a,f13);
  av_longlong(a,ll1);
  av_int(a,i13);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  fr = f_fi(f1,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_fi,&fr);
  av_float(a,f1);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f2i(f1,f2,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f2i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f3i(f1,f2,f3,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f3i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f4i(f1,f2,f3,f4,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f4i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f7i(f1,f2,f3,f4,f5,f6,f7,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f7i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f8i(f1,f2,f3,f4,f5,f6,f7,f8,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f8i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f12i(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f12i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  fr = f_f13i(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,i9);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  fr = 0.0; clear_traces();
  av_start_float(a,f_f13i,&fr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_float(a,f13);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  dr = d_di(d1,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_di,&dr);
  av_double(a,d1);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d2i(d1,d2,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d2i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d3i(d1,d2,d3,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d3i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d4i(d1,d2,d3,d4,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d4i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d7i(d1,d2,d3,d4,d5,d6,d7,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d7i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d8i(d1,d2,d3,d4,d5,d6,d7,d8,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d8i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d12i(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d12i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_double(a,d9);
  av_double(a,d10);
  av_double(a,d11);
  av_double(a,d12);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_d13i(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,i9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d13i,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_double(a,d9);
  av_double(a,d10);
  av_double(a,d11);
  av_double(a,d12);
  av_double(a,d13);
  av_int(a,i9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  return;
}
void
  pointer_tests (void)
{
  av_alist a;
  void* vpr;

  vpr = vp_vpdpcpsp(&uc1,&d2,str3,&I4);
  fprintf(out,"->0x%p\n",vpr);
  fflush(out);
  vpr = 0; clear_traces();
  av_start_ptr(a,vp_vpdpcpsp,void*,&vpr);
  av_ptr(a,void*,&uc1);
  av_ptr(a,double*,&d2);
  av_ptr(a,char*,str3);
  av_ptr(a,Int*,&I4);
  av_call(a);
  fprintf(out,"->0x%p\n",vpr);
  fflush(out);

  return;
}
void
  small_structure_return_tests (void)
{
  av_alist a;

  {
    Size1 r = S1_v();
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S1_v,Size1,1,&r);
    av_call(a);
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
  }
  {
    Size2 r = S2_v();
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S2_v,Size2,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
  }
  {
    Size3 r = S3_v();
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S3_v,Size3,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
  }
  {
    Size4 r = S4_v();
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S4_v,Size4,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
  }
  {
    Size7 r = S7_v();
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S7_v,Size7,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
  }
  {
    Size8 r = S8_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S8_v,Size8,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
  }
  {
    Size12 r = S12_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S12_v,Size12,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
  }
  {
    Size15 r = S15_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S15_v,Size15,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
  }
  {
    Size16 r = S16_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    av_start_struct(a,S16_v,Size16,1,&r);
    av_call(a);
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
  }
}
void
  structure_tests (void)
{
  av_alist a;
  Int Ir;
  Char Cr;
  Float Fr;
  Double Dr;
  J Jr;
  T Tr;
  X Xr;

  Ir = I_III(I1,I2,I3);
  fprintf(out,"->{%d}\n",Ir.x);
  fflush(out);
  Ir.x = 0; clear_traces();
  av_start_struct(a,I_III,Int,1,&Ir);
  av_struct(a,Int,I1);
  av_struct(a,Int,I2);
  av_struct(a,Int,I3);
  av_call(a);
  fprintf(out,"->{%d}\n",Ir.x);
  fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
  Cr = C_CdC(C1,d2,C3);
  fprintf(out,"->{'%c'}\n",Cr.x);
  fflush(out);
  Cr.x = '\0'; clear_traces();
  av_start_struct(a,C_CdC,Char,1,&Cr);
  av_struct(a,Char,C1);
  av_double(a,d2);
  av_struct(a,Char,C3);
  av_call(a);
  fprintf(out,"->{'%c'}\n",Cr.x);
  fflush(out);

  Fr = F_Ffd(F1,f2,d3);
  fprintf(out,"->{%g}\n",Fr.x);
  fflush(out);
  Fr.x = 0.0; clear_traces();
  av_start_struct(a,F_Ffd,Float,av_word_splittable_1(float),&Fr);
  av_struct(a,Float,F1);
  av_float(a,f2);
  av_double(a,d3);
  av_call(a);
  fprintf(out,"->{%g}\n",Fr.x);
  fflush(out);

  Dr = D_fDd(f1,D2,d3);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);
  Dr.x = 0.0; clear_traces();
  av_start_struct(a,D_fDd,Double,av_word_splittable_1(double),&Dr);
  av_float(a,f1);
  av_struct(a,Double,D2);
  av_double(a,d3);
  av_call(a);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);

  Dr = D_Dfd(D1,f2,d3);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);
  Dr.x = 0.0; clear_traces();
  av_start_struct(a,D_Dfd,Double,av_word_splittable_1(double),&Dr);
  av_struct(a,Double,D1);
  av_float(a,f2);
  av_double(a,d3);
  av_call(a);
  fprintf(out,"->{%g}\n",Dr.x);
  fflush(out);
#endif

  Jr = J_JiJ(J1,i2,J2);
  fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
  fflush(out);
  Jr.l1 = Jr.l2 = 0; clear_traces();
  av_start_struct(a,J_JiJ,J,av_word_splittable_2(long,long),&Jr);
  av_struct(a,J,J1);
  av_int(a,i2);
  av_struct(a,J,J2);
  av_call(a);
  fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
  fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
#ifndef SKIP_T
  Tr = T_TcT(T1,' ',T2);
  fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
  fflush(out);
  Tr.c[0] = Tr.c[1] = Tr.c[2] = 0; clear_traces();
  av_start_struct(a,T_TcT,T,1,&Tr);
  av_struct(a,T,T1);
  av_char(a,' ');
  av_struct(a,T,T2);
  av_call(a);
  fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
  fflush(out);
#endif

  Xr = X_BcdB(B1,c2,d3,B2);
  fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
  fflush(out);
  Xr.c[0]=Xr.c1='\0'; clear_traces();
  av_start_struct(a,X_BcdB,X,0,&Xr);
  av_struct(a,B,B1);
  av_char(a,c2);
  av_double(a,d3);
  av_struct(a,B,B2);
  av_call(a);
  fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
  fflush(out);
#endif

  return;
}

void
  gpargs_boundary_tests (void)
{
  av_alist a;
  long lr;
  long long llr;
  float fr;
  double dr;

  lr = l_l0K(K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l0K,&lr);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l1K(l1,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l1K,&lr);
  av_long(a,l1);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l2K(l1,l2,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l2K,&lr);
  av_long(a,l1);
  av_long(a,l2);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l3K(l1,l2,l3,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l3K,&lr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l4K(l1,l2,l3,l4,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l4K,&lr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l5K(l1,l2,l3,l4,l5,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l5K,&lr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  lr = l_l6K(l1,l2,l3,l4,l5,l6,K1,l9);
  fprintf(out,"->%ld\n",lr);
  fflush(out);
  lr = 0; clear_traces();
  av_start_long(a,l_l6K,&lr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_long(a,l6);
  av_struct(a,K,K1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%ld\n",lr);
  fflush(out);

  fr = f_f17l3L(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,l6,l7,l8,L1);
  fprintf(out,"->%g\n",fr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_float(a,f_f17l3L,&dr);
  av_float(a,f1);
  av_float(a,f2);
  av_float(a,f3);
  av_float(a,f4);
  av_float(a,f5);
  av_float(a,f6);
  av_float(a,f7);
  av_float(a,f8);
  av_float(a,f9);
  av_float(a,f10);
  av_float(a,f11);
  av_float(a,f12);
  av_float(a,f13);
  av_float(a,f14);
  av_float(a,f15);
  av_float(a,f16);
  av_float(a,f17);
  av_long(a,l6);
  av_long(a,l7);
  av_long(a,l8);
  av_struct(a,L,L1);
  av_call(a);
  fprintf(out,"->%g\n",fr);
  fflush(out);

  dr = d_d17l3L(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,l6,l7,l8,L1);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_d17l3L,&dr);
  av_double(a,d1);
  av_double(a,d2);
  av_double(a,d3);
  av_double(a,d4);
  av_double(a,d5);
  av_double(a,d6);
  av_double(a,d7);
  av_double(a,d8);
  av_double(a,d9);
  av_double(a,d10);
  av_double(a,d11);
  av_double(a,d12);
  av_double(a,d13);
  av_double(a,d14);
  av_double(a,d15);
  av_double(a,d16);
  av_double(a,d17);
  av_long(a,l6);
  av_long(a,l7);
  av_long(a,l8);
  av_struct(a,L,L1);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  llr = ll_l2ll(l1,l2,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l2ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_l3ll(l1,l2,l3,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l3ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_l4ll(l1,l2,l3,l4,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l4ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_l5ll(l1,l2,l3,l4,l5,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l5ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_l6ll(l1,l2,l3,l4,l5,l6,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l6ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_long(a,l6);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  llr = ll_l7ll(l1,l2,l3,l4,l5,l6,l7,ll1,l9);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);
  llr = 0; clear_traces();
  av_start_longlong(a,ll_l7ll,&llr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_long(a,l6);
  av_long(a,l7);
  av_longlong(a,ll1);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
  fflush(out);

  dr = d_l2d(l1,l2,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l2d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_l3d(l1,l2,l3,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l3d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_l4d(l1,l2,l3,l4,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l4d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_l5d(l1,l2,l3,l4,l5,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l5d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_l6d(l1,l2,l3,l4,l5,l6,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l6d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_long(a,l6);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  dr = d_l7d(l1,l2,l3,l4,l5,l6,l7,d2,l9);
  fprintf(out,"->%g\n",dr);
  fflush(out);
  dr = 0.0; clear_traces();
  av_start_double(a,d_l7d,&dr);
  av_long(a,l1);
  av_long(a,l2);
  av_long(a,l3);
  av_long(a,l4);
  av_long(a,l5);
  av_long(a,l6);
  av_long(a,l7);
  av_double(a,d2);
  av_long(a,l9);
  av_call(a);
  fprintf(out,"->%g\n",dr);
  fflush(out);

  return;
}

int
  main (void)
{
  out = stdout;
  void_tests();
  int_tests();
  float_tests();
  double_tests();
  mixed_number_tests();
  pointer_tests();
  small_structure_return_tests();
  structure_tests();
  gpargs_boundary_tests();

  exit(0);
}
