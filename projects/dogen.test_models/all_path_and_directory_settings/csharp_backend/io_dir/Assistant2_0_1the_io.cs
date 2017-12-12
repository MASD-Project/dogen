// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using System;
using System.Text;
using System.Collections;

namespace dogen.test_models.all_path_and_directory_settings
{
    class AssistantDumper
    {
        #region Properties
        private readonly StringBuilder _stringBuilder;
        private int _currentDepth;

        private const uint MaxDepth = 1000;
        private const string HashCode = "HashCode";
        private const string Type = "__type__";
        private const string StringType = "string";
        private const string ByteType = "byte";
        private const string SByteType = "sbyte";
        private const string IntType = "int";
        private const string UIntType = "uint";
        private const string LongType = "long";
        private const string ULongType = "ulong";
        private const string FloatType = "float";
        private const string DoubleType = "double";
        private const string CharType = "char";
        private const string DecimalType = "decimal";
        private const string BoolType = "bool";
        private const string NullValue = "<null>";
        private const string SystemObjectType = "System.Object";
        private const string KeyType = "key";
        private const string ValueType = "value";
        private const string DataKey = "data";
        #endregion

        #region Depth management
        public void IncrementDepth()
        {
            ++_currentDepth;
        }

        public void DecrementDepth()
        {
            ++_currentDepth;
        }

        public bool MaximumDepthExceeded()
        {
            return _currentDepth > MaxDepth;
        }
        #endregion

        #region Adds for JSON syntax
        public void AddStartObject()
        {
            _stringBuilder.Append("{ ");
        }

        public void AddEndObject()
        {
            _stringBuilder.Append(" }");
        }

        public void AddStartArray()
        {
            _stringBuilder.Append("[ ");
        }

        public void AddEndArray()
        {
            _stringBuilder.Append(" ]");
        }

        public void AddPairSeparator()
        {
            _stringBuilder.Append(" : ");
        }

        public void AddMemberSeparator()
        {
            _stringBuilder.Append(", ");
        }

        public void AddQuoted(string value)
        {
            if (value == null)
                _stringBuilder.Append("\"<null>\"");
            else
                _stringBuilder.Append("\"" + value + "\"");
        }

        public void AddNonQuoted(int value)
        {
            _stringBuilder.Append(Convert.ToString(value));
        }

        public void AddKey(string k)
        {
            AddQuoted(k);
        }

        public void AddType(string typeName, bool withSeparator = false)
        {
            AddKey(Type);
            AddPairSeparator();
            AddQuoted(typeName);
            HandleMemberSeparator(withSeparator);
        }

        private void AddKeyWithSeparator(string key)
        {
            AddKey(key);
            AddPairSeparator();
        }

        public void HandleMemberSeparator(bool withSeparator)
        {
            if (withSeparator)
                AddMemberSeparator();
        }
        #endregion

        #region Add value for well known types
        private bool HandleBoxedPrimitives(object value)
        {
            var type = value.GetType();
            if (type == typeof(string))
            {
                AddStartObject();
                AddType(StringType, true/*withSeparator*/);
                Add(DataKey, value as string);
                AddEndObject();
                return true;
            }

            if (type == typeof(byte))
            {
                AddStartObject();
                AddType(ByteType, true/*withSeparator*/);
                Add(DataKey, (byte)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(sbyte))
            {
                AddStartObject();
                AddType(SByteType, true/*withSeparator*/);
                Add(DataKey, (sbyte)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(int))
            {
                AddStartObject();
                AddType(IntType, true/*withSeparator*/);
                Add(DataKey, (int)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(uint))
            {
                AddStartObject();
                AddType(UIntType, true/*withSeparator*/);
                Add(DataKey, (uint)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(long))
            {
                AddStartObject();
                AddType(LongType, true/*withSeparator*/);
                Add(DataKey, (long)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(ulong))
            {
                AddStartObject();
                AddType(ULongType, true/*withSeparator*/);
                Add(DataKey, (ulong)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(float))
            {
                AddStartObject();
                AddType(FloatType, true/*withSeparator*/);
                Add(DataKey, (float)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(double))
            {
                AddStartObject();
                AddType(DoubleType, true/*withSeparator*/);
                Add(DataKey, (double)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(char))
            {
                AddStartObject();
                AddType(CharType, true/*withSeparator*/);
                Add(DataKey, (char)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(decimal))
            {
                AddStartObject();
                AddType(DecimalType, true/*withSeparator*/);
                Add(DataKey, (decimal)value);
                AddEndObject();
                return true;
            }

            if (type == typeof(bool))
            {
                AddStartObject();
                AddType(BoolType, true/*withSeparator*/);
                Add(DataKey, (bool)value);
                AddEndObject();
                return true;
            }

            return false;
        }

        private void AddValue(object value, bool withSeparator = false)
        {
            AddStartObject();
            AddType(SystemObjectType, true/*withSeparator*/);

            if (value == null)
            {
                Add(DataKey, NullValue);
                AddEndObject();
                HandleMemberSeparator(withSeparator);
                return;
            }

            AddKey(DataKey);
            AddPairSeparator();
            if (HandleBoxedPrimitives(value))
            {
                AddEndObject();
                HandleMemberSeparator(withSeparator);
                return;
            }

            AddStartObject();
            AddKey(HashCode);
            AddPairSeparator();
            AddNonQuoted(value.GetHashCode());

            AddEndObject(); // data
            AddEndObject();
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(string value, bool withSeparator = false)
        {
            AddQuoted(value);
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(byte value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(sbyte value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(int value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(uint value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(long value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(ulong value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(float value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(double value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(char value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(Convert.ToInt16(value)));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(decimal value, bool withSeparator = false)
        {
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(bool value, bool withSeparator = false)
        {
            if (value)
                _stringBuilder.Append("true");
            else
                _stringBuilder.Append("false");

            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(IEnumerable value, bool withSeparator = false)
        {
            AddStartArray();
            bool isFirst = true;
            foreach (var item in value)
            {
                if (!isFirst)
                    AddMemberSeparator();

                AddValue(item);
                isFirst = false;
            }
            AddEndArray();
            HandleMemberSeparator(withSeparator);
        }

        private void AddValue(IDictionary value, bool withSeparator = false)
        {
            AddStartArray();
            bool isFirst = true;
            foreach (DictionaryEntry item in value)
            {
                if (!isFirst)
                    AddMemberSeparator();

                AddStartArray();

                AddStartObject();
                AddType(KeyType, true/*withSeparator*/);
                Add(DataKey, item.Key);
                AddEndObject();

                AddMemberSeparator();

                AddStartObject();
                AddType(ValueType, true/*withSeparator*/);
                Add(DataKey, item.Value);
                AddEndObject();

                AddEndArray();
                isFirst = false;
            }
            AddEndArray();
            HandleMemberSeparator(withSeparator);
        }
        #endregion

        #region Add for well known types
        public void Add(string key, object value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, string value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, byte value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, sbyte value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, int value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, uint value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, long value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, ulong value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, float value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, double value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, char value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, decimal value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, bool value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, IEnumerable value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }

        public void Add(string key, IDictionary value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddValue(value, withSeparator);
        }
        #endregion

        public AssistantDumper()
        {
            _stringBuilder = new StringBuilder();
        }

        public override string ToString()
        {
            return _stringBuilder.ToString();
        }
    }
}
