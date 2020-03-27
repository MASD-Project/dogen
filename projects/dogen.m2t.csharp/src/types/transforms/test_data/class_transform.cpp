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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/class_transform.hpp"

namespace dogen::m2t::csharp::transforms::test_data {

std::string class_transform::static_id() {
    return traits::class_archetype();
}

std::string class_transform::id() const {
    return static_id();
}

physical::entities::name
class_transform::physical_name() const {
    using physical::helpers::name_factory;
    static const auto r(name_factory::make(csharp::traits::backend_qn(),
        traits::facet_qn(), class_transform::static_id()));
    return r;
}

const logical::entities::name& class_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

boost::filesystem::path class_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> class_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact class_transform::apply(
    const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name().location());
    const auto& o(a.as<logical::entities::structural::object>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Collections;" << std::endl;
a.stream() << "using System.Collections.Generic;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const bool has_attributes(!o.all_attributes().empty());
            const bool is_parent_or_has_attributes(
                !o.parents().empty() || has_attributes);
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal void Populate(" << sn << " value, uint position)" << std::endl;
a.stream() << "        {" << std::endl;
                if (!is_parent_or_has_attributes) {
a.stream() << "            // nothing to populate" << std::endl;
                } else {
                    unsigned int count(0);
                    if (!o.parents().empty()) {
                        const auto& pn(o.parents().front());
                        const auto pqn(a.get_qualified_name(pn));
a.stream() << "            " << pqn << "SequenceGenerator.Populate(value, position);" << std::endl;
                    }

                    for (const auto& attr : o.local_attributes()) {
                        const auto oap(a.get_assistant_properties(attr));
                        if (oap && oap->requires_assistance()) {
a.stream() << "            value." << attr.name().simple() << " = AssistantSequenceGenerator.Create" << oap->method_postfix() << "(position + " << count++ << ");" << std::endl;
                        } else {
                            const auto attr_qn(a.get_qualified_name(attr.parsed_type().current()));
a.stream() << "            value." << attr.name().simple() << " = " << attr_qn << "SequenceGenerator.Create(position + " << count++ << ");" << std::endl;
                        }
                    }
                }
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
            if (!o.is_parent()) {
a.stream() << "            var result = new " << sn << "();" << std::endl;
                if (has_attributes) {
a.stream() << "            Populate(result, position);" << std::endl;
                }
a.stream() << "            return result;" << std::endl;
            } else {
                auto leaves(o.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                const auto total(static_cast<unsigned int>(leaves.size()));
                for (const auto& l : leaves) {
a.stream() << "            if ((position % " << total << ") == " << i++ << ")" << std::endl;
a.stream() << "                return " << a.get_qualified_name(l) << "SequenceGenerator.Create(position);" << std::endl;
                }
a.stream() << "            return " << a.get_qualified_name(front) << "SequenceGenerator.Create(position);" << std::endl;
            }
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerator" << std::endl;
a.stream() << "        private class " << sn << "Enumerator : IEnumerator, IEnumerator<" << sn << ">, IDisposable" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region Properties" << std::endl;
a.stream() << "            private uint _position;" << std::endl;
a.stream() << "            private " << sn << " _current;" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            private void PopulateCurrent()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _current = " << sn << "SequenceGenerator.Create(_position);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IDisposable" << std::endl;
a.stream() << "            public void Dispose()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IEnumerator implementation" << std::endl;
a.stream() << "            public bool MoveNext()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                ++_position;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public void Reset()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _position = 0;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public object Current {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            " << sn << " IEnumerator<" << sn << ">.Current" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            public " << sn << "Enumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerable" << std::endl;
a.stream() << "        private class " << sn << "Enumerable : IEnumerable, IEnumerable<" << sn << ">" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region IEnumerable implementation" << std::endl;
a.stream() << "            public IEnumerator GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            IEnumerator<" << sn << "> IEnumerable<" << sn << ">.GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        static public IEnumerable<" << sn << "> Sequence()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return new " << sn << "Enumerable();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}
