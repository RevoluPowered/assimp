/*
---------------------------------------------------------------------------
Open Asset Import Library (ASSIMP)
---------------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/


package assimp;

/**
 * Base logging interface. Directly corresponding with the native
 * Logger interface
 *
 * @author Aramis (Alexander Gessler)
 * @version 1.0
 */
public interface Logger {

    /**
     * Debug log message
     */
    public static final int ERRORSEVERITY_DEBUGGING	= 0x1;

     /**
     * Information log message
     */
    public static final int ERRORSEVERITY_INFO		= 0x2;

     /**
     * Warn log message
     */
    public static final int ERRORSEVERITY_WARN		= 0x4;

     /**
     * Error log message
     */
    public static final int ERRORSEVERITY_ERR		= 0x8;


    /**
     * Write a debug message to the log
     * @param message Message to be logged
     */
    public void debug(String message);

    /**
     * Write an error message to the log
     * @param message Message to be logged
     */
    public void error(String message);

    /**
     * Write a warn message to the log
     * @param message Message to be logged
     */
    public void warn(String message);

    /**
     * Write an info message to the log
     * @param message Message to be logged
     */
    public void info(String message);

    /**
     * Attach a logstream to the logger
     * @param stream Log stream instance
     * @param severity Error severity. Bitwise combination of the
     * ERRORSEVERITY_XXX constants. Specify 0 to attach the
     * stream to all types of log messages.
     */
    public void attachStream(LogStream stream, int severity);

    /**
     * Detach a logstream from the logger
     * @param stream Log stream instance
     * @param severity Error severities to detach the stream from.
     * Bitwise combination of the ERRORSEVERITY_XXX constants.
     * Specify 0 to detach the stream from all types of log messages.
     */
    public void detachStream(LogStream stream, int severity);
}
