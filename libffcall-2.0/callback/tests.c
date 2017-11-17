/* Some random tests for vacall. */

/*
 * Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callback.h"

#include "testcases.c"

#if defined(__m68k__) && defined(__GNUC__)
/* "gcc-2.6.3 -freg-struct-return" returns  T = struct { char c[3]; }  (which
 * has size 4 !) in memory, in contrast to  struct { char a,b,c; }  and
 * struct { char c[4]; }  and  struct { char a,b,c,d; }  which have the same
 * size and the same alignment but are returned in registers. I don't know why.
 */
#define SKIP_T
#endif
#if defined(__sparc__) && defined(__sun) && defined(__SUNPRO_C) /* SUNWspro cc */
/* SunPRO cc miscompiles the simulator function for X_BcdB: d.i[1] is
 * temporarily stored in %l2 and put onto the stack from %l2, but in between
 * the copy of X has used %l2 as a counter without saving and restoring its
 * value.
 */
#define SKIP_X
#endif
#if defined(__mipsn32__) && !defined(__GNUC__)
/* The X test crashes for an unknown reason. */
#define SKIP_X
#endif


/* These functions simulate the behaviour of the functions defined in testcases.c. */

/* void tests */
void v_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&v_v) { fprintf(out,"wrong data for v_v\n"); exit(1); }
  va_start_void(alist);
  fprintf(out,"void f(void):\n");
  fflush(out);
  va_return_void(alist);
}

/* int tests */
void i_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_v) { fprintf(out,"wrong data for i_v\n"); exit(1); }
  va_start_int(alist);
 {int r=99;
  fprintf(out,"int f(void):");
  fflush(out);
  va_return_int(alist, r);
}}
void i_i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_i) { fprintf(out,"wrong data for i_i\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int r=a+1;
  fprintf(out,"int f(int):(%d)",a);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i2_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_i2) { fprintf(out,"wrong data for i_i2\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int r=a+b;
  fprintf(out,"int f(2*int):(%d,%d)",a,b);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i4_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_i4) { fprintf(out,"wrong data for i_i4\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int r=a+b+c+d;
  fprintf(out,"int f(4*int):(%d,%d,%d,%d)",a,b,c,d);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i8_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_i8) { fprintf(out,"wrong data for i_i8\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int e = va_arg_int(alist);
  int f = va_arg_int(alist);
  int g = va_arg_int(alist);
  int h = va_arg_int(alist);
  int r=a+b+c+d+e+f+g+h;
  fprintf(out,"int f(8*int):(%d,%d,%d,%d,%d,%d,%d,%d)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_int(alist, r);
}}
void i_i16_simulator (void* data, va_alist alist)
{
  if (data != (void*)&i_i16) { fprintf(out,"wrong data for i_i16\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  int d = va_arg_int(alist);
  int e = va_arg_int(alist);
  int f = va_arg_int(alist);
  int g = va_arg_int(alist);
  int h = va_arg_int(alist);
  int i = va_arg_int(alist);
  int j = va_arg_int(alist);
  int k = va_arg_int(alist);
  int l = va_arg_int(alist);
  int m = va_arg_int(alist);
  int n = va_arg_int(alist);
  int o = va_arg_int(alist);
  int p = va_arg_int(alist);
  int r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"int f(16*int):(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
          a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_int(alist, r);
}}

/* float tests */
void f_f_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f) { fprintf(out,"wrong data for f_f\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float r=a+1.0;
  fprintf(out,"float f(float):(%g)",a);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f2_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f2) { fprintf(out,"wrong data for f_f2\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float r=a+b;
  fprintf(out,"float f(2*float):(%g,%g)",a,b);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f4_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f4) { fprintf(out,"wrong data for f_f4\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float r=a+b+c+d;
  fprintf(out,"float f(4*float):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f8_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f8) { fprintf(out,"wrong data for f_f8\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float r=a+b+c+d+e+f+g+h;
  fprintf(out,"float f(8*float):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f16_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f16) { fprintf(out,"wrong data for f_f16\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  float m = va_arg_float(alist);
  float n = va_arg_float(alist);
  float o = va_arg_float(alist);
  float p = va_arg_float(alist);
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"float f(16*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f24_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f24) { fprintf(out,"wrong data for f_f24\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  float m = va_arg_float(alist);
  float n = va_arg_float(alist);
  float o = va_arg_float(alist);
  float p = va_arg_float(alist);
  float q = va_arg_float(alist);
  float s = va_arg_float(alist);
  float t = va_arg_float(alist);
  float u = va_arg_float(alist);
  float v = va_arg_float(alist);
  float w = va_arg_float(alist);
  float x = va_arg_float(alist);
  float y = va_arg_float(alist);
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+s+t+u+v+w+x+y;
  fprintf(out,"float f(24*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,u,v,w,x,y);
  fflush(out);
  va_return_float(alist, r);
}}

/* double tests */
void d_d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d) { fprintf(out,"wrong data for d_d\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double r=a+1.0;
  fprintf(out,"double f(double):(%g)",a);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d2_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d2) { fprintf(out,"wrong data for d_d2\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double r=a+b;
  fprintf(out,"double f(2*double):(%g,%g)",a,b);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d4_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d4) { fprintf(out,"wrong data for d_d4\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(4*double):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d8_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d8) { fprintf(out,"wrong data for d_d8\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double r=a+b+c+d+e+f+g+h;
  fprintf(out,"double f(8*double):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d16_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d16) { fprintf(out,"wrong data for d_d16\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double i = va_arg_double(alist);
  double j = va_arg_double(alist);
  double k = va_arg_double(alist);
  double l = va_arg_double(alist);
  double m = va_arg_double(alist);
  double n = va_arg_double(alist);
  double o = va_arg_double(alist);
  double p = va_arg_double(alist);
  double r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"double f(16*double):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  va_return_double(alist, r);
}}

/* pointer tests */
void vp_vpdpcpsp_simulator (void* data, va_alist alist)
{
  if (data != (void*)&vp_vpdpcpsp) { fprintf(out,"wrong data for vp_vpdpcpsp\n"); exit(1); }
  va_start_ptr(alist, void*);
 {void* a = va_arg_ptr(alist, void*);
  double* b = va_arg_ptr(alist, double*);
  char* c = va_arg_ptr(alist, char*);
  Int* d = va_arg_ptr(alist, Int*);
  void* ret = (char*)b + 1;
  fprintf(out,"void* f(void*,double*,char*,Int*):(0x%p,0x%p,0x%p,0x%p)",a,b,c,d);
  fflush(out);
  va_return_ptr(alist, void*, ret);
}}

/* mixed number tests */
void uc_ucsil_simulator (void* data, va_alist alist)
{
  if (data != (void*)&uc_ucsil) { fprintf(out,"wrong data for uc_ucsil\n"); exit(1); }
  va_start_uchar(alist);
 {uchar a = va_arg_uchar(alist);
  ushort b = va_arg_ushort(alist);
  uint c = va_arg_uint(alist);
  ulong d = va_arg_ulong(alist);
  uchar r = (uchar)-1;
  fprintf(out,"uchar f(uchar,ushort,uint,ulong):(%u,%u,%u,%lu)",a,b,c,d);
  fflush(out);
  va_return_uchar(alist, r);
}}
void d_iidd_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_iidd) { fprintf(out,"wrong data for d_iidd\n"); exit(1); }
  va_start_double(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(int,int,double,double):(%d,%d,%g,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void d_iiidi_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_iiidi) { fprintf(out,"wrong data for d_iiidi\n"); exit(1); }
  va_start_double(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  double d = va_arg_double(alist);
  int e = va_arg_int(alist);
  double r=a+b+c+d+e;
  fprintf(out,"double f(int,int,int,double,int):(%d,%d,%d,%g,%d)",a,b,c,d,e);
  fflush(out);
  va_return_double(alist, r);
}}
void d_idid_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_idid) { fprintf(out,"wrong data for d_idid\n"); exit(1); }
  va_start_double(alist);
 {int a = va_arg_int(alist);
  double b = va_arg_double(alist);
  int c = va_arg_int(alist);
  double d = va_arg_double(alist);
  double r=a+b+c+d;
  fprintf(out,"double f(int,double,int,double):(%d,%g,%d,%g)",a,b,c,d);
  fflush(out);
  va_return_double(alist, r);
}}
void d_fdi_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_fdi) { fprintf(out,"wrong data for d_fdi\n"); exit(1); }
  va_start_double(alist);
 {float a = va_arg_float(alist);
  double b = va_arg_double(alist);
  int c = va_arg_int(alist);
  double r=a+b+c;
  fprintf(out,"double f(float,double,int):(%g,%g,%d)",a,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void us_cdcd_simulator (void* data, va_alist alist)
{
  if (data != (void*)&us_cdcd) { fprintf(out,"wrong data for us_cdcd\n"); exit(1); }
  va_start_ushort(alist);
 {char a = va_arg_char(alist);
  double b = va_arg_double(alist);
  char c = va_arg_char(alist);
  double d = va_arg_double(alist);
  ushort r = (ushort)(a + b + c + d);
  fprintf(out,"ushort f(char,double,char,double):('%c',%g,'%c',%g)",a,b,c,d);
  fflush(out);
  va_return_ushort(alist, r);
}}
void ll_iiilli_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_iiilli) { fprintf(out,"wrong data for ll_iiilli\n"); exit(1); }
  va_start_longlong(alist);
 {int a = va_arg_int(alist);
  int b = va_arg_int(alist);
  int c = va_arg_int(alist);
  long long d = va_arg_longlong(alist);
  int e = va_arg_int(alist);
  long long r = (long long)(int)a + (long long)(int)b + (long long)(int)c + d + (long long)e;
  fprintf(out,"long long f(int,int,int,long long,int):(%d,%d,%d,0x%lx%08lx,%d)",a,b,c,(long)(d>>32),(long)(d&0xffffffff),e);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_flli_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_flli) { fprintf(out,"wrong data for ll_flli\n"); exit(1); }
  va_start_longlong(alist);
 {float a = va_arg_float(alist);
  long long b = va_arg_longlong(alist);
  int c = va_arg_int(alist);
  long long r = (long long)(int)a + b + (long long)c;
  fprintf(out,"long long f(float,long long,int):(%g,0x%lx%08lx,0x%lx)",a,(long)(b>>32),(long)(b&0xffffffff),(long)c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void f_fi_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_fi) { fprintf(out,"wrong data for f_fi\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+z;
  fprintf(out,"float f(float,int):(%g,%d)",a,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f2i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f2i) { fprintf(out,"wrong data for f_f2i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+z;
  fprintf(out,"float f(2*float,int):(%g,%g,%d)",a,b,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f3i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f3i) { fprintf(out,"wrong data for f_f3i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+z;
  fprintf(out,"float f(3*float,int):(%g,%g,%g,%d)",a,b,c,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f4i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f4i) { fprintf(out,"wrong data for f_f4i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+d+z;
  fprintf(out,"float f(4*float,int):(%g,%g,%g,%g,%d)",a,b,c,d,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f7i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f7i) { fprintf(out,"wrong data for f_f7i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+d+e+f+g+z;
  fprintf(out,"float f(7*float,int):(%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f8i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f8i) { fprintf(out,"wrong data for f_f8i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+d+e+f+g+h+z;
  fprintf(out,"float f(8*float,int):(%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f12i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f12i) { fprintf(out,"wrong data for f_f12i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+d+e+f+g+h+i+j+k+l+z;
  fprintf(out,"float f(12*float,int):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,i,j,k,l,z);
  fflush(out);
  va_return_float(alist, r);
}}
void f_f13i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f13i) { fprintf(out,"wrong data for f_f13i\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  float m = va_arg_float(alist);
  int z = va_arg_int(alist);
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+z;
  fprintf(out,"float f(13*float,int):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,i,j,k,l,m,z);
  fflush(out);
  va_return_float(alist, r);
}}
void d_di_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_di) { fprintf(out,"wrong data for d_di\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+z;
  fprintf(out,"double f(double,int):(%g,%d)",a,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d2i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d2i) { fprintf(out,"wrong data for d_d2i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+z;
  fprintf(out,"double f(2*double,int):(%g,%g,%d)",a,b,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d3i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d3i) { fprintf(out,"wrong data for d_d3i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+z;
  fprintf(out,"double f(3*double,int):(%g,%g,%g,%d)",a,b,c,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d4i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d4i) { fprintf(out,"wrong data for d_d4i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+d+z;
  fprintf(out,"double f(4*double,int):(%g,%g,%g,%g,%d)",a,b,c,d,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d7i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d7i) { fprintf(out,"wrong data for d_d7i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+d+e+f+g+z;
  fprintf(out,"double f(7*double,int):(%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d8i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d8i) { fprintf(out,"wrong data for d_d8i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+d+e+f+g+h+z;
  fprintf(out,"double f(8*double,int):(%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d12i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d12i) { fprintf(out,"wrong data for d_d12i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double i = va_arg_double(alist);
  double j = va_arg_double(alist);
  double k = va_arg_double(alist);
  double l = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+d+e+f+g+h+i+j+k+l+z;
  fprintf(out,"double f(12*double,int):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,i,j,k,l,z);
  fflush(out);
  va_return_double(alist, r);
}}
void d_d13i_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d13i) { fprintf(out,"wrong data for d_d13i\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double i = va_arg_double(alist);
  double j = va_arg_double(alist);
  double k = va_arg_double(alist);
  double l = va_arg_double(alist);
  double m = va_arg_double(alist);
  int z = va_arg_int(alist);
  double r=a+b+c+d+e+f+g+h+i+j+k+l+m+z;
  fprintf(out,"double f(13*double,int):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%d)",a,b,c,d,e,f,g,h,i,j,k,l,m,z);
  fflush(out);
  va_return_double(alist, r);
}}

/* small structure return tests */
void S1_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S1_v) { fprintf(out,"wrong data for S1_v\n"); exit(1); }
 {Size1 r;
  va_start_struct(alist, Size1, 1);
  r = Size1_1;
  fprintf(out,"Size1 f(void):");
  fflush(out);
  va_return_struct(alist, Size1, r);
}}
void S2_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S2_v) { fprintf(out,"wrong data for S2_v\n"); exit(1); }
 {Size2 r;
  va_start_struct(alist, Size2, 1);
  r = Size2_1;
  fprintf(out,"Size2 f(void):");
  fflush(out);
  va_return_struct(alist, Size2, r);
}}
void S3_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S3_v) { fprintf(out,"wrong data for S3_v\n"); exit(1); }
 {Size3 r;
  va_start_struct(alist, Size3, 1);
  r = Size3_1;
  fprintf(out,"Size3 f(void):");
  fflush(out);
  va_return_struct(alist, Size3, r);
}}
void S4_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S4_v) { fprintf(out,"wrong data for S4_v\n"); exit(1); }
 {Size4 r;
  va_start_struct(alist, Size4, 1);
  r = Size4_1;
  fprintf(out,"Size4 f(void):");
  fflush(out);
  va_return_struct(alist, Size4, r);
}}
void S7_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S7_v) { fprintf(out,"wrong data for S7_v\n"); exit(1); }
 {Size7 r;
  va_start_struct(alist, Size7, 1);
  r = Size7_1;
  fprintf(out,"Size7 f(void):");
  fflush(out);
  va_return_struct(alist, Size7, r);
}}
void S8_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S8_v) { fprintf(out,"wrong data for S8_v\n"); exit(1); }
 {Size8 r;
  va_start_struct(alist, Size8, 1);
  r = Size8_1;
  fprintf(out,"Size8 f(void):");
  fflush(out);
  va_return_struct(alist, Size8, r);
}}
void S12_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S12_v) { fprintf(out,"wrong data for S12_v\n"); exit(1); }
 {Size12 r;
  va_start_struct(alist, Size12, 1);
  r = Size12_1;
  fprintf(out,"Size12 f(void):");
  fflush(out);
  va_return_struct(alist, Size12, r);
}}
void S15_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S15_v) { fprintf(out,"wrong data for S15_v\n"); exit(1); }
 {Size15 r;
  va_start_struct(alist, Size15, 1);
  r = Size15_1;
  fprintf(out,"Size15 f(void):");
  fflush(out);
  va_return_struct(alist, Size15, r);
}}
void S16_v_simulator (void* data, va_alist alist)
{
  if (data != (void*)&S16_v) { fprintf(out,"wrong data for S16_v\n"); exit(1); }
 {Size16 r;
  va_start_struct(alist, Size16, 1);
  r = Size16_1;
  fprintf(out,"Size16 f(void):");
  fflush(out);
  va_return_struct(alist, Size16, r);
}}

/* structure tests */
void I_III_simulator (void* data, va_alist alist)
{
  if (data != (void*)&I_III) { fprintf(out,"wrong data for I_III\n"); exit(1); }
 {Int a;
  Int b;
  Int c;
  Int r;
  va_start_struct(alist, Int, 1);
  a = va_arg_struct(alist, Int);
  b = va_arg_struct(alist, Int);
  c = va_arg_struct(alist, Int);
  r.x = a.x + b.x + c.x;
  fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
  fflush(out);
  va_return_struct(alist, Int, r);
}}
#ifndef SKIP_EXTRA_STRUCTS
void C_CdC_simulator (void* data, va_alist alist)
{
  if (data != (void*)&C_CdC) { fprintf(out,"wrong data for C_CdC\n"); exit(1); }
 {Char a;
  double b;
  Char c;
  Char r;
  va_start_struct(alist, Char, 1);
  a = va_arg_struct(alist, Char);
  b = va_arg_double(alist);
  c = va_arg_struct(alist, Char);
  r.x = (a.x + c.x)/2;
  fprintf(out,"Char f(Char,double,Char):({'%c'},%g,{'%c'})",a.x,b,c.x);
  fflush(out);
  va_return_struct(alist, Char, r);
}}
void F_Ffd_simulator (void* data, va_alist alist)
{
  if (data != (void*)&F_Ffd) { fprintf(out,"wrong data for F_Ffd\n"); exit(1); }
 {Float a;
  float b;
  double c;
  Float r;
  va_start_struct(alist, Float, va_word_splittable_1(float));
  a = va_arg_struct(alist, Float);
  b = va_arg_float(alist);
  c = va_arg_double(alist);
  r.x = a.x + b + c;
  fprintf(out,"Float f(Float,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  va_return_struct(alist, Float, r);
}}
void D_fDd_simulator (void* data, va_alist alist)
{
  if (data != (void*)&D_fDd) { fprintf(out,"wrong data for D_fDd\n"); exit(1); }
 {float a;
  Double b;
  double c;
  Double r;
  va_start_struct(alist, Double, va_word_splittable_1(double));
  a = va_arg_float(alist);
  b = va_arg_struct(alist, Double);
  c = va_arg_double(alist);
  r.x = a + b.x + c;
  fprintf(out,"Double f(float,Double,double):(%g,{%g},%g)",a,b.x,c);
  fflush(out);
  va_return_struct(alist, Double, r);
}}
void D_Dfd_simulator (void* data, va_alist alist)
{
  if (data != (void*)&D_Dfd) { fprintf(out,"wrong data for D_Dfd\n"); exit(1); }
 {Double a;
  float b;
  double c;
  Double r;
  va_start_struct(alist, Double, va_word_splittable_1(double));
  a = va_arg_struct(alist, Double);
  b = va_arg_float(alist);
  c = va_arg_double(alist);
  r.x = a.x + b + c;
  fprintf(out,"Double f(Double,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  va_return_struct(alist, Double, r);
}}
#endif
void J_JiJ_simulator (void* data, va_alist alist)
{
  if (data != (void*)&J_JiJ) { fprintf(out,"wrong data for J_JiJ\n"); exit(1); }
 {J a;
  int b;
  J c;
  J r;
  va_start_struct(alist, J, va_word_splittable_2(long,long));
  a = va_arg_struct(alist, J);
  b = va_arg_int(alist);
  c = va_arg_struct(alist, J);
  r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
  fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
  fflush(out);
  va_return_struct(alist, J, r);
}}
#ifndef SKIP_EXTRA_STRUCTS
void T_TcT_simulator (void* data, va_alist alist)
{
  if (data != (void*)&T_TcT) { fprintf(out,"wrong data for T_TcT\n"); exit(1); }
 {T a;
  char b;
  T c;
  T r;
  va_start_struct(alist, T, 1);
  a = va_arg_struct(alist, T);
  b = va_arg_char(alist);
  c = va_arg_struct(alist, T);
  r.c[0]='b'; r.c[1]=c.c[1]; r.c[2]=c.c[2];
  fprintf(out,"T f(T,char,T):({\"%c%c%c\"},'%c',{\"%c%c%c\"})",a.c[0],a.c[1],a.c[2],b,c.c[0],c.c[1],c.c[2]);
  fflush(out);
  va_return_struct(alist, T, r);
}}
void X_BcdB_simulator (void* data, va_alist alist)
{
  if (data != (void*)&X_BcdB) { fprintf(out,"wrong data for X_BcdB\n"); exit(1); }
 {B a;
  char b;
  double c;
  B d;
  static X xr={"return val",'R'};
  X r;
  va_start_struct(alist, X, 0);
  a = va_arg_struct(alist, B);
  b = va_arg_char(alist);
  c = va_arg_double(alist);
  d = va_arg_struct(alist, B);
  r = xr;
  r.c1 = b;
  fprintf(out,"X f(B,char,double,B):({%g,{%d,%d,%d}},'%c',%g,{%g,{%d,%d,%d}})",
          a.d,a.i[0],a.i[1],a.i[2],b,c,d.d,d.i[0],d.i[1],d.i[2]);
  fflush(out);
  va_return_struct(alist, X, r);
}}
#endif

/* gpargs boundary tests */
void l_l0K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l0K) { fprintf(out,"wrong data for l_l0K\n"); exit(1); }
  va_start_long(alist);
 {K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(K,long):(%ld,%ld,%ld,%ld,%ld)",b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l1K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l1K) { fprintf(out,"wrong data for l_l1K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld)",a1,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l2K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l2K) { fprintf(out,"wrong data for l_l2K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + a2 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(2*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l3K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l3K) { fprintf(out,"wrong data for l_l3K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + a2 + a3 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(3*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l4K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l4K) { fprintf(out,"wrong data for l_l4K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + a2 + a3 + a4 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(4*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l5K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l5K) { fprintf(out,"wrong data for l_l5K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + a2 + a3 + a4 + a5 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(5*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void l_l6K_simulator (void* data, va_alist alist)
{
  if (data != (void*)&l_l6K) { fprintf(out,"wrong data for l_l6K\n"); exit(1); }
  va_start_long(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long a6 = va_arg_long(alist);
  K b = va_arg_struct(alist, K);
  long c = va_arg_long(alist);
  long r = a1 + a2 + a3 + a4 + a5 + a6 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(6*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,a6,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  va_return_long(alist, r);
}}
void f_f17l3L_simulator (void* data, va_alist alist)
{
  if (data != (void*)&f_f17l3L) { fprintf(out,"wrong data for f_f17l3L\n"); exit(1); }
  va_start_float(alist);
 {float a = va_arg_float(alist);
  float b = va_arg_float(alist);
  float c = va_arg_float(alist);
  float d = va_arg_float(alist);
  float e = va_arg_float(alist);
  float f = va_arg_float(alist);
  float g = va_arg_float(alist);
  float h = va_arg_float(alist);
  float i = va_arg_float(alist);
  float j = va_arg_float(alist);
  float k = va_arg_float(alist);
  float l = va_arg_float(alist);
  float m = va_arg_float(alist);
  float n = va_arg_float(alist);
  float o = va_arg_float(alist);
  float p = va_arg_float(alist);
  float q = va_arg_float(alist);
  long s = va_arg_long(alist);
  long t = va_arg_long(alist);
  long u = va_arg_long(alist);
  L z = va_arg_struct(alist, L);
  float r = a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+s+t+u+z.l1+z.l2+z.l3+z.l4+z.l5+z.l6;
  fprintf(out,"float f(17*float,3*int,L):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,u,z.l1,z.l2,z.l3,z.l4,z.l5,z.l6);
  fflush(out);
  va_return_float(alist, r);
}}
void d_d17l3L_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_d17l3L) { fprintf(out,"wrong data for d_d17l3L\n"); exit(1); }
  va_start_double(alist);
 {double a = va_arg_double(alist);
  double b = va_arg_double(alist);
  double c = va_arg_double(alist);
  double d = va_arg_double(alist);
  double e = va_arg_double(alist);
  double f = va_arg_double(alist);
  double g = va_arg_double(alist);
  double h = va_arg_double(alist);
  double i = va_arg_double(alist);
  double j = va_arg_double(alist);
  double k = va_arg_double(alist);
  double l = va_arg_double(alist);
  double m = va_arg_double(alist);
  double n = va_arg_double(alist);
  double o = va_arg_double(alist);
  double p = va_arg_double(alist);
  double q = va_arg_double(alist);
  long s = va_arg_long(alist);
  long t = va_arg_long(alist);
  long u = va_arg_long(alist);
  L z = va_arg_struct(alist, L);
  double r = a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+s+t+u+z.l1+z.l2+z.l3+z.l4+z.l5+z.l6;
  fprintf(out,"double f(17*double,3*int,L):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,u,z.l1,z.l2,z.l3,z.l4,z.l5,z.l6);
  fflush(out);
  va_return_double(alist, r);
}}
void ll_l2ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l2ll) { fprintf(out,"wrong data for ll_l2ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2) + b + c;
  fprintf(out,"long long f(2*long,long long,long):(%ld,%ld,0x%lx%08lx,%ld)",a1,a2,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_l3ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l3ll) { fprintf(out,"wrong data for ll_l3ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2 + a3) + b + c;
  fprintf(out,"long long f(3*long,long long,long):(%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_l4ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l4ll) { fprintf(out,"wrong data for ll_l4ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2 + a3 + a4) + b + c;
  fprintf(out,"long long f(4*long,long long,long):(%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_l5ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l5ll) { fprintf(out,"wrong data for ll_l5ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2 + a3 + a4 + a5) + b + c;
  fprintf(out,"long long f(5*long,long long,long):(%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_l6ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l6ll) { fprintf(out,"wrong data for ll_l6ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long a6 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
  fprintf(out,"long long f(6*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void ll_l7ll_simulator (void* data, va_alist alist)
{
  if (data != (void*)&ll_l7ll) { fprintf(out,"wrong data for ll_l7ll\n"); exit(1); }
  va_start_longlong(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long a6 = va_arg_long(alist);
  long a7 = va_arg_long(alist);
  long long b = va_arg_longlong(alist);
  long c = va_arg_long(alist);
  long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
  fprintf(out,"long long f(7*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,a7,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  va_return_longlong(alist, r);
}}
void d_l2d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l2d) { fprintf(out,"wrong data for d_l2d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2) + b + c;
  fprintf(out,"double f(2*long,double,long):(%ld,%ld,%g,%ld)",a1,a2,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void d_l3d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l3d) { fprintf(out,"wrong data for d_l3d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2 + a3) + b + c;
  fprintf(out,"double f(3*long,double,long):(%ld,%ld,%ld,%g,%ld)",a1,a2,a3,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void d_l4d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l4d) { fprintf(out,"wrong data for d_l4d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2 + a3 + a4) + b + c;
  fprintf(out,"double f(4*long,double,long):(%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void d_l5d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l5d) { fprintf(out,"wrong data for d_l5d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2 + a3 + a4 + a5) + b + c;
  fprintf(out,"double f(5*long,double,long):(%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void d_l6d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l6d) { fprintf(out,"wrong data for d_l6d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long a6 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
  fprintf(out,"double f(6*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,b,c);
  fflush(out);
  va_return_double(alist, r);
}}
void d_l7d_simulator (void* data, va_alist alist)
{
  if (data != (void*)&d_l7d) { fprintf(out,"wrong data for d_l7d\n"); exit(1); }
  va_start_double(alist);
 {long a1 = va_arg_long(alist);
  long a2 = va_arg_long(alist);
  long a3 = va_arg_long(alist);
  long a4 = va_arg_long(alist);
  long a5 = va_arg_long(alist);
  long a6 = va_arg_long(alist);
  long a7 = va_arg_long(alist);
  double b = va_arg_double(alist);
  long c = va_arg_long(alist);
  double r = (double) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
  fprintf(out,"double f(7*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,a7,b,c);
  fflush(out);
  va_return_double(alist, r);
}}


/*
 * The way we run these tests - first call the function directly, then
 * through vacall() - there is the danger that arguments or results seem
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

int main (void)
{
  callback_t callback;

  out = stdout;

  /* void tests */
  v_v();
  clear_traces();
  callback = alloc_callback(&v_v_simulator,(void*)&v_v);
  ((void (*) (void)) callback) ();

  /* int tests */
  { int ir;

    ir = i_v();
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_v_simulator,(void*)&i_v);
    ir = ((int (*) (void)) callback) ();
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i(i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i_simulator,(void*)&i_i);
    ir = ((int (*) (int)) callback) (i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i2(i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i2_simulator,(void*)&i_i2);
    ir = ((int (*) (int,int)) callback) (i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i4(i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i4_simulator,(void*)&i_i4);
    ir = ((int (*) (int,int,int,int)) callback) (i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i8(i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i8_simulator,(void*)&i_i8);
    ir = ((int (*) (int,int,int,int,int,int,int,int)) callback) (i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i16(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    callback = alloc_callback(&i_i16_simulator,(void*)&i_i16);
    ir = ((int (*) (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)) callback) (i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
  }

  /* float tests */
  { float fr;

    fr = f_f(f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f_simulator,(void*)&f_f);
    fr = ((float (*) (float)) callback) (f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f2(f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f2_simulator,(void*)&f_f2);
    fr = ((float (*) (float,float)) callback) (f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f4(f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f4_simulator,(void*)&f_f4);
    fr = ((float (*) (float,float,float,float)) callback) (f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f8(f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f8_simulator,(void*)&f_f8);
    fr = ((float (*) (float,float,float,float,float,float,float,float)) callback) (f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f16(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f16_simulator,(void*)&f_f16);
    fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f24(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f24_simulator,(void*)&f_f24);
    fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24);
    fprintf(out,"->%g\n",fr);
    fflush(out);
  }

  /* double tests */
  { double dr;

    dr = d_d(d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d_simulator,(void*)&d_d);
    dr = ((double (*) (double)) callback) (d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d2(d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d2_simulator,(void*)&d_d2);
    dr = ((double (*) (double,double)) callback) (d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d4(d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d4_simulator,(void*)&d_d4);
    dr = ((double (*) (double,double,double,double)) callback) (d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d8(d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d8_simulator,(void*)&d_d8);
    dr = ((double (*) (double,double,double,double,double,double,double,double)) callback) (d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d16(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d16_simulator,(void*)&d_d16);
    dr = ((double (*) (double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  /* pointer tests */
  { void* vpr;

    vpr = vp_vpdpcpsp(&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%p\n",vpr);
    fflush(out);
    vpr = 0; clear_traces();
    callback = alloc_callback(&vp_vpdpcpsp_simulator,(void*)&vp_vpdpcpsp);
    vpr = ((void* (*) (void*,double*,char*,Int*)) callback) (&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%p\n",vpr);
    fflush(out);
  }

  /* mixed number tests */
  { uchar ucr;
    ushort usr;
    float fr;
    double dr;
    long long llr;

    ucr = uc_ucsil(uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);
    ucr = 0; clear_traces();
    callback = alloc_callback(&uc_ucsil_simulator,(void*)&uc_ucsil);
    ucr = ((uchar (*) (uchar,ushort,uint,ulong)) callback) (uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);

    dr = d_iidd(i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_iidd_simulator,(void*)&d_iidd);
    dr = ((double (*) (int,int,double,double)) callback) (i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_iiidi(i1,i2,i3,d4,i5);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_iiidi_simulator,(void*)&d_iiidi);
    dr = ((double (*) (int,int,int,double,int)) callback) (i1,i2,i3,d4,i5);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_idid(i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_idid_simulator,(void*)&d_idid);
    dr = ((double (*) (int,double,int,double)) callback) (i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_fdi(f1,d2,i3);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_fdi_simulator,(void*)&d_fdi);
    dr = ((double (*) (float,double,int)) callback) (f1,d2,i3);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    usr = us_cdcd(c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);
    usr = 0; clear_traces();
    callback = alloc_callback(&us_cdcd_simulator,(void*)&us_cdcd);
    usr = ((ushort (*) (char,double,char,double)) callback) (c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);

    llr = ll_iiilli(i1,i2,i3,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_iiilli_simulator,(void*)&ll_iiilli);
    llr = ((long long (*) (int,int,int,long long,int)) callback) (i1,i2,i3,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_flli(f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_flli_simulator,(void*)&ll_flli);
    llr = ((long long (*) (float,long long,int)) callback) (f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    fr = f_fi(f1,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_fi_simulator,(void*)&f_fi);
    fr = ((float (*) (float,int)) callback) (f1,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f2i(f1,f2,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f2i_simulator,(void*)&f_f2i);
    fr = ((float (*) (float,float,int)) callback) (f1,f2,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f3i(f1,f2,f3,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f3i_simulator,(void*)&f_f3i);
    fr = ((float (*) (float,float,float,int)) callback) (f1,f2,f3,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f4i(f1,f2,f3,f4,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f4i_simulator,(void*)&f_f4i);
    fr = ((float (*) (float,float,float,float,int)) callback) (f1,f2,f3,f4,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f7i(f1,f2,f3,f4,f5,f6,f7,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f7i_simulator,(void*)&f_f7i);
    fr = ((float (*) (float,float,float,float,float,float,float,int)) callback) (f1,f2,f3,f4,f5,f6,f7,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f8i(f1,f2,f3,f4,f5,f6,f7,f8,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f8i_simulator,(void*)&f_f8i);
    fr = ((float (*) (float,float,float,float,float,float,float,float,int)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f12i(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f12i_simulator,(void*)&f_f12i);
    fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,int)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f13i(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f13i_simulator,(void*)&f_f13i);
    fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,int)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,i9);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    dr = d_di(d1,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_di_simulator,(void*)&d_di);
    dr = ((double (*) (double,int)) callback) (d1,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d2i(d1,d2,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d2i_simulator,(void*)&d_d2i);
    dr = ((double (*) (double,double,int)) callback) (d1,d2,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d3i(d1,d2,d3,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d3i_simulator,(void*)&d_d3i);
    dr = ((double (*) (double,double,double,int)) callback) (d1,d2,d3,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d4i(d1,d2,d3,d4,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d4i_simulator,(void*)&d_d4i);
    dr = ((double (*) (double,double,double,double,int)) callback) (d1,d2,d3,d4,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d7i(d1,d2,d3,d4,d5,d6,d7,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d7i_simulator,(void*)&d_d7i);
    dr = ((double (*) (double,double,double,double,double,double,double,int)) callback) (d1,d2,d3,d4,d5,d6,d7,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d8i(d1,d2,d3,d4,d5,d6,d7,d8,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d8i_simulator,(void*)&d_d8i);
    dr = ((double (*) (double,double,double,double,double,double,double,double,int)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d12i(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d12i_simulator,(void*)&d_d12i);
    dr = ((double (*) (double,double,double,double,double,double,double,double,double,double,double,double,int)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d13i(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d13i_simulator,(void*)&d_d13i);
    dr = ((double (*) (double,double,double,double,double,double,double,double,double,double,double,double,double,int)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,i9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  /* small structure return tests */
  {
    Size1 r = S1_v();
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S1_v_simulator,(void*)&S1_v);
    r = ((Size1 (*) (void)) callback) ();
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
  }
  {
    Size2 r = S2_v();
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S2_v_simulator,(void*)&S2_v);
    r = ((Size2 (*) (void)) callback) ();
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
  }
  {
    Size3 r = S3_v();
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S3_v_simulator,(void*)&S3_v);
    r = ((Size3 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
  }
  {
    Size4 r = S4_v();
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S4_v_simulator,(void*)&S4_v);
    r = ((Size4 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
  }
  {
    Size7 r = S7_v();
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S7_v_simulator,(void*)&S7_v);
    r = ((Size7 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
  }
  {
    Size8 r = S8_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S8_v_simulator,(void*)&S8_v);
    r = ((Size8 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
  }
  {
    Size12 r = S12_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S12_v_simulator,(void*)&S12_v);
    r = ((Size12 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
  }
  {
    Size15 r = S15_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S15_v_simulator,(void*)&S15_v);
    r = ((Size15 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
  }
  {
    Size16 r = S16_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    callback = alloc_callback(&S16_v_simulator,(void*)&S16_v);
    r = ((Size16 (*) (void)) callback) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
  }

  /* structure tests */
  { Int Ir;
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
    callback = alloc_callback(&I_III_simulator,(void*)&I_III);
    Ir = ((Int (*) (Int,Int,Int)) callback) (I1,I2,I3);
    fprintf(out,"->{%d}\n",Ir.x);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
    Cr = C_CdC(C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);
    Cr.x = '\0'; clear_traces();
    callback = alloc_callback(&C_CdC_simulator,(void*)&C_CdC);
    Cr = ((Char (*) (Char,double,Char)) callback) (C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);

    Fr = F_Ffd(F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);
    Fr.x = 0.0; clear_traces();
    callback = alloc_callback(&F_Ffd_simulator,(void*)&F_Ffd);
    Fr = ((Float (*) (Float,float,double)) callback) (F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);

    Dr = D_fDd(f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
    Dr.x = 0.0; clear_traces();
    callback = alloc_callback(&D_fDd_simulator,(void*)&D_fDd);
    Dr = ((Double (*) (float,Double,double)) callback) (f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);

    Dr = D_Dfd(D1,f2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
    Dr.x = 0.0; clear_traces();
    callback = alloc_callback(&D_Dfd_simulator,(void*)&D_Dfd);
    Dr = ((Double (*) (Double,float,double)) callback) (D1,f2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
#endif

    Jr = J_JiJ(J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);
    Jr.l1 = Jr.l2 = 0; clear_traces();
    callback = alloc_callback(&J_JiJ_simulator,(void*)&J_JiJ);
    Jr = ((J (*) (J,int,J)) callback) (J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
#ifndef SKIP_T
    Tr = T_TcT(T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
    Tr.c[0] = Tr.c[1] = Tr.c[2] = 0; clear_traces();
    callback = alloc_callback(&T_TcT_simulator,(void*)&T_TcT);
    Tr = ((T (*) (T,char,T)) callback) (T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
#endif

#ifndef SKIP_X
    Xr = X_BcdB(B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
    Xr.c[0]=Xr.c1='\0'; clear_traces();
    callback = alloc_callback(&X_BcdB_simulator,(void*)&X_BcdB);
    Xr = ((X (*) (B,char,double,B)) callback) (B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
#endif
#endif
  }

  /* gpargs boundary tests */
  { long lr;
    long long llr;
    float fr;
    double dr;

    lr = l_l0K(K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l0K_simulator,(void*)l_l0K);
    lr = ((long (*) (K,long)) callback) (K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l1K(l1,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l1K_simulator,(void*)l_l1K);
    lr = ((long (*) (long,K,long)) callback) (l1,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l2K(l1,l2,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l2K_simulator,(void*)l_l2K);
    lr = ((long (*) (long,long,K,long)) callback) (l1,l2,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l3K(l1,l2,l3,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l3K_simulator,(void*)l_l3K);
    lr = ((long (*) (long,long,long,K,long)) callback) (l1,l2,l3,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l4K(l1,l2,l3,l4,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l4K_simulator,(void*)l_l4K);
    lr = ((long (*) (long,long,long,long,K,long)) callback) (l1,l2,l3,l4,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l5K(l1,l2,l3,l4,l5,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l5K_simulator,(void*)l_l5K);
    lr = ((long (*) (long,long,long,long,long,K,long)) callback) (l1,l2,l3,l4,l5,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l6K(l1,l2,l3,l4,l5,l6,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    callback = alloc_callback(&l_l6K_simulator,(void*)l_l6K);
    lr = ((long (*) (long,long,long,long,long,long,K,long)) callback) (l1,l2,l3,l4,l5,l6,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    fr = f_f17l3L(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,l6,l7,l8,L1);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    callback = alloc_callback(&f_f17l3L_simulator,(void*)&f_f17l3L);
    fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,long,long,long,L)) callback) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,l6,l7,l8,L1);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    dr = d_d17l3L(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,l6,l7,l8,L1);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_d17l3L_simulator,(void*)&d_d17l3L);
    dr = ((double (*) (double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,long,long,long,L)) callback) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,l6,l7,l8,L1);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    llr = ll_l2ll(l1,l2,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l2ll_simulator,(void*)ll_l2ll);
    llr = ((long long (*) (long,long,long long,long)) callback) (l1,l2,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l3ll(l1,l2,l3,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l3ll_simulator,(void*)ll_l3ll);
    llr = ((long long (*) (long,long,long,long long,long)) callback) (l1,l2,l3,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l4ll(l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l4ll_simulator,(void*)ll_l4ll);
    llr = ((long long (*) (long,long,long,long,long long,long)) callback) (l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l5ll(l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l5ll_simulator,(void*)ll_l5ll);
    llr = ((long long (*) (long,long,long,long,long,long long,long)) callback) (l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l6ll(l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l6ll_simulator,(void*)ll_l6ll);
    llr = ((long long (*) (long,long,long,long,long,long,long long,long)) callback) (l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l7ll(l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    callback = alloc_callback(&ll_l7ll_simulator,(void*)ll_l7ll);
    llr = ((long long (*) (long,long,long,long,long,long,long,long long,long)) callback) (l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    dr = d_l2d(l1,l2,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l2d_simulator,(void*)d_l2d);
    dr = ((double (*) (long,long,double,long)) callback) (l1,l2,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l3d(l1,l2,l3,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l3d_simulator,(void*)d_l3d);
    dr = ((double (*) (long,long,long,double,long)) callback) (l1,l2,l3,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l4d(l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l4d_simulator,(void*)d_l4d);
    dr = ((double (*) (long,long,long,long,double,long)) callback) (l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l5d(l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l5d_simulator,(void*)d_l5d);
    dr = ((double (*) (long,long,long,long,long,double,long)) callback) (l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l6d(l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l6d_simulator,(void*)d_l6d);
    dr = ((double (*) (long,long,long,long,long,long,double,long)) callback) (l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l7d(l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    callback = alloc_callback(&d_l7d_simulator,(void*)d_l7d);
    dr = ((double (*) (long,long,long,long,long,long,long,double,long)) callback) (l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  exit(0);
}
