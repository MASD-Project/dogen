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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.text.csharp/types/transforms/io/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/io/assistant_transform.hpp"
#include "dogen.text.csharp/types/transforms/io/assistant_factory.hpp"

namespace dogen::text::csharp::transforms::io {
namespace {

const std::string transform_id("text.csharp.transforms.io.assistant_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& assistant_transform::static_archetype() {
    static auto r(assistant_factory::make());
    return r;
}

const physical::entities::archetype& assistant_transform::archetype() const {
    return static_archetype();
}

void assistant_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "assistant",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, lps, e, archetype().meta_name(), a);
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << "using System.Text;" << std::endl;
ast.stream() << "using System.Collections;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << "    class " << sn << "Dumper" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        #region Properties" << std::endl;
ast.stream() << "        private readonly StringBuilder _stringBuilder;" << std::endl;
ast.stream() << "        private int _currentDepth;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private const uint MaxDepth = 1000;" << std::endl;
ast.stream() << "        private const string HashCode = \"HashCode\";" << std::endl;
ast.stream() << "        private const string Type = \"__type__\";" << std::endl;
ast.stream() << "        private const string StringType = \"string\";" << std::endl;
ast.stream() << "        private const string ByteType = \"byte\";" << std::endl;
ast.stream() << "        private const string SByteType = \"sbyte\";" << std::endl;
ast.stream() << "        private const string IntType = \"int\";" << std::endl;
ast.stream() << "        private const string UIntType = \"uint\";" << std::endl;
ast.stream() << "        private const string LongType = \"long\";" << std::endl;
ast.stream() << "        private const string ULongType = \"ulong\";" << std::endl;
ast.stream() << "        private const string FloatType = \"float\";" << std::endl;
ast.stream() << "        private const string DoubleType = \"double\";" << std::endl;
ast.stream() << "        private const string CharType = \"char\";" << std::endl;
ast.stream() << "        private const string DecimalType = \"decimal\";" << std::endl;
ast.stream() << "        private const string BoolType = \"bool\";" << std::endl;
ast.stream() << "        private const string NullValue = \"<null>\";" << std::endl;
ast.stream() << "        private const string SystemObjectType = \"System.Object\";" << std::endl;
ast.stream() << "        private const string KeyType = \"key\";" << std::endl;
ast.stream() << "        private const string ValueType = \"value\";" << std::endl;
ast.stream() << "        private const string DataKey = \"data\";" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Depth management" << std::endl;
ast.stream() << "        public void IncrementDepth()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            ++_currentDepth;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void DecrementDepth()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            ++_currentDepth;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public bool MaximumDepthExceeded()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return _currentDepth > MaxDepth;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Adds for JSON syntax" << std::endl;
ast.stream() << "        public void AddStartObject()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\"{ \");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddEndObject()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\" }\");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddStartArray()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\"[ \");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddEndArray()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\" ]\");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddPairSeparator()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\" : \");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddMemberSeparator()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(\", \");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddQuoted(string value)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            if (value == null)" << std::endl;
ast.stream() << "                _stringBuilder.Append(\"\\\"<null>\\\"\");" << std::endl;
ast.stream() << "            else" << std::endl;
ast.stream() << "                _stringBuilder.Append(\"\\\"\" + value + \"\\\"\");" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddNonQuoted(int value)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddKey(string k)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddQuoted(k);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void AddType(string typeName, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKey(Type);" << std::endl;
ast.stream() << "            AddPairSeparator();" << std::endl;
ast.stream() << "            AddQuoted(typeName);" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddKeyWithSeparator(string key)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKey(key);" << std::endl;
ast.stream() << "            AddPairSeparator();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void HandleMemberSeparator(bool withSeparator)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            if (withSeparator)" << std::endl;
ast.stream() << "                AddMemberSeparator();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Add value for well known types" << std::endl;
ast.stream() << "        private bool HandleBoxedPrimitives(object value)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var type = value.GetType();" << std::endl;
ast.stream() << "            if (type == typeof(string))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(StringType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, value as string);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(byte))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(ByteType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (byte)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(sbyte))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(SByteType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (sbyte)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(int))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(IntType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (int)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(uint))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(UIntType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (uint)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(long))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(LongType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (long)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(ulong))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(ULongType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (ulong)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(float))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(FloatType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (float)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(double))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(DoubleType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (double)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(char))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(CharType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (char)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(decimal))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(DecimalType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (decimal)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (type == typeof(bool))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(BoolType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, (bool)value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            return false;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(object value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddStartObject();" << std::endl;
ast.stream() << "            AddType(SystemObjectType, true/*withSeparator*/);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            if (value == null)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                Add(DataKey, NullValue);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            AddKey(DataKey);" << std::endl;
ast.stream() << "            AddPairSeparator();" << std::endl;
ast.stream() << "            if (HandleBoxedPrimitives(value))" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << "                HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            AddStartObject();" << std::endl;
ast.stream() << "            AddKey(HashCode);" << std::endl;
ast.stream() << "            AddPairSeparator();" << std::endl;
ast.stream() << "            AddNonQuoted(value.GetHashCode());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            AddEndObject(); // data" << std::endl;
ast.stream() << "            AddEndObject();" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(string value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddQuoted(value);" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(byte value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(sbyte value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(int value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(uint value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(long value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(ulong value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(float value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(double value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(char value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(Convert.ToInt16(value)));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(decimal value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder.Append(Convert.ToString(value));" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(bool value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            if (value)" << std::endl;
ast.stream() << "                _stringBuilder.Append(\"true\");" << std::endl;
ast.stream() << "            else" << std::endl;
ast.stream() << "                _stringBuilder.Append(\"false\");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(IEnumerable value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddStartArray();" << std::endl;
ast.stream() << "            bool isFirst = true;" << std::endl;
ast.stream() << "            foreach (var item in value)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                if (!isFirst)" << std::endl;
ast.stream() << "                    AddMemberSeparator();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddValue(item);" << std::endl;
ast.stream() << "                isFirst = false;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            AddEndArray();" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        private void AddValue(IDictionary value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddStartArray();" << std::endl;
ast.stream() << "            bool isFirst = true;" << std::endl;
ast.stream() << "            foreach (DictionaryEntry item in value)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                if (!isFirst)" << std::endl;
ast.stream() << "                    AddMemberSeparator();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddStartArray();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(KeyType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, item.Key);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddMemberSeparator();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddStartObject();" << std::endl;
ast.stream() << "                AddType(ValueType, true/*withSeparator*/);" << std::endl;
ast.stream() << "                Add(DataKey, item.Value);" << std::endl;
ast.stream() << "                AddEndObject();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                AddEndArray();" << std::endl;
ast.stream() << "                isFirst = false;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            AddEndArray();" << std::endl;
ast.stream() << "            HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        #region Add for well known types" << std::endl;
ast.stream() << "        public void Add(string key, object value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, string value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, byte value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, sbyte value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, int value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, uint value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, long value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, ulong value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, float value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, double value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, char value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, decimal value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, bool value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, IEnumerable value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public void Add(string key, IDictionary value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            AddKeyWithSeparator(key);" << std::endl;
ast.stream() << "            AddValue(value, withSeparator);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public AssistantDumper()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            _stringBuilder = new StringBuilder();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public override string ToString()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return _stringBuilder.ToString();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    }" << std::endl;
        }
    } // sbf

    ast.update_artefact();
    stp.end_transform(a);
}
}
