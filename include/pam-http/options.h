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

