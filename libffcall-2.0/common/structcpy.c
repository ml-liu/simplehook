/* copy structs */

/*
 * Copyright 1995-2005 Bruno Haible <bruno@clisp.org>
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

void __structcpy (void* dest, const void* src, unsigned long size, unsigned long alignment)
{
  if (alignment % sizeof(long))
    { char* d = (char*)dest;
      const char* s = (const char*)src;
      do { *d++ = *s++; } while (--size > 0);
    }
  else
    /* If the alignment is a multiple of sizeof(long), the size is as well. */
    { long* d = (long*)dest;
      const long* s = (const long*)src;
      do { *d++ = *s++; } while ((size -= sizeof(long)) > 0);
    }
}
