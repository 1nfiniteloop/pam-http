#include <stdio.h>

#include "pam-http/options.h"
#include "stddef.h"
#include "string.h" /* memset, strncmp, strrchr, strdup */
#include "stdlib.h" /* free */

static char* value_as_string(const Args* args, const char* key, char* defaultValue) {
    char* value = defaultValue;
    size_t len = strlen(key);
    for (int i = 0; i < args->size; i++) {
        char* arg = (char*) args->arg[i];
        if (strncmp(arg, key, len) == 0 &&
                strchr(arg, '=') == arg + len) {
            value = arg + len + 1; /* step over equal-sign in 'value' */
        }
    }
    return value ? strdup(value) : value;
}

static long value_as_long(const Args* args, const char* key, long defaultValue) {
    long numericValue = defaultValue;
    char* value = value_as_string(args, key, NULL);
    if (value != NULL) {
        numericValue = atol(value);
        free(value);
    }
    return numericValue;
}

static const size_t len_without_trailing_slash(const char* path) {
    size_t len = strlen(path);
    if ((path + len - 1) == strrchr(path, '/')) {
        --len;
    }
    return len;
}

static char* absolute_path(const char* path, char* file) {
    char* absolutePath = NULL;
    if (file && path) {
        const size_t pathLength = len_without_trailing_slash(path);
        const size_t len = pathLength + /* trailing slash */ 1 + strlen(file) + /* null termination */ 1;
        absolutePath = calloc(len, sizeof(char));
        strncat(absolutePath, path, pathLength);
        strncat(absolutePath, "/", 1);
        strncat(absolutePath, file, strlen(file));
    } else if (file) {
        absolutePath = strdup(file);
    } else {
        /* Only path is given, or none */
    }
    return absolutePath;
}

Options* options_parse(const Args* args) {
    Options* options = malloc(sizeof(Options));
    if (options != NULL) {
        memset(options, 0, sizeof(Options));
        char* certpath = value_as_string(args, "cert-path", NULL);
        char* cacert = value_as_string(args, "cacert", NULL);
        char* key = value_as_string(args, "key", NULL);
        char* cert = value_as_string(args, "cert", NULL);
        options->timeout = value_as_long(args, "timeout", OPT_DEFAULT_TIMEOUT);
        options->url = value_as_string(args, "url", NULL);
        options->cacert = absolute_path(certpath, cacert);
        options->key = absolute_path(certpath, key);
        options->cert = absolute_path(certpath, cert);
        if (cert) {
            free(cert);
        }
        if (key) {
            free(key);
        }
        if (cacert) {
            free(cacert);
        }
        if (certpath) {
            free(certpath);
        }
    }
    return options;
}

void options_free(Options* opt) {
    if (opt != NULL) {
        if (opt->url) {
            free(opt->url);
        }
        if(opt->cacert) {
            free(opt->cacert);
        }
        if(opt->key) {
            free(opt->key);
        }
        if(opt->cert) {
            free(opt->cert);
        }
        free(opt);
        opt = NULL;
    }
}