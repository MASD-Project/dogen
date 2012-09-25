/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/domain/pod.hpp"

namespace dogen {
namespace sml {

bool pod::operator==(const pod& rhs) const {
    return
        name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_;
}

void pod::to_stream(std::ostream& stream) const {
    boost::io::ios_flags_saver ifs(stream);

    stream << std::boolalpha;
    stream << "\"pod\": {"
           << name() << ","
           << "\"properties\":" << properties() << ","
           << parent_name() << ","
           << "\"generate\": " << generate_
           << " }";
}

} }
