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
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.generation.csharp/types/formatters/io/traits.hpp"
#include "dogen.generation.csharp/types/formatters/assistant.hpp"
#include "dogen.generation.csharp/types/formatters/io/assistant_formatter.hpp"

namespace dogen::generation::csharp::formatters::io {

std::string assistant_formatter::static_id() {
    return traits::assistant_archetype();
}

std::string assistant_formatter::id() const {
    return static_id();
}

physical::entities::location assistant_formatter::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          assistant_formatter::static_id());
    return r;
}

const logical::entities::name& assistant_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_assistant_name());
    return r;
}

std::string assistant_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path assistant_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> assistant_formatter::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact assistant_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location());
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Text;" << std::endl;
a.stream() << "using System.Collections;" << std::endl;
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
a.stream() << "        private const string HashCode = \"HashCode\";" << std::endl;
a.stream() << "        private const string Type = \"__type__\";" << std::endl;
a.stream() << "        private const string StringType = \"string\";" << std::endl;
a.stream() << "        private const string ByteType = \"byte\";" << std::endl;
a.stream() << "        private const string SByteType = \"sbyte\";" << std::endl;
a.stream() << "        private const string IntType = \"int\";" << std::endl;
a.stream() << "        private const string UIntType = \"uint\";" << std::endl;
a.stream() << "        private const string LongType = \"long\";" << std::endl;
a.stream() << "        private const string ULongType = \"ulong\";" << std::endl;
a.stream() << "        private const string FloatType = \"float\";" << std::endl;
a.stream() << "        private const string DoubleType = \"double\";" << std::endl;
a.stream() << "        private const string CharType = \"char\";" << std::endl;
a.stream() << "        private const string DecimalType = \"decimal\";" << std::endl;
a.stream() << "        private const string BoolType = \"bool\";" << std::endl;
a.stream() << "        private const string NullValue = \"<null>\";" << std::endl;
a.stream() << "        private const string SystemObjectType = \"System.Object\";" << std::endl;
a.stream() << "        private const string KeyType = \"key\";" << std::endl;
a.stream() << "        private const string ValueType = \"value\";" << std::endl;
a.stream() << "        private const string DataKey = \"data\";" << std::endl;
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
a.stream() << "        public void AddStartArray()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\"[ \");" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void AddEndArray()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(\" ]\");" << std::endl;
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
a.stream() << "        #region Add value for well known types" << std::endl;
a.stream() << "        private bool HandleBoxedPrimitives(object value)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var type = value.GetType();" << std::endl;
a.stream() << "            if (type == typeof(string))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(StringType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, value as string);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(byte))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(ByteType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (byte)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(sbyte))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(SByteType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (sbyte)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(int))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(IntType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (int)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(uint))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(UIntType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (uint)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(long))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(LongType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (long)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(ulong))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(ULongType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (ulong)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(float))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(FloatType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (float)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(double))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(DoubleType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (double)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(char))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(CharType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (char)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(decimal))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(DecimalType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (decimal)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (type == typeof(bool))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(BoolType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, (bool)value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            return false;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(object value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddStartObject();" << std::endl;
a.stream() << "            AddType(SystemObjectType, true/*withSeparator*/);" << std::endl;
a.stream() << std::endl;
a.stream() << "            if (value == null)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                Add(DataKey, NullValue);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddKey(DataKey);" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "            if (HandleBoxedPrimitives(value))" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << "                HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddStartObject();" << std::endl;
a.stream() << "            AddKey(HashCode);" << std::endl;
a.stream() << "            AddPairSeparator();" << std::endl;
a.stream() << "            AddNonQuoted(value.GetHashCode());" << std::endl;
a.stream() << std::endl;
a.stream() << "            AddEndObject(); // data" << std::endl;
a.stream() << "            AddEndObject();" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(string value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddQuoted(value);" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(byte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(sbyte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(int value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(uint value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(long value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(ulong value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(float value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(double value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(char value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(Convert.ToInt16(value)));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(decimal value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(bool value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            if (value)" << std::endl;
a.stream() << "                _stringBuilder.Append(\"true\");" << std::endl;
a.stream() << "            else" << std::endl;
a.stream() << "                _stringBuilder.Append(\"false\");" << std::endl;
a.stream() << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(IEnumerable value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddStartArray();" << std::endl;
a.stream() << "            bool isFirst = true;" << std::endl;
a.stream() << "            foreach (var item in value)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                if (!isFirst)" << std::endl;
a.stream() << "                    AddMemberSeparator();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddValue(item);" << std::endl;
a.stream() << "                isFirst = false;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            AddEndArray();" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        private void AddValue(IDictionary value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddStartArray();" << std::endl;
a.stream() << "            bool isFirst = true;" << std::endl;
a.stream() << "            foreach (DictionaryEntry item in value)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                if (!isFirst)" << std::endl;
a.stream() << "                    AddMemberSeparator();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddStartArray();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(KeyType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, item.Key);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddMemberSeparator();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddStartObject();" << std::endl;
a.stream() << "                AddType(ValueType, true/*withSeparator*/);" << std::endl;
a.stream() << "                Add(DataKey, item.Value);" << std::endl;
a.stream() << "                AddEndObject();" << std::endl;
a.stream() << std::endl;
a.stream() << "                AddEndArray();" << std::endl;
a.stream() << "                isFirst = false;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            AddEndArray();" << std::endl;
a.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Add for well known types" << std::endl;
a.stream() << "        public void Add(string key, object value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, string value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, byte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, sbyte value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, int value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, uint value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, long value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, ulong value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, float value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, double value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, char value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, decimal value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, bool value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, IEnumerable value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public void Add(string key, IDictionary value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            AddKeyWithSeparator(key);" << std::endl;
a.stream() << "            AddValue(value, withSeparator);" << std::endl;
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
}
