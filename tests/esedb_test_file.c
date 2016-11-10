/*
 * Library file type testing program
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "esedb_test_libcerror.h"
#include "esedb_test_libclocale.h"
#include "esedb_test_libcsystem.h"
#include "esedb_test_libesedb.h"
#include "esedb_test_libuna.h"
#include "esedb_test_macros.h"
#include "esedb_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make esedb_test_file generate verbose output
#define ESEDB_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int esedb_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "esedb_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int esedb_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "esedb_test_file_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int esedb_test_file_open_source(
     libesedb_file_t **file,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "esedb_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libesedb_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libesedb_file_open_wide(
	          *file,
	          source,
	          LIBESEDB_OPEN_READ,
	          error );
#else
	result = libesedb_file_open(
	          *file,
	          source,
	          LIBESEDB_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libesedb_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int esedb_test_file_close_source(
     libesedb_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "esedb_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libesedb_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libesedb_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libesedb_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_file_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libesedb_file_t *file    = NULL;
	int result               = 0;

	/* Test libesedb_file_initialize
	 */
	result = libesedb_file_initialize(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libesedb_file_free(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libesedb_file_initialize(
	          NULL,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = (libesedb_file_t *) 0x12345678UL;

	result = libesedb_file_initialize(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	file = NULL;

#if defined( HAVE_ESEDB_TEST_MEMORY )

	/* Test libesedb_file_initialize with malloc failing
	 */
	esedb_test_malloc_attempts_before_fail = 0;

	result = libesedb_file_initialize(
	          &file,
	          &error );

	if( esedb_test_malloc_attempts_before_fail != -1 )
	{
		esedb_test_malloc_attempts_before_fail = -1;

		if( file != NULL )
		{
			libesedb_file_free(
			 &file,
			 NULL );
		}
	}
	else
	{
		ESEDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		ESEDB_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		ESEDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libesedb_file_initialize with memset failing
	 */
	esedb_test_memset_attempts_before_fail = 0;

	result = libesedb_file_initialize(
	          &file,
	          &error );

	if( esedb_test_memset_attempts_before_fail != -1 )
	{
		esedb_test_memset_attempts_before_fail = -1;

		if( file != NULL )
		{
			libesedb_file_free(
			 &file,
			 NULL );
		}
	}
	else
	{
		ESEDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		ESEDB_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		ESEDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_ESEDB_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libesedb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libesedb_file_free function
 * Returns 1 if successful or 0 if not
 */
int esedb_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libesedb_file_free(
	          NULL,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libesedb_file_open functions
 * Returns 1 if successful or 0 if not
 */
int esedb_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libesedb_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = esedb_test_file_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libesedb_file_initialize(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libesedb_file_open(
	          file,
	          narrow_source,
	          LIBESEDB_OPEN_READ,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libesedb_file_close(
	          file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libesedb_file_free(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libesedb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libesedb_file_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int esedb_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libesedb_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = esedb_test_file_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libesedb_file_initialize(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libesedb_file_open_wide(
	          file,
	          wide_source,
	          LIBESEDB_OPEN_READ,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libesedb_file_close(
	          file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libesedb_file_free(
	          &file,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "file",
         file );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libesedb_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libesedb_file_get_number_of_tables functions
 * Returns 1 if successful or 0 if not
 */
int esedb_test_file_get_number_of_tables(
     libesedb_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_tables     = 0;
	int result               = 0;

	result = libesedb_file_get_number_of_tables(
	          file,
	          &number_of_tables,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ESEDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libesedb_file_get_number_of_tables(
	          NULL,
	          &number_of_tables,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libesedb_file_get_number_of_tables(
	          file,
	          NULL,
	          &error );

	ESEDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ESEDB_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	libesedb_file_t *file      = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( ESEDB_TEST_FILE_VERBOSE )
	libesedb_notify_set_verbose(
	 1 );
	libesedb_notify_set_stream(
	 stderr,
	 NULL );
#endif

	ESEDB_TEST_RUN(
	 "libesedb_file_initialize",
	 esedb_test_file_initialize );

	ESEDB_TEST_RUN(
	 "libesedb_file_free",
	 esedb_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		ESEDB_TEST_RUN_WITH_ARGS(
		 "libesedb_file_open",
		 esedb_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		ESEDB_TEST_RUN_WITH_ARGS(
		 "libesedb_file_open_wide",
		 esedb_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBESEDB_HAVE_BFIO )

		/* TODO add test for libesedb_file_open_file_io_handle */

#endif /* defined( LIBESEDB_HAVE_BFIO ) */

		/* TODO add test for libesedb_file_close */

		/* Initialize test
		 */
		result = esedb_test_file_open_source(
		          &file,
		          source,
		          &error );

		ESEDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        ESEDB_TEST_ASSERT_IS_NOT_NULL(
	         "file",
	         file );

	        ESEDB_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		ESEDB_TEST_RUN_WITH_ARGS(
		 "libesedb_file_get_number_of_tables",
		 esedb_test_file_get_number_of_tables,
		 file );

		/* Clean up
		 */
		result = esedb_test_file_close_source(
		          &file,
		          &error );

		ESEDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		ESEDB_TEST_ASSERT_IS_NULL(
	         "file",
	         file );

	        ESEDB_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		esedb_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

