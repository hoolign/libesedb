/*
 * The page definition of an Extensible Storage Engine (ESE) Database File (EDB)
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _ESEDB_PAGE_H )
#define _ESEDB_PAGE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct esedb_page_header esedb_page_header_t;

struct esedb_page_header
{
	/* The XOR checksum
	 * A XOR-32 checksum calcalted over the bytes
	 * from offset 4 to end of the page
	 * with an initial value of 0x89abcdef
	 *
	 * This values was changed in Exchange 2003 SP1
	 * A XOR-32 checksum calcalted over the bytes
	 * from offset 8 to end of the page
	 * with an initial value of the page number
	 *
	 * Consists of 4 bytes
	 */
	uint8_t xor_checksum[ 4 ];

	/* The page number
	 *
	 * This values was changed in Exchange 2003 SP1
	 * to the ECC checksum
	 *
	 * Consists of 4 bytes
	 */
	union
	{
		uint8_t page_number[ 4 ];
		uint8_t ecc_checksum[ 4 ];
	};

	/* The last modification time
	 * Consists of 8 bytes
	 * Contains a database time structure
	 */
	uint8_t modification_time[ 8 ];

	/* The previous page number
	 * Consists of 4 bytes
	 */
	uint8_t previous_page[ 4 ];

	/* The next page number
	 * Consists of 4 bytes
	 */
	uint8_t next_page[ 4 ];

	/* The father object identifier
	 * Consists of 4 bytes
	 */
	uint8_t father_object_identifier[ 4 ];

	/* The available data size
	 * Consists of 2 bytes
	 */
	uint8_t available_data_size[ 2 ];

	/* The available uncommitted data size
	 * Consists of 2 bytes
	 */
	uint8_t available_uncommitted_data_size[ 2 ];

	/* The first available data offset
	 * Consists of 2 bytes
	 */
	uint8_t available_data_offset[ 2 ];

	/* The first available page tag
	 * Consists of 2 bytes
	 */
	uint8_t available_page_tag[ 2 ];

	/* The page flags
	 * Consists of 4 bytes
	 */
	uint8_t page_flags[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif

