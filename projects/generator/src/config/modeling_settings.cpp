/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/generator/config/modeling_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, modeling_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    using utility::streaming::jsonify;
    stream << "\"modeling_settings\": { "
           << "\"verbose\":" << value.verbose() << ", "
           << "\"target\": " << value.target() << ", "
           << "\"external_package_path\": \"" << value.external_package_path()
           << "\", "
           << "\"references\": " << value.references() << ", "
           << "\"disable_model_package\": " << value.disable_model_package()
           << " }";

    return stream;
}

} } }
