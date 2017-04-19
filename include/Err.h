/////////////////////////////////////////////////////////////////////
//
// SFGE - Simple and Fast Game Engine
//
// Copyright (c) 2016-2017 DonRumata710 
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
/////////////////////////////////////////////////////////////////////


#pragma once

#include <string>


namespace sfge
{


    /////////////////////////////////////////////////////////////////////
    /// Exception - class for convenient throwing of exceptions
    /////////////////////////////////////////////////////////////////////
    class Exception : public std::exception
    {
    public:
        /////////////////////////////////////////////////////////////////////
        /// constructor
        /// 
        /// Create exception object with message.
        /// 
        /// @param msg - description of exception
        /////////////////////////////////////////////////////////////////////
        Exception (const std::string& msg);

        /////////////////////////////////////////////////////////////////////
        /// what - get description of exception
        /// 
        /// Overridden method of std::exception.
        /// 
        /// @return description of exception
        /////////////////////////////////////////////////////////////////////
        virtual char const* what () const noexcept override;

    private:
        char* m_message = nullptr;
    };


    /////////////////////////////////////////////////////////////////////
    /// critical_error inform about some error which crash application
    ///
    /// @param message - description of error
    /////////////////////////////////////////////////////////////////////
    void critical_error (const std::string& message);

    /////////////////////////////////////////////////////////////////////
    /// runtime_error inform about some error
    ///
    /// @param message - description of error
    /////////////////////////////////////////////////////////////////////
    void runtime_error (const std::string& message);

    /////////////////////////////////////////////////////////////////////
    /// debug_message inform about some event which can be importaint
    /// for programmer
    ///
    /// @param message - description of error
    /////////////////////////////////////////////////////////////////////
    void debug_message (const std::string& message);


}