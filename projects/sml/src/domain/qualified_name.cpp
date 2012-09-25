/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/io/meta_types_io.hpp"

namespace dogen {
namespace sml {

bool qualified_name::operator==(const qualified_name& rhs) const {
    return
        model_name_ == rhs.model_name_ &&
        external_package_path_ == rhs.external_package_path_ &&
        package_path_ == rhs.package_path_ &&
        type_name_ == rhs.type_name_ &&
        meta_type_ == rhs.meta_type_;
}

void qualified_name::to_stream(std::ostream& stream) const {
    stream << "\"qualified_name\": {"
           << "\"model_name\":\"" << model_name_ << "\", "
           << "\"external_package_path\":" << external_package_path_ << ", "
           << "\"package_path\":" << package_path_ << ", "
           << "\"type_name\":\"" << type_name_ << "\", "
           << "\"meta_type\":" << "\"" << meta_type_ << "\""
           << " }";
}

} }
