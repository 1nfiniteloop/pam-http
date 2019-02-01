/*
 * The MIT License
 *
 * Copyright 2019 Lars Gunnarsson.
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
 */

#ifndef HTTP_OPTIONS_H
#define HTTP_OPTIONS_H

#define OPT_DEFAULT_TIMEOUT 30L

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        const char** arg;
        int size;
    } Args;

    typedef struct {
        long timeout;
        char* url;
        char* cacert;
        char* key;
        char* cert;
    } Options ;

    /**
     * Parse command-line arguments formatted as "key=value" into options.
     *
     * @param args
     * @return options
     */
    Options* options_parse(const Args* args);

    /**
     * Free memory resources.
     *
     * @param opt
     */
    void options_free(Options* opt);


#ifdef __cplusplus
}
#endif

#endif /* HTTP_OPTIONS_H */

