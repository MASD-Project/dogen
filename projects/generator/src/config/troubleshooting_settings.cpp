/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/generator/config/troubleshooting_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream& operator<<(std::ostream& stream, troubleshooting_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    stream << "\"troubleshooting_settings\": { "
           << "\"verbose\": " << value.verbose() << ", "
           << "\"debug_dir\": " << value.debug_dir() << ", "
           << "\"save_dia_model\": " << value.save_dia_model() << ", "
           << "\"save_sml_model\": " << value.save_sml_model() << ", "
           << "\"stop_after_formatting\": "
           << value.stop_after_formatting() << ", "
           << "\"stop_after_merging\": " << value.stop_after_merging()
           << " }";

    return stream;
}

} } }
