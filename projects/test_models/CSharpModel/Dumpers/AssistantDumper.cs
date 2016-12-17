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

namespace Dogen.TestModels.CSharpModel
{
    class AssistantDumper
    {
        #region Properties
        private readonly StringBuilder _stringBuilder;
        private int _currentDepth;

        private const uint MaxDepth = 1000;
        private const string Type = "__type__";
        private const string HashCode = "HashCode";
        private const string SystemObjectType = "System.Object";
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

        private void HandleMemberSeparator(bool withSeparator)
        {
            if (withSeparator)
                AddMemberSeparator();
        }
        #endregion

        #region Adds for well known types
        public void Add(string key, object value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddStartObject();
            AddType(SystemObjectType, true/*withSeparator*/);
            AddKey(HashCode);
            AddPairSeparator();
            AddNonQuoted(value.GetHashCode());
            AddEndObject();
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, string value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            AddQuoted(value);
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, byte value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, sbyte value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, int value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, uint value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, long value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, ulong value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, float value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, double value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, char value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(Convert.ToInt16(value)));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, decimal value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            _stringBuilder.Append(Convert.ToString(value));
            HandleMemberSeparator(withSeparator);
        }

        public void Add(string key, bool value, bool withSeparator = false)
        {
            AddKeyWithSeparator(key);
            if (value)
                _stringBuilder.Append("true");
            else
                _stringBuilder.Append("false");

            HandleMemberSeparator(withSeparator);
        }
        #endregion

        public AssistantDumper()
        {
            _stringBuilder = new StringBuilder();
        }

        public string Dump()
        {
            return _stringBuilder.ToString();
        }
    }
}
