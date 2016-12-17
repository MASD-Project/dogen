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
#include "dogen/quilt.csharp/types/formatters/test_data/assistant_formatter.hpp"
#include "dogen/quilt.csharp/types/fabric/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace test_data {

std::string assistant_formatter::static_artefact() {
    return traits::assistant_archetype();
}

std::string assistant_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location assistant_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::kernel(),
          traits::facet(),
          assistant_formatter::static_artefact());
    return r;
}

std::type_index assistant_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::assistant)));
    return r;
}

boost::filesystem::path assistant_formatter::
full_path(const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> assistant_formatter::
inclusion_dependencies(const yarn::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact
assistant_formatter::format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    {
        const auto sn(e.name().simple());
        // const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Provides helper methods for the sequence generators." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        public static object CreateObject(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return \"this is an object: \" + Convert.ToString(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static string CreateString(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return \"this is a string: \" + Convert.ToString(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static byte CreateByte(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToByte(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static sbyte CreateShortByte(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToSByte(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static int CreateInt(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt32(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static uint CreateUInt(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return position;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static short CreateShort(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt16(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ushort CreateUShort(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToUInt16(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static long CreateLong(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt64(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ulong CreateULong(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToUInt64(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static float CreateFloat(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToSingle(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static double CreateDouble(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToDouble(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static char CreateChar(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToChar(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static bool CreateBool(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return position % 2 == 0;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static decimal CreateDecimal(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToDecimal(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }
