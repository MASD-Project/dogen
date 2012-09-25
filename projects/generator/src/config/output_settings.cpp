/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/generator/config/output_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, output_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    stream << "\"output_settings\": { "
           << "\"verbose\":" << value.verbose() << ", "
           << "\"output_to_stdout\": " << value.output_to_stdout() << ", "
           << "\"output_to_file\": " << value.output_to_file() << ", "
           << "\"delete_extra_files\": " << value.delete_extra_files() << ", "
           << "\"force_writes\": " << value.force_write()
           << " }";

    return stream;
}

} } }
