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
using log4net;
using log4net.Core;
using log4net.Layout;
using log4net.Appender;
using log4net.Repository.Hierarchy;
using System.Runtime.CompilerServices;

namespace Dogen.TestModels.CSharpModel.Tests
{
    /// <summary>
    /// Configures the log file for unit tests.
    /// </summary>
    class LogConfigurator : IDisposable
    {
        readonly FileAppender _appender;

        public LogConfigurator(string fixtureName, [CallerMemberName] string testName = null)
        {
            var hierarchy = (Hierarchy)LogManager.GetRepository();
            var patternLayout = new PatternLayout();
            patternLayout.ConversionPattern = "%date{yyyy-MM-dd HH:mm:ss.ffffff} [%-5level] [%logger] %message%newline";
            patternLayout.ActivateOptions();

            _appender = new FileAppender();
            _appender.AppendToFile = false;
            _appender.File = "logs/" + fixtureName + "/" +testName + ".log";
            _appender.Layout = patternLayout;
            _appender.ActivateOptions();

            var memory = new MemoryAppender();
            memory.ActivateOptions();

            hierarchy.Root.AddAppender(memory);
            hierarchy.Root.AddAppender(_appender);
            hierarchy.Root.Level = Level.Fine;
            hierarchy.Configured = true;
        }

        #region IDisposable
        public void Dispose()
        {
            if (_appender != null)
            {
                var hierarchy = (Hierarchy)LogManager.GetRepository();
                hierarchy.Root.RemoveAppender(_appender);
            }
        }
        #endregion
    }
}
