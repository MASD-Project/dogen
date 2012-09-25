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
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/layer_io.hpp"

namespace dogen {
namespace dia {

std::ostream& operator<<(std::ostream& stream, dogen::dia::layer layer) {
    boost::io::ios_flags_saver ifs(stream);

    stream << std::boolalpha;
    stream << "\"layer\": {"
           << " \"name\": \"" << layer.name() << "\","
           << " \"visible\": "  << layer.visible() << ","
           << " \"active\": " << layer.active() << ","
           << " \"objects\":" << layer.objects()
           << " }";
    return(stream);
}

} }
