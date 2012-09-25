/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/sml/domain/model.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/package_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"

namespace dogen {
namespace sml {

bool model::operator==(const model& rhs) const {
    return
        name_ == rhs.name_ &&
        packages_ == rhs.packages_ &&
        pods_ == rhs.pods_ &&
        primitives_ == rhs.primitives_ &&
        external_package_path_ == rhs.external_package_path_ &&
        schema_name_ == rhs.schema_name_;
}

void model::to_stream(std::ostream& stream) const {
    stream << "\"model\": {"
           << "\"name\": \"" << name_ << "\","
           << "\"packages\":" << packages_ << ","
           << "\"pods\":" << pods_ << ","
           << "\"primitives\":" << primitives_
           << "\"external_package_path:" << external_package_path_
           << "\"schema_name:\"" << schema_name_
           << " }";
}

} }
