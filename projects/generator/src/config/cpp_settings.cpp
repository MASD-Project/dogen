/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/jsonify_io.hpp"
#include "dogen/generator/config/cpp_settings.hpp"

namespace dogen {
namespace generator {
namespace config {

std::ostream&
operator<<(std::ostream& stream, cpp_settings value) {
    boost::io::ios_flags_saver ifs(stream);
    stream << std::boolalpha;

    using dogen::utility::streaming::jsonify;
    stream << "\"cpp_settings\": { "
           << "\"verbose\":" << value.verbose() << ", "
           << "\"split_project\":" << value.split_project() << ", "
           << "\"project_dir\": " << value.project_directory() << ", "
           << "\"src_dir\": " << value.source_directory() << ", "
           << "\"include_dir\": " << value.include_directory() << ", "
           << "\"disable_backend\": " << value.disable_backend() << ", "
           << "\"disable_cmakelists\": " << value.disable_cmakelists()
           << ", "
           << "\"disable_complete_constructor\": "
           << value.disable_complete_constructor() << ", "
           << "\"enabled_facets\": [";

    // FIXME: until we fix JSON output, we need to do this manually.
    bool is_first(true);
    for (const auto f : value.enabled_facets()) {
        stream << (is_first ? "" : ", ") << f;
        is_first = false;
    }

    stream << "], "
           << "\"header_extension\": "
           << jsonify(value.header_extension())
           << ", "
           << "\"source_extension\": "
           << jsonify(value.source_extension())
           << ", "
           << "\"disable_facet_folders\": " << value.disable_facet_folders()
           << ", "
           << "\"disable_unique_file_names\": "
           << value.disable_unique_file_names() << ", "
           << "\"domain_facet_folder\": "
           << jsonify(value.domain_facet_folder()) << ", "
           << "\"hash_facet_folder\": "
           << jsonify(value.hash_facet_folder()) << ", "
           << "\"io_facet_folder\": "
           << jsonify(value.io_facet_folder()) << ", "
           << "\"serialization_facet_folder\": "
           << jsonify(value.serialization_facet_folder()) << ", "
           << "\"disable_xml_serialization\": "
           << value.disable_xml_serialization() << ", "
           << "\"use_integrated_io\": " << value.use_integrated_io() << ", "
           << "\"disable_versioning\": " << value.disable_versioning()
           << " }";

    return stream;
}

} } }
