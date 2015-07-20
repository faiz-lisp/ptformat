/*
 * Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	FILE *fp;
	unsigned char c0;
	unsigned char c1;
	unsigned char xor[256];
	unsigned char ct;
	unsigned char px;
	unsigned char lutseenwild[256] = {
		//	0  1  2  3  4  5  6  7   8  9  a  b  c  d  e  f
			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1,  0, 0, 0, 1, 0, 1, 0, 1,
			0, 0, 0, 1, 0, 1, 0, 1,  0, 0, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 0, 0, 0, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,

			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 0, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 0, 0, 1, 0, 0,
			0, 1, 0, 1, 0, 1, 0, 0,  0, 1, 0, 1, 0, 1, 0, 1,

			0, 1, 0, 1, 0, 0, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 0,  0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 0, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,

			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 1,
			0, 1, 0, 1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 0, 0,
			0, 1, 0, 1, 0, 0, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
			0, 1, 0, 0, 0, 1, 0, 0,  0, 1, 0, 1, 0, 1, 0, 0,
	};

	unsigned char lut[256][64] = {
	/*00 */	{},
	/*01 */	{
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*02 */	{},
	/*03 */	{
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*04 */	{},
	/*05 */	{
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*06 */	{},
	/*07 */	{
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*08 */	{},
	/*09 */	{
			1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
		},
	/*0a */	{},
	/*0b */	{
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		},
	/*0c */	{},
	/*0d */	{
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		},
	/*0e */	{},
	/*0f */	{
			3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		},
	/*10 */	{},
	/*11 */	{
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			3, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		},
	/*12 */	{},
	/*13 */	{
			3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 3, 3, 1, 1, 1, 3, 1, 1, 3, 1,
		},
	/*14 */	{},
	/*15 */	{
			1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		},
	/*16 */	{},
	/*17 */	{
			3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
			1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		},
	/*18 */	{},
	/*19 */	{},
	/*1a */	{},
	/*1b */	{
			3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
			3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
			3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
		},
	/*1c */	{},
	/*1d */	{
			1, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
		},
	/*1e */	{},
	/*1f */	{
			3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		},
	/*20 */	{},
	/*21 */	{},
	/*22 */	{},
	/*23 */	{
			3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
		},
	/*24 */	{},
	/*25 */	{
			1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
			3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
			3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
		},
	/*26 */	{},
	/*27 */	{
			3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		},
	/*28 */	{},
	/*29 */	{},
	/*2a */	{},
	/*2b */	{
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		},
	/*2c */	{},
	/*2d */	{
			1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		},
	/*2e */	{},
	/*2f */	{
			3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		},
	/*30 */	{},
	/*31 */	{
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		},
	/*32 */	{},
	/*33 */	{},
	/*34 */	{},
	/*35 */	{},
	/*36 */	{},
	/*37 */	{
			3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
		},
	/*38 */	{},
	/*39 */	{
			1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*3a */	{},
	/*3b */	{
			3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*3c */	{},
	/*3d */	{
			1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*3e */	{},
	/*3f */	{
			3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*40 */	{},
	/*41 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*42 */	{},
	/*43 */	{
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*44 */	{},
	/*45 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*46 */	{},
	/*47 */	{
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*48 */	{},
	/*49 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
		},
	/*4a */	{},
	/*4b */	{
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
			3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
			3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		},
	/*4c */	{},
	/*4d */	{},
	/*4e */	{},
	/*4f */	{
			3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		},
	/*50 */	{},
	/*51 */	{
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		},
	/*52 */	{},
	/*53 */	{
			3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		},
	/*54 */	{},
	/*55 */	{
			1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		},
	/*56 */	{},
	/*57 */	{
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
			1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		},
	/*58 */	{},
	/*59 */	{
			1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		},
	/*5a */	{},
	/*5b */	{},
	/*5c */	{},
	/*5d */	{
			1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
		},
	/*5e */	{},
	/*5f */	{
			3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		},
	/*60 */	{},
	/*61 */	{
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		},
	/*62 */	{},
	/*63 */	{
			3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
		},
	/*64 */	{},
	/*65 */	{
			1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
			3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
			3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
		},
	/*66 */	{},
	/*67 */	{
			3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
			1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		},
	/*68 */	{},
	/*69 */	{
			1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
			1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		},
	/*6a */	{},
	/*6b */	{},
	/*6c */	{},
	/*6d */	{
			1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		},
	/*6e */	{},
	/*6f */	{},
	/*70 */	{},
	/*71 */	{
			1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		},
	/*72 */	{},
	/*73 */	{
			3, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 1,
		},
	/*74 */	{},
	/*75 */	{
			1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		},
	/*76 */	{},
	/*77 */	{},
	/*78 */	{},
	/*79 */	{
			1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*7a */	{},
	/*7b */	{
			3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*7c */	{},
	/*7d */	{
			1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 3, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*7e */	{},
	/*7f */	{
			3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*80 */	{},
	/*81 */	{
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*82 */	{},
	/*83 */	{
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*84 */	{},
	/*85 */	{},
	/*86 */	{},
	/*87 */	{
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*88 */	{},
	/*89 */	{
			1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 3,
		},
	/*8a */	{},
	/*8b */	{
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		},
	/*8c */	{},
	/*8d */	{
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 3, 1, 3,
		},
	/*8e */	{},
	/*8f */	{
			3, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		},
	/*90 */	{},
	/*91 */	{
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		},
	/*92 */	{},
	/*93 */	{
			3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
		},
	/*94 */	{},
	/*95 */	{
			1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		},
	/*96 */	{},
	/*97 */	{},
	/*98 */	{},
	/*99 */	{
			1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
			1, 3, 3, 1, 3, 3, 1 ,3, 3, 1, 1, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		},
	/*9a */	{},
	/*9b */	{
			3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1,
			3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
			3, 1, 1, 3, 1, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1,
		},
	/*9c */	{},
	/*9d */	{
			1, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
		},
	/*9e */	{},
	/*9f */	{
			3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		},
	/*a0 */	{},
	/*a1 */	{
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
		},
	/*a2 */	{},
	/*a3 */	{},
	/*a4 */	{},
	/*a5 */	{
			1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
			3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
			3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
		},
	/*a6 */	{},
	/*a7 */	{
			3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 3, 1, 3, 3, 3, 1,
			1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		},
	/*a8 */	{},
	/*a9 */	{
			1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
			1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		},
	/*aa */	{},
	/*ab */	{
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		},
	/*ac */	{},
	/*ad */	{
			1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		},
	/*ae */	{},
	/*af */	{
			3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		},
	/*b0 */	{},
	/*b1 */	{
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		},
	/*b2 */	{},
	/*b3 */	{
			3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		},
	/*b4 */	{},
	/*b5 */	{
			1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
			3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
			3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		},
	/*b6 */	{},
	/*b7 */	{
			3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
		},
	/*b8 */	{},
	/*b9 */	{
			1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*ba */	{},
	/*bb */	{
			3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*bc */	{},
	/*bd */	{
			1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*be */	{},
	/*bf */	{
			3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*c0 */	{},
	/*c1 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*c2 */	{},
	/*c3 */	{
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*c4 */	{},
	/*c5 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		},
	/*c6 */	{},
	/*c7 */	{
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		},
	/*c8 */	{},
	/*c9 */	{
			1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1,
		},
	/*ca */	{},
	/*cb */	{
			3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,
			3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3,
			3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
		},
	/*cc */	{},
	/*cd */	{
			1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3,
			3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3,
			3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1,
		},
	/*ce */	{},
	/*cf */	{
			3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
		},
	/*d0 */	{},
	/*d1 */	{
			1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3,
			1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1,
			1, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1,
		},
	/*d2 */	{},
	/*d3 */	{
			3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3,
		},
	/*d4 */	{},
	/*d5 */	{
			1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
			3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1,
		},
	/*d6 */	{},
	/*d7 */	{
			3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1,
			1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3,
			1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3,
		},
	/*d8 */	{},
	/*d9 */	{
			1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3,
			1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 3, 1,
			1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
		},
	/*da */	{},
	/*db */	{
			3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3,
			3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 1,
			3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3,
		},
	/*dc */	{},
	/*dd */	{
			1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1,
		},
	/*de */	{},
	/*df */	{},
	/*e0 */	{},
	/*e1 */	{
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1,
		},
	/*e2 */	{},
	/*e3 */	{
			3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1,
			3, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 1, 1, 3,
		},
	/*e4 */	{},
	/*e5 */	{},
	/*e6 */	{},
	/*e7 */	{
			3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1,
			1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1, 3, 1, 1, 3,
		},
	/*e8 */	{},
	/*e9 */	{
			1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 3,
			1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1,
			1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
		},
	/*ea */	{},
	/*eb */	{
			3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
			3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1,
			3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3,
		},
	/*ec */	{},
	/*ed */	{},
	/*ee */	{},
	/*ef */	{
			3, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
		},
	/*f0 */	{},
	/*f1 */	{
			1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3,
			1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3,
			1, 3, 1, 3, 3, 1, 3, 1, 1, 3, 1, 3, 3, 1, 3, 1,
		},
	/*f2 */	{},
	/*f3 */	{},
	/*f4 */	{},
	/*f5 */	{
			1, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1,
			3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1,
			3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1,
		},
	/*f6 */	{},
	/*f7 */	{},
	/*f8 */	{},
	/*f9 */	{
			1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*fa */	{},
	/*fb */	{
			3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
		},
	/*fc */	{},
	/*fd */	{
			1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3,
			1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 3, 1, 3, 1,
			3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
		},
	/*fe */	{},
	/*ff */	{}
	};

	uint16_t i;
	int j;
	int li;
	int len;
	unsigned char message;
	int blocks;
	int bl;

	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0x40, SEEK_SET);
	fread(&c0, 1, 1, fp);
	fread(&c1, 1, 1, fp);
	i = 2;

	fseek(fp, 0x0, SEEK_SET);

	int count = 0;
	for (i = 0; i < 256; i++) {
		if (lutseenwild[i]) {
			count++;
		}
	}
	fprintf(stderr, "Total tables reversed: %d out of 128\n", count);

	switch (c0) {
	case 0x00:
		fprintf(stderr, "Success! easy one\n");
		xor[0] = c0;
		xor[1] = c1;
		for (i = 2; i < 64; i++) {
			xor[i] = (xor[i-1] + c1 - c0) & 0xff;
		}
		
		px = xor[0];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		printf("%c", message);

		px  = xor[1];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		printf("%c", message);

		i = 2;
		while (fread(&ct, 1, 1, fp) != 0) {
			if (i%64 == 0) {
				i = 0;
			}
			message = xor[i] ^ ct;
			printf("%c", message);
			i++;
		}
		break;
	case 0x80:
		fprintf(stderr, "Success! easy two\n");
		xor[0] = c0;
		xor[1] = c1;
		for (i = 2; i < 256; i++) {
			if (i%64 == 0) {
				xor[i] = c0;
			} else {
				xor[i] = ((xor[i-1] + c1 - c0) & 0xff);
			}
		}
		
		for (i = 0; i < 64; i++) {
			xor[i] ^= 0x80;
		}
		for (i = 128; i < 192; i++) {
			xor[i] ^= 0x80;
		}

		px = xor[0];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		printf("%c", message);

		px  = xor[1];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		printf("%c", message);

		i = 2;
		while (fread(&ct, 1, 1, fp) != 0) {
			if (i%256 == 0) {
				i = 0;
			}
			message = xor[i] ^ ct;
			printf("%c", message);
			i++;
		}
		break;
		
	case 0x40:
	case 0xc0:
		li = c1;
		if (lutseenwild[li]) {
			fprintf(stderr, "Success! Found lookup table 0x%x\n", li);
		} else {
			fprintf(stderr, "Can't find lookup table for c1=0x%x\n", li);
		}
		xor[0] = c0;
		xor[1] = c1;
		for (i = 2; i < 256; i++) {
			if (i%64 == 0) {
				xor[i] = c0;
			} else {
				xor[i] = ((xor[i-1] + c1 - c0) & 0xff);
			}
		}
		
		if (lutseenwild[li]) {
			for (i = 0; i < 64; i++) {
				xor[i] ^= (lut[li][i] * 0x40);
			}

			int inv = 0;
			for (i = 128; i < 192; i++) {
				inv = (lut[li][i-128] == 3) ? 1 : 3;
				xor[i] ^= (inv * 0x40);
			}
	
			for (i = 192; i < 256; i++) {
				xor[i] ^= 0x80;
			}
		}

		px = xor[0];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		if (lutseenwild[li]) {
			printf("%c", message);
		} else {
			printf("%02x ", message);
		}
		px  = xor[1];
		fread(&ct, 1, 1, fp);
		message = px ^ ct;
		if (lutseenwild[li]) {
			printf("%c", message);
		} else {
			printf("%02x ", message);
		}

		i = 2;
		j = 3;
		while (fread(&ct, 1, 1, fp) != 0) {
			if (i%256 == 0) {
				i = 0;
			}
			message = xor[i] ^ ct;
			if (lutseenwild[li]) {
				printf("%c", message);
			} else {
				printf("%02x ", message);
				if (j%16 == 0) {
					printf("\n");
					j = 0;
				}
			}
			i++;
			j++;
		}
		break;
	default:
		fprintf(stderr, "Failed c[0] c[1]: %02x %02x\n", c0, c1);
	}
		
	fclose(fp);
	return 0;
}


