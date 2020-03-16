/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/lexical_cast/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/lexical_cast/enum_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::lexical_cast {

std::string enum_header_formatter::static_id() {
    return traits::enum_header_archetype();
}

std::string enum_header_formatter::id() const {
    return static_id();
}

physical::location
enum_header_formatter::archetype_location() const {
    static physical::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          enum_header_formatter::static_id());
    return r;
}

const assets::meta_model::name& enum_header_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types enum_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_formatter::inclusion_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path enum_header_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> enum_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {
    auto builder(f.make());

    const auto eh_fn(types::traits::enum_header_archetype());
    builder.add(e.name(), eh_fn);
    builder.add(inclusion_constants::boost::lexical_cast());

    return builder.build();
}

extraction::meta_model::artefact enum_header_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& enm(a.as<assets::meta_model::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(enm));
        const auto qn(a.get_qualified_name(enm.name()));
        const auto sn(enm.name().simple());
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline std::string lexical_cast(const " << qn << "& v) {" << std::endl;
        if (!a.is_cpp_standard_98()) {
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << std::endl;
        }
a.stream() << "    switch (v) {" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (a.is_cpp_standard_98())
                enu_qn = a.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;
a.stream() << "    case " << enu_qn << ":" << std::endl;
a.stream() << "        return \"" << sn + "::" + enu_sn << "\";" << std::endl;
        }
a.stream() << "    default:" << std::endl;
a.stream() << "        throw boost::bad_lexical_cast();" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline " << qn << " lexical_cast(const std::string & s) {" << std::endl;
        if (!a.is_cpp_standard_98()) {
a.stream() << "    using " << qn << ";" << std::endl;
a.stream() << std::endl;
        }

        for (const auto& enu : enm.enumerators()) {
           const auto enu_sn(enu.name().simple());
           std::string enu_qn;
           if (a.is_cpp_standard_98())
               enu_qn = a.get_qualified_namespace(enm.name()) + "::" + enu_sn;
           else
               enu_qn = sn + "::" + enu_sn;
a.stream() << "    if (s == \"" << enu_sn << "\" || s == \"" << sn + "::" + enu_sn << "\")" << std::endl;
a.stream() << "        return " << enu_qn << ";" << std::endl;
        }
a.stream() << "    throw boost::bad_lexical_cast();" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}
