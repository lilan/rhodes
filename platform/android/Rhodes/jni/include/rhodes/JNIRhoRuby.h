/*------------------------------------------------------------------------
* (The MIT License)
* 
* Copyright (c) 2008-2011 Rhomobile, Inc.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* 
* http://rhomobile.com
*------------------------------------------------------------------------*/

#ifndef JNIRHORUBY_H_INCLUDED
#define JNIRHORUBY_H_INCLUDED

#include <ruby.h>
#include <ruby/ext/rho/rhoruby.h>

#include <rhodes.h>

class RhoValueConverter
{
private:
    static jclass clsHashMap;
    static jclass clsVector;

    static jmethodID midHashMapConstructor;
    static jmethodID midVectorConstructor;
    static jmethodID midPut;
    static jmethodID midAddElement;

    static bool init;

    JNIEnv* env;

public:
    RhoValueConverter(JNIEnv *e);

    jhobject createObject(rho_param *p);
};

namespace details
{

template <>
struct rho_cast_helper<VALUE, jobject>: public RhoJniConvertor
{
    VALUE operator()(JNIEnv *env, jobject obj);
    VALUE convertJavaMapToRubyHash(JNIEnv *env, jobject objMap);
};

template <>
struct rho_cast_helper<VALUE, jstring>
{
    VALUE operator()(JNIEnv *env, jstring obj);
};

template <>
struct rho_cast_helper<jobject, VALUE>
{
    jobject operator()(JNIEnv *env, VALUE value);
};

template <>
struct rho_cast_helper<jhobject, VALUE>
{
    jhobject operator()(JNIEnv *env, VALUE value) { return jhobject(rho_cast<jobject>(env, value)); }
};

template <>
struct rho_cast_helper<jstring, VALUE>
{
    jstring operator()(JNIEnv *env, VALUE value);
};

template <>
struct rho_cast_helper<jhstring, VALUE>
{
    jhstring operator()(JNIEnv *env, VALUE value) { return jhstring(rho_cast<jstring>(env, value)); }
};

}
#endif // JNIRHORUBY_H_INCLUDED
