/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/hex_dumper_io.hpp"

namespace dogen {
namespace utility {
namespace streaming {

void
hex_dumper(std::ostream& stream, const char* buffer, const unsigned int size) {
    boost::io::ios_all_saver saver(stream);

    const unsigned int chars_per_line(16);
    unsigned char printable_str[chars_per_line + 1];
    printable_str[chars_per_line] = 0;
    unsigned int line_no(0);

    for(unsigned int i(0); i < size; ++i) {
        // if we're on the very first character, output the line
        // number details before anything else.
        if (!i) {
            stream << std::setw(8) << std::setfill('0')
                   << std::hex << line_no++ << ": ";
        }

        const unsigned int c((unsigned int)(unsigned char)buffer[i]);
        stream << std::setw(2) << std::setfill('0') << std::hex << c << " ";
        if (c < 32 || c > 126) {
            printable_str[i % chars_per_line] = '.';
        } else {
            printable_str[i % chars_per_line] = c;
        }

        // if we're on a multiple of 16 other than zero (well, of 15
        // as we are zero-based), we have reached EOL so we need to
        // write out the printable string buffer.
        const bool atEol((i % chars_per_line) == (chars_per_line - 1));
        if (i && atEol) {
            stream << "  " << printable_str << std::endl;

            // output the next line number, unless we're on the last line.
            if (i != size - 1)
            {
                stream << std::setw(8) << std::setfill('0')
                       << std::hex << line_no++ << ": ";
            }
        }
    }

    const unsigned int remainder(chars_per_line - (size % chars_per_line));
    if (remainder != chars_per_line)
    {
        // if we didn't end on a multiple of 16, pad the hexadecimal
        // print and clear up any trailing characters on the printable
        // string buffer.
        for(unsigned int i(0); i < remainder; ++i) {
            printable_str[chars_per_line - 1 - i] = ' ';
            stream << "   ";
        }
        stream << "  " << printable_str << std::endl;
    }
}

} } }
