/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include "dogen/utility/xml/node_types_io.hpp"
#include "dogen/utility/xml/text_reader_io.hpp"

namespace dogen {
namespace utility {
namespace xml {

std::ostream& operator<<(std::ostream& stream, const text_reader& value) {
    boost::io::ios_flags_saver ifs(stream);

    stream << std::boolalpha;
    return stream << "\"text_reader\": {"
                  << "\"file_name\": \"" << value.file_name().string() << "\","
                  << "\"node_name\": \"" << value.name() << "\","
                  << "\"has_value\": " << value.has_value() << ","
                  << "\"value\": \"" << value.value_as_string() << "\","
                  << "\"type\": \"" << value.node_type() << "\""
                  << " }";
}

} } }
