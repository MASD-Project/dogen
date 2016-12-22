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
#include "dogen/quilt.csharp/types/formatters/io/assistant_formatter.hpp"
#include "dogen/quilt.csharp/types/fabric/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/io/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace io {

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
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Text;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    class " << sn << "Dumper" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        #region Properties" << std::endl;
a.stream() << "        private readonly StringBuilder _stringBuilder;" << std::endl;
a.stream() << "        private int _currentDepth;" << std::endl;
a.stream() << std::endl;
a.stream() << "        private const uint MaxDepth = 1000;" << std::endl;
a.stream() << "        private const string Type = \"__type__\";" << std::endl;
a.stream() << "        private const string HashCode = \"HashCode\";" << std::endl;
a.stream() << "        private const string SystemObjectType = \"System.Object\";" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Depth management" << std::endl;
a.stream() << "        public void IncrementDepth()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            ++_currentDepth;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void DecrementDepth()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            ++_currentDepth;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public bool MaximumDepthExceeded()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return _currentDepth > MaxDepth;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Adds for JSON syntax" << std::endl;
a.stream() << "        public void AddStartObject()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\"{ \");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddEndObject()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\" }\");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddPairSeparator()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\" : \");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddMemberSeparator()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\", \");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddQuoted(string value)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            if (value == null)" << std::endl;
a.stream() << "                _stringBuilder.Append(\"\\\"<null>\\\"\");" << std::endl;
a.stream() << "            else" << std::endl;
a.stream() << "                _stringBuilder.Append(\"\\\"\" + value + \"\\\"\");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddNonQuoted(int value)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddKey(string k)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddQuoted(k);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddType(string typeName, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKey(Type);" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "            AddQuoted(typeName);" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddKeyWithSeparator(string key)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKey(key);" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void HandleMemberSeparator(bool withSeparator)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            if (withSeparator)" << std::endl;
a.stream() << "                AddMemberSeparator();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Adds for well known types" << std::endl;
a.stream() << "        public void Add(string key, object value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddStartObject();" << std::endl;
a.stream() << "            AddType(SystemObjectType, true/*withSeparator*/);" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (value == null)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                Add(\"data\", \"<null>\");" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddKey(\"data\");" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "            AddStartObject();" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddKey(HashCode);" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "            AddNonQuoted(value.GetHashCode());" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddEndObject(); // data" << std::endl;
a.stream() << "            AddEndObject();" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, string value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddQuoted(value);" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, byte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, sbyte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, int value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, uint value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, long value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, ulong value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, float value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, double value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, char value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(Convert.ToInt16(value)));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, decimal value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, bool value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            if (value)" << std::endl;
a.stream() << "                _stringBuilder.Append(\"true\");" << std::endl;
a.stream() << "            else" << std::endl;
a.stream() << "                _stringBuilder.Append(\"false\");" << std::endl;
a.stream() << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        public AssistantDumper()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder = new StringBuilder();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public override string ToString()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return _stringBuilder.ToString();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }
