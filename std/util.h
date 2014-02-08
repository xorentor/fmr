/*
 Copyright (C) Free Mind Foundation 2013
 www.fmf-base.org
 
 authors:
 xorentor

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef UTILS_H
#define UTILS_H

#define ROUND2(x)     (((x)+1)&~1)

#define MAX_CONTENT	8192

struct filebuffer {
	pe_t *e;
	char content[ MAX_CONTENT ];
	int32 length;
};

struct line {
	pe_t *e;
	char *start;
	int32 length;
};

#endif
