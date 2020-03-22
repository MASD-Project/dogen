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
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/enum_transform.hpp"

namespace dogen::m2t::csharp::transforms::test_data {

std::string enum_transform::static_id() {
    return traits::enum_archetype();
}

std::string enum_transform::id() const {
    return static_id();
}

physical::entities::location enum_transform::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::backend(), traits::facet(),
          enum_transform::static_id());
    return r;
}

const logical::entities::name& enum_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_transform::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path enum_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> enum_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact enum_transform::format(
    const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location());
    const auto& ye(a.as<logical::entities::structural::enumeration>(static_id(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Collections;" << std::endl;
a.stream() << "using System.Collections.Generic;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = (" << sn << ")(position % " << ye.enumerators().size() << ");" << std::endl;
a.stream() << "            return result;" << std::endl;
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
