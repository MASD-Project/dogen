/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/generator/config/sql_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, sql_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    stream << "\"sql_settings\": { "
           << "\"verbose\":" << value.verbose() << ", "
           << "\"disable_backend\": " << value.disable_backend() << ", "
           << "\"create_schema\": " << value.create_schema() << ", "
           << "\"schema_name\": \"" << value.schema_name() << "\""
           << " }";

    return stream;
}

} } }
